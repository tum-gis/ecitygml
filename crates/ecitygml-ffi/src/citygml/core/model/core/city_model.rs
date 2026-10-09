//! `CityModel`, an owned city model.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/core/abstract_feature_with_lifespan.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_feature.rs")]
#[diplomat::include("src/gml/core/model/feature/abstract_feature.rs")]
#[diplomat::include("src/gml/core/model/base/abstract_gml.rs")]
#[diplomat::include("src/gml/core/model/abstract_object.rs")]
pub mod ffi {
    use crate::citygml::core::model::core::refs::abstract_city_object_kind_ref::ffi::AbstractCityObjectKindRefIterator;

    /// A city model; mutable for `recompute_child_bounding_shapes`.
    #[diplomat::opaque_mut]
    pub struct CityModel(pub(crate) ecitygml::model::core::CityModel);

    impl CityModel {
        impl_gml_abstract_object_methods! {}
        impl_gml_abstract_gml_methods! {}
        impl_gml_abstract_feature_methods! {}
        impl_abstract_feature_methods! {}
        impl_abstract_feature_with_lifespan_methods! {}

        /// Lazily iterates over all features at any depth (Rust: `IterFeatures::iter_features`).
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn iter_features<'a>(&'a self) -> Box<crate::citygml::core::model::core::refs::abstract_feature_kind_ref::ffi::AbstractFeatureKindRefIterator<'a>>{
            Box::new(
                crate::citygml::core::model::core::refs::abstract_feature_kind_ref::ffi::AbstractFeatureKindRefIterator(
                    ecitygml::model::common::IterFeatures::iter_features(&self.0),
                ),
            )
        }

        /// Lazily iterates over all city objects at any depth, without the city model itself (Rust:
        /// `iter_city_objects`).
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn iter_city_objects<'a>(&'a self) -> Box<AbstractCityObjectKindRefIterator<'a>> {
            Box::new(AbstractCityObjectKindRefIterator(Box::new(
                self.0.iter_city_objects(),
            )))
        }

        /// Recomputes the bounding shape of every feature below the city model from its geometry.
        pub fn recompute_child_bounding_shapes(&mut self) {
            self.0.recompute_child_bounding_shapes();
        }

        /// Number of direct `cityObjectMember`s.
        pub fn city_objects_len(&self) -> usize {
            self.0.city_object_members_len()
        }
    }
}

pub use ffi::CityModel;
