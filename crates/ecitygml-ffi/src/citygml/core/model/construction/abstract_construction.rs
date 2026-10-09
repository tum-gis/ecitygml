//! Methods of ecitygml's `AbstractConstruction`, generated into the bridge of every construction type.
//!
//! Like all abstract-type macros (see `src/gml/core/model/feature/abstract_feature.rs`): each type invokes the
//! macro of every abstract supertype itself and includes this file with `#[diplomat::include(...)]`.

#[diplomat::macro_rules]
macro_rules! impl_abstract_construction_methods {
    () => {
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn date_of_construction<'a>(
            &'a self,
        ) -> Option<&'a crate::gml::core::model::xs::date::ffi::Date> {
            ecitygml::model::construction::AsAbstractConstruction::date_of_construction(&self.0)
                .map(crate::gml::core::model::xs::date::ffi::Date::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn date_of_demolition<'a>(
            &'a self,
        ) -> Option<&'a crate::gml::core::model::xs::date::ffi::Date> {
            ecitygml::model::construction::AsAbstractConstruction::date_of_demolition(&self.0)
                .map(crate::gml::core::model::xs::date::ffi::Date::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn heights<'a>(
            &'a self,
        ) -> Box<crate::citygml::core::model::construction::height::ffi::HeightIterator<'a>> {
            Box::new(
                crate::citygml::core::model::construction::height::ffi::HeightIterator(
                    ecitygml::model::construction::AsAbstractConstruction::heights(&self.0).iter(),
                ),
            )
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn occupancies<'a>(
            &'a self,
        ) -> Box<crate::citygml::core::model::core::occupancy::ffi::OccupancyIterator<'a>> {
            Box::new(
                crate::citygml::core::model::core::occupancy::ffi::OccupancyIterator(
                    ecitygml::model::construction::AsAbstractConstruction::occupancies(&self.0)
                        .iter(),
                ),
            )
        }
    };
}
