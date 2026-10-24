//! The cases of `writer.md`.

use crate::{TempDir, feature_types, fixture, read};
use ecitygml::io::{CitygmlFormat, Error, GmlReader, GmlWriter};
use ecitygml::model::common::IterFeatures;
use ecitygml::model::construction::WallSurface;
use ecitygml::model::core::{AsAbstractThematicSurface, CityModel};
use egml::io::util::Formatting;
use egml::model::geometry::primitives::{AbstractRingKind, AbstractSurfaceKind};

fn model() -> CityModel {
    read(&fixture(
        "fzk-haus/FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml",
    ))
}

fn assert_reads_back(path: &std::path::Path, model: &CityModel) {
    let written = read(path.to_str().expect("should be UTF-8"));
    assert_eq!(
        feature_types(&written),
        feature_types(model),
        "{}",
        path.display()
    );
}

/// The model written as `Gml` text.
fn text(model: &CityModel, formatting: Option<Formatting>) -> String {
    let mut data = Vec::new();
    let mut writer = GmlWriter::new(&mut data, CitygmlFormat::Gml);
    if let Some(formatting) = formatting {
        writer = writer.with_formatting(formatting);
    }
    writer.finish(model).expect("should write");
    String::from_utf8(data).expect("should be UTF-8")
}

#[test]
fn writer_in_memory() {
    let model = model();
    for format in [
        CitygmlFormat::Gml,
        CitygmlFormat::GmlGz,
        CitygmlFormat::GmlZst,
    ] {
        let mut data = Vec::new();
        let writer = GmlWriter::new(&mut data, format);
        writer.finish(&model).expect("should write");
        let written = GmlReader::new(data.as_slice(), format)
            .finish()
            .expect("should read");
        assert_eq!(feature_types(&written), feature_types(&model), "{format:?}");
        if format == CitygmlFormat::Gml {
            assert!(String::from_utf8_lossy(&data).contains("<bldg:Building"));
        }
    }
}

#[test]
fn writer_files() {
    let model = model();
    let dir = TempDir::new();
    for name in ["out.gml", "out.gml.gz", "out.gml.zst"] {
        let path = dir.join(name);
        GmlWriter::from_path(&path)
            .expect("should create")
            .finish(&model)
            .expect("should write");
        assert_reads_back(&path, &model);
    }
}

#[test]
fn writer_overwrites_file() {
    let model = model();
    let dir = TempDir::new();
    let path = dir.join("out.gml");
    std::fs::write(&path, "x".repeat(100_000)).expect("should write");
    GmlWriter::from_path(&path)
        .expect("should create")
        .finish(&model)
        .expect("should write");
    assert_reads_back(&path, &model);
}

#[test]
fn writer_base_path_with_format() {
    let model = model();
    let dir = TempDir::new();
    std::fs::write(dir.join("out.gml.gz"), "x".repeat(100_000)).expect("should write");
    GmlWriter::from_base_path_with_format(dir.join("out"), CitygmlFormat::GmlGz)
        .expect("should create")
        .finish(&model)
        .expect("should write");
    assert_reads_back(&dir.join("out.gml.gz"), &model);
}

#[test]
fn writer_formatting() {
    let model = model();
    let default = text(&model, None);
    assert!(default.lines().count() > 1);
    assert!(!default.lines().any(|line| line.starts_with([' ', '\t'])));
    assert_eq!(text(&model, Some(Formatting::NewLine)), default);
    let indent = |char, size| Some(Formatting::Indent { char, size });
    assert_eq!(text(&model, indent(b' ', 0)), default);

    let compact = text(&model, Some(Formatting::Compact));
    assert!(compact.lines().count() < default.lines().count());

    let spaces = text(&model, indent(b' ', 2));
    assert!(spaces.lines().any(|line| line.starts_with("  <")));
    assert!(!spaces.lines().any(|line| line.starts_with('\t')));

    let tabs = text(&model, indent(b'\t', 1));
    assert!(tabs.lines().any(|line| line.starts_with("\t<")));
    let written = GmlReader::new(tabs.as_bytes(), CitygmlFormat::Gml)
        .finish()
        .expect("should read");
    assert_eq!(feature_types(&written), feature_types(&model));
}

const FZK_LOD2: &str = "fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml";

#[test]
fn writer_keeps_references() {
    let text = text(&read(&fixture(FZK_LOD2)), None);
    assert_eq!(
        text.matches("xlink:href=\"#PolyID7350_878_759628_120742\"")
            .count(),
        1
    );
    assert_eq!(
        text.matches("gml:id=\"PolyID7350_878_759628_120742\"")
            .count(),
        1
    );
}

/// The exterior ring positions of every polygon of the wall surfaces' LoD2 multi surfaces, in document order.
fn wall_coordinates(city_model: &CityModel) -> Vec<(f64, f64, f64)> {
    city_model
        .iter_features()
        .filter_map(|feature| <&WallSurface>::try_from(feature).ok())
        .filter_map(|wall| wall.lod2_multi_surface().and_then(|p| p.object()))
        .flat_map(|multi_surface| multi_surface.surface_member())
        .filter_map(|member| match member.object() {
            Some(AbstractSurfaceKind::Polygon(polygon)) => polygon.exterior(),
            _ => None,
        })
        .flat_map(|ring| match ring {
            AbstractRingKind::LinearRing(ring) => ring.points().to_vec(),
            other => panic!("expected a linear ring, got {other:?}"),
        })
        .map(|p| (p.x(), p.y(), p.z()))
        .collect()
}

#[test]
fn writer_preserves_coordinates() {
    let model = read(&fixture(FZK_LOD2));
    let text = text(&model, None);
    let written = GmlReader::new(text.as_bytes(), CitygmlFormat::Gml)
        .finish()
        .expect("should read");
    let coordinates = wall_coordinates(&model);
    assert!(!coordinates.is_empty());
    assert_eq!(wall_coordinates(&written), coordinates);
}

#[test]
fn writer_unsupported_extension() {
    let error = GmlWriter::from_path(TempDir::new().join("out.txt"))
        .err()
        .unwrap();
    assert!(matches!(error, Error::InvalidFileExtension(_)), "{error:?}");
    assert!(error.to_string().contains("txt"), "{error}");
}

#[test]
fn writer_missing_directory() {
    let error = GmlWriter::from_path(TempDir::new().join("missing/out.gml"))
        .err()
        .unwrap();
    assert!(matches!(error, Error::StdIo(_)), "{error:?}");
}
