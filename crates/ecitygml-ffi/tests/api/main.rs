//! Tests of the bridge API that the generated bindings wrap one-to-one, using only what is public,
//! like the bindings.
//!
//! The modules mirror the crate's layout (`citygml::core::model`, `citygml::io`, `gml::core::model`);
//! this file holds the shared helpers, which every test module imports with `use crate::*;`.

use ecitygml_ffi::citygml::core::model::core::city_model::CityModel;
use ecitygml_ffi::citygml::io::gml::read::GmlReader;
use ecitygml_ffi::error::{Error, ErrorKind};
use std::sync::atomic::{AtomicUsize, Ordering};

use diplomat_runtime::{
    DiplomatWrite, diplomat_buffer_write_create, diplomat_buffer_write_destroy,
};

mod citygml;
mod gml;

const FIXTURES: &str = concat!(env!("CARGO_MANIFEST_DIR"), "/../../tests/fixtures/");

/// `GmlReader::from_path(path)?.finish()`, as in Rust.
fn read(path: &[u8]) -> Result<Box<CityModel>, Box<Error>> {
    GmlReader::from_path(path)?.finish()
}

fn read_error(path: &str) -> Box<Error> {
    read(path.as_bytes()).err().unwrap()
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

/// Reads a temporary copy of FZK LoD1 with the first `from` replaced by `to`.
fn read_modified(from: &str, to: &str) -> Box<CityModel> {
    read_fixture_modified("FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml", from, to)
}

/// Reads a temporary copy of a fixture with the first `from` replaced by `to`.
fn read_fixture_modified(fixture: &str, from: &str, to: &str) -> Box<CityModel> {
    let original = std::fs::read_to_string(format!("{FIXTURES}{fixture}")).unwrap();
    // Unique per call: tests run in parallel threads of one process.
    static NEXT: AtomicUsize = AtomicUsize::new(0);
    let n = NEXT.fetch_add(1, Ordering::Relaxed);
    let name = format!("ecitygml-ffi-{}-{n}.gml", std::process::id());
    let path = std::env::temp_dir().join(name);
    std::fs::write(&path, original.replacen(from, to, 1)).unwrap();
    let city_model = read(path.to_str().unwrap().as_bytes()).unwrap();
    std::fs::remove_file(&path).unwrap();
    city_model
}

/// A model with the FZK LoD2 header (namespaces, envelope) and `member` as its only city object.
fn read_member(member: &str) -> Box<CityModel> {
    let text = std::fs::read_to_string(format!(
        "{FIXTURES}FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml"
    ))
    .unwrap();
    let header = &text[..text.find("<cityObjectMember>").unwrap()];
    let format = ecitygml_ffi::citygml::io::format::CitygmlFormat::Gml;
    GmlReader::new((header.to_owned() + member).as_bytes(), format)
        .finish()
        .unwrap()
}

/// The first feature of a model that `try_from` accepts.
fn first<'a, T>(
    city_model: &'a CityModel,
    try_from: impl Fn(
        &ecitygml_ffi::citygml::core::model::core::refs::abstract_feature_kind_ref::AbstractFeatureKindRef<'a>,
    ) -> Option<&'a T>,
) -> &'a T {
    let mut features = city_model.iter_features();
    std::iter::from_fn(|| features.next())
        .find_map(|f| try_from(&f))
        .unwrap()
}
