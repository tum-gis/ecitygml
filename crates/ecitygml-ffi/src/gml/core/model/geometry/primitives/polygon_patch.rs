//! `PolygonPatch` (`gml:PolygonPatch`), a surface patch.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/gml/core/model/common/triangulate.rs")]
pub mod ffi {
    use crate::error::ffi::Error;
    use crate::gml::core::model::geometry::direct_position::ffi::DirectPositionIterator;
    use crate::gml::core::model::geometry::envelope::ffi::Envelope;
    use crate::gml::core::model::geometry::primitives::abstract_ring_kind::ffi::{
        AbstractRingKind, AbstractRingKindIterator,
    };
    use crate::gml::core::model::geometry::primitives::abstract_surface_patch_kind::ffi::AbstractSurfacePatchKind;

    /// A polygon patch, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct PolygonPatch(egml::model::geometry::primitives::PolygonPatch);

    impl PolygonPatch {
        impl_triangulate_methods! {}
        /// The patch as a polygon patch, or none if it is another type (Rust: `PolygonPatch::try_from`, which
        /// takes the patch by value).
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn try_from<'a>(patch: &'a AbstractSurfacePatchKind) -> Option<&'a PolygonPatch> {
            match &patch.0 {
                egml::model::geometry::primitives::AbstractSurfacePatchKind::PolygonPatch(x) => {
                    Some(PolygonPatch::transparent_convert(x))
                }
                _ => None,
            }
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn exterior<'a>(&'a self) -> Option<&'a AbstractRingKind> {
            self.0.exterior().map(AbstractRingKind::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn interior<'a>(&'a self) -> Box<AbstractRingKindIterator<'a>> {
            Box::new(AbstractRingKindIterator(self.0.interior().iter()))
        }

        /// Exterior area minus the holes; fails if the patch has no exterior ring.
        pub fn area_3d(&self) -> Result<f64, Box<Error>> {
            Ok(self.0.area_3d()?)
        }

        /// All positions of the exterior and interior rings.
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

pub use ffi::PolygonPatch;
