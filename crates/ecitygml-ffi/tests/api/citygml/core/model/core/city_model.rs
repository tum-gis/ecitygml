//! `CityModel` and the core abstract types (`AbstractFeature`, lifespan, `AbstractGml`).

use crate::*;

#[test]
fn bounded_by() {
    let path = format!("{FIXTURES}FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml");
    let city_model = read(path.as_bytes()).unwrap();
    let envelope = city_model.bounded_by().unwrap().envelope().unwrap();
    assert_eq!(envelope.size_x(), 12.0);
    assert_eq!(envelope.size_y(), 10.0);
    assert!((envelope.size_z() - 6.517669).abs() < 1e-9);
}

/// FZK LoD1 with lifespan dates on the city model itself (the fixtures only have them on buildings).
fn read_with_lifespan() -> Box<CityModel> {
    read_modified(
        "</gml:boundedBy>",
        "</gml:boundedBy>\n  <creationDate>2017-01-23T00:00:00+01:00</creationDate>\n  <validFrom>2018-01-01T12:30:00.5Z</validFrom>",
    )
}

#[test]
fn lifespan() {
    let city_model = read_with_lifespan();

    let creation_date = city_model.creation_date().unwrap();
    assert_eq!(
        written(|w| creation_date.to_rfc3339(w)),
        "2017-01-23T00:00:00+01:00"
    );
    assert_eq!(creation_date.timestamp(), 1485126000);
    assert_eq!(creation_date.offset_seconds(), 3600);

    let valid_from = city_model.valid_from().unwrap();
    assert_eq!(valid_from.offset_seconds(), 0);
    assert_eq!(valid_from.timestamp_subsec_nanos(), 500_000_000);

    assert!(city_model.termination_date().is_none());
    assert!(city_model.valid_to().is_none());
}

#[test]
fn lifespan_absent() {
    let path = format!("{FIXTURES}FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml");
    let city_model = read(path.as_bytes()).unwrap();
    assert!(city_model.creation_date().is_none());
}

#[test]
fn feature_id() {
    // The fixtures' city models have no gml:id; the reader generates `ecitygml-gen-feature-<n>`.
    let path = format!("{FIXTURES}FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml");
    let city_model = read(path.as_bytes()).unwrap();
    let generated = city_model.feature_id().as_str();
    assert!(
        generated.starts_with("ecitygml-gen-feature-"),
        "{generated}"
    );

    let city_model = read_modified("<CityModel ", "<CityModel gml:id=\"CM_1\" ");
    assert_eq!(city_model.feature_id().as_str(), "CM_1");
}

#[test]
fn abstract_gml_id_and_names() {
    let path = format!("{FIXTURES}FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml");
    let city_model = read(path.as_bytes()).unwrap();
    let mut names = city_model.names();
    let name = names.next().unwrap();
    assert_eq!(name.value(), "AC14-FZK-Haus");
    assert!(name.code_space().is_none());
    assert!(names.next().is_none());

    let city_model = read_modified("<CityModel ", "<CityModel gml:id=\"CM_gml\" ");
    assert_eq!(city_model.id().unwrap().as_str(), "CM_gml");
}

mod city_objects {
    use super::*;
    use ecitygml_ffi::citygml::core::model::building::building::Building;
    use ecitygml_ffi::citygml::core::model::common::feature_type::FeatureType;
    use ecitygml_ffi::citygml::core::model::construction::wall_surface::WallSurface;
    use ecitygml_ffi::citygml::core::model::core::refs::abstract_feature_kind_ref::AbstractFeatureKindRef;
    use ecitygml_ffi::citygml::core::model::transportation::road::Road;

    #[test]
    fn iter_city_objects_at_all_depths() {
        let path = format!("{FIXTURES}FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml");
        let city_model = read(path.as_bytes()).unwrap();
        let mut city_objects = city_model.iter_city_objects();
        let types: Vec<FeatureType> = std::iter::from_fn(|| city_objects.next())
            .map(|c| c.feature_type())
            .collect();
        // Unlike `iter_features()`, no city model; boundaries and their fillings are city objects too.
        assert!(!types.contains(&FeatureType::CityModel));
        assert_eq!(
            types
                .iter()
                .filter(|t| **t == FeatureType::Building)
                .count(),
            1
        );
        assert_eq!(
            types
                .iter()
                .filter(|t| **t == FeatureType::WallSurface)
                .count(),
            4
        );
        assert_eq!(city_model.city_objects_len(), 1);
    }

    #[test]
    fn from_city_object_converts_to_concrete_types() {
        let path = format!("{FIXTURES}ASAM-Ex_Bidirectional_Junction.gml");
        let city_model = read(path.as_bytes()).unwrap();
        let mut city_objects = city_model.iter_city_objects();
        let first = city_objects.next().unwrap();
        assert_eq!(first.feature_type(), FeatureType::Road);
        let feature = AbstractFeatureKindRef::from_city_object(&first);
        assert_eq!(feature.feature_type(), FeatureType::Road);
        let road = Road::try_from(&feature).unwrap();
        assert_eq!(
            road.feature_id().as_str(),
            "UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f"
        );
        assert!(Building::try_from(&feature).is_none());
    }

    #[test]
    fn recompute_child_bounding_shapes() {
        // The FZK LoD2 wall surfaces have no `gml:boundedBy`; the reader derives none when told
        // not to rebuild object bounds, recomputing derives it from their polygons.
        let path = format!("{FIXTURES}FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml");
        let mut reader = GmlReader::from_path(path.as_bytes()).unwrap();
        reader.with_rebuild_object_bounds(false);
        let mut city_model = reader.finish().unwrap();
        let walls_bounded = |city_model: &CityModel| {
            let mut features = city_model.iter_features();
            std::iter::from_fn(|| features.next())
                .filter_map(|f| WallSurface::try_from(&f).map(|w| w.bounded_by().is_some()))
                .collect::<Vec<_>>()
        };
        assert_eq!(walls_bounded(&city_model), [false; 4]);
        city_model.recompute_child_bounding_shapes();
        assert_eq!(walls_bounded(&city_model), [true; 4]);
    }
}
