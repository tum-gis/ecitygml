//! `MultiCurve`, `AbstractCurveProperty`, `AbstractCurveKind` and `LineString`.

use crate::*;

use ecitygml_ffi::citygml::core::model::transportation::traffic_space::TrafficSpace;
use ecitygml_ffi::gml::core::model::common::geometry_type::GeometryType;
use ecitygml_ffi::gml::core::model::geometry::primitives::line_string::LineString;

#[test]
fn traffic_space_lod2_multi_curves() {
    let city_model = read(format!("{FIXTURES}ASAM-UC_RoadShape.gml").as_bytes()).unwrap();
    let mut features = city_model.iter_features();
    let spaces: Vec<_> = std::iter::from_fn(|| features.next())
        .filter_map(|feature| TrafficSpace::try_from(&feature))
        .collect();
    assert_eq!(spaces.len(), 2);

    for space in spaces {
        assert!(space.lod0_multi_curve().is_none());
        assert!(space.lod3_multi_curve().is_none());
        let property = space.lod2_multi_curve().unwrap();
        assert!(property.href().is_none());
        let multi_curve = property.object().unwrap();
        assert!((multi_curve.length_3d().unwrap() - 40.0).abs() < 1e-9);
        assert!(multi_curve.compute_envelope().is_some());

        let mut members = multi_curve.curve_member();
        let curve = members.next().unwrap().object().unwrap();
        assert!(members.next().is_none());
        assert_eq!(curve.geometry_type(), GeometryType::LineString);
        assert!((curve.length_3d() - 40.0).abs() < 1e-9);
        assert!(curve.compute_envelope().is_some());

        let line_string = LineString::try_from(curve).unwrap();
        assert!((line_string.length_3d() - 40.0).abs() < 1e-9);
        let mut points = line_string.points();
        assert!(points.next().is_some());
        assert!(points.next().is_some());
        assert!(points.next().is_none());
    }
}

#[test]
fn unresolved_href_member_fails() {
    // The reader keeps a member whose `xlink:href` it can't resolve as a reference only.
    let city_model = read_fixture_modified(
        "ASAM-UC_RoadShape.gml",
        "</lod2Solid>",
        "</lod2Solid><lod0MultiCurve><gml:MultiCurve><gml:curveMember xlink:href=\"#CurveID_1\"/></gml:MultiCurve></lod0MultiCurve>",
    );
    let mut features = city_model.iter_features();
    let space = std::iter::from_fn(|| features.next())
        .find_map(|feature| TrafficSpace::try_from(&feature))
        .unwrap();
    let multi_curve = space.lod0_multi_curve().unwrap().object().unwrap();
    let error = multi_curve.length_3d().unwrap_err();
    assert_eq!(error.kind(), ErrorKind::UnresolvedReference);
    assert!(written(|w| error.message(w)).contains("CurveID_1"));
    let mut members = multi_curve.curve_member();
    let member = members.next().unwrap();
    assert!(member.object().is_none());
    assert_eq!(member.href().unwrap().local_id(), Some("CurveID_1"));
}
