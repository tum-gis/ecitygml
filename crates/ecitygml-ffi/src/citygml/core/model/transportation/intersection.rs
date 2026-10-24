//! `Intersection`, mirroring `ecitygml::model::transportation::Intersection`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/transportation/abstract_transportation_space.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_unoccupied_space.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_physical_space.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_space.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_city_object.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_feature_with_lifespan.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_feature.rs")]
#[diplomat::include("src/gml/core/model/feature/abstract_feature.rs")]
#[diplomat::include("src/gml/core/model/base/abstract_gml.rs")]
#[diplomat::include("src/gml/core/model/abstract_object.rs")]
pub mod ffi {
    use crate::citygml::core::model::core::refs::abstract_feature_kind_ref::ffi::AbstractFeatureKindRef;
    use crate::citygml::core::model::transportation::values::intersection_class_value::ffi::IntersectionClassValue;

    /// A intersection, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct Intersection(ecitygml::model::transportation::Intersection);

    impl Intersection {
        impl_gml_abstract_object_methods! {}
        impl_gml_abstract_gml_methods! {}
        impl_gml_abstract_feature_methods! {}
        impl_abstract_feature_methods! {}
        impl_abstract_feature_with_lifespan_methods! {}
        impl_abstract_city_object_methods! {}
        impl_abstract_space_methods! {}
        impl_abstract_physical_space_methods! {}
        impl_abstract_unoccupied_space_methods! {}
        impl_abstract_transportation_space_methods! {}

        /// The feature as a intersection, or none if it is another type (Rust: `<&Intersection>::try_from`).
        pub fn try_from<'a>(feature: &AbstractFeatureKindRef<'a>) -> Option<&'a Intersection> {
            <&ecitygml::model::transportation::Intersection>::try_from(feature.0)
                .ok()
                .map(Intersection::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        #[diplomat::attr(dart, rename = "classifier")] // `class` is reserved in Dart, which has no escaping
        pub fn class<'a>(&'a self) -> Option<&'a IntersectionClassValue> {
            self.0
                .class()
                .map(IntersectionClassValue::transparent_convert)
        }
    }
}

pub use ffi::Intersection;
