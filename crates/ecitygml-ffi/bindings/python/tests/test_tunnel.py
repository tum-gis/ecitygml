"""Tunnel and TunnelPart (AbstractTunnel getters).

Ported from the former PyO3 bindings' `test_tunnel.py`. Not ported (not in the Diplomat
bindings): `repr`. `iter_features()` also yields the city model first.
"""

from pathlib import Path
from typing import Any

import pytest

from conftest import FZK_LOD2, city_objects_of, features_of, objects, read_model
from ecitygml import CityModel, FeatureType, GmlWriter, Tunnel, TunnelPart

# No fixture contains a tunnel: the FZK LoD2 file header (namespaces, envelope) is reused with
# a single tunnel member, its properties in the order of the CityGML 3.0 schema.
MEMBER = """<cityObjectMember>
    <tun:Tunnel gml:id="tunnel_1">
      <con:dateOfConstruction>1990-05-01</con:dateOfConstruction>
      <tun:class codeSpace="https://example.org/tunnel_class">1000</tun:class>
      <tun:function>1010</tun:function>
      <tun:function>1020</tun:function>
      <tun:usage>1000</tun:usage>
      <tun:tunnelPart>
        <tun:TunnelPart gml:id="tunnel_part_1">
          <tun:function>1030</tun:function>
        </tun:TunnelPart>
      </tun:tunnelPart>
    </tun:Tunnel>
  </cityObjectMember>
</CityModel>
"""


@pytest.fixture(scope="module")
def tunnel_path(tmp_path_factory: pytest.TempPathFactory) -> Path:
    text = FZK_LOD2.read_text()
    header = text[: text.index("<cityObjectMember>")]
    path = tmp_path_factory.mktemp("tunnel") / "tunnel.gml"
    path.write_text(header + MEMBER)
    return path


@pytest.fixture(scope="module")
def model(tunnel_path: Path) -> CityModel:
    return read_model(tunnel_path)


@pytest.fixture(scope="module")
def tunnel(model: CityModel) -> Tunnel:
    return features_of(model, Tunnel)[0]


def ymd(date: Any) -> tuple[int, int, int]:
    return (date.year(), date.month(), date.day())


class TestFeatures:
    def test_tunnel_and_part_are_features(self, model: CityModel) -> None:
        types = [f.feature_type() for f in model.iter_features()]
        assert types == [FeatureType.CityModel, FeatureType.Tunnel, FeatureType.TunnelPart]

    def test_filter_by_feature_type(self, model: CityModel) -> None:
        features = list(model.iter_features())
        tunnels = [Tunnel.try_from(f) for f in features if f.feature_type() == FeatureType.Tunnel]
        assert [x.id().as_str() for x in tunnels] == ["tunnel_1"]
        assert [p.id().as_str() for p in features_of(model, TunnelPart)] == ["tunnel_part_1"]


    def test_city_objects(self, model: CityModel) -> None:
        assert model.city_objects_len() == 1
        types = [c.feature_type() for c in model.iter_city_objects()]
        assert types == [FeatureType.Tunnel, FeatureType.TunnelPart]
        assert len(city_objects_of(model, TunnelPart)) == 1

class TestAbstractTunnel:
    def test_class(self, tunnel: Tunnel) -> None:
        assert tunnel.class_() is not None
        assert tunnel.class_().value() == "1000"
        assert tunnel.class_().code().code_space() == "https://example.org/tunnel_class"

    def test_functions_and_usages(self, tunnel: Tunnel) -> None:
        assert [f.value() for f in tunnel.functions()] == ["1010", "1020"]
        assert [u.value() for u in tunnel.usages()] == ["1000"]
        assert all(f.code().code_space() is None for f in tunnel.functions())

    def test_inherits_construction_getters(self, tunnel: Tunnel) -> None:
        assert ymd(tunnel.date_of_construction()) == (1990, 5, 1)
        assert list(tunnel.heights()) == []

    def test_tunnel_parts(self, model: CityModel, tunnel: Tunnel) -> None:
        parts = objects(tunnel.tunnel_parts())
        assert len(parts) == 1
        assert isinstance(parts[0], TunnelPart)
        part_types = [f.feature_type() for f in model.iter_features() if TunnelPart.try_from(f) is not None]
        assert part_types == [FeatureType.TunnelPart]
        assert parts[0].class_() is None
        assert [f.value() for f in parts[0].functions()] == ["1030"]


def test_write_round_trip(model: CityModel, tmp_path: Path) -> None:
    path = tmp_path / "written.gml"
    GmlWriter.from_path(str(path)).finish(model)
    written = read_model(path)
    tunnel = features_of(written, Tunnel)[0]
    assert tunnel.class_() is not None
    assert (tunnel.class_().value(), tunnel.class_().code().code_space()) == (
        "1000",
        "https://example.org/tunnel_class",
    )
    assert [f.value() for f in tunnel.functions()] == ["1010", "1020"]
    assert ymd(tunnel.date_of_construction()) == (1990, 5, 1)
    assert [p.id().as_str() for p in objects(tunnel.tunnel_parts())] == ["tunnel_part_1"]
