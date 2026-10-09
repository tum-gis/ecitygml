//! `LineString` (`gml:LineString`).

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/gml/core/model/base/abstract_gml.rs")]
#[diplomat::include("src/gml/core/model/abstract_object.rs")]
pub mod ffi {
    use crate::gml::core::model::geometry::direct_position::ffi::DirectPositionIterator;
    use crate::gml::core::model::geometry::envelope::ffi::Envelope;
    use crate::gml::core::model::geometry::primitives::abstract_curve_kind::ffi::AbstractCurveKind;

    /// A line string, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct LineString(egml::model::geometry::primitives::LineString);

    impl LineString {
        impl_gml_abstract_object_methods! {}
        impl_gml_abstract_gml_methods! {}

        /// The curve as a line string, or none if it is another type (Rust: `LineString::try_from`,
        /// which takes the curve by value).
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn try_from<'a>(curve: &'a AbstractCurveKind) -> Option<&'a LineString> {
            match &curve.0 {
                egml::model::geometry::primitives::AbstractCurveKind::LineString(line_string) => {
                    Some(LineString::transparent_convert(line_string))
                }
                _ => None,
            }
        }

        /// The positions (`gml:posList`).
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn points<'a>(&'a self) -> Box<DirectPositionIterator<'a>> {
            Box::new(DirectPositionIterator(
                self.0.points().iter().collect::<Vec<_>>().into_iter(),
            ))
        }

        pub fn length_3d(&self) -> f64 {
            self.0.length_3d()
        }

        /// Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
        pub fn compute_envelope(&self) -> Option<Box<Envelope>> {
            egml::model::common::ComputeEnvelope::compute_envelope(&self.0)
                .map(|envelope| Box::new(Envelope(envelope)))
        }
    }
}

pub use ffi::LineString;
