//! `MultiSurface`, `AbstractSurfaceProperty`, `AbstractSurfaceKind` and `Polygon`.

use crate::*;

use ecitygml_ffi::citygml::core::model::transportation::traffic_space::TrafficSpace;
use ecitygml_ffi::gml::core::model::common::geometry_type::GeometryType;
use ecitygml_ffi::gml::core::model::geometry::primitives::polygon::Polygon;

/// A 10 m x 4 m rectangle with a 1 m x 1 m hole (39 m^2), given to the first traffic space.
const LOD2_MULTI_SURFACE: &str = "</lod2Solid>
          <lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id=\"PolyID_space\">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:posList srsDimension=\"3\">0 0 0 10 0 0 10 4 0 0 4 0 0 0 0</gml:posList>
                    </gml:LinearRing>
                  </gml:exterior>
                  <gml:interior>
                    <gml:LinearRing>
                      <gml:posList srsDimension=\"3\">1 1 0 1 2 0 2 2 0 2 1 0 1 1 0</gml:posList>
                    </gml:LinearRing>
                  </gml:interior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </lod2MultiSurface>";

#[test]
fn traffic_space_lod2_multi_surface() {
    let city_model =
        read_fixture_modified("ASAM-UC_RoadShape.gml", "</lod2Solid>", LOD2_MULTI_SURFACE);
    let mut features = city_model.iter_features();
    let spaces: Vec<_> = std::iter::from_fn(|| features.next())
        .filter_map(|feature| TrafficSpace::try_from(&feature))
        .collect();
    assert_eq!(spaces.len(), 2);
    // Only the first traffic space got one; the fixture's surfaces belong to TrafficAreas.
    assert!(spaces[1].lod2_multi_surface().is_none());

    let space = spaces[0];
    assert!(space.lod0_multi_surface().is_none());
    assert!(space.lod3_multi_surface().is_none());
    let property = space.lod2_multi_surface().unwrap();
    assert!(property.href().is_none());
    let multi_surface = property.object().unwrap();
    assert!((multi_surface.area_3d().unwrap() - 39.0).abs() < 1e-9);
    assert!(multi_surface.compute_envelope().is_some());
    // Exterior and interior ring, 4 positions each (egml drops the repeated closing position).
    let mut points = multi_surface.points();
    assert_eq!(std::iter::from_fn(|| points.next()).count(), 8);

    let mut members = multi_surface.surface_member();
    let surface = members.next().unwrap().object().unwrap();
    assert!(members.next().is_none());
    assert_eq!(surface.geometry_type(), GeometryType::Polygon);
    assert_eq!(surface.id().unwrap().as_str(), "PolyID_space");
    assert!((surface.area_3d().unwrap() - 39.0).abs() < 1e-9);
    assert!(surface.compute_envelope().is_some());

    let polygon = Polygon::try_from(surface).unwrap();
    assert!((polygon.area_3d().unwrap() - 39.0).abs() < 1e-9);
    assert!(polygon.compute_envelope().is_some());
    let mut points = polygon.points();
    assert_eq!(std::iter::from_fn(|| points.next()).count(), 8);
}

#[test]
fn unresolved_href_member_fails() {
    // The reader keeps a member whose `xlink:href` it can't resolve as a reference only.
    let city_model = read_fixture_modified(
        "ASAM-UC_RoadShape.gml",
        "</lod2Solid>",
        "</lod2Solid><lod3MultiSurface><gml:MultiSurface><gml:surfaceMember xlink:href=\"#PolyID_1\"/></gml:MultiSurface></lod3MultiSurface>",
    );
    let mut features = city_model.iter_features();
    let space = std::iter::from_fn(|| features.next())
        .find_map(|feature| TrafficSpace::try_from(&feature))
        .unwrap();
    let multi_surface = space.lod3_multi_surface().unwrap().object().unwrap();
    let error = multi_surface.area_3d().unwrap_err();
    assert_eq!(error.kind(), ErrorKind::UnresolvedReference);
    assert!(written(|w| error.message(w)).contains("PolyID_1"));
    let mut members = multi_surface.surface_member();
    let member = members.next().unwrap();
    assert!(member.object().is_none());
    assert_eq!(member.href().unwrap().local_id(), Some("PolyID_1"));
}
