//! Web (`wasm32`): the browser's file picker and downloads; no threads, so background work
//! runs at the start of the next frame (after a frame showing "Loading…" was presented).

use super::{CITYGML_EXTENSIONS, TITLE};
use ecitygml::io::{CitygmlFormat, GmlReader};
use ecitygml_core::model::core::CityModel;
use std::cell::RefCell;
use std::io::Cursor;
use three_d::WindowSettings;
use wasm_bindgen::{JsCast, JsValue};

type Task = Box<dyn FnOnce()>;

thread_local! {
    static OPENED_FILE: RefCell<Option<OpenedFile>> = const { RefCell::new(None) };
    static DEFERRED_TASKS: RefCell<Vec<Task>> = const { RefCell::new(Vec::new()) };
}

pub fn init_logging() {
    use tracing_subscriber::filter::LevelFilter;
    use tracing_subscriber::prelude::*;

    console_error_panic_hook::set_once();
    // No timestamps: `SystemTime` isn't available in the browser. INFO, as on the desktop.
    let console = tracing_subscriber::fmt::layer()
        .with_ansi(false)
        .without_time()
        .with_writer(tracing_web::MakeWebConsoleWriter::new())
        .with_filter(LevelFilter::INFO);
    tracing_subscriber::registry().with(console).init();
}

/// Without a size, the canvas follows the size of the browser window.
pub fn window_settings() -> WindowSettings {
    WindowSettings {
        title: TITLE.into(),
        ..Default::default()
    }
}

/// A CityGML file chosen in the browser's file picker, read into memory.
pub struct OpenedFile {
    name: String,
    bytes: Vec<u8>,
}

impl OpenedFile {
    pub fn read_city_model(self) -> Result<CityModel, ecitygml::io::Error> {
        let format = CitygmlFormat::from_path(&self.name)
            .ok_or_else(|| ecitygml::io::Error::InvalidFileExtension(self.name.clone()))?;
        GmlReader::new(Cursor::new(self.bytes), format).finish()
    }
}

/// Opens the browser's file picker; the chosen file is returned by [`take_opened_file`] in a
/// later frame, once it has been read.
pub fn request_open_file() {
    wasm_bindgen_futures::spawn_local(async {
        let Some(handle) = rfd::AsyncFileDialog::new()
            .add_filter("CityGML", CITYGML_EXTENSIONS)
            .pick_file()
            .await
        else {
            return;
        };
        let file = OpenedFile {
            name: handle.file_name(),
            bytes: handle.read().await,
        };
        OPENED_FILE.with(|opened| *opened.borrow_mut() = Some(file));
    });
}

/// The file chosen since the last call, if any.
pub fn take_opened_file() -> Option<OpenedFile> {
    OPENED_FILE.with(|file| file.borrow_mut().take())
}

/// Defers `task` to the next [`run_deferred_tasks`] call.
pub fn spawn(task: impl FnOnce() + Send + 'static) {
    DEFERRED_TASKS.with(|tasks| tasks.borrow_mut().push(Box::new(task)));
}

/// Runs the tasks deferred in previous frames; blocks the page while they run.
pub fn run_deferred_tasks() {
    let tasks = DEFERRED_TASKS.with(|tasks| std::mem::take(&mut *tasks.borrow_mut()));
    for task in tasks {
        task();
    }
}

/// Downloads `bytes` as `file_name`. Returns the file name, or why the download failed.
pub fn save_file(
    bytes: &[u8],
    file_name: &str,
    _filter: (&str, &[&str]),
) -> Option<Result<String, String>> {
    Some(
        download(bytes, file_name)
            .map(|()| file_name.to_string())
            .map_err(|e| format!("{e:?}")),
    )
}

fn download(bytes: &[u8], file_name: &str) -> Result<(), JsValue> {
    let parts = js_sys::Array::of1(&js_sys::Uint8Array::from(bytes));
    let blob = web_sys::Blob::new_with_u8_array_sequence(&parts)?;
    let url = web_sys::Url::create_object_url_with_blob(&blob)?;

    let document = web_sys::window()
        .and_then(|window| window.document())
        .ok_or_else(|| JsValue::from_str("no document"))?;
    let anchor: web_sys::HtmlAnchorElement = document.create_element("a")?.dyn_into()?;
    anchor.set_href(&url);
    anchor.set_download(file_name);
    anchor.click();

    web_sys::Url::revoke_object_url(&url)
}
