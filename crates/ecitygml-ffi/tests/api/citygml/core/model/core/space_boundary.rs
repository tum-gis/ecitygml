//! `AbstractSpace::boundaries`, `AbstractSpaceBoundaryProperty` and `AbstractSpaceBoundaryKind`.

use crate::*;

use ecitygml_ffi::citygml::core::model::building::building::Building;
use ecitygml_ffi::citygml::core::model::common::feature_type::FeatureType;
use ecitygml_ffi::citygml::core::model::construction::wall_surface::WallSurface;
use ecitygml_ffi::citygml::core::model::core::refs::abstract_feature_kind_ref::AbstractFeatureKindRef;
use ecitygml_ffi::citygml::core::model::transportation::traffic_area::TrafficArea;
use ecitygml_ffi::citygml::core::model::transportation::traffic_space::TrafficSpace;

fn first_building(city_model: &CityModel) -> &Building {
    let mut features = city_model.iter_features();
    std::iter::from_fn(|| features.next())
        .find_map(|feature| Building::try_from(&feature))
        .unwrap()
}

#[test]
fn building_boundaries() {
    let path = format!("{FIXTURES}FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml");
    let city_model = read(path.as_bytes()).unwrap();
    let building = first_building(&city_model);

    let mut boundaries = building.boundaries();
    let mut types = Vec::new();
    let mut wall_area = 0.0;
    while let Some(property) = boundaries.next() {
        assert!(property.href().is_none());
        let boundary = property.object().unwrap();
        // AbstractSpaceBoundaryKind has the getters of every ancestor and its feature type.
        assert!(boundary.feature_id().as_str().starts_with("GML_"));
        types.push(boundary.feature_type());

        // From<&AbstractSpaceBoundaryKind> for AbstractFeatureKindRef, then the usual downcast.
        let feature = AbstractFeatureKindRef::from_space_boundary(boundary);
        assert_eq!(feature.feature_type(), boundary.feature_type());
        if let Some(wall) = WallSurface::try_from(&feature) {
            let multi_surface = wall.lod2_multi_surface().unwrap().object().unwrap();
            wall_area += multi_surface.area_3d().unwrap();
        }
    }
    let count = |t: FeatureType| types.iter().filter(|&&x| x == t).count();
    assert_eq!(types.len(), 7);
    assert_eq!(count(FeatureType::WallSurface), 4);
    assert_eq!(count(FeatureType::RoofSurface), 2);
    assert_eq!(count(FeatureType::GroundSurface), 1);
    assert!((wall_area - 188.62887820601463).abs() < 1e-6, "{wall_area}");
}

#[test]
fn filling_surfaces_through_boundaries() {
    let path = format!("{FIXTURES}FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml");
    let city_model = read(path.as_bytes()).unwrap();
    let mut boundaries = first_building(&city_model).boundaries();
    let mut fillings = 0;
    while let Some(property) = boundaries.next() {
        let feature = AbstractFeatureKindRef::from_space_boundary(property.object().unwrap());
        if let Some(wall) = WallSurface::try_from(&feature) {
            let mut surfaces = wall.filling_surfaces();
            fillings += std::iter::from_fn(|| surfaces.next()).count();
        }
    }
    assert_eq!(fillings, 13);
}

#[test]
fn traffic_space_boundaries() {
    let city_model = read(format!("{FIXTURES}ASAM-UC_RoadShape.gml").as_bytes()).unwrap();
    let mut features = city_model.iter_features();
    let spaces: Vec<_> = std::iter::from_fn(|| features.next())
        .filter_map(|feature| TrafficSpace::try_from(&feature))
        .collect();
    assert_eq!(spaces.len(), 2);

    let mut total = 0.0;
    for space in spaces {
        let mut boundaries = space.boundaries();
        let boundary = boundaries.next().unwrap().object().unwrap();
        assert!(boundaries.next().is_none());
        assert_eq!(boundary.feature_type(), FeatureType::TrafficArea);
        let feature = AbstractFeatureKindRef::from_space_boundary(boundary);
        let area = TrafficArea::try_from(&feature).unwrap();
        assert_eq!(area.functions().next().unwrap().value(), "1");
        total += area
            .lod2_multi_surface()
            .unwrap()
            .object()
            .unwrap()
            .area_3d()
            .unwrap();
    }
    assert!((total - 282.1405004348745).abs() < 1e-6, "{total}");
}

#[test]
fn no_and_href_only_boundaries() {
    let path = format!("{FIXTURES}FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml");
    let city_model = read(path.as_bytes()).unwrap();
    assert!(first_building(&city_model).boundaries().next().is_none());

    let city_model = read_modified(
        "<lod1Solid>",
        "<boundary xlink:href=\"#Missing_boundary\"/><lod1Solid>",
    );
    let mut boundaries = first_building(&city_model).boundaries();
    let property = boundaries.next().unwrap();
    assert!(boundaries.next().is_none());
    assert!(property.object().is_none());
    assert_eq!(
        property.href().unwrap().local_id(),
        Some("Missing_boundary")
    );
}
