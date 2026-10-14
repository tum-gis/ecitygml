//! `Vector3`, mirroring `nalgebra::Vector3<f64>` (e.g. a translation).

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    /// A 3D vector, passed by value (e.g. the translation of `CityModel::apply_translation`).
    #[derive(Debug, Clone, Copy, PartialEq)]
    pub struct Vector3 {
        pub x: f64,
        pub y: f64,
        pub z: f64,
    }
}

pub use ffi::Vector3;

impl From<Vector3> for nalgebra::Vector3<f64> {
    fn from(vector: Vector3) -> Self {
        nalgebra::Vector3::new(vector.x, vector.y, vector.z)
    }
}
