//! `AbstractBuildingSubdivisionKind`, mirroring `ecitygml::model::building::AbstractBuildingSubdivisionKind`.

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
    use crate::citygml::core::model::common::feature_type::ffi::FeatureType;

    /// A building subdivision (storey or building unit), borrowed from a city model. It has the
    /// getters of every ancestor, like the concrete types, which add none; `feature_type()` tells
    /// which one it is.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct AbstractBuildingSubdivisionKind(
        ecitygml::model::building::AbstractBuildingSubdivisionKind,
    );

    impl AbstractBuildingSubdivisionKind {
        impl_gml_abstract_object_methods! {}
        impl_gml_abstract_gml_methods! {}
        impl_gml_abstract_feature_methods! {}
        impl_abstract_feature_methods! {}
        impl_abstract_feature_with_lifespan_methods! {}
        impl_abstract_city_object_methods! {}
        impl_abstract_space_methods! {}
        impl_abstract_logical_space_methods! {}
        impl_abstract_building_subdivision_methods! {}

        pub fn feature_type(&self) -> FeatureType {
            ecitygml::model::common::HasFeatureType::feature_type(&self.0).into()
        }
    }
}

pub use ffi::AbstractBuildingSubdivisionKind;
