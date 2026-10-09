//! `Shell`, `Polygon` rings, `AbstractRingKind` and `LinearRing`.

use crate::*;

use ecitygml_ffi::citygml::core::model::building::building::Building;
use ecitygml_ffi::gml::core::model::common::geometry_type::GeometryType;
use ecitygml_ffi::gml::core::model::geometry::primitives::linear_ring::LinearRing;
use ecitygml_ffi::gml::core::model::geometry::primitives::polygon::Polygon;

fn first_building(city_model: &CityModel) -> &Building {
    let mut features = city_model.iter_features();
    std::iter::from_fn(|| features.next())
        .find_map(|feature| Building::try_from(&feature))
        .unwrap()
}

#[test]
fn solid_shell_polygons_and_rings() {
    let path = format!("{FIXTURES}FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml");
    let city_model = read(path.as_bytes()).unwrap();
    let solid = first_building(&city_model)
        .lod1_solid()
        .unwrap()
        .object()
        .unwrap();

    assert!(solid.interior().next().is_none());
    let shell = solid.exterior().unwrap();
    assert!((shell.volume_3d().unwrap() - 782.1228).abs() < 1e-6);
    assert!(shell.compute_envelope().is_some());

    let mut members = shell.members();
    let mut polygons = Vec::new();
    while let Some(member) = members.next() {
        assert!(member.href().is_none());
        polygons.push(Polygon::try_from(member.object().unwrap()).unwrap());
    }
    assert_eq!(polygons.len(), 6);

    for polygon in &polygons {
        assert!(polygon.interior().next().is_none());
        let exterior = polygon.exterior().unwrap();
        assert_eq!(exterior.geometry_type(), GeometryType::LinearRing);
        let ring = LinearRing::try_from(exterior).unwrap();
        // egml drops the repeated closing position.
        let mut points = ring.points();
        assert_eq!(std::iter::from_fn(|| points.next()).count(), 4);
        assert!(ring.area_3d() > 0.0);
        assert!(ring.compute_envelope().is_some());
    }
    let first = LinearRing::try_from(polygons[0].exterior().unwrap()).unwrap();
    let point = first.points().next().unwrap();
    assert_eq!(
        (point.x(), point.y(), point.z()),
        (457842.0, 5439083.0, 111.8)
    );
    // The 12 m x 10 m ground face; the perimeter includes the closing segment.
    assert!((first.length_3d() - 44.0).abs() < 1e-9);
    assert!((first.area_3d() - 120.0).abs() < 1e-9);
}

#[test]
fn polygon_interior_rings() {
    // A 10 m x 4 m rectangle with a 1 m x 1 m hole.
    let city_model = read_modified(
        "<lod1Solid>",
        "<lod2MultiSurface><gml:MultiSurface><gml:surfaceMember><gml:Polygon>\
         <gml:exterior><gml:LinearRing><gml:posList srsDimension=\"3\">0 0 0 10 0 0 10 4 0 0 4 0 0 0 0</gml:posList></gml:LinearRing></gml:exterior>\
         <gml:interior><gml:LinearRing><gml:posList srsDimension=\"3\">1 1 0 1 2 0 2 2 0 2 1 0 1 1 0</gml:posList></gml:LinearRing></gml:interior>\
         </gml:Polygon></gml:surfaceMember></gml:MultiSurface></lod2MultiSurface><lod1Solid>",
    );
    let building = first_building(&city_model);
    let multi_surface = building.lod2_multi_surface().unwrap().object().unwrap();
    let member = multi_surface.surface_member().next().unwrap();
    let polygon = Polygon::try_from(member.object().unwrap()).unwrap();
    assert!((polygon.exterior().unwrap().area_3d() - 40.0).abs() < 1e-9);
    let mut interior = polygon.interior();
    let hole = interior.next().unwrap();
    assert!(interior.next().is_none());
    assert!((hole.area_3d() - 1.0).abs() < 1e-9);
    assert!((hole.length_3d() - 4.0).abs() < 1e-9);
}
