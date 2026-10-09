//! `TrafficSpace`.

use crate::*;

use ecitygml_ffi::citygml::core::model::core::enums::space_type::SpaceType;
use ecitygml_ffi::citygml::core::model::transportation::enums::granularity_value::GranularityValue;
use ecitygml_ffi::citygml::core::model::transportation::enums::traffic_direction_value::TrafficDirectionValue;
use ecitygml_ffi::citygml::core::model::transportation::traffic_space::TrafficSpace;

fn traffic_spaces(city_model: &CityModel) -> Vec<&TrafficSpace> {
    let mut features = city_model.iter_features();
    std::iter::from_fn(|| features.next())
        .filter_map(|feature| TrafficSpace::try_from(&feature))
        .collect()
}

#[test]
fn found_via_iter_features_and_try_from() {
    let city_model = read(format!("{FIXTURES}ASAM-UC_RoadShape.gml").as_bytes()).unwrap();
    let spaces = traffic_spaces(&city_model);
    assert_eq!(spaces.len(), 2);

    let mut directions: Vec<_> = spaces.iter().map(|s| s.traffic_direction()).collect();
    directions.sort_by_key(|d| format!("{d:?}"));
    assert_eq!(
        directions,
        [
            Some(TrafficDirectionValue::Backwards),
            Some(TrafficDirectionValue::Forwards)
        ]
    );
}

#[test]
fn own_and_inherited_getters() {
    let city_model = read(format!("{FIXTURES}ASAM-UC_RoadShape.gml").as_bytes()).unwrap();
    let space = traffic_spaces(&city_model)[0];

    // TrafficSpace
    assert_eq!(space.granularity(), GranularityValue::Lane);
    assert!(space.class().is_none());
    let mut functions = space.functions();
    let functions: Vec<_> = std::iter::from_fn(|| functions.next())
        .map(|f| f.value())
        .collect();
    assert_eq!(functions, ["1"]);
    let mut usages = space.usages();
    assert_eq!(usages.next().unwrap().code().value(), "2");
    assert!(usages.next().is_none());
    assert!(space.occupancies().next().is_none());

    // AbstractSpace, AbstractCityObject, AbstractFeature (ecitygml and egml)
    assert_eq!(space.space_type(), Some(SpaceType::Open));
    assert!(space.relative_to_terrain().is_none());
    assert!(!space.feature_id().as_str().is_empty());
    assert!(space.creation_date().is_none());
    let _ = space.bounded_by();
}

#[test]
fn feature_type_of_other_features() {
    use ecitygml_ffi::citygml::core::model::common::feature_type::FeatureType;
    let path = format!("{FIXTURES}FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml");
    let city_model = read(path.as_bytes()).unwrap();
    let mut features = city_model.iter_features();
    let types: Vec<_> = std::iter::from_fn(|| features.next())
        .map(|f| f.feature_type())
        .collect();
    assert!(types.contains(&FeatureType::Building));
    assert!(traffic_spaces(&city_model).is_empty());
}
