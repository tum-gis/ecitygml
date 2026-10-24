//! The cases of `reader.md`.

use crate::*;

use ecitygml_ffi::citygml::core::model::construction::wall_surface::WallSurface;
use ecitygml_ffi::citygml::io::format::CitygmlFormat;

const FZK_LOD1: &str = "fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml";
const FZK_LOD2: &str = "fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml";

#[test]
fn reader_from_bytes() {
    let data = std::fs::read(fixture(FZK_LOD1)).expect("should read the fixture");
    let city_model = GmlReader::new(&data, CitygmlFormat::Gml).finish().unwrap();
    assert_eq!(city_model.city_objects_len(), 1);
}

#[test]
fn reader_compressed() {
    for (extension, format) in [("gz", CitygmlFormat::GmlGz), ("zst", CitygmlFormat::GmlZst)] {
        let path = fixture(&format!(
            "fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml.{extension}"
        ));
        assert_eq!(read(&path).city_objects_len(), 1, "{path}");

        let data = std::fs::read(&path).expect("should read the fixture");
        let city_model = GmlReader::new(&data, format).finish().unwrap();
        assert_eq!(city_model.city_objects_len(), 1, "{path}");
    }
}

#[test]
fn reader_default_rebuilds_object_bounds() {
    let city_model = read(&fixture(FZK_LOD2));
    let mut features = city_model.iter_features();
    let bounded: Vec<bool> = std::iter::from_fn(|| features.next())
        .filter_map(|feature| {
            WallSurface::try_from(&feature).map(|wall| wall.bounded_by().is_some())
        })
        .collect();
    assert_eq!(bounded, [true; 4]);
}

#[test]
fn reader_finish_once() {
    let mut reader = GmlReader::from_path(fixture(FZK_LOD1).as_bytes()).unwrap();
    reader.with_rebuild_object_bounds(false);
    assert_eq!(reader.finish().unwrap().city_objects_len(), 1);
    let error = reader.finish().err().unwrap();
    assert_error(&error, ErrorKind::InvalidArgument, "already finished");
}

#[test]
fn reader_missing_file() {
    let error = GmlReader::from_path(fixture("does-not-exist.gml").as_bytes())
        .err()
        .unwrap();
    assert_error(&error, ErrorKind::Io, "No such file");
}

#[test]
fn reader_unsupported_extension() {
    let error = GmlReader::from_path(fixture("README.md").as_bytes())
        .err()
        .unwrap();
    assert_error(&error, ErrorKind::InvalidArgument, "md");
}

#[test]
fn reader_non_utf8_path() {
    let error = GmlReader::from_path(b"\xff.gml").err().unwrap();
    assert_error(&error, ErrorKind::InvalidArgument, "`path`");
}

#[test]
fn reader_invalid_content() {
    let mut reader = GmlReader::from_path(fixture("invalid/unclosed-tag.gml").as_bytes()).unwrap();
    let error = reader.finish().err().unwrap();
    assert_error(&error, ErrorKind::Parse, "tag not closed");
}
