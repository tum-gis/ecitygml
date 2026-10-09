//! `MultiCurve` (`gml:MultiCurve`).

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/gml/core/model/base/abstract_gml.rs")]
#[diplomat::include("src/gml/core/model/abstract_object.rs")]
pub mod ffi {
    use crate::error::ffi::Error;
    use crate::gml::core::model::geometry::envelope::ffi::Envelope;
    use crate::gml::core::model::geometry::primitives::abstract_curve_property::ffi::AbstractCurvePropertyIterator;

    /// A multi curve, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct MultiCurve(egml::model::geometry::aggregates::MultiCurve);

    impl MultiCurve {
        impl_gml_abstract_object_methods! {}
        impl_gml_abstract_gml_methods! {}

        /// The geometry as a `MultiCurve`, or none if it is another type (Rust: nested
        /// `AbstractGeometryKind` variants).
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn try_from<'a>(
            geometry: &'a crate::gml::core::model::geometry::abstract_geometry_kind::ffi::AbstractGeometryKind,
        ) -> Option<&'a MultiCurve> {
            match &geometry.0 {
                egml::model::geometry::AbstractGeometryKind::AbstractGeometricAggregateKind(
                    egml::model::geometry::aggregates::AbstractGeometricAggregateKind::MultiCurve(
                        x,
                    ),
                ) => Some(MultiCurve::transparent_convert(x)),
                _ => None,
            }
        }

        /// The curve members (`gml:curveMember`).
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn curve_member<'a>(&'a self) -> Box<AbstractCurvePropertyIterator<'a>> {
            Box::new(AbstractCurvePropertyIterator(self.0.curve_member().iter()))
        }

        /// Sum of the members' lengths; fails with `UnresolvedReference` if a member is only an
        /// `xlink:href`.
        pub fn length_3d(&self) -> Result<f64, Box<Error>> {
            Ok(self.0.length_3d()?)
        }

        /// Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
        pub fn compute_envelope(&self) -> Option<Box<Envelope>> {
            egml::model::common::ComputeEnvelope::compute_envelope(&self.0)
                .map(|envelope| Box::new(Envelope(envelope)))
        }
    }
}

pub use ffi::MultiCurve;
