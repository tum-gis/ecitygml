//! `AbstractCurveKind`, any curve; convert it with e.g. `LineString::try_from`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/gml/core/model/base/abstract_gml.rs")]
#[diplomat::include("src/gml/core/model/abstract_object.rs")]
pub mod ffi {
    use crate::gml::core::model::common::geometry_type::ffi::GeometryType;
    use crate::gml::core::model::geometry::envelope::ffi::Envelope;

    /// A curve of any type, borrowed from a city model; convert it with e.g. `LineString::try_from`.
    /// Rings: `AbstractRingKind::try_from`.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct AbstractCurveKind(pub(crate) egml::model::geometry::primitives::AbstractCurveKind);

    impl AbstractCurveKind {
        impl_gml_abstract_object_methods! {}
        impl_gml_abstract_gml_methods! {}

        /// The geometry as an `AbstractCurveKind`, or none if it is another type (Rust: nested
        /// `AbstractGeometryKind` variants).
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn try_from<'a>(
            geometry: &'a crate::gml::core::model::geometry::abstract_geometry_kind::ffi::AbstractGeometryKind,
        ) -> Option<&'a AbstractCurveKind> {
            match &geometry.0 {
                egml::model::geometry::AbstractGeometryKind::AbstractGeometricPrimitiveKind(egml::model::geometry::primitives::AbstractGeometricPrimitiveKind::AbstractCurveKind(x)) => Some(AbstractCurveKind::transparent_convert(x)),
                _ => None,
            }
        }

        pub fn geometry_type(&self) -> GeometryType {
            egml::model::common::HasGeometryType::geometry_type(&self.0).into()
        }

        pub fn length_3d(&self) -> f64 {
            self.0.length_3d()
        }

        /// Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
        pub fn compute_envelope(&self) -> Option<Box<Envelope>> {
            egml::model::common::ComputeEnvelope::compute_envelope(&self.0)
                .map(|envelope| Box::new(Envelope(envelope)))
        }
    }
}

pub use ffi::AbstractCurveKind;
