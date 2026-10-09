//! `BuildingUnit`, mirroring `ecitygml::model::building::BuildingUnit`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/building/abstract_building_subdivision.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_logical_space.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_space.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_city_object.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_feature_with_lifespan.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_feature.rs")]
#[diplomat::include("src/gml/core/model/feature/abstract_feature.rs")]
#[diplomat::include("src/gml/core/model/base/abstract_gml.rs")]
#[diplomat::include("src/gml/core/model/abstract_object.rs")]
pub mod ffi {
    use crate::citygml::core::model::core::refs::abstract_feature_kind_ref::ffi::AbstractFeatureKindRef;

    /// A building unit, borrowed from a city model. It has no properties of its own in CityGML 3.0.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct BuildingUnit(ecitygml::model::building::BuildingUnit);

    impl BuildingUnit {
        impl_gml_abstract_object_methods! {}
        impl_gml_abstract_gml_methods! {}
        impl_gml_abstract_feature_methods! {}
        impl_abstract_feature_methods! {}
        impl_abstract_feature_with_lifespan_methods! {}
        impl_abstract_city_object_methods! {}
        impl_abstract_space_methods! {}
        impl_abstract_logical_space_methods! {}
        impl_abstract_building_subdivision_methods! {}

        /// The feature as a building unit, or none if it is another type (Rust: `<&BuildingUnit>::try_from`).
        pub fn try_from<'a>(feature: &AbstractFeatureKindRef<'a>) -> Option<&'a BuildingUnit> {
            <&ecitygml::model::building::BuildingUnit>::try_from(feature.0)
                .ok()
                .map(BuildingUnit::transparent_convert)
        }
    }
}

pub use ffi::BuildingUnit;
