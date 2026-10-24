//! `GenericAttributeKind`, any generic attribute, and its iterator.
//! Not bound yet: the values of `DateAttribute`, `CodeAttribute` and `UriAttribute` (their `name` is
//! available).

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::citygml::core::model::generics::double_attribute::ffi::DoubleAttribute;
    use crate::citygml::core::model::generics::int_attribute::ffi::IntAttribute;
    use crate::citygml::core::model::generics::string_attribute::ffi::StringAttribute;

    /// A generic attribute of any kind, borrowed from a city model; get its value with `as_string`,
    /// `as_int`, `as_double`, `MeasureAttribute::try_from` or `GenericAttributeSet::try_from`.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct GenericAttributeKind(pub(crate) ecitygml::model::generics::GenericAttributeKind);

    impl GenericAttributeKind {
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn name<'a>(&'a self) -> &'a str {
            self.0.name()
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn as_string<'a>(&'a self) -> Option<&'a StringAttribute> {
            self.0.as_string().map(StringAttribute::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn as_int<'a>(&'a self) -> Option<&'a IntAttribute> {
            self.0.as_int().map(IntAttribute::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn as_double<'a>(&'a self) -> Option<&'a DoubleAttribute> {
            self.0.as_double().map(DoubleAttribute::transparent_convert)
        }
    }

    /// Iterates over generic attributes, borrowed from a city model.
    #[diplomat::opaque_mut]
    pub struct GenericAttributeKindIterator<'a>(
        pub(crate) std::slice::Iter<'a, ecitygml::model::generics::GenericAttributeKind>,
    );

    impl<'a> GenericAttributeKindIterator<'a> {
        #[diplomat::attr(auto, iterator)]
        #[allow(clippy::should_implement_trait)] // Diplomat's iterator protocol, not `Iterator`
        pub fn next(&mut self) -> Option<&'a GenericAttributeKind> {
            self.0.next().map(GenericAttributeKind::transparent_convert)
        }
    }
}

pub use ffi::{GenericAttributeKind, GenericAttributeKindIterator};
