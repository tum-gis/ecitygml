//! `Point` (`gml:Point`).

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/gml/core/model/base/abstract_gml.rs")]
#[diplomat::include("src/gml/core/model/abstract_object.rs")]
pub mod ffi {
    use crate::gml::core::model::geometry::direct_position::ffi::DirectPosition;
    use crate::gml::core::model::geometry::envelope::ffi::Envelope;

    /// A point, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct Point(egml::model::geometry::primitives::Point);

    impl Point {
        impl_gml_abstract_object_methods! {}
        impl_gml_abstract_gml_methods! {}

        /// The geometry as a `Point`, or none if it is another type (Rust: nested
        /// `AbstractGeometryKind` variants).
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn try_from<'a>(
            geometry: &'a crate::gml::core::model::geometry::abstract_geometry_kind::ffi::AbstractGeometryKind,
        ) -> Option<&'a Point> {
            match &geometry.0 {
                egml::model::geometry::AbstractGeometryKind::AbstractGeometricPrimitiveKind(
                    egml::model::geometry::primitives::AbstractGeometricPrimitiveKind::Point(x),
                ) => Some(Point::transparent_convert(x)),
                _ => None,
            }
        }

        /// The position (`gml:pos`).
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn pos<'a>(&'a self) -> &'a DirectPosition {
            DirectPosition::transparent_convert(self.0.pos())
        }

        /// Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
        pub fn compute_envelope(&self) -> Option<Box<Envelope>> {
            egml::model::common::ComputeEnvelope::compute_envelope(&self.0)
                .map(|envelope| Box::new(Envelope(envelope)))
        }
    }
}

pub use ffi::Point;
