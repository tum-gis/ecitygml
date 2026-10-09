//! `AuxiliaryTrafficSpace` and `AuxiliaryTrafficArea`.

use crate::*;

use ecitygml_ffi::citygml::core::model::core::enums::space_type::SpaceType;
use ecitygml_ffi::citygml::core::model::transportation::auxiliary_traffic_area::AuxiliaryTrafficArea;
use ecitygml_ffi::citygml::core::model::transportation::auxiliary_traffic_space::AuxiliaryTrafficSpace;
use ecitygml_ffi::citygml::core::model::transportation::enums::granularity_value::GranularityValue;
use ecitygml_ffi::citygml::core::model::transportation::traffic_area::TrafficArea;
use ecitygml_ffi::citygml::core::model::transportation::traffic_space::TrafficSpace;

fn road_shape() -> Box<CityModel> {
    read(format!("{FIXTURES}ASAM-UC_RoadShape.gml").as_bytes()).unwrap()
}

#[test]
fn auxiliary_traffic_spaces() {
    let city_model = road_shape();
    let mut features = city_model.iter_features();
    let features: Vec<_> = std::iter::from_fn(|| features.next()).collect();
    let spaces: Vec<_> = features
        .iter()
        .filter_map(|feature| AuxiliaryTrafficSpace::try_from(feature))
        .collect();
    assert_eq!(spaces.len(), 2);
    // Traffic spaces aren't auxiliary ones and vice versa.
    let traffic_space = features
        .iter()
        .find(|feature| TrafficSpace::try_from(feature).is_some())
        .unwrap();
    assert!(AuxiliaryTrafficSpace::try_from(traffic_space).is_none());

    for space in spaces {
        // AuxiliaryTrafficSpace
        assert!(space.class().is_none());
        assert!(space.functions().next().is_none());
        assert!(space.usages().next().is_none());
        assert_eq!(space.granularity(), GranularityValue::Lane);
        // AbstractSpace and further ancestors
        assert_eq!(space.space_type(), Some(SpaceType::Open));
        let solid = space.lod2_solid().unwrap().object().unwrap();
        assert!((solid.volume_3d().unwrap() - 100.0).abs() < 1e-6);
        let multi_curve = space.lod2_multi_curve().unwrap().object().unwrap();
        assert!((multi_curve.length_3d().unwrap() - 40.0).abs() < 1e-9);
        assert!(space.feature_id().as_str().starts_with("UUID_"));
    }
}

#[test]
fn auxiliary_traffic_areas() {
    let city_model = road_shape();
    let mut features = city_model.iter_features();
    let features: Vec<_> = std::iter::from_fn(|| features.next()).collect();
    let areas: Vec<_> = features
        .iter()
        .filter_map(|feature| AuxiliaryTrafficArea::try_from(feature))
        .collect();
    assert_eq!(areas.len(), 2);
    let traffic_area = features
        .iter()
        .find(|feature| TrafficArea::try_from(feature).is_some())
        .unwrap();
    assert!(AuxiliaryTrafficArea::try_from(traffic_area).is_none());

    for area in areas {
        // AuxiliaryTrafficArea
        assert!(area.class().is_none());
        assert!(area.functions().next().is_none());
        assert!(area.usages().next().is_none());
        assert!(area.surface_material().is_none());
        // AbstractThematicSurface and further ancestors
        assert!(area.lod0_multi_surface().is_none());
        let multi_surface = area.lod2_multi_surface().unwrap().object().unwrap();
        assert!((multi_surface.area_3d().unwrap() - 40.0).abs() < 1e-6);
        assert_eq!(area.names().next().unwrap().value(), "Lane");
    }
}
