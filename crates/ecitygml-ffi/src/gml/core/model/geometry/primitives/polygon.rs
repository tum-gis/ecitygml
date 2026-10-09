//! `Polygon` (`gml:Polygon`).

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
    use crate::gml::core::model::geometry::primitives::abstract_ring_kind::ffi::{
        AbstractRingKind, AbstractRingKindIterator,
    };
    use crate::gml::core::model::geometry::primitives::abstract_surface_kind::ffi::AbstractSurfaceKind;

    /// A polygon, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct Polygon(egml::model::geometry::primitives::Polygon);

    impl Polygon {
        impl_gml_abstract_object_methods! {}
        impl_gml_abstract_gml_methods! {}
        impl_triangulate_methods! {}

        /// The surface as a polygon, or none if it is another type (Rust: `Polygon::try_from`,
        /// which takes the surface by value).
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn try_from<'a>(surface: &'a AbstractSurfaceKind) -> Option<&'a Polygon> {
            match &surface.0 {
                egml::model::geometry::primitives::AbstractSurfaceKind::Polygon(polygon) => {
                    Some(Polygon::transparent_convert(polygon))
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

        /// Exterior area minus the holes; fails if the polygon has no exterior ring.
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

pub use ffi::Polygon;
