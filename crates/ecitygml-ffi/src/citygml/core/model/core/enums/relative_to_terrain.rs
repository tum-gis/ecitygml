//! `RelativeToTerrain`, mirroring `ecitygml::model::core::enums::RelativeToTerrain`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    /// Position of a city object relative to the terrain.
    #[diplomat::enum_convert(ecitygml::model::core::enums::RelativeToTerrain)]
    #[derive(Debug, PartialEq, Eq)]
    pub enum RelativeToTerrain {
        EntirelyAboveTerrain,
        SubstantiallyAboveTerrain,
        SubstantiallyAboveAndBelowTerrain,
        SubstantiallyBelowTerrain,
        EntirelyBelowTerrain,
    }
}

pub use ffi::RelativeToTerrain;
