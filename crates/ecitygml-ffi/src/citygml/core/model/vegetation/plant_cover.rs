//! `PlantCover`, mirroring `ecitygml::model::vegetation::PlantCover`.

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

    /// A plant cover (an area covered by vegetation), borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct PlantCover(ecitygml::model::vegetation::PlantCover);

    impl PlantCover {
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

        /// The feature as a plant cover, or none if it is another type (Rust: `<&PlantCover>::try_from`).
        pub fn try_from<'a>(feature: &AbstractFeatureKindRef<'a>) -> Option<&'a PlantCover> {
            <&ecitygml::model::vegetation::PlantCover>::try_from(feature.0)
                .ok()
                .map(PlantCover::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn class<'a>(&'a self) -> Option<&'a crate::citygml::core::model::vegetation::values::plant_cover_class_value::ffi::PlantCoverClassValue>{
            self.0.class().map(crate::citygml::core::model::vegetation::values::plant_cover_class_value::ffi::PlantCoverClassValue::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn functions<'a>(&'a self) -> Box<crate::citygml::core::model::vegetation::values::plant_cover_function_value::ffi::PlantCoverFunctionValueIterator<'a>>{
            Box::new(crate::citygml::core::model::vegetation::values::plant_cover_function_value::ffi::PlantCoverFunctionValueIterator(self.0.functions().iter()))
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn usages<'a>(&'a self) -> Box<crate::citygml::core::model::vegetation::values::plant_cover_usage_value::ffi::PlantCoverUsageValueIterator<'a>>{
            Box::new(crate::citygml::core::model::vegetation::values::plant_cover_usage_value::ffi::PlantCoverUsageValueIterator(self.0.usages().iter()))
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn average_height<'a>(&'a self) -> Option<&'a Measure> {
            self.0.average_height().map(Measure::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn min_height<'a>(&'a self) -> Option<&'a Measure> {
            self.0.min_height().map(Measure::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn max_height<'a>(&'a self) -> Option<&'a Measure> {
            self.0.max_height().map(Measure::transparent_convert)
        }
    }
}

pub use ffi::PlantCover;
