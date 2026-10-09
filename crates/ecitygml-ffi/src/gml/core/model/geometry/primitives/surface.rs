//! `Surface` (`gml:Surface`), a surface made of patches.

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
    use crate::gml::core::model::geometry::direct_position::ffi::DirectPositionIterator;
    use crate::gml::core::model::geometry::envelope::ffi::Envelope;
    use crate::gml::core::model::geometry::primitives::abstract_surface_kind::ffi::AbstractSurfaceKind;
    use crate::gml::core::model::geometry::primitives::abstract_surface_patch_kind::ffi::AbstractSurfacePatchKindIterator;

    /// A surface made of patches, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct Surface(egml::model::geometry::primitives::Surface);

    impl Surface {
        impl_gml_abstract_object_methods! {}
        impl_gml_abstract_gml_methods! {}
        impl_triangulate_methods! {}

        /// The surface as a `gml:Surface`, or none if it is another type (Rust: `Surface::try_from`,
        /// which takes the surface by value).
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn try_from<'a>(surface: &'a AbstractSurfaceKind) -> Option<&'a Surface> {
            match &surface.0 {
                egml::model::geometry::primitives::AbstractSurfaceKind::Surface(x) => {
                    Some(Surface::transparent_convert(x))
                }
                _ => None,
            }
        }

        /// The patches (`gml:patches`).
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn patches<'a>(&'a self) -> Box<AbstractSurfacePatchKindIterator<'a>> {
            Box::new(AbstractSurfacePatchKindIterator(self.0.patches().iter()))
        }

        pub fn area_3d(&self) -> Result<f64, Box<Error>> {
            Ok(self.0.area_3d()?)
        }

        /// All positions of the patches.
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

pub use ffi::Surface;
