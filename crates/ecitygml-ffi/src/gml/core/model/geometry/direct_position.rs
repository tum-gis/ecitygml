//! `DirectPosition`, a 3D coordinate (`gml:pos`).

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::error::ffi::Error;

    /// A 3D coordinate, created or borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct DirectPosition(pub(crate) egml::model::geometry::DirectPosition);

    impl DirectPosition {
        /// Creates a position; fails with `InvalidArgument` if a coordinate is NaN or infinite.
        #[diplomat::attr(supports = fallible_constructors, constructor)]
        // C++ and Kotlin have no fallible constructors and can't use `new` as a method name.
        #[diplomat::attr(not(supports = fallible_constructors), rename = "create")]
        pub fn new(x: f64, y: f64, z: f64) -> Result<Box<DirectPosition>, Box<Error>> {
            Ok(Box::new(DirectPosition(
                egml::model::geometry::DirectPosition::new(x, y, z)?,
            )))
        }

        pub fn x(&self) -> f64 {
            self.0.x()
        }

        pub fn y(&self) -> f64 {
            self.0.y()
        }

        pub fn z(&self) -> f64 {
            self.0.z()
        }
    }

    /// Iterates over positions, borrowed from a city model.
    #[diplomat::opaque_mut]
    pub struct DirectPositionIterator<'a>(
        pub(crate) std::vec::IntoIter<&'a egml::model::geometry::DirectPosition>,
    );

    impl<'a> DirectPositionIterator<'a> {
        #[diplomat::attr(auto, iterator)]
        #[allow(clippy::should_implement_trait)] // Diplomat's iterator protocol, not `Iterator`
        pub fn next(&mut self) -> Option<&'a DirectPosition> {
            self.0.next().map(DirectPosition::transparent_convert)
        }
    }
}

pub use ffi::{DirectPosition, DirectPositionIterator};
