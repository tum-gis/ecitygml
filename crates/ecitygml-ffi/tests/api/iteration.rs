//! The cases of `iteration.md`.

use crate::*;

const FZK_LOD3: &str = "fzk-haus/FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml";
const ASAM_ROAD_SHAPE: &str = "asam-opendrive/ASAM-UC_RoadShape.gml";

#[test]
fn iterator_exhausted() {
    let city_model = read(&fixture(FZK_LOD3));
    let mut features = city_model.iter_features();
    let mut count = 0;
    while features.next().is_some() {
        count += 1;
    }
    assert_eq!(count, 22);
    assert!(features.next().is_none());
}

#[test]
fn iterator_stopped_early() {
    let city_model = read(&fixture(ASAM_ROAD_SHAPE));
    let mut features = city_model.iter_features();
    let first = features.next().unwrap();
    assert_eq!(first.feature_type(), FeatureType::CityModel);
    drop(first);
    drop(features);
    assert_eq!(feature_types(&city_model).len(), 11);
    assert_eq!(city_model.city_objects_len(), 1);
}

#[test]
fn iterators_independent() {
    let city_model = read(&fixture(FZK_LOD3));
    let (mut first, mut second) = (city_model.iter_features(), city_model.iter_features());
    let (mut a, mut b) = (Vec::new(), Vec::new());
    loop {
        match (first.next(), second.next()) {
            (Some(x), Some(y)) => {
                a.push(x.feature_type());
                b.push(y.feature_type());
            }
            (None, None) => break,
            _ => panic!("the iterators should end together"),
        }
    }
    assert_eq!(a.len(), 22);
    assert_eq!(a, b);
    assert_eq!(a, feature_types(&city_model));
}
