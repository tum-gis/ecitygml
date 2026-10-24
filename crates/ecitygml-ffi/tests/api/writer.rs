//! The cases of `writer.md`.

use crate::*;

use ecitygml_ffi::citygml::core::model::construction::wall_surface::WallSurface;
use ecitygml_ffi::citygml::io::format::CitygmlFormat;
use ecitygml_ffi::citygml::io::gml::write::GmlWriter;
use ecitygml_ffi::gml::core::model::geometry::primitives::linear_ring::LinearRing;
use ecitygml_ffi::gml::core::model::geometry::primitives::polygon::Polygon;
use ecitygml_ffi::gml::io::util::formatting::Formatting;

fn model() -> Box<CityModel> {
    read(&fixture(
        "fzk-haus/FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml",
    ))
}

fn assert_reads_back(path: &str, model: &CityModel) {
    assert_eq!(feature_types(&read(path)), feature_types(model), "{path}");
}

/// The model written as `Gml` text.
fn text(model: &CityModel, formatting: Option<Box<Formatting>>) -> String {
    let mut writer = GmlWriter::new(CitygmlFormat::Gml);
    if let Some(formatting) = formatting {
        writer.with_formatting(&formatting);
    }
    writer.finish(model).unwrap();
    String::from_utf8(writer.data().to_vec()).expect("should be UTF-8")
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
    let mut result = Vec::new();
    let mut features = city_model.iter_features();
    while let Some(feature) = features.next() {
        let Some(wall) = WallSurface::try_from(&feature) else {
            continue;
        };
        let Some(multi_surface) = wall.lod2_multi_surface().and_then(|p| p.object()) else {
            continue;
        };
        let mut members = multi_surface.surface_member();
        while let Some(member) = members.next() {
            let Some(polygon) = member.object().and_then(Polygon::try_from) else {
                continue;
            };
            let ring = LinearRing::try_from(polygon.exterior().unwrap()).unwrap();
            let mut points = ring.points();
            while let Some(p) = points.next() {
                result.push((p.x(), p.y(), p.z()));
            }
        }
    }
    result
}

#[test]
fn writer_preserves_coordinates() {
    let model = read(&fixture(FZK_LOD2));
    let mut writer = GmlWriter::new(CitygmlFormat::Gml);
    writer.finish(&model).unwrap();
    let written = GmlReader::new(writer.data(), CitygmlFormat::Gml)
        .finish()
        .unwrap();
    let coordinates = wall_coordinates(&model);
    assert!(!coordinates.is_empty());
    assert_eq!(wall_coordinates(&written), coordinates);
}

#[test]
fn writer_in_memory() {
    let model = model();
    for format in [
        CitygmlFormat::Gml,
        CitygmlFormat::GmlGz,
        CitygmlFormat::GmlZst,
    ] {
        let mut writer = GmlWriter::new(format);
        assert!(writer.data().is_empty());
        writer.finish(&model).unwrap();
        let written = GmlReader::new(writer.data(), format).finish().unwrap();
        assert_eq!(feature_types(&written), feature_types(&model));
        if format == CitygmlFormat::Gml {
            assert!(String::from_utf8_lossy(writer.data()).contains("<bldg:Building"));
        }
    }
}

#[test]
fn writer_files() {
    let model = model();
    let dir = TempDir::new();
    for name in ["out.gml", "out.gml.gz", "out.gml.zst"] {
        let path = dir.path(name);
        GmlWriter::from_path(path.as_bytes())
            .unwrap()
            .finish(&model)
            .unwrap();
        assert_reads_back(&path, &model);
    }
}

#[test]
fn writer_overwrites_file() {
    let model = model();
    let dir = TempDir::new();
    let path = dir.path("out.gml");
    std::fs::write(&path, "x".repeat(100_000)).expect("should write");
    GmlWriter::from_path(path.as_bytes())
        .unwrap()
        .finish(&model)
        .unwrap();
    assert_reads_back(&path, &model);
}

#[test]
fn writer_base_path_with_format() {
    let model = model();
    let dir = TempDir::new();
    std::fs::write(dir.path("out.gml.gz"), "x".repeat(100_000)).expect("should write");
    GmlWriter::from_base_path_with_format(dir.path("out").as_bytes(), CitygmlFormat::GmlGz)
        .unwrap()
        .finish(&model)
        .unwrap();
    assert_reads_back(&dir.path("out.gml.gz"), &model);
}

#[test]
fn writer_formatting() {
    let model = model();
    let default = text(&model, None);
    assert!(default.lines().count() > 1);
    assert!(!default.lines().any(|line| line.starts_with([' ', '\t'])));
    assert_eq!(text(&model, Some(Formatting::new_line())), default);
    assert_eq!(text(&model, Some(Formatting::indent(b' ', 0))), default);

    let compact = text(&model, Some(Formatting::compact()));
    assert!(compact.lines().count() < default.lines().count());

    let spaces = text(&model, Some(Formatting::indent(b' ', 2)));
    assert!(spaces.lines().any(|line| line.starts_with("  <")));
    assert!(!spaces.lines().any(|line| line.starts_with('\t')));

    let tabs = text(&model, Some(Formatting::indent(b'\t', 1)));
    assert!(tabs.lines().any(|line| line.starts_with("\t<")));
    let written = GmlReader::new(tabs.as_bytes(), CitygmlFormat::Gml)
        .finish()
        .unwrap();
    assert_eq!(feature_types(&written), feature_types(&model));
}

#[test]
fn writer_finish_once() {
    let model = model();
    let mut writer = GmlWriter::new(CitygmlFormat::Gml);
    writer.finish(&model).unwrap();
    let error = writer.finish(&model).err().unwrap();
    assert_error(&error, ErrorKind::InvalidArgument, "already finished");
}

#[test]
fn writer_unsupported_extension() {
    let dir = TempDir::new();
    let error = GmlWriter::from_path(dir.path("out.txt").as_bytes())
        .err()
        .unwrap();
    assert_error(&error, ErrorKind::InvalidArgument, "txt");
}

#[test]
fn writer_missing_directory() {
    let dir = TempDir::new();
    let error = GmlWriter::from_path(dir.path("missing/out.gml").as_bytes())
        .err()
        .unwrap();
    assert_error(&error, ErrorKind::Io, "");
}
