//! Conformance suite of the FFI API: the fixture cases of `crates/ecitygml/tests/conformance/<dataset>.md`, one
//! module per dataset, as in every binding. See `crates/ecitygml/tests/conformance/README.md`.

use ecitygml_ffi::citygml::core::model::core::city_model::CityModel;
use ecitygml_ffi::citygml::io::gml::read::GmlReader;

use diplomat_runtime::{
    DiplomatWrite, diplomat_buffer_write_create, diplomat_buffer_write_destroy,
};

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

/// Reads `tests/fixtures/<dataset>/<file>`, as the bindings do: `GmlReader::from_path(path)?.finish()`.
fn read(dataset: &str, file: &str) -> Box<CityModel> {
    let path = format!(
        "{}/../../tests/fixtures/{dataset}/{file}",
        env!("CARGO_MANIFEST_DIR")
    );
    GmlReader::from_path(path.as_bytes())
        .and_then(|mut reader| reader.finish())
        .unwrap_or_else(|_| panic!("{path} should be readable"))
}

fn assert_close(actual: f64, expected: f64) {
    assert!(
        (actual - expected).abs() <= TOLERANCE,
        "{actual} is not within {TOLERANCE} of {expected}"
    );
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
