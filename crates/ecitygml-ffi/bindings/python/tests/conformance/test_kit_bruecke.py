"""The cases of crates/ecitygml/tests/conformance/kit-bruecke.md."""

from pathlib import Path

import pytest

from conformance.helpers import close, read
from ecitygml import Bridge, CityModel, FeatureType, GmlReader, GmlWriter

BRIDGE_ID = "_Modellbahnbruecke-LoD2-V03_BD.rx3tFkxPQkL5qDXML1W7"


@pytest.fixture(scope="module")
def model() -> CityModel:
    return read("kit-bruecke", "Modellbahnbruecke-LoD2-V03__v3.gml")


def bridge(city_model: CityModel) -> Bridge:
    return next(b for f in city_model.iter_features() if (b := Bridge.try_from(f)) is not None)


def corner(position: object) -> tuple[float, float, float]:
    return (position.x(), position.y(), position.z())


def feature_types(city_model: CityModel) -> list[str]:
    # Two returned FeatureType values never compare equal (only one against the class constant), hence `str`.
    return [str(f.feature_type()) for f in city_model.iter_features()]


def test_bridge_city_model(model: CityModel) -> None:
    assert model.city_objects_len() == 1
    envelope = model.bounded_by().envelope()
    assert corner(envelope.lower_corner()) == close((457644.585, 5439126.455, 109.0))
    assert corner(envelope.upper_corner()) == close((457708.084, 5439157.169, 124.3))
    expected = (
        [FeatureType.CityModel, FeatureType.Bridge, FeatureType.Appearance]
        + [FeatureType.ParameterizedTexture] * 3
        + [FeatureType.BridgeInstallation] * 2
        + [FeatureType.BridgeConstructiveElement] * 11
    )
    assert feature_types(model) == [str(t) for t in expected]
    assert len(list(model.iter_city_objects())) == 14


def test_bridge_attributes(model: CityModel) -> None:
    b = bridge(model)
    assert b.feature_id().as_str() == BRIDGE_ID
    assert list(b.names()) == []
    assert b.class_() is None
    assert list(b.functions()) == []
    assert list(b.usages()) == []
    assert list(b.bridge_parts()) == []
    assert list(b.boundaries()) == []
    assert b.date_of_construction() is None
    assert b.creation_date() is None
    assert list(b.heights()) == []
    assert list(b.occupancies()) == []
    assert list(b.generic_attributes()) == []
    assert list(b.external_references()) == []


def test_bridge_geometry(model: CityModel) -> None:
    b = bridge(model)
    envelope = b.bounded_by().envelope()
    assert corner(envelope.lower_corner()) == close((457645.136, 5439126.692, 115.3))
    assert corner(envelope.upper_corner()) == close((457707.533, 5439156.931, 116.2))
    prop = b.lod2_multi_surface()
    assert prop.href() is None
    multi_surface = prop.object()
    assert len(list(multi_surface.surface_member())) == 18
    assert multi_surface.area_3d() == close(795.4201811265907)
    triangulation = multi_surface.triangulate()
    assert len(list(triangulation.surface().triangles())) == 60
    assert not triangulation.has_skipped()
    assert b.lod1_solid() is None
    assert b.lod2_solid() is None
    assert b.lod3_multi_surface() is None


def test_bridge_round_trip(model: CityModel, tmp_path: Path) -> None:
    path = tmp_path / "round-trip.gml"
    GmlWriter.from_path(str(path)).finish(model)
    written = GmlReader.from_path(str(path)).finish()
    assert feature_types(written) == feature_types(model)
    assert bridge(written).feature_id().as_str() == BRIDGE_ID
