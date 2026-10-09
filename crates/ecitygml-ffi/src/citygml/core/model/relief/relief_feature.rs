//! `ReliefFeature`, mirroring `ecitygml::model::relief::ReliefFeature`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/core/abstract_space_boundary.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_city_object.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_feature_with_lifespan.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_feature.rs")]
#[diplomat::include("src/gml/core/model/feature/abstract_feature.rs")]
#[diplomat::include("src/gml/core/model/base/abstract_gml.rs")]
#[diplomat::include("src/gml/core/model/abstract_object.rs")]
pub mod ffi {
    use crate::citygml::core::model::common::level_of_detail::ffi::LevelOfDetail;
    use crate::citygml::core::model::core::refs::abstract_feature_kind_ref::ffi::AbstractFeatureKindRef;
    use crate::citygml::core::model::relief::abstract_relief_component_property::ffi::AbstractReliefComponentPropertyIterator;

    /// A relief (terrain) feature made of relief components, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct ReliefFeature(ecitygml::model::relief::ReliefFeature);

    impl ReliefFeature {
        impl_gml_abstract_object_methods! {}
        impl_gml_abstract_gml_methods! {}
        impl_gml_abstract_feature_methods! {}
        impl_abstract_feature_methods! {}
        impl_abstract_feature_with_lifespan_methods! {}
        impl_abstract_city_object_methods! {}
        impl_abstract_space_boundary_methods! {}

        /// The feature as a relief feature, or none if it is another type (Rust: `<&ReliefFeature>::try_from`).
        pub fn try_from<'a>(feature: &AbstractFeatureKindRef<'a>) -> Option<&'a ReliefFeature> {
            <&ecitygml::model::relief::ReliefFeature>::try_from(feature.0)
                .ok()
                .map(ReliefFeature::transparent_convert)
        }

        pub fn lod(&self) -> LevelOfDetail {
            self.0.lod().into()
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn relief_components<'a>(&'a self) -> Box<AbstractReliefComponentPropertyIterator<'a>> {
            Box::new(AbstractReliefComponentPropertyIterator(
                self.0.relief_components().iter(),
            ))
        }
    }
}

pub use ffi::ReliefFeature;
