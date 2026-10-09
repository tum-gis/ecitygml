//! `DoubleAttribute`, mirroring `ecitygml::model::generics::DoubleAttribute`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    /// A generic attribute with a floating-point value, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct DoubleAttribute(ecitygml::model::generics::DoubleAttribute);

    impl DoubleAttribute {
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn name<'a>(&'a self) -> &'a str {
            &self.0.name
        }

        pub fn value(&self) -> f64 {
            self.0.value
        }
    }
}

pub use ffi::DoubleAttribute;
