//! Methods of ecitygml's `AbstractFeatureWithLifespan`, generated into the bridge of every feature type
//! that derives from it.
//!
//! Like all abstract-type macros (see `src/gml/core/model/feature/abstract_feature.rs`): each type invokes the
//! macro of every abstract supertype itself and includes this file with `#[diplomat::include(...)]`.

#[diplomat::macro_rules]
macro_rules! impl_abstract_feature_with_lifespan_methods {
    () => {
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn creation_date<'a>(
            &'a self,
        ) -> Option<&'a crate::gml::core::model::xs::date_time::ffi::DateTime> {
            ecitygml::model::core::AsAbstractFeatureWithLifespan::creation_date(&self.0)
                .map(crate::gml::core::model::xs::date_time::ffi::DateTime::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn termination_date<'a>(
            &'a self,
        ) -> Option<&'a crate::gml::core::model::xs::date_time::ffi::DateTime> {
            ecitygml::model::core::AsAbstractFeatureWithLifespan::termination_date(&self.0)
                .map(crate::gml::core::model::xs::date_time::ffi::DateTime::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn valid_from<'a>(
            &'a self,
        ) -> Option<&'a crate::gml::core::model::xs::date_time::ffi::DateTime> {
            ecitygml::model::core::AsAbstractFeatureWithLifespan::valid_from(&self.0)
                .map(crate::gml::core::model::xs::date_time::ffi::DateTime::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn valid_to<'a>(
            &'a self,
        ) -> Option<&'a crate::gml::core::model::xs::date_time::ffi::DateTime> {
            ecitygml::model::core::AsAbstractFeatureWithLifespan::valid_to(&self.0)
                .map(crate::gml::core::model::xs::date_time::ffi::DateTime::transparent_convert)
        }
    };
}
