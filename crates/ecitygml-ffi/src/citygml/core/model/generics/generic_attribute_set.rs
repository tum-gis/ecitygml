//! `GenericAttributeSet`, mirroring `ecitygml::model::generics::GenericAttributeSet`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::citygml::core::model::generics::generic_attribute_kind::ffi::{
        GenericAttributeKind, GenericAttributeKindIterator,
    };

    /// A named set of generic attributes, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct GenericAttributeSet(ecitygml::model::generics::GenericAttributeSet);

    impl GenericAttributeSet {
        /// The attribute as a set, or none if it is another kind (Rust has no `as_set`; it matches
        /// `GenericAttributeKind::GenericAttributeSet`).
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn try_from<'a>(
            attribute: &'a GenericAttributeKind,
        ) -> Option<&'a GenericAttributeSet> {
            match &attribute.0 {
                ecitygml::model::generics::GenericAttributeKind::GenericAttributeSet(x) => {
                    Some(GenericAttributeSet::transparent_convert(x))
                }
                _ => None,
            }
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn name<'a>(&'a self) -> &'a str {
            &self.0.name
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn generic_attributes<'a>(&'a self) -> Box<GenericAttributeKindIterator<'a>> {
            Box::new(GenericAttributeKindIterator(
                self.0.generic_attributes.iter(),
            ))
        }
    }
}

pub use ffi::GenericAttributeSet;
