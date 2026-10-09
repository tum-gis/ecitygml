//! Methods of ecitygml's `AbstractPhysicalSpace`, generated into the bridge of every physical space type.
//!
//! Like all abstract-type macros (see `src/gml/core/model/feature/abstract_feature.rs`): each type invokes the
//! macro of every abstract supertype itself and includes this file with `#[diplomat::include(...)]`.
//! Not bound yet: point_cloud.

#[diplomat::macro_rules]
macro_rules! impl_abstract_physical_space_methods {
    () => {
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn lod1_terrain_intersection_curve<'a>(&'a self) -> Option<&'a crate::gml::core::model::geometry::aggregates::multi_curve_property::ffi::MultiCurveProperty> {
            ecitygml::model::core::AsAbstractPhysicalSpace::lod1_terrain_intersection_curve(&self.0)
                .map(crate::gml::core::model::geometry::aggregates::multi_curve_property::ffi::MultiCurveProperty::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn lod2_terrain_intersection_curve<'a>(&'a self) -> Option<&'a crate::gml::core::model::geometry::aggregates::multi_curve_property::ffi::MultiCurveProperty> {
            ecitygml::model::core::AsAbstractPhysicalSpace::lod2_terrain_intersection_curve(&self.0)
                .map(crate::gml::core::model::geometry::aggregates::multi_curve_property::ffi::MultiCurveProperty::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn lod3_terrain_intersection_curve<'a>(&'a self) -> Option<&'a crate::gml::core::model::geometry::aggregates::multi_curve_property::ffi::MultiCurveProperty> {
            ecitygml::model::core::AsAbstractPhysicalSpace::lod3_terrain_intersection_curve(&self.0)
                .map(crate::gml::core::model::geometry::aggregates::multi_curve_property::ffi::MultiCurveProperty::transparent_convert)
        }
    };
}
