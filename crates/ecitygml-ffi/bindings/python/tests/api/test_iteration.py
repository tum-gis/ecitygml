"""The cases of crates/ecitygml/tests/api/iteration.md."""

import gc

import pytest

from api.helpers import feature_types, fixture
from conftest import read_model
from ecitygml import FeatureType, WallSurface

FZK_LOD3 = fixture("fzk-haus/FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml")
ASAM_ROAD_SHAPE = fixture("asam-opendrive/ASAM-UC_RoadShape.gml")


def test_iterator_exhausted() -> None:
    features = read_model(FZK_LOD3).iter_features()
    assert sum(1 for _ in features) == 22
    with pytest.raises(StopIteration):
        next(features)
    with pytest.raises(StopIteration):
        next(features)


def test_iterator_stopped_early() -> None:
    city_model = read_model(ASAM_ROAD_SHAPE)
    features = city_model.iter_features()
    assert next(features).feature_type() == FeatureType.CityModel
    del features
    gc.collect()
    assert len(list(city_model.iter_features())) == 11
    assert city_model.city_objects_len() == 1


def test_iterators_independent() -> None:
    city_model = read_model(FZK_LOD3)
    first, second = city_model.iter_features(), city_model.iter_features()
    a, b = [], []
    for x, y in zip(first, second, strict=True):
        a.append(str(x.feature_type()))
        b.append(str(y.feature_type()))
    assert len(a) == 22
    assert a == b == feature_types(city_model)


def test_iterator_keeps_model_alive() -> None:
    features = read_model(FZK_LOD3).iter_features()
    gc.collect()
    assert sum(WallSurface.try_from(f) is not None for f in features) == 4


def test_native_iteration() -> None:
    types = []
    for feature in read_model(FZK_LOD3).iter_features():
        types.append(feature.feature_type())
    assert len(types) == 22
    assert types[0] == FeatureType.CityModel
