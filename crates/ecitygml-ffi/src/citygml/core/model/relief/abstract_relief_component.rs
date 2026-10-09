//! Methods of ecitygml's `AbstractReliefComponent`, generated into the bridge of every relief component type.
//!
//! Like all abstract-type macros (see `src/gml/core/model/feature/abstract_feature.rs`): each type invokes the
//! macro of every abstract supertype itself and includes this file with `#[diplomat::include(...)]`.
//! Not bound yet: extent.

#[diplomat::macro_rules]
macro_rules! impl_abstract_relief_component_methods {
    () => {
        pub fn lod(
            &self,
        ) -> crate::citygml::core::model::common::level_of_detail::ffi::LevelOfDetail {
            ecitygml::model::relief::AsAbstractReliefComponent::lod(&self.0).into()
        }
    };
}
