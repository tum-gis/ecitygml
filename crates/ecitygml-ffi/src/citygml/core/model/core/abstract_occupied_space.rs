//! Methods of ecitygml's `AbstractOccupiedSpace`, generated into the bridge of every occupied space type.
//!
//! Like all abstract-type macros (see `src/gml/core/model/feature/abstract_feature.rs`): each type invokes the
//! macro of every abstract supertype itself and includes this file with `#[diplomat::include(...)]`.
//! Not bound yet: implicit_representations_by_lod.

#[diplomat::macro_rules]
macro_rules! impl_abstract_occupied_space_methods {
    () => {
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn lod1_implicit_representation<'a>(&'a self) -> Option<&'a crate::citygml::core::model::core::implicit_geometry_property::ffi::ImplicitGeometryProperty> {
            ecitygml::model::core::AsAbstractOccupiedSpace::lod1_implicit_representation(&self.0)
                .map(crate::citygml::core::model::core::implicit_geometry_property::ffi::ImplicitGeometryProperty::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn lod2_implicit_representation<'a>(&'a self) -> Option<&'a crate::citygml::core::model::core::implicit_geometry_property::ffi::ImplicitGeometryProperty> {
            ecitygml::model::core::AsAbstractOccupiedSpace::lod2_implicit_representation(&self.0)
                .map(crate::citygml::core::model::core::implicit_geometry_property::ffi::ImplicitGeometryProperty::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn lod3_implicit_representation<'a>(&'a self) -> Option<&'a crate::citygml::core::model::core::implicit_geometry_property::ffi::ImplicitGeometryProperty> {
            ecitygml::model::core::AsAbstractOccupiedSpace::lod3_implicit_representation(&self.0)
                .map(crate::citygml::core::model::core::implicit_geometry_property::ffi::ImplicitGeometryProperty::transparent_convert)
        }
    };
}
