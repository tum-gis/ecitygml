//! Reading and writing city models with `GmlReader` and `GmlWriter`.

use crate::*;

#[test]
fn reads_city_objects() {
    let path = format!("{FIXTURES}FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml");
    assert_eq!(read(path.as_bytes()).unwrap().city_objects_len(), 1);
}

#[test]
fn read_errors() {
    let missing = read_error("/nonexistent/model.gml");
    assert_eq!(missing.kind(), ErrorKind::Io);
    assert!(written(|w| missing.message(w)).contains("No such file"));

    assert_eq!(
        read_error(&format!("{FIXTURES}../../README.md")).kind(),
        ErrorKind::InvalidArgument
    );

    let not_utf8 = read(b"\xff.gml").err().unwrap();
    assert_eq!(not_utf8.kind(), ErrorKind::InvalidArgument);
    assert!(written(|w| not_utf8.message(w)).contains("`path`"));
}

#[test]
fn gml_reader_options_and_single_finish() {
    let path = format!("{FIXTURES}FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml");
    let mut reader = GmlReader::from_path(path.as_bytes()).unwrap();
    reader.with_rebuild_object_bounds(false);
    assert_eq!(reader.finish().unwrap().city_objects_len(), 1);

    let again = reader.finish().err().unwrap();
    assert_eq!(again.kind(), ErrorKind::InvalidArgument);
    assert!(written(|w| again.message(w)).contains("already finished"));
}

#[test]
fn gml_reader_from_bytes() {
    use ecitygml_ffi::citygml::io::format::CitygmlFormat;
    let data = std::fs::read(format!(
        "{FIXTURES}FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml"
    ))
    .unwrap();
    let mut reader = GmlReader::new(&data, CitygmlFormat::Gml);
    assert_eq!(reader.finish().unwrap().city_objects_len(), 1);

    let error = GmlReader::new(b"<no-citygml", CitygmlFormat::Gml)
        .finish()
        .err()
        .unwrap();
    assert_eq!(error.kind(), ErrorKind::Parse);
}

mod writer {
    use crate::*;

    use ecitygml_ffi::citygml::core::model::building::building::Building;
    use ecitygml_ffi::citygml::core::model::common::feature_type::FeatureType;
    use ecitygml_ffi::citygml::io::format::CitygmlFormat;
    use ecitygml_ffi::citygml::io::gml::write::GmlWriter;
    use ecitygml_ffi::gml::io::util::formatting::Formatting;

    const FZK_LOD3: &str = "FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml";

    fn feature_types(city_model: &CityModel) -> Vec<FeatureType> {
        let mut features = city_model.iter_features();
        std::iter::from_fn(|| features.next())
            .map(|f| f.feature_type())
            .collect()
    }

    fn building_id(city_model: &CityModel) -> String {
        let mut features = city_model.iter_features();
        let building = std::iter::from_fn(|| features.next())
            .find_map(|f| Building::try_from(&f))
            .unwrap();
        building.feature_id().as_str().to_owned()
    }

    fn temp_path(name: &str) -> std::path::PathBuf {
        let dir = std::env::temp_dir().join(format!("ecitygml-ffi-writer-{}", std::process::id()));
        std::fs::create_dir_all(&dir).unwrap();
        dir.join(name)
    }

    #[test]
    fn round_trip_through_files() {
        let model = read(format!("{FIXTURES}{FZK_LOD3}").as_bytes()).unwrap();
        for name in ["round_trip.gml", "round_trip.gml.gz", "round_trip.gml.zst"] {
            let path = temp_path(name);
            let mut writer = GmlWriter::from_path(path.to_str().unwrap().as_bytes()).unwrap();
            writer.finish(&model).unwrap();
            let written = read(path.to_str().unwrap().as_bytes()).unwrap();
            assert_eq!(feature_types(&written), feature_types(&model), "{name}");
            assert_eq!(building_id(&written), building_id(&model));
            std::fs::remove_file(path).unwrap();
        }
    }

    #[test]
    fn base_path_with_format_and_overwrite() {
        let model = read(format!("{FIXTURES}{FZK_LOD3}").as_bytes()).unwrap();
        let base = temp_path("base");
        let path = temp_path("base.gml.gz");
        std::fs::write(&path, "x".repeat(100_000)).unwrap();
        let mut writer = GmlWriter::from_base_path_with_format(
            base.to_str().unwrap().as_bytes(),
            CitygmlFormat::GmlGz,
        )
        .unwrap();
        writer.finish(&model).unwrap();
        let written = read(path.to_str().unwrap().as_bytes()).unwrap();
        assert_eq!(feature_types(&written), feature_types(&model));
        std::fs::remove_file(path).unwrap();
    }

    #[test]
    fn round_trip_in_memory() {
        let model = read(format!("{FIXTURES}{FZK_LOD3}").as_bytes()).unwrap();
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
        }
    }

    fn written_text(model: &CityModel, formatting: Option<&Formatting>) -> String {
        let mut writer = GmlWriter::new(CitygmlFormat::Gml);
        if let Some(formatting) = formatting {
            writer.with_formatting(formatting);
        }
        writer.finish(model).unwrap();
        String::from_utf8(writer.data().to_vec()).unwrap()
    }

    #[test]
    fn formatting() {
        let model = read(format!("{FIXTURES}{FZK_LOD3}").as_bytes()).unwrap();
        let default = written_text(&model, None);
        assert!(default.lines().count() > 1);
        assert!(!default.lines().any(|l| l.starts_with([' ', '\t'])));
        assert_eq!(written_text(&model, Some(&Formatting::new_line())), default);

        let compact = written_text(&model, Some(&Formatting::compact()));
        assert!(compact.lines().count() < default.lines().count());

        let spaces = written_text(&model, Some(&Formatting::indent(b' ', 2)));
        assert!(spaces.lines().any(|l| l.starts_with("  <")));
        assert!(!spaces.lines().any(|l| l.starts_with('\t')));
        let tabs = written_text(&model, Some(&Formatting::indent(b'\t', 1)));
        assert!(tabs.lines().any(|l| l.starts_with("\t<")));
        let written = GmlReader::new(tabs.as_bytes(), CitygmlFormat::Gml)
            .finish()
            .unwrap();
        assert_eq!(feature_types(&written), feature_types(&model));
    }

    #[test]
    fn errors() {
        let model = read(format!("{FIXTURES}{FZK_LOD3}").as_bytes()).unwrap();
        let unknown = GmlWriter::from_path(temp_path("out.txt").to_str().unwrap().as_bytes())
            .err()
            .unwrap();
        assert_eq!(unknown.kind(), ErrorKind::InvalidArgument);
        assert!(written(|w| unknown.message(w)).contains("txt"));

        let missing = temp_path("missing").join("out.gml");
        let error = GmlWriter::from_path(missing.to_str().unwrap().as_bytes())
            .err()
            .unwrap();
        assert_eq!(error.kind(), ErrorKind::Io);

        let mut writer = GmlWriter::new(CitygmlFormat::Gml);
        writer.finish(&model).unwrap();
        let again = writer.finish(&model).unwrap_err();
        assert_eq!(again.kind(), ErrorKind::InvalidArgument);
        assert!(written(|w| again.message(w)).contains("already finished"));
    }
}
