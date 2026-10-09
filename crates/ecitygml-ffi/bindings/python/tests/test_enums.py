"""The FeatureType and LevelOfDetail enums.

Ported from the former PyO3 bindings' `test_enums.py`. Diplomat's nanobind backend generates
no enum methods (Rust's `as_index()`), but the `LevelOfDetail.Zero` … `Three` constants are nanobind
enum members whose `.value` is the discriminant, set to the index in the bridge. Levels returned by
getters (e.g. `ReliefFeature.lod()`) are wrapper objects without `.value`; they compare equal to the
constants. Concrete
classes have no `feature_type()`; the features of `iter_features()` (`AbstractFeatureKindRef`) do.
"""

from typing import Any

from conftest import features_of
from ecitygml import Building, FeatureType, LevelOfDetail, Road


class TestFeatureType:
    def test_equality(self) -> None:
        assert FeatureType.Building == FeatureType.Building

    def test_inequality(self) -> None:
        assert FeatureType.Road != FeatureType.Building

    def test_value_zero(self) -> None:
        assert LevelOfDetail.Zero.value == 0

    def test_value_one(self) -> None:
        assert LevelOfDetail.One.value == 1

    def test_value_two(self) -> None:
        assert LevelOfDetail.Two.value == 2

    def test_value_three(self) -> None:
        assert LevelOfDetail.Three.value == 3

    def test_repr_contains_variant_name(self) -> None:
        assert "Building" in repr(FeatureType.Building)

    def test_matches_building_feature_type(self, fzk_lod2_model: Any) -> None:
        feature = next(f for f in fzk_lod2_model.iter_features() if Building.try_from(f) is not None)
        assert feature.feature_type() == FeatureType.Building

    def test_matches_road_feature_type(self, asam_junction_model: Any) -> None:
        feature = next(f for f in asam_junction_model.iter_features() if Road.try_from(f) is not None)
        assert feature.feature_type() == FeatureType.Road
        assert len(features_of(asam_junction_model, Road)) == 1

    def test_all_expected_variants_exist(self) -> None:
        expected = [
            "Building",
            "Road",
            "Section",
            "Intersection",
            "TrafficSpace",
            "TrafficArea",
            "AuxiliaryTrafficSpace",
            "AuxiliaryTrafficArea",
            "WallSurface",
            "RoofSurface",
            "GroundSurface",
            "DoorSurface",
            "WindowSurface",
            "TinRelief",
            "ReliefFeature",
            "SolitaryVegetationObject",
            "CityFurniture",
        ]
        for name in expected:
            assert hasattr(FeatureType, name), f"Missing FeatureType.{name}"


class TestLevelOfDetail:
    def test_equality(self) -> None:
        assert LevelOfDetail.One == LevelOfDetail.One

    def test_inequality(self) -> None:
        assert LevelOfDetail.One != LevelOfDetail.Two

    def test_value_zero(self) -> None:
        assert LevelOfDetail.Zero.value == 0

    def test_value_one(self) -> None:
        assert LevelOfDetail.One.value == 1

    def test_value_two(self) -> None:
        assert LevelOfDetail.Two.value == 2

    def test_value_three(self) -> None:
        assert LevelOfDetail.Three.value == 3

    def test_repr_contains_variant_name(self) -> None:
        assert "One" in repr(LevelOfDetail.One)
