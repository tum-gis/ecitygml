//! `LevelOfDetail` and `FeatureType`.

use crate::*;

use ecitygml_ffi::citygml::core::model::common::feature_type::FeatureType;
use ecitygml_ffi::citygml::core::model::common::level_of_detail::LevelOfDetail;

#[test]
fn level_of_detail_index_and_try_from() {
    let all = [
        LevelOfDetail::Zero,
        LevelOfDetail::One,
        LevelOfDetail::Two,
        LevelOfDetail::Three,
    ];
    for (index, lod) in all.into_iter().enumerate() {
        assert_eq!(lod.as_index(), index);
        assert_eq!(LevelOfDetail::try_from(index as u8).unwrap(), lod);
    }

    let error = LevelOfDetail::try_from(4).unwrap_err();
    assert_eq!(error.kind(), ErrorKind::InvalidArgument);
    assert!(written(|w| error.message(w)).contains('4'));
}

#[test]
fn feature_type_to_string() {
    // As Rust's `Display` (strum): the variant name.
    assert_eq!(written(|w| FeatureType::Building.to_string(w)), "Building");
    assert_eq!(
        written(|w| FeatureType::TinRelief.to_string(w)),
        "TinRelief"
    );
}
