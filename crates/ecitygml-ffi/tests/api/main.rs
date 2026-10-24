//! API suite of the FFI API: the behaviour cases of `crates/ecitygml/tests/api/<area>.md`, one module per area
//! (`geometry`, `iteration`, `reader`, `types`, `writer`), as in every binding. See `crates/ecitygml/tests/api/README.md`.
//!
//! The modules `citygml` and `gml` mirror the crate's layout and hold the bridge tests not harmonized into case
//! lists yet. This file holds the shared helpers, which every test module imports with `use crate::*;`.

use ecitygml_ffi::citygml::core::model::common::feature_type::FeatureType;
use ecitygml_ffi::citygml::core::model::core::city_model::CityModel;
use ecitygml_ffi::citygml::io::gml::read::GmlReader;
use ecitygml_ffi::error::{Error, ErrorKind};
use std::path::PathBuf;
use std::sync::atomic::{AtomicUsize, Ordering};

use diplomat_runtime::{
    DiplomatWrite, diplomat_buffer_write_create, diplomat_buffer_write_destroy,
};

mod geometry;
mod iteration;
mod reader;
mod types;
mod writer;

/// `tests/fixtures/<path>`.
fn fixture(path: &str) -> String {
    format!("{}/../../tests/fixtures/{path}", env!("CARGO_MANIFEST_DIR"))
}

/// Reads the file at `path`, as the bindings do: `GmlReader::from_path(path)?.finish()`.
fn read(path: &str) -> Box<CityModel> {
    GmlReader::from_path(path.as_bytes())
        .and_then(|mut reader| reader.finish())
        .unwrap_or_else(|error| panic!("{path}: {}", message(&error)))
}

fn message(error: &Error) -> String {
    written(|w| error.message(w))
}

/// Asserts the error's kind and that its message contains `part`.
fn assert_error(error: &Error, kind: ErrorKind, part: &str) {
    let message = message(error);
    assert_eq!(error.kind(), kind, "{message}");
    assert!(message.contains(part), "{message}");
}

fn feature_types(city_model: &CityModel) -> Vec<FeatureType> {
    let mut features = city_model.iter_features();
    std::iter::from_fn(|| features.next())
        .map(|feature| feature.feature_type())
        .collect()
}

/// A fresh temporary directory, unique per call (tests run in parallel threads of one process), removed on drop.
struct TempDir(PathBuf);

impl TempDir {
    fn new() -> Self {
        static NEXT: AtomicUsize = AtomicUsize::new(0);
        let n = NEXT.fetch_add(1, Ordering::Relaxed);
        let dir = std::env::temp_dir().join(format!("ecitygml-ffi-api-{}-{n}", std::process::id()));
        std::fs::create_dir_all(&dir).expect("should create the temporary directory");
        Self(dir)
    }

    /// The path of `name` in the directory, as a string.
    fn path(&self, name: &str) -> String {
        self.0
            .join(name)
            .to_str()
            .expect("should be UTF-8")
            .to_owned()
    }
}

impl Drop for TempDir {
    fn drop(&mut self) {
        let _ = std::fs::remove_dir_all(&self.0);
    }
}

/// Collects what a method writes to a `DiplomatWrite`.
fn written(write_to: impl FnOnce(&mut DiplomatWrite)) -> String {
    let write = diplomat_buffer_write_create(16);
    // SAFETY: `write` was just created and is destroyed below.
    let text = unsafe {
        write_to(&mut *write);
        String::from_utf8((*write).as_bytes().to_vec()).unwrap()
    };
    unsafe { diplomat_buffer_write_destroy(write) };
    text
}
