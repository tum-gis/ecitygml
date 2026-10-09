//! Methods of ecitygml's `AbstractSpace`, generated into the bridge of every space type.
//!
//! Like all abstract-type macros (see `src/gml/core/model/feature/abstract_feature.rs`): each type invokes the
//! macro of every abstract supertype itself and includes this file with `#[diplomat::include(...)]`.
//! Not bound yet: volumes, areas, *_by_lod.

#[diplomat::macro_rules]
macro_rules! impl_abstract_space_methods {
    () => {
        pub fn space_type(
            &self,
        ) -> Option<crate::citygml::core::model::core::enums::space_type::ffi::SpaceType> {
            ecitygml::model::core::AsAbstractSpace::space_type(&self.0).map(Into::into)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn lod1_solid<'a>(
            &'a self,
        ) -> Option<&'a crate::gml::core::model::geometry::primitives::solid_property::ffi::SolidProperty> {
            ecitygml::model::core::AsAbstractSpace::lod1_solid(&self.0)
                .map(crate::gml::core::model::geometry::primitives::solid_property::ffi::SolidProperty::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn lod2_solid<'a>(
            &'a self,
        ) -> Option<&'a crate::gml::core::model::geometry::primitives::solid_property::ffi::SolidProperty> {
            ecitygml::model::core::AsAbstractSpace::lod2_solid(&self.0)
                .map(crate::gml::core::model::geometry::primitives::solid_property::ffi::SolidProperty::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn lod3_solid<'a>(
            &'a self,
        ) -> Option<&'a crate::gml::core::model::geometry::primitives::solid_property::ffi::SolidProperty> {
            ecitygml::model::core::AsAbstractSpace::lod3_solid(&self.0)
                .map(crate::gml::core::model::geometry::primitives::solid_property::ffi::SolidProperty::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn lod0_multi_surface<'a>(
            &'a self,
        ) -> Option<&'a crate::gml::core::model::geometry::aggregates::multi_surface_property::ffi::MultiSurfaceProperty> {
            ecitygml::model::core::AsAbstractSpace::lod0_multi_surface(&self.0)
                .map(crate::gml::core::model::geometry::aggregates::multi_surface_property::ffi::MultiSurfaceProperty::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn lod2_multi_surface<'a>(
            &'a self,
        ) -> Option<&'a crate::gml::core::model::geometry::aggregates::multi_surface_property::ffi::MultiSurfaceProperty> {
            ecitygml::model::core::AsAbstractSpace::lod2_multi_surface(&self.0)
                .map(crate::gml::core::model::geometry::aggregates::multi_surface_property::ffi::MultiSurfaceProperty::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn lod3_multi_surface<'a>(
            &'a self,
        ) -> Option<&'a crate::gml::core::model::geometry::aggregates::multi_surface_property::ffi::MultiSurfaceProperty> {
            ecitygml::model::core::AsAbstractSpace::lod3_multi_surface(&self.0)
                .map(crate::gml::core::model::geometry::aggregates::multi_surface_property::ffi::MultiSurfaceProperty::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn lod0_multi_curve<'a>(
            &'a self,
        ) -> Option<&'a crate::gml::core::model::geometry::aggregates::multi_curve_property::ffi::MultiCurveProperty> {
            ecitygml::model::core::AsAbstractSpace::lod0_multi_curve(&self.0)
                .map(crate::gml::core::model::geometry::aggregates::multi_curve_property::ffi::MultiCurveProperty::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn lod2_multi_curve<'a>(
            &'a self,
        ) -> Option<&'a crate::gml::core::model::geometry::aggregates::multi_curve_property::ffi::MultiCurveProperty> {
            ecitygml::model::core::AsAbstractSpace::lod2_multi_curve(&self.0)
                .map(crate::gml::core::model::geometry::aggregates::multi_curve_property::ffi::MultiCurveProperty::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn lod3_multi_curve<'a>(
            &'a self,
        ) -> Option<&'a crate::gml::core::model::geometry::aggregates::multi_curve_property::ffi::MultiCurveProperty> {
            ecitygml::model::core::AsAbstractSpace::lod3_multi_curve(&self.0)
                .map(crate::gml::core::model::geometry::aggregates::multi_curve_property::ffi::MultiCurveProperty::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn lod0_point<'a>(
            &'a self,
        ) -> Option<&'a crate::gml::core::model::geometry::primitives::point_property::ffi::PointProperty> {
            ecitygml::model::core::AsAbstractSpace::lod0_point(&self.0)
                .map(crate::gml::core::model::geometry::primitives::point_property::ffi::PointProperty::transparent_convert)
        }

        /// The space's boundaries (e.g. wall surfaces or traffic areas).
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn boundaries<'a>(
            &'a self,
        ) -> Box<crate::citygml::core::model::core::abstract_space_boundary_property::ffi::AbstractSpaceBoundaryPropertyIterator<'a>> {
            Box::new(
                crate::citygml::core::model::core::abstract_space_boundary_property::ffi::AbstractSpaceBoundaryPropertyIterator(
                    ecitygml::model::core::AsAbstractSpace::boundaries(&self.0).iter(),
                ),
            )
        }
    };
}
