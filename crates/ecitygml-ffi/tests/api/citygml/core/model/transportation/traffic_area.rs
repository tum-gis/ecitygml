//! `TrafficArea`.

use crate::*;

use ecitygml_ffi::citygml::core::model::transportation::traffic_area::TrafficArea;
use ecitygml_ffi::citygml::core::model::transportation::traffic_space::TrafficSpace;

fn traffic_areas(city_model: &CityModel) -> Vec<&TrafficArea> {
    let mut features = city_model.iter_features();
    std::iter::from_fn(|| features.next())
        .filter_map(|feature| TrafficArea::try_from(&feature))
        .collect()
}

#[test]
fn found_via_iter_features_and_try_from() {
    let city_model = read(format!("{FIXTURES}ASAM-UC_RoadShape.gml").as_bytes()).unwrap();
    let areas = traffic_areas(&city_model);
    assert_eq!(areas.len(), 2);

    // Not a traffic area: the traffic spaces bounded by them.
    let mut features = city_model.iter_features();
    let space = std::iter::from_fn(|| features.next())
        .find(|feature| TrafficSpace::try_from(feature).is_some())
        .unwrap();
    assert!(TrafficArea::try_from(&space).is_none());
}

#[test]
fn own_and_inherited_getters() {
    let city_model = read(format!("{FIXTURES}ASAM-UC_RoadShape.gml").as_bytes()).unwrap();
    let area = traffic_areas(&city_model)[0];

    // TrafficArea
    assert!(area.class().is_none());
    let mut functions = area.functions();
    assert_eq!(functions.next().unwrap().value(), "1");
    assert!(functions.next().is_none());
    let mut usages = area.usages();
    assert_eq!(usages.next().unwrap().code().value(), "2");
    assert!(usages.next().is_none());
    assert!(area.surface_material().is_none());

    // AbstractThematicSurface
    assert!(area.lod0_multi_curve().is_none());
    assert!(area.lod0_multi_surface().is_none());
    assert!(area.lod1_multi_surface().is_none());
    assert!(area.lod3_multi_surface().is_none());
    let multi_surface = area.lod2_multi_surface().unwrap().object().unwrap();
    assert!((multi_surface.area_3d().unwrap() - 160.79800993793438).abs() < 1e-6);

    // AbstractCityObject, AbstractFeature (ecitygml and egml), AbstractGml
    assert!(area.relative_to_terrain().is_none());
    assert!(area.feature_id().as_str().starts_with("UUID_8625bf6f"));
    assert_eq!(area.id().unwrap().as_str(), area.feature_id().as_str());
    assert_eq!(area.names().next().unwrap().value(), "Lane");
    assert!(area.creation_date().is_none());
}

#[test]
fn total_lod2_area() {
    let city_model = read(format!("{FIXTURES}ASAM-UC_RoadShape.gml").as_bytes()).unwrap();
    let total: f64 = traffic_areas(&city_model)
        .iter()
        .map(|area| {
            let property = area.lod2_multi_surface().unwrap();
            property.object().unwrap().area_3d().unwrap()
        })
        .sum();
    assert!((total - 282.1405004348745).abs() < 1e-6, "{total}");
}
