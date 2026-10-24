//! The cases of `iteration.md`. `iterator_keeps_model_alive` is scoped out: the borrow checker rules it out.

use crate::{feature_types, fixture, read};
use ecitygml::model::common::{FeatureType, HasFeatureType, IterFeatures};

const FZK_LOD3: &str = "fzk-haus/FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml";
const ASAM_ROAD_SHAPE: &str = "asam-opendrive/ASAM-UC_RoadShape.gml";

#[test]
fn iterator_exhausted() {
    let city_model = read(&fixture(FZK_LOD3));
    let mut features = city_model.iter_features();
    assert_eq!(features.by_ref().count(), 22);
    assert!(features.next().is_none());
    assert!(features.next().is_none());
}

#[test]
fn iterator_stopped_early() {
    let city_model = read(&fixture(ASAM_ROAD_SHAPE));
    let mut features = city_model.iter_features();
    let first = features.next().expect("should have a feature");
    assert_eq!(first.feature_type(), FeatureType::CityModel);
    drop(features);
    assert_eq!(city_model.iter_features().count(), 11);
    assert_eq!(city_model.city_object_members_len(), 1);
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

#[test]
fn native_iteration() {
    let city_model = read(&fixture(FZK_LOD3));
    let mut types = Vec::new();
    for feature in city_model.iter_features() {
        types.push(feature.feature_type());
    }
    assert_eq!(types.len(), 22);
    assert_eq!(types[0], FeatureType::CityModel);
}
