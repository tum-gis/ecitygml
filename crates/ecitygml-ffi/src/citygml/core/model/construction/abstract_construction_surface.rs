//! Methods of ecitygml's `AbstractConstructionSurface`, generated into the bridge of every construction surface type.
//!
//! Like all abstract-type macros (see `src/gml/core/model/feature/abstract_feature.rs`): each type invokes the
//! macro of every abstract supertype itself and includes this file with `#[diplomat::include(...)]`.

#[diplomat::macro_rules]
macro_rules! impl_abstract_construction_surface_methods {
    () => {
        /// The door and window surfaces in this surface (`con:fillingSurface`).
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn filling_surfaces<'a>(
            &'a self,
        ) -> Box<crate::citygml::core::model::construction::abstract_filling_surface_property::ffi::AbstractFillingSurfacePropertyIterator<'a>> {
            Box::new(
                crate::citygml::core::model::construction::abstract_filling_surface_property::ffi::AbstractFillingSurfacePropertyIterator(
                    ecitygml::model::construction::AsAbstractConstructionSurface::filling_surfaces(&self.0).iter(),
                ),
            )
        }
    };
}
