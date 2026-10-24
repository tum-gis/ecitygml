//! Conformance suite of the Rust library, the reference the FFI API and the bindings follow: the fixture cases of
//! the case lists `<dataset>.md` in this folder, one module per dataset, as in every binding. See `README.md`.

use ecitygml::io::GmlReader;
use ecitygml::model::core::CityModel;

mod asam_opendrive;
mod fzk_haus;
mod fzk_haus_citygml_3_0;
mod kit_bruecke;
mod ogc_citygml_3_0_encodings;
mod railway_scene;
mod synthetic;
mod tum_main_entrance;

/// The tolerance of floating point comparisons in the case lists.
const TOLERANCE: f64 = 1e-6;

/// Reads `tests/fixtures/<dataset>/<file>`.
fn read(dataset: &str, file: &str) -> CityModel {
    let path = format!(
        "{}/../../tests/fixtures/{dataset}/{file}",
        env!("CARGO_MANIFEST_DIR")
    );
    GmlReader::from_path(&path)
        .unwrap_or_else(|error| panic!("{path}: {error}"))
        .finish()
        .unwrap_or_else(|error| panic!("{path}: {error}"))
}

fn assert_close(actual: f64, expected: f64) {
    assert!(
        (actual - expected).abs() <= TOLERANCE,
        "{actual} is not within {TOLERANCE} of {expected}"
    );
}
