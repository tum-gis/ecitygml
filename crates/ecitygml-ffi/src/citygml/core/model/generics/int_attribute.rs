//! `IntAttribute`, mirroring `ecitygml::model::generics::IntAttribute`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    /// A generic attribute with an integer value, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct IntAttribute(ecitygml::model::generics::IntAttribute);

    impl IntAttribute {
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn name<'a>(&'a self) -> &'a str {
            &self.0.name
        }

        pub fn value(&self) -> i64 {
            self.0.value
        }
    }
}

pub use ffi::IntAttribute;
