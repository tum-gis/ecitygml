//! `AbstractSurfaceKind`, any surface; convert it with e.g. `Polygon::try_from`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/gml/core/model/base/abstract_gml.rs")]
#[diplomat::include("src/gml/core/model/abstract_object.rs")]
#[diplomat::include("src/gml/core/model/common/triangulate.rs")]
pub mod ffi {
    use crate::error::ffi::Error;
    use crate::gml::core::model::common::geometry_type::ffi::GeometryType;
    use crate::gml::core::model::geometry::direct_position::ffi::DirectPositionIterator;
    use crate::gml::core::model::geometry::envelope::ffi::Envelope;

    /// A surface of any type, borrowed from a city model; convert it with `Polygon::try_from`,
    /// `CompositeSurface::try_from`, `Shell::try_from`, `Surface::try_from` or
    /// `TriangulatedSurface::try_from`.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct AbstractSurfaceKind(
        pub(crate) egml::model::geometry::primitives::AbstractSurfaceKind,
    );

    impl AbstractSurfaceKind {
        impl_gml_abstract_object_methods! {}
        impl_gml_abstract_gml_methods! {}
        impl_triangulate_methods! {}

        /// The geometry as an `AbstractSurfaceKind`, or none if it is another type (Rust: nested
        /// `AbstractGeometryKind` variants).
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn try_from<'a>(
            geometry: &'a crate::gml::core::model::geometry::abstract_geometry_kind::ffi::AbstractGeometryKind,
        ) -> Option<&'a AbstractSurfaceKind> {
            match &geometry.0 {
                egml::model::geometry::AbstractGeometryKind::AbstractGeometricPrimitiveKind(egml::model::geometry::primitives::AbstractGeometricPrimitiveKind::AbstractSurfaceKind(x)) => Some(AbstractSurfaceKind::transparent_convert(x)),
                _ => None,
            }
        }

        pub fn geometry_type(&self) -> GeometryType {
            egml::model::common::HasGeometryType::geometry_type(&self.0).into()
        }

        pub fn area_3d(&self) -> Result<f64, Box<Error>> {
            Ok(self.0.area_3d()?)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn points<'a>(&'a self) -> Box<DirectPositionIterator<'a>> {
            Box::new(DirectPositionIterator(self.0.points().into_iter()))
        }

        /// Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
        pub fn compute_envelope(&self) -> Option<Box<Envelope>> {
            egml::model::common::ComputeEnvelope::compute_envelope(&self.0)
                .map(|envelope| Box::new(Envelope(envelope)))
        }
    }
}

pub use ffi::AbstractSurfaceKind;
