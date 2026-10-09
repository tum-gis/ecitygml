//! `AbstractSurfacePatchKind`, any surface patch; convert it with e.g. `PolygonPatch::try_from`; and
//! its iterator.

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

    /// A surface patch of any type, borrowed from a city model; convert it with
    /// `PolygonPatch::try_from` or `Triangle::try_from`. Patches aren't GML objects (no `gml:id`).
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct AbstractSurfacePatchKind(
        pub(crate) egml::model::geometry::primitives::AbstractSurfacePatchKind,
    );

    impl AbstractSurfacePatchKind {
        impl_triangulate_methods! {}
        pub fn area_3d(&self) -> Result<f64, Box<Error>> {
            Ok(self.0.area_3d()?)
        }

        /// The patch's positions.
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

    /// Iterates over surface patches, borrowed from a city model.
    #[diplomat::opaque_mut]
    pub struct AbstractSurfacePatchKindIterator<'a>(
        pub(crate) std::slice::Iter<'a, egml::model::geometry::primitives::AbstractSurfacePatchKind>,
    );

    impl<'a> AbstractSurfacePatchKindIterator<'a> {
        #[diplomat::attr(auto, iterator)]
        #[allow(clippy::should_implement_trait)] // Diplomat's iterator protocol, not `Iterator`
        pub fn next(&mut self) -> Option<&'a AbstractSurfacePatchKind> {
            self.0
                .next()
                .map(AbstractSurfacePatchKind::transparent_convert)
        }
    }
}

pub use ffi::{AbstractSurfacePatchKind, AbstractSurfacePatchKindIterator};
