//! API suite of the Rust library, the reference the FFI API and the bindings follow: the behaviour cases of the case
//! lists `<area>.md` in this folder, one module per area, as in every binding. See `README.md`.

use ecitygml::io::GmlReader;
use ecitygml::model::common::{FeatureType, HasFeatureType, IterFeatures};
use ecitygml::model::core::CityModel;
use std::path::PathBuf;
use std::sync::atomic::{AtomicUsize, Ordering};

mod arena;
mod geometry;
mod iteration;
mod reader;
mod types;
mod writer;

/// `tests/fixtures/<path>`.
fn fixture(path: &str) -> String {
    format!("{}/../../tests/fixtures/{path}", env!("CARGO_MANIFEST_DIR"))
}

/// Reads the file at `path`.
fn read(path: &str) -> CityModel {
    GmlReader::from_path(path)
        .unwrap_or_else(|error| panic!("{path}: {error}"))
        .finish()
        .unwrap_or_else(|error| panic!("{path}: {error}"))
}

/// A fresh temporary directory, unique per call (tests run in parallel threads of one process), removed on drop.
struct TempDir(PathBuf);

impl TempDir {
    fn new() -> Self {
        static NEXT: AtomicUsize = AtomicUsize::new(0);
        let n = NEXT.fetch_add(1, Ordering::Relaxed);
        let dir = std::env::temp_dir().join(format!("ecitygml-api-{}-{n}", std::process::id()));
        std::fs::create_dir_all(&dir).expect("should create the temporary directory");
        Self(dir)
    }

    fn join(&self, path: &str) -> PathBuf {
        self.0.join(path)
    }
}

impl Drop for TempDir {
    fn drop(&mut self) {
        let _ = std::fs::remove_dir_all(&self.0);
    }
}

fn feature_types(city_model: &CityModel) -> Vec<FeatureType> {
    city_model
        .iter_features()
        .map(|feature| feature.feature_type())
        .collect()
}
