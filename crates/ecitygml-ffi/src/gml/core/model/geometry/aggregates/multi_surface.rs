//! `MultiSurface` (`gml:MultiSurface`).

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
    use crate::gml::core::model::geometry::primitives::abstract_surface_property::ffi::AbstractSurfacePropertyIterator;

    /// A multi surface, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct MultiSurface(egml::model::geometry::aggregates::MultiSurface);

    impl MultiSurface {
        impl_gml_abstract_object_methods! {}
        impl_gml_abstract_gml_methods! {}
        impl_triangulate_methods! {}

        /// The geometry as a `MultiSurface`, or none if it is another type (Rust: nested
        /// `AbstractGeometryKind` variants).
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn try_from<'a>(
            geometry: &'a crate::gml::core::model::geometry::abstract_geometry_kind::ffi::AbstractGeometryKind,
        ) -> Option<&'a MultiSurface> {
            match &geometry.0 {
                egml::model::geometry::AbstractGeometryKind::AbstractGeometricAggregateKind(
                    egml::model::geometry::aggregates::AbstractGeometricAggregateKind::MultiSurface(
                        x,
                    ),
                ) => Some(MultiSurface::transparent_convert(x)),
                _ => None,
            }
        }

        /// The surface members (`gml:surfaceMember`).
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn surface_member<'a>(&'a self) -> Box<AbstractSurfacePropertyIterator<'a>> {
            Box::new(AbstractSurfacePropertyIterator(
                self.0.surface_member().iter(),
            ))
        }

        /// Sum of the members' areas; fails with `UnresolvedReference` if a member is only an
        /// `xlink:href`.
        pub fn area_3d(&self) -> Result<f64, Box<Error>> {
            Ok(self.0.area_3d()?)
        }

        /// All positions of the inline members.
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

pub use ffi::MultiSurface;
