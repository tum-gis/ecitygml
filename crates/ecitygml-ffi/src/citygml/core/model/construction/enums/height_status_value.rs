//! `HeightStatusValue`, mirroring `ecitygml::model::construction::enums::HeightStatusValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    /// Whether a height was estimated or measured.
    #[diplomat::enum_convert(ecitygml::model::construction::enums::HeightStatusValue)]
    #[derive(Debug, PartialEq, Eq)]
    pub enum HeightStatusValue {
        Estimated,
        Measured,
    }
}

pub use ffi::HeightStatusValue;
