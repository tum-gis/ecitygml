//! `StringAttribute`, mirroring `ecitygml::model::generics::StringAttribute`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    /// A generic attribute with a text value, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct StringAttribute(ecitygml::model::generics::StringAttribute);

    impl StringAttribute {
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn name<'a>(&'a self) -> &'a str {
            &self.0.name
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn value<'a>(&'a self) -> &'a str {
            &self.0.value
        }
    }
}

pub use ffi::StringAttribute;
