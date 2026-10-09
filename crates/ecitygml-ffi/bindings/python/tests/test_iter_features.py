"""CityModel.iter_features() and iter_city_objects() (lazy iterators) and city_objects_len().

Ported from the former PyO3 bindings' `test_city_model.py` (renamed: `test_city_model.py`
already holds the Diplomat bindings' own city-model tests). Filtering by class
(`iter_features(WallSurface)`) is `try_from` over `iter_features()` here. Not ported (not in the
Diplomat bindings): filtering arguments (`iter_city_objects(Road)`; `city_objects_of` filters with
`try_from` instead) and their errors, the `Feature` alias, iterating while the model is mutated;
the former laziness tests about unbound feature types no longer apply, since every feature can be
iterated.

Differs from the former bindings: `iter_features()` also yields the city model itself, first, as Rust's
`IterFeatures::iter_features` does; the former bindings skipped it.
"""

from collections.abc import Iterator
from typing import Any

from conftest import ASAM_JUNCTION, FZK_LOD3, city_objects_of, features_of, read_model
from ecitygml import Building, FeatureType, Road, TrafficSpace, WallSurface, WindowSurface


class TestIterFeatures:
    def test_is_an_iterator(self, fzk_lod3_model: Any) -> None:
        features = fzk_lod3_model.iter_features()
        assert isinstance(features, Iterator)
        assert iter(features) is features

    def test_single_pass(self, fzk_lod3_model: Any) -> None:
        features = fzk_lod3_model.iter_features()
        assert sum(WallSurface.try_from(f) is not None for f in features) == 4
        assert list(features) == []

    def test_returns_nested_features(self, fzk_lod3_model: Any) -> None:
        types = [f.feature_type() for f in fzk_lod3_model.iter_features()]
        assert types.count(FeatureType.Building) == 1
        assert types.count(FeatureType.WallSurface) == 4
        assert types.count(FeatureType.WindowSurface) == 11
        assert types.count(FeatureType.DoorSurface) == 2

    def test_yields_city_model_itself_first(self, fzk_lod3_model: Any) -> None:
        # Archived as `test_excludes_city_model_itself`: Rust yields the city model, once and first.
        types = [f.feature_type() for f in fzk_lod3_model.iter_features()]
        assert types[0] == FeatureType.CityModel
        assert types.count(FeatureType.CityModel) == 1

    def test_filter_by_class(self, fzk_lod3_model: Any) -> None:
        walls = features_of(fzk_lod3_model, WallSurface)
        assert len(walls) == 4
        assert all(isinstance(w, WallSurface) for w in walls)

    def test_filter_by_class_without_matches(self, fzk_lod3_model: Any) -> None:
        assert features_of(fzk_lod3_model, Road) == []

    def test_filter_by_feature_type_matches_class(self, fzk_lod3_model: Any) -> None:
        features = list(fzk_lod3_model.iter_features())
        by_type = [i for i, f in enumerate(features) if f.feature_type() == FeatureType.WindowSurface]
        by_class = [i for i, f in enumerate(features) if WindowSurface.try_from(f) is not None]
        assert by_type == by_class

    def test_feature_type_matches_class(self, asam_junction_model: Any) -> None:
        for feature in asam_junction_model.iter_features():
            if TrafficSpace.try_from(feature) is not None:
                assert feature.feature_type() == FeatureType.TrafficSpace


class TestLaziness:
    def test_filtered_traffic_spaces(self, asam_junction_model: Any) -> None:
        assert len(features_of(asam_junction_model, TrafficSpace)) == 7

    def test_iterator_keeps_model_alive(self) -> None:
        features = read_model(FZK_LOD3).iter_features()  # model not referenced elsewhere
        assert sum(WallSurface.try_from(f) is not None for f in features) == 4


class TestCityObjects:
    def test_city_objects_len_counts_direct_members(self, fzk_lod3_model: Any) -> None:
        assert fzk_lod3_model.city_objects_len() == 1


class TestIterCityObjects:
    def test_all_depths(self, fzk_lod3_model: Any) -> None:
        # As in Rust, city objects at every depth, not only the direct members, and no city model.
        types = [c.feature_type() for c in fzk_lod3_model.iter_city_objects()]
        assert types.count(FeatureType.Building) == 1
        assert types.count(FeatureType.WallSurface) == 4
        assert FeatureType.CityModel not in types

    def test_filter_by_class(self, asam_junction_model: Any) -> None:
        roads = city_objects_of(asam_junction_model, Road)
        assert [r.id().as_str() for r in roads] == ["UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f"]
        assert all(isinstance(r, Road) for r in roads)

    def test_filter_by_feature_type(self, asam_junction_model: Any) -> None:
        types = [c.feature_type() for c in asam_junction_model.iter_city_objects()]
        assert types.count(FeatureType.Road) == 1
        assert types.count(FeatureType.Building) == 0
        assert city_objects_of(asam_junction_model, Building) == []

    def test_is_lazy(self) -> None:
        # Archived with an error for unbound types further on; every city object is bound here.
        model = read_model(ASAM_JUNCTION)
        city_objects = model.iter_city_objects()
        assert next(city_objects).feature_type() == FeatureType.Road
        assert len(list(city_objects)) > 0
