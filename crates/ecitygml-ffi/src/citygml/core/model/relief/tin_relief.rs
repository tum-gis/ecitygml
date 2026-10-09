//! `TinRelief`, mirroring `ecitygml::model::relief::TinRelief`.

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
    use crate::citygml::core::model::core::refs::abstract_feature_kind_ref::ffi::AbstractFeatureKindRef;
    use crate::citygml::core::model::relief::tin_property::ffi::TinProperty;

    /// A relief component given as a triangulated irregular network, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct TinRelief(ecitygml::model::relief::TinRelief);

    impl TinRelief {
        impl_gml_abstract_object_methods! {}
        impl_gml_abstract_gml_methods! {}
        impl_gml_abstract_feature_methods! {}
        impl_abstract_feature_methods! {}
        impl_abstract_feature_with_lifespan_methods! {}
        impl_abstract_city_object_methods! {}
        impl_abstract_space_boundary_methods! {}
        impl_abstract_relief_component_methods! {}

        /// The feature as a tin relief, or none if it is another type (Rust: `<&TinRelief>::try_from`).
        pub fn try_from<'a>(feature: &AbstractFeatureKindRef<'a>) -> Option<&'a TinRelief> {
            <&ecitygml::model::relief::TinRelief>::try_from(feature.0)
                .ok()
                .map(TinRelief::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn tin<'a>(&'a self) -> Option<&'a TinProperty> {
            self.0.tin().map(TinProperty::transparent_convert)
        }
    }
}

pub use ffi::TinRelief;
