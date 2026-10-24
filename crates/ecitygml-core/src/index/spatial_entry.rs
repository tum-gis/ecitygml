use crate::model::core::refs::AbstractCityObjectKindRef;
use ::bvh::aabb::{Aabb, Bounded};
use ::bvh::bounding_hierarchy::BHShape;
use egml::model::common::ComputeEnvelope;
use egml::model::feature::AsAbstractFeature;
use egml::model::geometry::Envelope;
use slotmap::DefaultKey;

/// Why a city object could not be inserted into the index.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub(super) enum SkipReason {
    /// Neither the geometry nor the stored bounding shape yield an envelope.
    NoEnvelope,
    /// The envelope has a NaN or infinite coordinate.
    NonFiniteEnvelope,
}

/// A city object in the BVH, referenced by its arena key.
pub(super) struct SpatialEntry {
    key: DefaultKey,
    aabb: Aabb<f64, 3>,
    node_index: usize,
}

impl SpatialEntry {
    /// Creates an entry from the envelope of the object's own geometry, falling back to its
    /// stored `gml:boundedBy` envelope.
    pub(super) fn from_city_object(
        key: DefaultKey,
        city_object: AbstractCityObjectKindRef<'_>,
    ) -> Result<Self, SkipReason> {
        let envelope = city_object
            .compute_envelope()
            .or_else(|| city_object.bounded_by()?.envelope().cloned())
            .ok_or(SkipReason::NoEnvelope)?;
        let aabb = envelope_to_aabb(&envelope).ok_or(SkipReason::NonFiniteEnvelope)?;

        Ok(Self {
            key,
            aabb,
            node_index: 0,
        })
    }

    pub(super) fn key(&self) -> DefaultKey {
        self.key
    }
}

impl Bounded<f64, 3> for SpatialEntry {
    fn aabb(&self) -> Aabb<f64, 3> {
        self.aabb
    }
}

impl BHShape<f64, 3> for SpatialEntry {
    fn bh_node_index(&self) -> usize {
        self.node_index
    }

    fn set_bh_node_index(&mut self, index: usize) {
        self.node_index = index;
    }
}

/// Converts an envelope to an AABB, or returns `None` if any coordinate is NaN or infinite.
///
/// Zero-extent AABBs (flat, linear or point geometry) need no padding: the intersection test of
/// the `bvh` crate is inclusive, so touching boxes intersect.
pub(super) fn envelope_to_aabb(envelope: &Envelope) -> Option<Aabb<f64, 3>> {
    let lower = envelope.lower_corner();
    let upper = envelope.upper_corner();
    let min = [lower.x(), lower.y(), lower.z()];
    let max = [upper.x(), upper.y(), upper.z()];
    if !min.iter().chain(max.iter()).all(|x| x.is_finite()) {
        return None;
    }

    Some(Aabb::with_bounds(min.into(), max.into()))
}
