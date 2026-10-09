//! `AbstractRingKind`, any ring; convert it with `LinearRing::try_from`; and its iterator.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/gml/core/model/base/abstract_gml.rs")]
#[diplomat::include("src/gml/core/model/abstract_object.rs")]
pub mod ffi {
    use crate::gml::core::model::common::geometry_type::ffi::GeometryType;
    use crate::gml::core::model::geometry::direct_position::ffi::DirectPositionIterator;
    use crate::gml::core::model::geometry::envelope::ffi::Envelope;
    use crate::gml::core::model::geometry::primitives::abstract_curve_kind::ffi::AbstractCurveKind;

    /// A ring of any type, borrowed from a city model; convert it with `LinearRing::try_from`.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct AbstractRingKind(pub(crate) egml::model::geometry::primitives::AbstractRingKind);

    impl AbstractRingKind {
        impl_gml_abstract_object_methods! {}
        impl_gml_abstract_gml_methods! {}

        /// The curve as a ring, or none if it is another type (Rust: `AbstractRingKind::try_from`,
        /// which takes the curve by value).
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn try_from<'a>(curve: &'a AbstractCurveKind) -> Option<&'a AbstractRingKind> {
            match &curve.0 {
                egml::model::geometry::primitives::AbstractCurveKind::AbstractRingKind(ring) => {
                    Some(AbstractRingKind::transparent_convert(ring))
                }
                _ => None,
            }
        }

        pub fn geometry_type(&self) -> GeometryType {
            egml::model::common::HasGeometryType::geometry_type(&self.0).into()
        }

        /// The positions, without the repeated closing position.
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn points<'a>(&'a self) -> Box<DirectPositionIterator<'a>> {
            Box::new(DirectPositionIterator(
                self.0.points().iter().collect::<Vec<_>>().into_iter(),
            ))
        }

        pub fn length_3d(&self) -> f64 {
            self.0.length_3d()
        }

        pub fn area_3d(&self) -> f64 {
            self.0.area_3d()
        }

        /// Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
        pub fn compute_envelope(&self) -> Option<Box<Envelope>> {
            egml::model::common::ComputeEnvelope::compute_envelope(&self.0)
                .map(|envelope| Box::new(Envelope(envelope)))
        }
    }

    /// Iterates over rings (e.g. a polygon's interior rings), borrowed from a city model.
    #[diplomat::opaque_mut]
    pub struct AbstractRingKindIterator<'a>(
        pub(crate) std::slice::Iter<'a, egml::model::geometry::primitives::AbstractRingKind>,
    );

    impl<'a> AbstractRingKindIterator<'a> {
        #[diplomat::attr(auto, iterator)]
        #[allow(clippy::should_implement_trait)] // Diplomat's iterator protocol, not `Iterator`
        pub fn next(&mut self) -> Option<&'a AbstractRingKind> {
            self.0.next().map(AbstractRingKind::transparent_convert)
        }
    }
}

pub use ffi::{AbstractRingKind, AbstractRingKindIterator};
