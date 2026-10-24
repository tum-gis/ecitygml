//! Methods of ecitygml's `AbstractBuildingSubdivision`, generated into the bridge of every building subdivision type.
//!
//! Like all abstract-type macros (see `src/gml/core/model/feature/abstract_feature.rs`): each type invokes the
//! macro of every abstract supertype itself and includes this file with `#[diplomat::include(...)]`.
//! Not bound yet: elevations, sort_key, building_constructive_elements, building_furniture,
//! building_installations, building_rooms.

#[diplomat::macro_rules]
macro_rules! impl_abstract_building_subdivision_methods {
    () => {
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        #[diplomat::attr(dart, rename = "classifier")] // `class` is reserved in Dart, which has no escaping
        pub fn class<'a>(
            &'a self,
        ) -> Option<&'a crate::citygml::core::model::building::values::building_subdivision_class_value::ffi::BuildingSubdivisionClassValue> {
            ecitygml::model::building::AsAbstractBuildingSubdivision::class(&self.0)
                .map(crate::citygml::core::model::building::values::building_subdivision_class_value::ffi::BuildingSubdivisionClassValue::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn functions<'a>(
            &'a self,
        ) -> Box<crate::citygml::core::model::building::values::building_subdivision_function_value::ffi::BuildingSubdivisionFunctionValueIterator<'a>> {
            Box::new(crate::citygml::core::model::building::values::building_subdivision_function_value::ffi::BuildingSubdivisionFunctionValueIterator(
                ecitygml::model::building::AsAbstractBuildingSubdivision::functions(&self.0).iter(),
            ))
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn usages<'a>(
            &'a self,
        ) -> Box<crate::citygml::core::model::building::values::building_subdivision_usage_value::ffi::BuildingSubdivisionUsageValueIterator<'a>> {
            Box::new(crate::citygml::core::model::building::values::building_subdivision_usage_value::ffi::BuildingSubdivisionUsageValueIterator(
                ecitygml::model::building::AsAbstractBuildingSubdivision::usages(&self.0).iter(),
            ))
        }
    };
}
