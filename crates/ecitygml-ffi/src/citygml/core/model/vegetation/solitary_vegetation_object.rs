//! `SolitaryVegetationObject`, mirroring `ecitygml::model::vegetation::SolitaryVegetationObject`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/vegetation/abstract_vegetation_object.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_occupied_space.rs")]
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
    use crate::gml::core::model::basic_types::measure::ffi::Measure;

    /// A solitary vegetation object (e.g. a tree), borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct SolitaryVegetationObject(ecitygml::model::vegetation::SolitaryVegetationObject);

    impl SolitaryVegetationObject {
        impl_gml_abstract_object_methods! {}
        impl_gml_abstract_gml_methods! {}
        impl_gml_abstract_feature_methods! {}
        impl_abstract_feature_methods! {}
        impl_abstract_feature_with_lifespan_methods! {}
        impl_abstract_city_object_methods! {}
        impl_abstract_space_methods! {}
        impl_abstract_physical_space_methods! {}
        impl_abstract_occupied_space_methods! {}
        impl_abstract_vegetation_object_methods! {}

        /// The feature as a solitary vegetation object, or none if it is another type (Rust: `<&SolitaryVegetationObject>::try_from`).
        pub fn try_from<'a>(
            feature: &AbstractFeatureKindRef<'a>,
        ) -> Option<&'a SolitaryVegetationObject> {
            <&ecitygml::model::vegetation::SolitaryVegetationObject>::try_from(feature.0)
                .ok()
                .map(SolitaryVegetationObject::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        #[diplomat::attr(dart, rename = "classifier")] // `class` is reserved in Dart, which has no escaping
        pub fn class<'a>(&'a self) -> Option<&'a crate::citygml::core::model::vegetation::values::solitary_vegetation_object_class_value::ffi::SolitaryVegetationObjectClassValue>{
            self.0.class().map(crate::citygml::core::model::vegetation::values::solitary_vegetation_object_class_value::ffi::SolitaryVegetationObjectClassValue::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn functions<'a>(&'a self) -> Box<crate::citygml::core::model::vegetation::values::solitary_vegetation_object_function_value::ffi::SolitaryVegetationObjectFunctionValueIterator<'a>>{
            Box::new(crate::citygml::core::model::vegetation::values::solitary_vegetation_object_function_value::ffi::SolitaryVegetationObjectFunctionValueIterator(self.0.functions().iter()))
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn usages<'a>(&'a self) -> Box<crate::citygml::core::model::vegetation::values::solitary_vegetation_object_usage_value::ffi::SolitaryVegetationObjectUsageValueIterator<'a>>{
            Box::new(crate::citygml::core::model::vegetation::values::solitary_vegetation_object_usage_value::ffi::SolitaryVegetationObjectUsageValueIterator(self.0.usages().iter()))
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn species<'a>(
            &'a self,
        ) -> Option<
            &'a crate::citygml::core::model::vegetation::values::species_value::ffi::SpeciesValue,
        > {
            self.0
                .species()
                .map(crate::citygml::core::model::vegetation::values::species_value::ffi::SpeciesValue::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn height<'a>(&'a self) -> Option<&'a Measure> {
            self.0.height().map(Measure::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn trunk_diameter<'a>(&'a self) -> Option<&'a Measure> {
            self.0.trunk_diameter().map(Measure::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn crown_diameter<'a>(&'a self) -> Option<&'a Measure> {
            self.0.crown_diameter().map(Measure::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn root_ball_diameter<'a>(&'a self) -> Option<&'a Measure> {
            self.0
                .root_ball_diameter()
                .map(Measure::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn max_root_ball_depth<'a>(&'a self) -> Option<&'a Measure> {
            self.0
                .max_root_ball_depth()
                .map(Measure::transparent_convert)
        }
    }
}

pub use ffi::SolitaryVegetationObject;
