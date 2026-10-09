//! `GranularityValue`, mirroring `ecitygml::model::transportation::enums::GranularityValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    /// Level of subdivision of a transportation space (lane or way).
    #[diplomat::enum_convert(ecitygml::model::transportation::enums::GranularityValue)]
    #[derive(Debug, PartialEq, Eq)]
    pub enum GranularityValue {
        Lane,
        Way,
    }
}

pub use ffi::GranularityValue;
