//! `CityFurniture`, mirroring `ecitygml::model::city_furniture::CityFurniture`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
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

    /// A city furniture object (e.g. a traffic sign or bench), borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct CityFurniture(ecitygml::model::city_furniture::CityFurniture);

    impl CityFurniture {
        impl_gml_abstract_object_methods! {}
        impl_gml_abstract_gml_methods! {}
        impl_gml_abstract_feature_methods! {}
        impl_abstract_feature_methods! {}
        impl_abstract_feature_with_lifespan_methods! {}
        impl_abstract_city_object_methods! {}
        impl_abstract_space_methods! {}
        impl_abstract_physical_space_methods! {}
        impl_abstract_occupied_space_methods! {}

        /// The feature as a city furniture, or none if it is another type (Rust: `<&CityFurniture>::try_from`).
        pub fn try_from<'a>(feature: &AbstractFeatureKindRef<'a>) -> Option<&'a CityFurniture> {
            <&ecitygml::model::city_furniture::CityFurniture>::try_from(feature.0)
                .ok()
                .map(CityFurniture::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn class<'a>(&'a self) -> Option<&'a crate::citygml::core::model::city_furniture::values::city_furniture_class_value::ffi::CityFurnitureClassValue>{
            self.0.class().map(crate::citygml::core::model::city_furniture::values::city_furniture_class_value::ffi::CityFurnitureClassValue::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn functions<'a>(&'a self) -> Box<crate::citygml::core::model::city_furniture::values::city_furniture_function_value::ffi::CityFurnitureFunctionValueIterator<'a>>{
            Box::new(crate::citygml::core::model::city_furniture::values::city_furniture_function_value::ffi::CityFurnitureFunctionValueIterator(self.0.functions().iter()))
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn usages<'a>(&'a self) -> Box<crate::citygml::core::model::city_furniture::values::city_furniture_usage_value::ffi::CityFurnitureUsageValueIterator<'a>>{
            Box::new(crate::citygml::core::model::city_furniture::values::city_furniture_usage_value::ffi::CityFurnitureUsageValueIterator(self.0.usages().iter()))
        }
    }
}

pub use ffi::CityFurniture;
