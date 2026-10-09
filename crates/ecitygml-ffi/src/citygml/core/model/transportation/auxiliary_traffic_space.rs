//! `AuxiliaryTrafficSpace`, mirroring `ecitygml::model::transportation::AuxiliaryTrafficSpace`.

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
    use crate::citygml::core::model::core::refs::abstract_feature_kind_ref::ffi::AbstractFeatureKindRef;
    use crate::citygml::core::model::transportation::enums::granularity_value::ffi::GranularityValue;
    use crate::citygml::core::model::transportation::values::auxiliary_traffic_space_class_value::ffi::AuxiliaryTrafficSpaceClassValue;
    use crate::citygml::core::model::transportation::values::auxiliary_traffic_space_function_value::ffi::AuxiliaryTrafficSpaceFunctionValueIterator;
    use crate::citygml::core::model::transportation::values::auxiliary_traffic_space_usage_value::ffi::AuxiliaryTrafficSpaceUsageValueIterator;

    /// An auxiliary traffic space, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct AuxiliaryTrafficSpace(ecitygml::model::transportation::AuxiliaryTrafficSpace);

    impl AuxiliaryTrafficSpace {
        impl_gml_abstract_object_methods! {}
        impl_gml_abstract_gml_methods! {}
        impl_gml_abstract_feature_methods! {}
        impl_abstract_feature_methods! {}
        impl_abstract_feature_with_lifespan_methods! {}
        impl_abstract_city_object_methods! {}
        impl_abstract_space_methods! {}
        impl_abstract_physical_space_methods! {}
        impl_abstract_unoccupied_space_methods! {}

        /// The feature as an auxiliary traffic space, or none if it is another type (Rust: `<&AuxiliaryTrafficSpace>::try_from`).
        pub fn try_from<'a>(
            feature: &AbstractFeatureKindRef<'a>,
        ) -> Option<&'a AuxiliaryTrafficSpace> {
            <&ecitygml::model::transportation::AuxiliaryTrafficSpace>::try_from(feature.0)
                .ok()
                .map(AuxiliaryTrafficSpace::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn class<'a>(&'a self) -> Option<&'a AuxiliaryTrafficSpaceClassValue> {
            self.0
                .class()
                .map(AuxiliaryTrafficSpaceClassValue::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn functions<'a>(&'a self) -> Box<AuxiliaryTrafficSpaceFunctionValueIterator<'a>> {
            Box::new(AuxiliaryTrafficSpaceFunctionValueIterator(
                self.0.functions().iter(),
            ))
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn usages<'a>(&'a self) -> Box<AuxiliaryTrafficSpaceUsageValueIterator<'a>> {
            Box::new(AuxiliaryTrafficSpaceUsageValueIterator(
                self.0.usages().iter(),
            ))
        }

        /// Returned by value (Rust: `&GranularityValue`), as Diplomat enums are values.
        pub fn granularity(&self) -> GranularityValue {
            (*self.0.granularity()).into()
        }
    }
}

pub use ffi::AuxiliaryTrafficSpace;
