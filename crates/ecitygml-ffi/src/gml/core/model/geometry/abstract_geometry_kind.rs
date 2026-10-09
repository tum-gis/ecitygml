//! `AbstractGeometryKind`, any geometry; convert it with e.g. `MultiSurface::try_from`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/gml/core/model/base/abstract_gml.rs")]
#[diplomat::include("src/gml/core/model/abstract_object.rs")]
#[diplomat::include("src/gml/core/model/common/triangulate.rs")]
pub mod ffi {
    use crate::gml::core::model::common::geometry_type::ffi::GeometryType;
    use crate::gml::core::model::geometry::envelope::ffi::Envelope;

    /// A geometry of any type, borrowed from a city model; convert it with `MultiSurface::try_from`,
    /// `MultiCurve::try_from`, `Point::try_from`, `Solid::try_from`, `AbstractSurfaceKind::try_from`
    /// or `AbstractCurveKind::try_from`. Not bound yet: `MultiPoint`, `MultiGeometry`.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct AbstractGeometryKind(pub(crate) egml::model::geometry::AbstractGeometryKind);

    impl AbstractGeometryKind {
        impl_gml_abstract_object_methods! {}
        impl_gml_abstract_gml_methods! {}
        impl_triangulate_methods! {}

        pub fn geometry_type(&self) -> GeometryType {
            egml::model::common::HasGeometryType::geometry_type(&self.0).into()
        }

        /// Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
        pub fn compute_envelope(&self) -> Option<Box<Envelope>> {
            egml::model::common::ComputeEnvelope::compute_envelope(&self.0)
                .map(|envelope| Box::new(Envelope(envelope)))
        }
    }
}

pub use ffi::AbstractGeometryKind;
