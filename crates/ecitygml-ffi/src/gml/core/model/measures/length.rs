//! `Length` (`gml:LengthType`), mirroring `egml::model::measures::Length`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    /// A length with its unit of measure, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct Length(egml::model::measures::Length);

    impl Length {
        pub fn value(&self) -> f64 {
            self.0.value()
        }

        /// Unit of measure (`uom`), e.g. `m`.
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn uom<'a>(&'a self) -> &'a str {
            self.0.uom()
        }
    }
}

pub use ffi::Length;
