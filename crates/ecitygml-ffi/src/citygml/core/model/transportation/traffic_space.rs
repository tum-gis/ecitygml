//! `TrafficSpace`, mirroring `ecitygml::model::transportation::TrafficSpace`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
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
    use crate::citygml::core::model::core::occupancy::ffi::OccupancyIterator;
    use crate::citygml::core::model::core::refs::abstract_feature_kind_ref::ffi::AbstractFeatureKindRef;
    use crate::citygml::core::model::transportation::enums::granularity_value::ffi::GranularityValue;
    use crate::citygml::core::model::transportation::enums::traffic_direction_value::ffi::TrafficDirectionValue;
    use crate::citygml::core::model::transportation::values::traffic_space_class_value::ffi::TrafficSpaceClassValue;
    use crate::citygml::core::model::transportation::values::traffic_space_function_value::ffi::TrafficSpaceFunctionValueIterator;
    use crate::citygml::core::model::transportation::values::traffic_space_usage_value::ffi::TrafficSpaceUsageValueIterator;

    /// A traffic space, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct TrafficSpace(ecitygml::model::transportation::TrafficSpace);

    impl TrafficSpace {
        impl_gml_abstract_object_methods! {}
        impl_gml_abstract_gml_methods! {}
        impl_gml_abstract_feature_methods! {}
        impl_abstract_feature_methods! {}
        impl_abstract_feature_with_lifespan_methods! {}
        impl_abstract_city_object_methods! {}
        impl_abstract_space_methods! {}
        impl_abstract_physical_space_methods! {}
        impl_abstract_unoccupied_space_methods! {}

        /// The feature as a traffic space, or none if it is another type (Rust: `<&TrafficSpace>::try_from`).
        pub fn try_from<'a>(feature: &AbstractFeatureKindRef<'a>) -> Option<&'a TrafficSpace> {
            <&ecitygml::model::transportation::TrafficSpace>::try_from(feature.0)
                .ok()
                .map(TrafficSpace::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn class<'a>(&'a self) -> Option<&'a TrafficSpaceClassValue> {
            self.0
                .class()
                .map(TrafficSpaceClassValue::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn functions<'a>(&'a self) -> Box<TrafficSpaceFunctionValueIterator<'a>> {
            Box::new(TrafficSpaceFunctionValueIterator(self.0.functions().iter()))
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn usages<'a>(&'a self) -> Box<TrafficSpaceUsageValueIterator<'a>> {
            Box::new(TrafficSpaceUsageValueIterator(self.0.usages().iter()))
        }

        /// Returned by value (Rust: `&GranularityValue`), as Diplomat enums are values.
        pub fn granularity(&self) -> GranularityValue {
            (*self.0.granularity()).into()
        }

        pub fn traffic_direction(&self) -> Option<TrafficDirectionValue> {
            self.0.traffic_direction().map(Into::into)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn occupancies<'a>(&'a self) -> Box<OccupancyIterator<'a>> {
            Box::new(OccupancyIterator(self.0.occupancies().iter()))
        }
    }
}

pub use ffi::TrafficSpace;
