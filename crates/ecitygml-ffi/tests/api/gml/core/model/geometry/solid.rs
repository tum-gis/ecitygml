//! `Solid` and `SolidProperty`.

use crate::*;

use ecitygml_ffi::citygml::core::model::transportation::traffic_space::TrafficSpace;

#[test]
fn total_traffic_space_volume() {
    let city_model = read(format!("{FIXTURES}ASAM-UC_RoadShape.gml").as_bytes()).unwrap();
    let mut features = city_model.iter_features();
    let spaces: Vec<_> = std::iter::from_fn(|| features.next())
        .filter_map(|feature| TrafficSpace::try_from(&feature))
        .collect();

    let mut total = 0.0;
    for space in &spaces {
        let property = space.lod2_solid().unwrap();
        assert!(property.href().is_none());
        let solid = property.object().unwrap();
        assert!(solid.compute_envelope().is_some());
        assert!(solid.points().next().is_some());
        total += solid.volume_3d().unwrap();
    }
    assert!((total - 1260.0).abs() < 1e-6, "{total}");
}

#[test]
fn unresolved_href_member_fails_instead_of_being_skipped() {
    // The reader keeps a member whose `xlink:href` it can't resolve as a reference only.
    let city_model = read_fixture_modified(
        "ASAM-UC_RoadShape.gml",
        "</lod2Solid>",
        "</lod2Solid><lod3Solid><gml:Solid><gml:exterior><gml:Shell><gml:surfaceMember xlink:href=\"#PolyID_1\"/></gml:Shell></gml:exterior></gml:Solid></lod3Solid>",
    );
    let mut features = city_model.iter_features();
    let space = std::iter::from_fn(|| features.next())
        .find_map(|feature| TrafficSpace::try_from(&feature))
        .unwrap();
    let solid = space.lod3_solid().unwrap().object().unwrap();
    let error = solid.volume_3d().unwrap_err();
    assert_eq!(error.kind(), ErrorKind::UnresolvedReference);
    assert!(written(|w| error.message(w)).contains("PolyID_1"));
}
