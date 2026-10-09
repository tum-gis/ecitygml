//! `TransformationMatrix4x4`, mirroring `ecitygml::model::core::TransformationMatrix4x4`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::error::ffi::{Error, ErrorKind};

    /// A 4x4 transformation matrix, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct TransformationMatrix4x4(ecitygml::model::core::TransformationMatrix4x4);

    impl TransformationMatrix4x4 {
        /// The entry at `row` and `column` (0 to 3), as nalgebra's `matrix()[(row, column)]`; fails
        /// with `InvalidArgument` instead of panicking above 3. Rust's `to_row_major()` returns a
        /// `Vec`, which the Python backend can only return through NumPy.
        pub fn get(&self, row: usize, column: usize) -> Result<f64, Box<Error>> {
            if row > 3 || column > 3 {
                return Err(crate::error::Error::new(
                    ErrorKind::InvalidArgument,
                    format!("matrix index ({row}, {column}) is out of range 0..4"),
                ));
            }
            Ok(self.0.matrix()[(row, column)])
        }
    }
}

pub use ffi::TransformationMatrix4x4;
