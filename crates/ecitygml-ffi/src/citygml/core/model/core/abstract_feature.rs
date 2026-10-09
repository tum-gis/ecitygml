//! Methods of ecitygml's `AbstractFeature`, generated into the bridge of every feature type.
//!
//! Like all abstract-type macros (see `src/gml/core/model/feature/abstract_feature.rs`): each type invokes the
//! macro of every abstract supertype itself and includes this file with `#[diplomat::include(...)]`.

#[diplomat::macro_rules]
macro_rules! impl_abstract_feature_methods {
    () => {
        /// The feature's `gml:id`.
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn feature_id<'a>(&'a self) -> &'a crate::gml::core::model::base::id::ffi::Id {
            crate::gml::core::model::base::id::ffi::Id::transparent_convert(
                ecitygml::model::core::AsAbstractFeature::feature_id(&self.0),
            )
        }
    };
}
