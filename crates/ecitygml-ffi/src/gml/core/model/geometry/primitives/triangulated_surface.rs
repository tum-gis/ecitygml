//! `TriangulatedSurface` (`gml:TriangulatedSurface`), a surface made of triangles.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/gml/core/model/base/abstract_gml.rs")]
#[diplomat::include("src/gml/core/model/abstract_object.rs")]
pub mod ffi {
    use crate::error::ffi::Error;
    use crate::gml::core::model::geometry::direct_position::ffi::DirectPositionIterator;
    use crate::gml::core::model::geometry::envelope::ffi::Envelope;
    use crate::gml::core::model::geometry::primitives::abstract_surface_kind::ffi::AbstractSurfaceKind;
    use crate::gml::core::model::geometry::primitives::surface::ffi::Surface;
    use crate::gml::core::model::geometry::primitives::triangle::ffi::TriangleIterator;

    /// A surface made of triangles, borrowed from a city model or a triangulation.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct TriangulatedSurface(egml::model::geometry::primitives::TriangulatedSurface);

    impl TriangulatedSurface {
        impl_gml_abstract_object_methods! {}
        impl_gml_abstract_gml_methods! {}

        /// The surface as a triangulated surface, or none if it is another type (Rust: a
        /// `TriangulatedSurface` in `AbstractSurfaceKind::SurfaceKind`).
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn try_from<'a>(surface: &'a AbstractSurfaceKind) -> Option<&'a TriangulatedSurface> {
            match &surface.0 {
                egml::model::geometry::primitives::AbstractSurfaceKind::SurfaceKind(
                    egml::model::geometry::primitives::SurfaceKind::TriangulatedSurface(x),
                ) => Some(TriangulatedSurface::transparent_convert(x)),
                _ => None,
            }
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn triangles<'a>(&'a self) -> Box<TriangleIterator<'a>> {
            Box::new(TriangleIterator(self.0.triangles().into_iter()))
        }

        /// The underlying surface, whose patches are the triangles.
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn surface<'a>(&'a self) -> &'a Surface {
            Surface::transparent_convert(self.0.surface())
        }

        /// All corners of the triangles.
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn points<'a>(&'a self) -> Box<DirectPositionIterator<'a>> {
            Box::new(DirectPositionIterator(self.0.points().into_iter()))
        }

        pub fn area_3d(&self) -> Result<f64, Box<Error>> {
            Ok(self.0.area_3d()?)
        }

        /// Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
        pub fn compute_envelope(&self) -> Option<Box<Envelope>> {
            egml::model::common::ComputeEnvelope::compute_envelope(&self.0)
                .map(|envelope| Box::new(Envelope(envelope)))
        }
    }
}

pub use ffi::TriangulatedSurface;
