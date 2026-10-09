//! Methods of egml's `AbstractObject`, generated into the bridge of every GML object type (features
//! and geometries).
//!
//! Like all abstract-type macros (see `src/gml/core/model/feature/abstract_feature.rs`): each type invokes the
//! macro of every abstract supertype itself and includes this file with `#[diplomat::include(...)]`.
//! Empty because egml's `AbstractObject` has no fields yet — the macro is already invoked by every
//! GML object type, so methods can be added here in one place.

#[diplomat::macro_rules]
macro_rules! impl_gml_abstract_object_methods {
    () => {};
}
