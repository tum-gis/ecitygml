//! `AbstractReliefComponentKind`, mirroring `ecitygml::model::relief::AbstractReliefComponentKind`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/relief/abstract_relief_component.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_space_boundary.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_city_object.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_feature_with_lifespan.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_feature.rs")]
#[diplomat::include("src/gml/core/model/feature/abstract_feature.rs")]
#[diplomat::include("src/gml/core/model/base/abstract_gml.rs")]
#[diplomat::include("src/gml/core/model/abstract_object.rs")]
pub mod ffi {
    use crate::citygml::core::model::common::feature_type::ffi::FeatureType;

    /// A relief component (a TIN relief), borrowed from a city model. It has the getters of every
    /// ancestor; `feature_type()` tells which component it is. Not bound yet: the concrete types'
    /// own getters (e.g. `tin`); get a `TinRelief` from the features with `TinRelief::try_from`.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct AbstractReliefComponentKind(ecitygml::model::relief::AbstractReliefComponentKind);

    impl AbstractReliefComponentKind {
        impl_gml_abstract_object_methods! {}
        impl_gml_abstract_gml_methods! {}
        impl_gml_abstract_feature_methods! {}
        impl_abstract_feature_methods! {}
        impl_abstract_feature_with_lifespan_methods! {}
        impl_abstract_city_object_methods! {}
        impl_abstract_space_boundary_methods! {}
        impl_abstract_relief_component_methods! {}

        pub fn feature_type(&self) -> FeatureType {
            ecitygml::model::common::HasFeatureType::feature_type(&self.0).into()
        }
    }
}

pub use ffi::AbstractReliefComponentKind;
