//! Methods of egml's `AbstractGml`, generated into the bridge of every GML object type (features
//! and geometries).
//!
//! Like all abstract-type macros (see `src/gml/core/model/feature/abstract_feature.rs`): each type invokes the
//! macro of every abstract supertype itself and includes this file with `#[diplomat::include(...)]`.

#[diplomat::macro_rules]
macro_rules! impl_gml_abstract_gml_methods {
    () => {
        /// The object's `gml:id`, if it has one.
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn id<'a>(&'a self) -> Option<&'a crate::gml::core::model::base::id::ffi::Id> {
            egml::model::base::AsAbstractGml::id(&self.0)
                .map(crate::gml::core::model::base::id::ffi::Id::transparent_convert)
        }

        /// The object's `gml:name`s.
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn names<'a>(
            &'a self,
        ) -> Box<crate::gml::core::model::basic_types::code::ffi::CodeIterator<'a>> {
            Box::new(
                crate::gml::core::model::basic_types::code::ffi::CodeIterator(
                    egml::model::base::AsAbstractGml::names(&self.0).iter(),
                ),
            )
        }
    };
}
