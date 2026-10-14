//! `Scale3`, mirroring `nalgebra::Scale3<f64>` (a scale factor per axis).

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    /// A scale factor per axis, passed by value (the argument of `CityModel::apply_scale`).
    #[derive(Debug, Clone, Copy, PartialEq)]
    pub struct Scale3 {
        pub x: f64,
        pub y: f64,
        pub z: f64,
    }
}

pub use ffi::Scale3;

impl From<Scale3> for nalgebra::Scale3<f64> {
    fn from(scale: Scale3) -> Self {
        nalgebra::Scale3::new(scale.x, scale.y, scale.z)
    }
}
