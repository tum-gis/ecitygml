//! The cases of `reader.md`.

use crate::{fixture, read};
use ecitygml::io::{CitygmlFormat, Error, GmlReader};
use ecitygml::model::common::IterFeatures;
use ecitygml::model::construction::WallSurface;
use egml::model::feature::AsAbstractFeature as _;

const FZK_LOD1: &str = "fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml";
const FZK_LOD2: &str = "fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml";

#[test]
fn reader_from_bytes() {
    let data = std::fs::read(fixture(FZK_LOD1)).expect("should read the fixture");
    let city_model = GmlReader::new(data.as_slice(), CitygmlFormat::Gml)
        .finish()
        .expect("should read");
    assert_eq!(city_model.city_object_members_len(), 1);
}

#[test]
fn reader_compressed() {
    for (extension, format) in [("gz", CitygmlFormat::GmlGz), ("zst", CitygmlFormat::GmlZst)] {
        let path = fixture(&format!(
            "fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml.{extension}"
        ));
        assert_eq!(read(&path).city_object_members_len(), 1, "{path}");

        let data = std::fs::read(&path).expect("should read the fixture");
        let city_model = GmlReader::new(data.as_slice(), format)
            .finish()
            .expect("should read");
        assert_eq!(city_model.city_object_members_len(), 1, "{path}");
    }
}

#[test]
fn reader_default_rebuilds_object_bounds() {
    let city_model = read(&fixture(FZK_LOD2));
    let bounded: Vec<bool> = city_model
        .iter_features()
        .filter_map(|feature| <&WallSurface>::try_from(feature).ok())
        .map(|wall| wall.bounded_by().is_some())
        .collect();
    assert_eq!(bounded, [true; 4]);
}

#[test]
fn reader_missing_file() {
    let error = GmlReader::from_path(fixture("does-not-exist.gml"))
        .err()
        .unwrap();
    assert!(matches!(error, Error::StdIo(_)), "{error:?}");
    assert!(error.to_string().contains("No such file"), "{error}");
}

#[test]
fn reader_unsupported_extension() {
    let error = GmlReader::from_path(fixture("README.md")).err().unwrap();
    assert!(matches!(error, Error::InvalidFileExtension(_)), "{error:?}");
    assert!(error.to_string().contains("md"), "{error}");
}

#[test]
fn reader_invalid_content() {
    let reader = GmlReader::from_path(fixture("invalid/unclosed-tag.gml")).expect("should open");
    let error = reader.finish().err().unwrap();
    assert!(
        !matches!(error, Error::StdIo(_) | Error::InvalidFileExtension(_)),
        "{error:?}"
    );
    assert!(error.to_string().contains("tag not closed"), "{error}");
}
