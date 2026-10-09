//! `Road`, `Section`, `Intersection`, `Marking` and their properties.

use crate::*;

use ecitygml_ffi::citygml::core::model::transportation::road::Road;
use ecitygml_ffi::citygml::core::model::transportation::traffic_space::TrafficSpace;

fn first_road(city_model: &CityModel) -> &Road {
    let mut features = city_model.iter_features();
    std::iter::from_fn(|| features.next())
        .find_map(|feature| Road::try_from(&feature))
        .unwrap()
}

fn count<T>(next: impl FnMut() -> Option<T>) -> usize {
    std::iter::from_fn(next).count()
}

#[test]
fn road_with_section() {
    let city_model = read(format!("{FIXTURES}ASAM-UC_RoadShape.gml").as_bytes()).unwrap();
    let mut features = city_model.iter_features();
    let features: Vec<_> = std::iter::from_fn(|| features.next()).collect();
    assert_eq!(features.iter().filter_map(|f| Road::try_from(f)).count(), 1);
    let traffic_space = features
        .iter()
        .find(|f| TrafficSpace::try_from(f).is_some())
        .unwrap();
    assert!(Road::try_from(traffic_space).is_none());

    let road = first_road(&city_model);
    // Road
    assert!(road.class().is_none());
    assert!(road.functions().next().is_none());
    assert!(road.usages().next().is_none());
    assert!(road.intersections().next().is_none());
    // AbstractTransportationSpace: the fixture puts all spaces into the section.
    assert!(road.traffic_direction().is_none());
    assert!(road.occupancies().next().is_none());
    assert!(road.traffic_spaces().next().is_none());
    assert!(road.auxiliary_traffic_spaces().next().is_none());
    assert!(road.markings().next().is_none());
    assert!(road.holes().next().is_none());
    // AbstractFeature
    assert!(road.feature_id().as_str().starts_with("UUID_8a13804c"));

    let mut sections = road.sections();
    let property = sections.next().unwrap();
    assert!(sections.next().is_none());
    assert!(property.href().is_none());
    let section = property.object().unwrap();
    assert!(section.class().is_none());
    assert!(section.feature_id().as_str().starts_with("UUID_0950bfa5"));

    let mut spaces = section.traffic_spaces();
    let mut granularities = Vec::new();
    while let Some(property) = spaces.next() {
        assert!(property.href().is_none());
        granularities.push(property.object().unwrap().granularity());
    }
    assert_eq!(granularities.len(), 2);
    let mut auxiliary = section.auxiliary_traffic_spaces();
    let mut volume = 0.0_f64;
    while let Some(property) = auxiliary.next() {
        let solid = property
            .object()
            .unwrap()
            .lod2_solid()
            .unwrap()
            .object()
            .unwrap();
        volume += solid.volume_3d().unwrap();
    }
    assert!((volume - 200.0).abs() < 1e-6, "{volume}");
    assert!(section.markings().next().is_none());
    assert!(section.holes().next().is_none());
}

#[test]
fn road_with_sections_intersection_and_markings() {
    let city_model =
        read(format!("{FIXTURES}ASAM-Ex_Bidirectional_Junction.gml").as_bytes()).unwrap();
    let road = first_road(&city_model);

    let mut sections = road.sections();
    let sections: Vec<_> = std::iter::from_fn(|| sections.next())
        .map(|property| property.object().unwrap())
        .collect();
    assert_eq!(sections.len(), 3);

    let mut per_section = Vec::new();
    for section in &sections {
        let mut spaces = section.traffic_spaces();
        per_section.push(count(|| spaces.next()));
    }
    assert_eq!(per_section, [2, 1, 1]);

    let mut markings = sections[0].markings();
    let mut n = 0;
    while let Some(property) = markings.next() {
        let marking = property.object().unwrap();
        assert!(marking.class().is_none());
        assert!(marking.lod2_multi_surface().unwrap().object().is_some());
        n += 1;
    }
    assert_eq!(n, 4);

    let mut intersections = road.intersections();
    let intersection = intersections.next().unwrap().object().unwrap();
    assert!(intersections.next().is_none());
    assert!(intersection.class().is_none());
    let mut spaces = intersection.traffic_spaces();
    assert_eq!(count(|| spaces.next()), 3);
}
