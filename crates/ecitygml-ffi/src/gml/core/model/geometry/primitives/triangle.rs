//! `Triangle` (`gml:Triangle`), a surface patch.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/gml/core/model/common/triangulate.rs")]
pub mod ffi {
    use crate::gml::core::model::geometry::direct_position::ffi::{
        DirectPosition, DirectPositionIterator,
    };
    use crate::gml::core::model::geometry::envelope::ffi::Envelope;
    use crate::gml::core::model::geometry::primitives::abstract_ring_kind::ffi::AbstractRingKind;
    use crate::gml::core::model::geometry::primitives::abstract_surface_patch_kind::ffi::AbstractSurfacePatchKind;

    /// A triangle, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct Triangle(egml::model::geometry::primitives::Triangle);

    impl Triangle {
        impl_triangulate_methods! {}
        /// The patch as a triangle, or none if it is another type (Rust: `Triangle::try_from`, which
        /// takes the patch by value).
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn try_from<'a>(patch: &'a AbstractSurfacePatchKind) -> Option<&'a Triangle> {
            match &patch.0 {
                egml::model::geometry::primitives::AbstractSurfacePatchKind::Triangle(x) => {
                    Some(Triangle::transparent_convert(x))
                }
                _ => None,
            }
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn exterior<'a>(&'a self) -> &'a AbstractRingKind {
            AbstractRingKind::transparent_convert(self.0.exterior())
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn a<'a>(&'a self) -> &'a DirectPosition {
            DirectPosition::transparent_convert(self.0.a())
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn b<'a>(&'a self) -> &'a DirectPosition {
            DirectPosition::transparent_convert(self.0.b())
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn c<'a>(&'a self) -> &'a DirectPosition {
            DirectPosition::transparent_convert(self.0.c())
        }

        pub fn area(&self) -> f64 {
            self.0.area()
        }

        /// The three corners.
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn points<'a>(&'a self) -> Box<DirectPositionIterator<'a>> {
            Box::new(DirectPositionIterator(
                self.0.points().iter().collect::<Vec<_>>().into_iter(),
            ))
        }

        /// Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
        pub fn compute_envelope(&self) -> Option<Box<Envelope>> {
            egml::model::common::ComputeEnvelope::compute_envelope(&self.0)
                .map(|envelope| Box::new(Envelope(envelope)))
        }
    }

    /// Iterates over triangles (e.g. of a triangulated surface), borrowed from a city model.
    #[diplomat::opaque_mut]
    pub struct TriangleIterator<'a>(
        pub(crate) std::vec::IntoIter<&'a egml::model::geometry::primitives::Triangle>,
    );

    impl<'a> TriangleIterator<'a> {
        #[diplomat::attr(auto, iterator)]
        #[allow(clippy::should_implement_trait)] // Diplomat's iterator protocol, not `Iterator`
        pub fn next(&mut self) -> Option<&'a Triangle> {
            self.0.next().map(Triangle::transparent_convert)
        }
    }
}

pub use ffi::{Triangle, TriangleIterator};
