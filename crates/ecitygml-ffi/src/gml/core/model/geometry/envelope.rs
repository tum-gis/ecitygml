//! `Envelope`, an axis-aligned bounding box (`gml:Envelope`).

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::gml::core::model::geometry::direct_position::ffi::DirectPosition;

    /// An axis-aligned bounding box, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct Envelope(pub(crate) egml::model::geometry::Envelope);

    impl Envelope {
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn lower_corner<'a>(&'a self) -> &'a DirectPosition {
            DirectPosition::transparent_convert(self.0.lower_corner())
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn upper_corner<'a>(&'a self) -> &'a DirectPosition {
            DirectPosition::transparent_convert(self.0.upper_corner())
        }

        /// Extent along the x axis.
        pub fn size_x(&self) -> f64 {
            self.0.size_x()
        }

        /// Extent along the y axis.
        pub fn size_y(&self) -> f64 {
            self.0.size_y()
        }

        /// Extent along the z axis.
        pub fn size_z(&self) -> f64 {
            self.0.size_z()
        }

        /// Volume of the box (`size_x * size_y * size_z`); `0.0` if an extent is zero.
        pub fn volume(&self) -> f64 {
            self.0.volume()
        }

        /// Whether `point` lies inside or on the boundary of the box.
        pub fn contains(&self, point: &DirectPosition) -> bool {
            self.0.contains(&point.0)
        }
    }
}

pub use ffi::Envelope;
