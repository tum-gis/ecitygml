//! `Measure` (`gml:MeasureType`), a value with a unit of measure.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    /// A numeric value with its unit of measure, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct Measure(egml::model::basic_types::Measure);

    impl Measure {
        pub fn value(&self) -> f64 {
            self.0.value
        }

        /// Unit of measure (`uom`), e.g. `m2`.
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn uom<'a>(&'a self) -> &'a str {
            &self.0.uom
        }
    }
}

pub use ffi::Measure;
