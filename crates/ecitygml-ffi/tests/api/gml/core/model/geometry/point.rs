//! `Point` and `PointProperty`.

use crate::*;

use ecitygml_ffi::citygml::core::model::transportation::traffic_space::TrafficSpace;

#[test]
fn traffic_space_lod0_point() {
    let city_model = read_fixture_modified(
        "ASAM-UC_RoadShape.gml",
        "</lod2Solid>",
        "</lod2Solid><lod0Point><gml:Point gml:id=\"PointID_space\"><gml:pos srsDimension=\"3\">1.5 -2.5 3.25</gml:pos></gml:Point></lod0Point>",
    );
    let mut features = city_model.iter_features();
    let spaces: Vec<_> = std::iter::from_fn(|| features.next())
        .filter_map(|feature| TrafficSpace::try_from(&feature))
        .collect();
    assert_eq!(spaces.len(), 2);
    assert!(spaces[1].lod0_point().is_none());

    let property = spaces[0].lod0_point().unwrap();
    assert!(property.href().is_none());
    let point = property.object().unwrap();
    assert_eq!(point.id().unwrap().as_str(), "PointID_space");
    let pos = point.pos();
    assert_eq!((pos.x(), pos.y(), pos.z()), (1.5, -2.5, 3.25));
    let envelope = point.compute_envelope().unwrap();
    assert_eq!(envelope.lower_corner().x(), 1.5);
    assert_eq!(envelope.upper_corner().z(), 3.25);
}
