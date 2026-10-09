//! Methods of ecitygml's `AbstractCityObject`, generated into the bridge of every city object type.
//!
//! Like all abstract-type macros (see `src/gml/core/model/feature/abstract_feature.rs`): each type invokes the
//! macro of every abstract supertype itself and includes this file with `#[diplomat::include(...)]`.
//! Not bound yet: appearances.

#[diplomat::macro_rules]
macro_rules! impl_abstract_city_object_methods {
    () => {
        pub fn relative_to_terrain(
            &self,
        ) -> Option<crate::citygml::core::model::core::enums::relative_to_terrain::ffi::RelativeToTerrain> {
            ecitygml::model::core::AsAbstractCityObject::relative_to_terrain(&self.0)
                .map(Into::into)
        }

        pub fn relative_to_water(
            &self,
        ) -> Option<crate::citygml::core::model::core::enums::relative_to_water::ffi::RelativeToWater> {
            ecitygml::model::core::AsAbstractCityObject::relative_to_water(&self.0).map(Into::into)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn external_references<'a>(
            &'a self,
        ) -> Box<crate::citygml::core::model::core::external_reference::ffi::ExternalReferenceIterator<'a>> {
            Box::new(crate::citygml::core::model::core::external_reference::ffi::ExternalReferenceIterator(
                ecitygml::model::core::AsAbstractCityObject::external_references(&self.0).iter(),
            ))
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn generic_attributes<'a>(
            &'a self,
        ) -> Box<crate::citygml::core::model::generics::generic_attribute_kind::ffi::GenericAttributeKindIterator<'a>> {
            Box::new(crate::citygml::core::model::generics::generic_attribute_kind::ffi::GenericAttributeKindIterator(
                ecitygml::model::core::AsAbstractCityObject::generic_attributes(&self.0).iter(),
            ))
        }

        /// Relations to other city objects (`relatedTo`).
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn related_to<'a>(
            &'a self,
        ) -> Box<crate::citygml::core::model::core::city_object_relation_property::ffi::CityObjectRelationPropertyIterator<'a>> {
            Box::new(crate::citygml::core::model::core::city_object_relation_property::ffi::CityObjectRelationPropertyIterator(
                ecitygml::model::core::AsAbstractCityObject::related_to(&self.0).iter(),
            ))
        }
    };
}
