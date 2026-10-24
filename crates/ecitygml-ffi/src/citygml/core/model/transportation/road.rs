//! `Road`, mirroring `ecitygml::model::transportation::Road`.

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
    use crate::citygml::core::model::transportation::intersection_property::ffi::IntersectionPropertyIterator;
    use crate::citygml::core::model::transportation::section_property::ffi::SectionPropertyIterator;
    use crate::citygml::core::model::transportation::values::road_class_value::ffi::RoadClassValue;
    use crate::citygml::core::model::transportation::values::road_function_value::ffi::RoadFunctionValueIterator;
    use crate::citygml::core::model::transportation::values::road_usage_value::ffi::RoadUsageValueIterator;

    /// A road, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct Road(ecitygml::model::transportation::Road);

    impl Road {
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

        /// The feature as a road, or none if it is another type (Rust: `<&Road>::try_from`).
        pub fn try_from<'a>(feature: &AbstractFeatureKindRef<'a>) -> Option<&'a Road> {
            <&ecitygml::model::transportation::Road>::try_from(feature.0)
                .ok()
                .map(Road::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        #[diplomat::attr(dart, rename = "classifier")] // `class` is reserved in Dart, which has no escaping
        pub fn class<'a>(&'a self) -> Option<&'a RoadClassValue> {
            self.0.class().map(RoadClassValue::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn functions<'a>(&'a self) -> Box<RoadFunctionValueIterator<'a>> {
            Box::new(RoadFunctionValueIterator(self.0.functions().iter()))
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn usages<'a>(&'a self) -> Box<RoadUsageValueIterator<'a>> {
            Box::new(RoadUsageValueIterator(self.0.usages().iter()))
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn sections<'a>(&'a self) -> Box<SectionPropertyIterator<'a>> {
            Box::new(SectionPropertyIterator(self.0.sections().iter()))
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn intersections<'a>(&'a self) -> Box<IntersectionPropertyIterator<'a>> {
            Box::new(IntersectionPropertyIterator(self.0.intersections().iter()))
        }
    }
}

pub use ffi::Road;
