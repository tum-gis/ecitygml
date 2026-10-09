"""Bridge and BridgePart (AbstractBridge getters).

Ported from the former PyO3 bindings' `test_bridge.py`. Not ported (not in the Diplomat
bindings): `repr`. `iter_features()` also yields the city model first.
"""

from pathlib import Path
from typing import Any

import pytest

from conftest import FZK_LOD2, city_objects_of, features_of, objects, read_model
from ecitygml import CityModel, FeatureType, GmlWriter, Bridge, BridgePart

# No fixture contains a bridge: the FZK LoD2 file header (namespaces, envelope) is reused with
# a single bridge member, its properties in the order of the CityGML 3.0 schema.
MEMBER = """<cityObjectMember>
    <brid:Bridge gml:id="bridge_1">
      <con:dateOfConstruction>1990-05-01</con:dateOfConstruction>
      <brid:class codeSpace="https://example.org/bridge_class">1000</brid:class>
      <brid:function>1010</brid:function>
      <brid:function>1020</brid:function>
      <brid:usage>1000</brid:usage>
      <brid:isMovable>true</brid:isMovable>
      <brid:bridgePart>
        <brid:BridgePart gml:id="bridge_part_1">
          <brid:isMovable>false</brid:isMovable>
        </brid:BridgePart>
      </brid:bridgePart>
    </brid:Bridge>
  </cityObjectMember>
</CityModel>
"""


@pytest.fixture(scope="module")
def bridge_path(tmp_path_factory: pytest.TempPathFactory) -> Path:
    text = FZK_LOD2.read_text()
    header = text[: text.index("<cityObjectMember>")]
    path = tmp_path_factory.mktemp("bridge") / "bridge.gml"
    path.write_text(header + MEMBER)
    return path


@pytest.fixture(scope="module")
def model(bridge_path: Path) -> CityModel:
    return read_model(bridge_path)


@pytest.fixture(scope="module")
def bridge(model: CityModel) -> Bridge:
    return features_of(model, Bridge)[0]


def ymd(date: Any) -> tuple[int, int, int]:
    return (date.year(), date.month(), date.day())


class TestFeatures:
    def test_bridge_and_part_are_features(self, model: CityModel) -> None:
        types = [f.feature_type() for f in model.iter_features()]
        assert types == [FeatureType.CityModel, FeatureType.Bridge, FeatureType.BridgePart]

    def test_filter_by_feature_type(self, model: CityModel) -> None:
        features = list(model.iter_features())
        bridges = [Bridge.try_from(f) for f in features if f.feature_type() == FeatureType.Bridge]
        assert [x.id().as_str() for x in bridges] == ["bridge_1"]
        assert [p.id().as_str() for p in features_of(model, BridgePart)] == ["bridge_part_1"]


    def test_city_objects(self, model: CityModel) -> None:
        assert model.city_objects_len() == 1
        types = [c.feature_type() for c in model.iter_city_objects()]
        assert types == [FeatureType.Bridge, FeatureType.BridgePart]
        assert len(city_objects_of(model, BridgePart)) == 1

class TestAbstractBridge:
    def test_class(self, bridge: Bridge) -> None:
        assert bridge.class_() is not None
        assert bridge.class_().value() == "1000"
        assert bridge.class_().code().code_space() == "https://example.org/bridge_class"

    def test_functions_and_usages(self, bridge: Bridge) -> None:
        assert [f.value() for f in bridge.functions()] == ["1010", "1020"]
        assert [u.value() for u in bridge.usages()] == ["1000"]
        assert all(f.code().code_space() is None for f in bridge.functions())

    def test_is_movable(self, bridge: Bridge) -> None:
        assert bridge.is_movable() is True
        assert objects(bridge.bridge_parts())[0].is_movable() is False

    def test_inherits_construction_getters(self, bridge: Bridge) -> None:
        assert ymd(bridge.date_of_construction()) == (1990, 5, 1)
        assert list(bridge.heights()) == []

    def test_bridge_parts(self, model: CityModel, bridge: Bridge) -> None:
        parts = objects(bridge.bridge_parts())
        assert len(parts) == 1
        assert isinstance(parts[0], BridgePart)
        part_types = [f.feature_type() for f in model.iter_features() if BridgePart.try_from(f) is not None]
        assert part_types == [FeatureType.BridgePart]
        assert parts[0].class_() is None
        assert list(parts[0].functions()) == []


def test_write_round_trip(model: CityModel, tmp_path: Path) -> None:
    path = tmp_path / "written.gml"
    GmlWriter.from_path(str(path)).finish(model)
    written = read_model(path)
    bridge = features_of(written, Bridge)[0]
    assert bridge.class_() is not None
    assert (bridge.class_().value(), bridge.class_().code().code_space()) == (
        "1000",
        "https://example.org/bridge_class",
    )
    assert [f.value() for f in bridge.functions()] == ["1010", "1020"]
    assert bridge.is_movable() is True
    assert ymd(bridge.date_of_construction()) == (1990, 5, 1)
    assert [p.id().as_str() for p in objects(bridge.bridge_parts())] == ["bridge_part_1"]
