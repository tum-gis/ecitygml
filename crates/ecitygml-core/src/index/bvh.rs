use crate::Error;
use crate::arena::CityModelArena;
use crate::index::spatial_entry::{SkipReason, SpatialEntry, envelope_to_aabb};
use crate::model::core::refs::AbstractCityObjectKindRef;
use crate::model::core::{AsAbstractFeature, CityModel};
use ::bvh::bvh::Bvh;
use egml::model::geometry::{DirectPosition, Envelope};
use slotmap::DefaultKey;
use tracing::{debug, warn};

/// A bounding volume hierarchy over the city objects of a [`CityModelArena`].
///
/// Every city object is represented by the axis-aligned bounding box of its own geometry, falling
/// back to its stored `gml:boundedBy` envelope. Geometry of nested city objects is not included:
/// in the arena, nested objects (e.g. the `TrafficSpace`s of a `Road`) are separate entries with
/// their own boxes. Objects without an envelope, or with a non-finite one, are skipped.
///
/// Entries reference objects by their arena [`DefaultKey`], which stays valid for the lifetime of
/// the index and can be resolved with [`CityModelArena::get_city_object`].
///
/// Queries are a coarse filter: they return every object whose bounding box intersects the query
/// box, including boxes that only touch it.
pub struct BvhIndex {
    bvh: Bvh<f64, 3>,
    entries: Vec<SpatialEntry>,
    arena: CityModelArena,
}

impl BvhIndex {
    /// Builds the index over all city objects of `arena`, taking ownership of it.
    pub fn from_arena(arena: CityModelArena) -> Self {
        let mut entries = Vec::new();
        let mut without_envelope = 0usize;
        for (key, city_object) in arena.iter_city_objects_with_keys() {
            match SpatialEntry::from_city_object(key, city_object) {
                Ok(entry) => entries.push(entry),
                Err(SkipReason::NoEnvelope) => without_envelope += 1,
                Err(SkipReason::NonFiniteEnvelope) => warn!(
                    id = %city_object.feature_id(),
                    "skipping city object with a non-finite envelope in the spatial index"
                ),
            }
        }
        debug!(
            indexed = entries.len(),
            without_envelope, "built spatial index; city objects without an envelope were skipped"
        );

        let bvh = Bvh::build(&mut entries);
        Self {
            bvh,
            entries,
            arena,
        }
    }

    /// Flattens `city_model` into an arena and builds the index over it.
    pub fn from_city_model(city_model: CityModel) -> Result<Self, Error> {
        let arena = CityModelArena::from_city_model(city_model)?;
        Ok(Self::from_arena(arena))
    }

    /// The arena holding the indexed objects.
    pub fn arena(&self) -> &CityModelArena {
        &self.arena
    }

    /// Consumes the index and returns the arena.
    pub fn into_arena(self) -> CityModelArena {
        self.arena
    }

    /// The number of indexed city objects.
    pub fn len(&self) -> usize {
        self.entries.len()
    }

    /// Returns `true` if no city object is indexed.
    pub fn is_empty(&self) -> bool {
        self.entries.is_empty()
    }

    /// Returns the arena keys of all objects whose bounding box intersects `envelope`.
    ///
    /// A query envelope with a NaN or infinite coordinate matches nothing and logs a warning.
    pub fn query_envelope_keys<'a>(
        &'a self,
        envelope: &Envelope,
    ) -> impl Iterator<Item = DefaultKey> + use<'a> {
        let hits = match envelope_to_aabb(envelope) {
            Some(query) => self.bvh.traverse(&query, &self.entries),
            None => {
                warn!(
                    ?envelope,
                    "ignoring spatial query with a non-finite envelope"
                );
                Vec::new()
            }
        };
        hits.into_iter().map(SpatialEntry::key)
    }

    /// Returns all city objects whose bounding box intersects `envelope`.
    ///
    /// A query envelope with a NaN or infinite coordinate matches nothing and logs a warning.
    pub fn query_envelope<'a>(
        &'a self,
        envelope: &Envelope,
    ) -> impl Iterator<Item = AbstractCityObjectKindRef<'a>> + use<'a> {
        self.query_envelope_keys(envelope)
            .filter_map(|key| self.arena.get_city_object(key))
    }

    /// Returns all city objects whose bounding box intersects the cube of half-size `radius`
    /// around `point`.
    ///
    /// # Errors
    ///
    /// Returns [`Error::GmlError`] wrapping [`egml::Error::InvalidDistance`] if `radius` is
    /// negative, NaN or infinite (see [`Envelope::enlarge`]).
    pub fn query_point<'a>(
        &'a self,
        point: &DirectPosition,
        radius: f64,
    ) -> Result<impl Iterator<Item = AbstractCityObjectKindRef<'a>> + use<'a>, Error> {
        let envelope = Envelope::new(*point, *point)?.enlarge(radius)?;
        Ok(self.query_envelope(&envelope))
    }
}

#[cfg(test)]
mod tests {
    use super::BvhIndex;
    use crate::Error;
    use crate::arena::CityModelArena;
    use crate::model::core::refs::AbstractCityObjectKindRef;
    use crate::model::core::{
        AbstractCityObjectProperty, AsAbstractFeature, AsAbstractSpaceMut, CityModel,
    };
    use crate::model::transportation::enums::GranularityValue;
    use crate::model::transportation::{
        AsAbstractTransportationSpaceMut, Road, TrafficSpace, TrafficSpaceProperty,
    };
    use egml::model::base::Id;
    use egml::model::feature::{AsAbstractFeatureMut, BoundingShape};
    use egml::model::geometry::aggregates::{MultiCurve, MultiCurveProperty};
    use egml::model::geometry::primitives::{AbstractCurveProperty, LineString};
    use egml::model::geometry::{DirectPosition, Envelope};

    fn id(value: &str) -> Id {
        Id::try_from(value).expect("valid id")
    }

    fn position(x: f64, y: f64, z: f64) -> DirectPosition {
        DirectPosition::new(x, y, z).expect("finite")
    }

    fn envelope(lower: [f64; 3], upper: [f64; 3]) -> Envelope {
        Envelope::new(
            position(lower[0], lower[1], lower[2]),
            position(upper[0], upper[1], upper[2]),
        )
        .expect("valid envelope")
    }

    /// A lod0 multi curve consisting of one line string through `points`.
    fn multi_curve(points: &[[f64; 3]]) -> MultiCurveProperty {
        let line_string = LineString::new(points.iter().map(|p| position(p[0], p[1], p[2])))
            .expect("line string");
        let curve = AbstractCurveProperty::from_object(line_string.into());
        MultiCurveProperty::from_object(MultiCurve::new([curve]).expect("multi curve"))
    }

    /// A road whose lod0 centre line runs through `points`.
    fn road(name: &str, points: &[[f64; 3]]) -> Road {
        let mut road = Road::new(id(name));
        road.set_lod0_multi_curve(Some(multi_curve(points)));
        road
    }

    fn city_model(roads: Vec<Road>) -> CityModel {
        let mut city_model = CityModel::new(id("city_model"));
        for road in roads {
            city_model
                .push_city_object_member(AbstractCityObjectProperty::from_object(road.into()));
        }
        city_model
    }

    fn index(roads: Vec<Road>) -> BvhIndex {
        BvhIndex::from_city_model(city_model(roads)).expect("index")
    }

    /// The sorted ids of the query results.
    fn ids<'a>(results: impl Iterator<Item = AbstractCityObjectKindRef<'a>>) -> Vec<String> {
        let mut ids: Vec<String> = results.map(|x| x.feature_id().to_string()).collect();
        ids.sort();
        ids
    }

    /// Two parallel flat roads, ten metres apart along y.
    fn two_roads() -> BvhIndex {
        index(vec![
            road("road_a", &[[0.0, 0.0, 5.0], [10.0, 0.0, 5.0]]),
            road("road_b", &[[0.0, 10.0, 5.0], [10.0, 10.0, 5.0]]),
        ])
    }

    #[test]
    fn test_query_around_one_object_returns_exactly_that_object() {
        let index = two_roads();

        let query = envelope([4.0, -1.0, 0.0], [6.0, 1.0, 10.0]);

        assert_eq!(ids(index.query_envelope(&query)), vec!["road_a"]);
    }

    #[test]
    fn test_query_in_empty_space_returns_nothing() {
        let index = two_roads();

        let query = envelope([100.0, 100.0, 0.0], [110.0, 110.0, 10.0]);

        assert_eq!(index.query_envelope(&query).count(), 0);
    }

    #[test]
    fn test_enlarged_query_finds_object_missed_by_plain_query() {
        let index = two_roads();
        // Between the two roads, two metres away from road_a.
        let query = envelope([4.0, 2.0, 0.0], [6.0, 3.0, 10.0]);

        assert_eq!(index.query_envelope(&query).count(), 0);
        let enlarged = query.enlarge(2.5).expect("valid distance");
        assert_eq!(ids(index.query_envelope(&enlarged)), vec!["road_a"]);
    }

    #[test]
    fn test_point_query_rejects_invalid_radius() {
        let index = two_roads();

        for radius in [-1.0, f64::NAN, f64::INFINITY] {
            assert!(matches!(
                index.query_point(&position(0.0, 0.0, 0.0), radius),
                Err(Error::GmlError(egml::Error::InvalidDistance { .. }))
            ));
        }
    }

    #[test]
    fn test_overlapping_objects_are_both_returned() {
        let index = index(vec![
            road("road_a", &[[0.0, 0.0, 0.0], [10.0, 10.0, 0.0]]),
            road("road_b", &[[0.0, 10.0, 0.0], [10.0, 0.0, 0.0]]),
            road("road_c", &[[50.0, 50.0, 0.0], [60.0, 60.0, 0.0]]),
        ]);

        let query = envelope([4.0, 4.0, -1.0], [6.0, 6.0, 1.0]);

        assert_eq!(ids(index.query_envelope(&query)), vec!["road_a", "road_b"]);
    }

    #[test]
    fn test_flat_curve_is_found_by_query_touching_its_plane() {
        let index = index(vec![road("flat", &[[0.0, 0.0, 3.0], [10.0, 5.0, 3.0]])]);

        // A query that is itself flat and lies exactly in the curve's plane.
        let query = envelope([2.0, 0.0, 3.0], [3.0, 5.0, 3.0]);

        assert_eq!(ids(index.query_envelope(&query)), vec!["flat"]);
    }

    #[test]
    fn test_degenerate_point_geometry_is_found() {
        // Line strings reject repeated positions, so the point comes from a stored bounding shape.
        let mut point = Road::new(id("point"));
        point.set_bounded_by(Some(BoundingShape::new(envelope(
            [5.0, 5.0, 5.0],
            [5.0, 5.0, 5.0],
        ))));
        let index = index(vec![
            road("vertical", &[[1.0, 1.0, 0.0], [1.0, 1.0, 20.0]]),
            point,
        ]);

        assert_eq!(
            ids(index
                .query_point(&position(1.0, 1.0, 10.0), 0.0)
                .expect("valid radius")),
            vec!["vertical"]
        );
        assert_eq!(
            ids(index
                .query_point(&position(5.0, 5.0, 5.0), 0.0)
                .expect("valid radius")),
            vec!["point"]
        );
        assert_eq!(
            ids(index
                .query_point(&position(5.5, 5.0, 5.0), 1.0)
                .expect("valid radius")),
            vec!["point"]
        );
    }

    #[test]
    fn test_objects_without_geometry_are_skipped() {
        let index = index(vec![
            Road::new(id("no_geometry")),
            road("road_a", &[[0.0, 0.0, 0.0], [10.0, 0.0, 0.0]]),
        ]);

        assert_eq!(index.len(), 1);
        let everything = envelope([-1e9, -1e9, -1e9], [1e9, 1e9, 1e9]);
        assert_eq!(ids(index.query_envelope(&everything)), vec!["road_a"]);
    }

    #[test]
    fn test_stored_bounding_shape_is_used_when_geometry_is_missing() {
        let mut road = Road::new(id("bounded_only"));
        road.set_bounded_by(Some(BoundingShape::new(envelope(
            [0.0, 0.0, 0.0],
            [1.0, 1.0, 1.0],
        ))));
        let index = index(vec![road]);

        let query = envelope([0.5, 0.5, 0.5], [2.0, 2.0, 2.0]);

        assert_eq!(ids(index.query_envelope(&query)), vec!["bounded_only"]);
    }

    #[test]
    fn test_nested_city_objects_are_indexed_individually() {
        let mut traffic_space = TrafficSpace::new(id("traffic_space"), GranularityValue::Lane);
        traffic_space.set_lod0_multi_curve(Some(multi_curve(&[[0.0, 0.0, 0.0], [1.0, 0.0, 0.0]])));
        let mut road = road("road_a", &[[0.0, 0.0, 0.0], [10.0, 0.0, 0.0]]);
        road.push_traffic_space(TrafficSpaceProperty::from_object(traffic_space));
        let index = index(vec![road]);

        let near_start = envelope([0.0, -1.0, -1.0], [0.5, 1.0, 1.0]);
        let near_end = envelope([9.0, -1.0, -1.0], [9.5, 1.0, 1.0]);

        assert_eq!(
            ids(index.query_envelope(&near_start)),
            vec!["road_a", "traffic_space"]
        );
        assert_eq!(ids(index.query_envelope(&near_end)), vec!["road_a"]);
    }

    #[test]
    fn test_empty_model_gives_empty_index() {
        let index = index(Vec::new());

        assert!(index.is_empty());
        let query = envelope([0.0, 0.0, 0.0], [1.0, 1.0, 1.0]);
        assert_eq!(index.query_envelope(&query).count(), 0);
        assert_eq!(
            index
                .query_point(&position(0.0, 0.0, 0.0), 1.0)
                .expect("valid radius")
                .count(),
            0
        );
    }

    #[test]
    fn test_non_finite_query_returns_nothing() {
        let index = two_roads();
        let query = Envelope::new_unchecked(
            DirectPosition::new_unchecked(f64::NEG_INFINITY, 0.0, 0.0),
            DirectPosition::new_unchecked(10.0, 10.0, 10.0),
        );

        assert_eq!(index.query_envelope(&query).count(), 0);
    }

    #[test]
    fn test_non_finite_bounding_shape_is_skipped() {
        let mut road = Road::new(id("broken"));
        road.set_bounded_by(Some(BoundingShape::new(Envelope::new_unchecked(
            DirectPosition::new_unchecked(0.0, f64::NEG_INFINITY, 0.0),
            DirectPosition::new_unchecked(1.0, 1.0, 1.0),
        ))));
        let index = index(vec![road]);

        assert!(index.is_empty());
    }

    #[test]
    fn test_results_resolve_through_the_arena() {
        let index = two_roads();
        let query = envelope([4.0, 9.0, 0.0], [6.0, 11.0, 10.0]);

        let keys: Vec<_> = index.query_envelope_keys(&query).collect();

        assert_eq!(keys.len(), 1);
        let resolved = index
            .arena()
            .get_city_object(keys[0])
            .expect("key in arena");
        assert_eq!(resolved.feature_id().to_string(), "road_b");
    }

    #[test]
    fn test_index_from_arena_matches_index_from_city_model() {
        let arena = CityModelArena::from_city_model(city_model(vec![road(
            "road_a",
            &[[0.0, 0.0, 0.0], [1.0, 0.0, 0.0]],
        )]))
        .expect("arena");
        let index = BvhIndex::from_arena(arena);

        assert_eq!(index.len(), 1);
        assert_eq!(index.arena().iter_city_objects().count(), 1);
    }
}
