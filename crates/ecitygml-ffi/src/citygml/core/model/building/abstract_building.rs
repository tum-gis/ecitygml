//! Methods of ecitygml's `AbstractBuilding`, generated into the bridge of every building type.
//!
//! Like all abstract-type macros (see `src/gml/core/model/feature/abstract_feature.rs`): each type invokes the
//! macro of every abstract supertype itself and includes this file with `#[diplomat::include(...)]`.
//! Not bound yet: building_constructive_elements, building_installations, building_rooms,
//! addresses.

#[diplomat::macro_rules]
macro_rules! impl_abstract_building_methods {
    () => {
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn class<'a>(
            &'a self,
        ) -> Option<&'a crate::citygml::core::model::building::values::building_class_value::ffi::BuildingClassValue> {
            ecitygml::model::building::AsAbstractBuilding::class(&self.0)
                .map(crate::citygml::core::model::building::values::building_class_value::ffi::BuildingClassValue::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn functions<'a>(
            &'a self,
        ) -> Box<crate::citygml::core::model::building::values::building_function_value::ffi::BuildingFunctionValueIterator<'a>> {
            Box::new(crate::citygml::core::model::building::values::building_function_value::ffi::BuildingFunctionValueIterator(
                ecitygml::model::building::AsAbstractBuilding::functions(&self.0).iter(),
            ))
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn usages<'a>(
            &'a self,
        ) -> Box<crate::citygml::core::model::building::values::building_usage_value::ffi::BuildingUsageValueIterator<'a>> {
            Box::new(crate::citygml::core::model::building::values::building_usage_value::ffi::BuildingUsageValueIterator(
                ecitygml::model::building::AsAbstractBuilding::usages(&self.0).iter(),
            ))
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn roof_type<'a>(
            &'a self,
        ) -> Option<&'a crate::citygml::core::model::building::values::roof_type_value::ffi::RoofTypeValue> {
            ecitygml::model::building::AsAbstractBuilding::roof_type(&self.0)
                .map(crate::citygml::core::model::building::values::roof_type_value::ffi::RoofTypeValue::transparent_convert)
        }

        pub fn storeys_above_ground(&self) -> Option<i64> {
            ecitygml::model::building::AsAbstractBuilding::storeys_above_ground(&self.0)
        }

        pub fn storeys_below_ground(&self) -> Option<i64> {
            ecitygml::model::building::AsAbstractBuilding::storeys_below_ground(&self.0)
        }

        /// The storeys and building units (`buildingSubdivision`).
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn building_subdivisions<'a>(
            &'a self,
        ) -> Box<crate::citygml::core::model::building::abstract_building_subdivision_property::ffi::AbstractBuildingSubdivisionPropertyIterator<'a>> {
            Box::new(
                crate::citygml::core::model::building::abstract_building_subdivision_property::ffi::AbstractBuildingSubdivisionPropertyIterator(
                    ecitygml::model::building::AsAbstractBuilding::building_subdivisions(&self.0).iter(),
                ),
            )
        }
    };
}
