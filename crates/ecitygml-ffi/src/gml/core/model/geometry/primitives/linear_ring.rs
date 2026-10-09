//! `LinearRing` (`gml:LinearRing`).

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
    use crate::gml::core::model::geometry::primitives::abstract_ring_kind::ffi::AbstractRingKind;

    /// A linear ring, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct LinearRing(egml::model::geometry::primitives::LinearRing);

    impl LinearRing {
        impl_gml_abstract_object_methods! {}
        impl_gml_abstract_gml_methods! {}

        /// The ring as a linear ring, or none if it is another type (Rust: `LinearRing::try_from`,
        /// which takes the ring by value). Follows nested rings (`AbstractRingKind::AbstractRingKind`).
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn try_from<'a>(ring: &'a AbstractRingKind) -> Option<&'a LinearRing> {
            let mut ring = &ring.0;
            loop {
                match ring {
                    egml::model::geometry::primitives::AbstractRingKind::LinearRing(x) => {
                        return Some(LinearRing::transparent_convert(x));
                    }
                    egml::model::geometry::primitives::AbstractRingKind::AbstractRingKind(x) => {
                        ring = x
                    }
                }
            }
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
}

pub use ffi::LinearRing;
