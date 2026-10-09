//! Methods of egml's `AbstractFeature`, generated into the bridge of every feature type.
//!
//! Diplomat bridges have no inheritance and `diplomat-tool` expands macros in `impl` blocks only one
//! level deep, so each feature type invokes the macro of every abstract supertype itself (and
//! includes this file with `#[diplomat::include(...)]`, from which `diplomat-tool` reads the macro).

#[diplomat::macro_rules]
macro_rules! impl_gml_abstract_feature_methods {
    () => {
        /// The feature's bounding shape (`gml:boundedBy`), if it has one.
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn bounded_by<'a>(
            &'a self,
        ) -> Option<&'a crate::gml::core::model::feature::bounding_shape::ffi::BoundingShape> {
            egml::model::feature::AsAbstractFeature::bounded_by(&self.0)
                .map(crate::gml::core::model::feature::bounding_shape::ffi::BoundingShape::transparent_convert)
        }
    };
}
