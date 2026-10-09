//! Methods of ecitygml's `AbstractThematicSurface`, generated into the bridge of every thematic surface type.
//!
//! Like all abstract-type macros (see `src/gml/core/model/feature/abstract_feature.rs`): each type invokes the
//! macro of every abstract supertype itself and includes this file with `#[diplomat::include(...)]`.
//! Not bound yet: areas, point_cloud, multi_surfaces_by_lod.

#[diplomat::macro_rules]
macro_rules! impl_abstract_thematic_surface_methods {
    () => {
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn lod0_multi_curve<'a>(
            &'a self,
        ) -> Option<&'a crate::gml::core::model::geometry::aggregates::multi_curve_property::ffi::MultiCurveProperty> {
            ecitygml::model::core::AsAbstractThematicSurface::lod0_multi_curve(&self.0)
                .map(crate::gml::core::model::geometry::aggregates::multi_curve_property::ffi::MultiCurveProperty::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn lod0_multi_surface<'a>(
            &'a self,
        ) -> Option<&'a crate::gml::core::model::geometry::aggregates::multi_surface_property::ffi::MultiSurfaceProperty> {
            ecitygml::model::core::AsAbstractThematicSurface::lod0_multi_surface(&self.0)
                .map(crate::gml::core::model::geometry::aggregates::multi_surface_property::ffi::MultiSurfaceProperty::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn lod1_multi_surface<'a>(
            &'a self,
        ) -> Option<&'a crate::gml::core::model::geometry::aggregates::multi_surface_property::ffi::MultiSurfaceProperty> {
            ecitygml::model::core::AsAbstractThematicSurface::lod1_multi_surface(&self.0)
                .map(crate::gml::core::model::geometry::aggregates::multi_surface_property::ffi::MultiSurfaceProperty::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn lod2_multi_surface<'a>(
            &'a self,
        ) -> Option<&'a crate::gml::core::model::geometry::aggregates::multi_surface_property::ffi::MultiSurfaceProperty> {
            ecitygml::model::core::AsAbstractThematicSurface::lod2_multi_surface(&self.0)
                .map(crate::gml::core::model::geometry::aggregates::multi_surface_property::ffi::MultiSurfaceProperty::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn lod3_multi_surface<'a>(
            &'a self,
        ) -> Option<&'a crate::gml::core::model::geometry::aggregates::multi_surface_property::ffi::MultiSurfaceProperty> {
            ecitygml::model::core::AsAbstractThematicSurface::lod3_multi_surface(&self.0)
                .map(crate::gml::core::model::geometry::aggregates::multi_surface_property::ffi::MultiSurfaceProperty::transparent_convert)
        }
    };
}
