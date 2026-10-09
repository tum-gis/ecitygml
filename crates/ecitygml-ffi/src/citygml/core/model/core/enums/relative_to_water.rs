//! `RelativeToWater`, mirroring `ecitygml::model::core::enums::RelativeToWater`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    /// Position of a city object relative to the water surface.
    #[diplomat::enum_convert(ecitygml::model::core::enums::RelativeToWater)]
    #[derive(Debug, PartialEq, Eq)]
    pub enum RelativeToWater {
        EntirelyAboveWaterSurface,
        SubstantiallyAboveWaterSurface,
        SubstantiallyAboveAndBelowWaterSurface,
        SubstantiallyBelowWaterSurface,
        EntirelyBelowWaterSurface,
        TemporarilyAboveAndBelowWaterSurface,
    }
}

pub use ffi::RelativeToWater;
