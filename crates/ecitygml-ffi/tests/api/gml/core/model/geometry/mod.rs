//! Geometry: positions and envelopes here, geometry types in the submodules.

use crate::*;

mod composite_surface;
mod multi_curve;
mod multi_surface;
mod point;
mod shell;
mod solid;
mod triangulation;

#[test]
fn envelope_corners() {
    let path = format!("{FIXTURES}FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml");
    let city_model = read(path.as_bytes()).unwrap();
    let envelope = city_model.bounded_by().unwrap().envelope().unwrap();
    let lower = envelope.lower_corner();
    assert_eq!(
        (lower.x(), lower.y(), lower.z()),
        (457842.0, 5439083.0, 111.8)
    );
    let upper = envelope.upper_corner();
    assert_eq!(
        (upper.x(), upper.y(), upper.z()),
        (457854.0, 5439093.0, 118.317669)
    );
}

#[test]
fn envelope_volume_and_contains() {
    use ecitygml_ffi::gml::core::model::geometry::direct_position::DirectPosition;
    let path = format!("{FIXTURES}FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml");
    let city_model = read(path.as_bytes()).unwrap();
    let envelope = city_model.bounded_by().unwrap().envelope().unwrap();

    // 12 m x 10 m x 6.517669 m
    assert!((envelope.volume() - 782.12028).abs() < 1e-6);

    // The boundary is inside.
    assert!(envelope.contains(envelope.lower_corner()));
    assert!(envelope.contains(envelope.upper_corner()));
    let center = DirectPosition::new(457848.0, 5439088.0, 115.0).unwrap();
    assert!(envelope.contains(&center));
    let above = DirectPosition::new(457848.0, 5439088.0, 118.4).unwrap();
    assert!(!envelope.contains(&above));
    let west = DirectPosition::new(457841.9, 5439088.0, 115.0).unwrap();
    assert!(!envelope.contains(&west));
}

#[test]
fn direct_position_new() {
    use ecitygml_ffi::gml::core::model::geometry::direct_position::DirectPosition;
    let position = DirectPosition::new(1.0, 2.0, 3.0).unwrap();
    assert_eq!((position.x(), position.y(), position.z()), (1.0, 2.0, 3.0));

    let error = DirectPosition::new(f64::NAN, 0.0, 0.0).err().unwrap();
    assert_eq!(error.kind(), ErrorKind::InvalidArgument);
    assert!(written(|w| error.message(w)).contains("non-finite"));
}
