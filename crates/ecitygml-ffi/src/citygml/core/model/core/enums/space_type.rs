//! `SpaceType`, mirroring `ecitygml::model::core::enums::SpaceType`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    /// Whether a space is closed, open or semi-open.
    #[diplomat::enum_convert(ecitygml::model::core::enums::SpaceType)]
    #[derive(Debug, PartialEq, Eq)]
    pub enum SpaceType {
        Closed,
        Open,
        SemiOpen,
    }
}

pub use ffi::SpaceType;
