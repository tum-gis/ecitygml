//! `MeasureAttribute`, mirroring `ecitygml::model::generics::MeasureAttribute`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::citygml::core::model::generics::generic_attribute_kind::ffi::GenericAttributeKind;
    use crate::gml::core::model::basic_types::measure::ffi::Measure;

    /// A generic attribute with a value and unit of measure, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct MeasureAttribute(ecitygml::model::generics::MeasureAttribute);

    impl MeasureAttribute {
        /// The attribute as a measure attribute, or none if it is another kind (Rust has no
        /// `as_measure`; it matches `GenericAttributeKind::MeasureAttribute`).
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn try_from<'a>(attribute: &'a GenericAttributeKind) -> Option<&'a MeasureAttribute> {
            match &attribute.0 {
                ecitygml::model::generics::GenericAttributeKind::MeasureAttribute(x) => {
                    Some(MeasureAttribute::transparent_convert(x))
                }
                _ => None,
            }
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn name<'a>(&'a self) -> &'a str {
            &self.0.name
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn value<'a>(&'a self) -> &'a Measure {
            Measure::transparent_convert(&self.0.value)
        }
    }
}

pub use ffi::MeasureAttribute;
