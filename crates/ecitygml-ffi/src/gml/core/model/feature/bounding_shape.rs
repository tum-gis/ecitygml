//! `BoundingShape`, the content of `gml:boundedBy`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::gml::core::model::geometry::envelope::ffi::Envelope;

    /// The bounding shape of a feature (`gml:boundedBy`), borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct BoundingShape(egml::model::feature::BoundingShape);

    impl BoundingShape {
        /// The envelope; none if the shape is nil.
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn envelope<'a>(&'a self) -> Option<&'a Envelope> {
            self.0.envelope().map(Envelope::transparent_convert)
        }
    }
}

pub use ffi::BoundingShape;
