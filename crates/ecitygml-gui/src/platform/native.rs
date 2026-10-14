//! Desktop: native file dialogs, the file system, and threads.

use super::{CITYGML_EXTENSIONS, TITLE};
use ecitygml::io::GmlReader;
use ecitygml_core::model::core::CityModel;
use std::cell::RefCell;
use std::path::PathBuf;
use three_d::WindowSettings;

thread_local! {
    static OPENED_FILE: RefCell<Option<OpenedFile>> = const { RefCell::new(None) };
}

pub fn init_logging() {
    tracing_subscriber::fmt::init();
}

pub fn window_settings() -> WindowSettings {
    WindowSettings {
        title: TITLE.into(),
        min_size: (900, 600),
        initial_size: Some((1600, 900)),
        ..Default::default()
    }
}

/// A CityGML file chosen in the open dialog.
pub struct OpenedFile(PathBuf);

impl OpenedFile {
    pub fn read_city_model(self) -> Result<CityModel, ecitygml::io::Error> {
        GmlReader::from_path(&self.0)?.finish()
    }
}

/// Shows the open dialog; the chosen file is returned by [`take_opened_file`].
pub fn request_open_file() {
    let path = rfd::FileDialog::new()
        .add_filter("CityGML", CITYGML_EXTENSIONS)
        .pick_file();
    OPENED_FILE.with(|file| *file.borrow_mut() = path.map(OpenedFile));
}

/// The file chosen since the last call, if any.
pub fn take_opened_file() -> Option<OpenedFile> {
    OPENED_FILE.with(|file| file.borrow_mut().take())
}

/// Runs `task` on a background thread.
pub fn spawn(task: impl FnOnce() + Send + 'static) {
    std::thread::spawn(task);
}

/// Nothing to do on the desktop: tasks run on their own threads.
pub fn run_deferred_tasks() {}

/// Asks where to save `bytes` and writes them there.
///
/// Returns `None` if the dialog was cancelled, otherwise where the file was saved or why it
/// could not be saved.
pub fn save_file(
    bytes: &[u8],
    file_name: &str,
    filter: (&str, &[&str]),
) -> Option<Result<String, String>> {
    let path = rfd::FileDialog::new()
        .add_filter(filter.0, filter.1)
        .set_file_name(file_name)
        .save_file()?;

    Some(
        std::fs::write(&path, bytes)
            .map(|()| path.display().to_string())
            .map_err(|e| e.to_string()),
    )
}
