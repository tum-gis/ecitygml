//! Methods of egml's `ApplyTransform` trait, generated into the bridge of every transformable type.
//!
//! Like the abstract-type macros (see `src/gml/core/model/feature/abstract_feature.rs`): each type
//! invokes the macro itself and includes this file with `#[diplomat::include(...)]`. Only owned types
//! invoke it (currently `CityModel`): everything else is reached through read-only references.

#[diplomat::macro_rules]
macro_rules! impl_apply_transform_methods {
    () => {
        /// Translates the geometry and every stored envelope by `vector` (Rust:
        /// `ApplyTransform::apply_translation`).
        pub fn apply_translation(
            &mut self,
            vector: crate::gml::core::model::common::vector3::ffi::Vector3,
        ) {
            egml::model::common::ApplyTransform::apply_translation(&mut self.0, vector.into());
        }

        /// Scales the geometry and every stored envelope by `scale`, per axis and about the origin (Rust:
        /// `ApplyTransform::apply_scale`).
        pub fn apply_scale(&mut self, scale: crate::gml::core::model::common::scale3::ffi::Scale3) {
            egml::model::common::ApplyTransform::apply_scale(&mut self.0, scale.into());
        }
    };
}
