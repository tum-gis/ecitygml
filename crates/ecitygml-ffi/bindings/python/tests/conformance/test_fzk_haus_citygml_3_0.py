"""The cases of crates/ecitygml/tests/conformance/fzk-haus-citygml-3.0.md."""

from collections import Counter
from pathlib import Path
from typing import Any

import pytest

from conformance.helpers import building, close, first_name, read
from ecitygml import (
    AbstractFeatureKindRef,
    CityModel,
    FeatureType,
    GmlReader,
    GmlWriter,
    GroundSurface,
    HeightStatusValue,
    RoofSurface,
    Storey,
    WallSurface,
)

DATASET = "fzk-haus-citygml-3.0"
CONSTRUCTION = "01-FZK-Haus-LoD2-Tex-Storey-Construction-CG30-V01.gml"
INTERIOR = "04-FZK-Haus-LoD2-Tex-Storey-CG30-V01-InteriorSurface.gml"
WINDOW = "04-FZK-Haus-LoD2-Tex-Storey-Construction-CG30-V01-Window-Interior.gml"
POINT_CLOUD = "06-FZK-Haus-LoD2-Tex-Storey-CG30-V01-PointCloud-thinned.gml"

CONSTRUCTION_ID = "_FZK-Haus-Storey-Construction_BD.DX9Xm6VLbbyLGAxG2v86"
TEST_BUILDING_ID = "KIT-Test-Building-01"
WINDOW_ID = "_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz"

WALL, ROOF, GROUND = FeatureType.WallSurface, FeatureType.RoofSurface, FeatureType.GroundSurface


def corner(position: Any) -> tuple[float, float, float]:
    return (position.x(), position.y(), position.z())


def feature_types(city_model: CityModel) -> list[str]:
    # Two returned FeatureType values never compare equal (only one against the class constant), hence `str`.
    return [str(f.feature_type()) for f in city_model.iter_features()]


def names(types: list[Any]) -> list[str]:
    return [str(t) for t in types]


def storeys(city_model: CityModel) -> list[Storey]:
    return [s for f in city_model.iter_features() if (s := Storey.try_from(f)) is not None]


def assert_city_model(
    city_model: CityModel, lower: tuple[float, float, float], upper: tuple[float, float, float]
) -> None:
    assert city_model.city_objects_len() == 1
    envelope = city_model.bounded_by().envelope()
    assert corner(envelope.lower_corner()) == close(lower)
    assert corner(envelope.upper_corner()) == close(upper)


def assert_height_and_occupancy(b: Any) -> None:
    """The one height and occupancy of the storey examples' buildings."""
    [height] = list(b.heights())
    assert height.high_reference().value() == "highestRoofEdge"
    assert height.low_reference().value() == "lowestGroundPoint"
    assert height.status() == HeightStatusValue.Measured
    assert height.length().value() == close(6.52)
    assert height.length().uom() == "urn:adv:uom:m"
    [occupancy] = list(b.occupancies())
    assert occupancy.number_of_occupants() == 2


def assert_storeys(city_model: CityModel, classes: list[str | None]) -> None:
    """The storeys' first names and classes."""
    found = storeys(city_model)
    assert [first_name(s) for s in found] == ["Ground Floor", "Second Floor"]
    assert [s.class_().value() if s.class_() is not None else None for s in found] == classes


def boundary_surfaces(storey: Storey) -> list[tuple[str, str, Any]]:
    """A storey's boundaries as (feature type, first name, LoD2 multi surface); all inline."""
    result = []
    for prop in storey.boundaries():
        assert prop.href() is None
        feature = AbstractFeatureKindRef.from_space_boundary(prop.object())
        surface = WallSurface.try_from(feature) or RoofSurface.try_from(feature) or GroundSurface.try_from(feature)
        assert surface is not None, str(feature.feature_type())
        result.append((str(feature.feature_type()), first_name(surface), surface.lod2_multi_surface()))
    return result


def assert_round_trip(city_model: CityModel, tmp_path: Path, building_id: str) -> None:
    path = tmp_path / "round-trip.gml"
    GmlWriter.from_path(str(path)).finish(city_model)
    written = GmlReader.from_path(str(path)).finish()
    assert feature_types(written) == feature_types(city_model)
    assert building(written).feature_id().as_str() == building_id


@pytest.fixture(scope="module")
def construction() -> CityModel:
    return read(DATASET, CONSTRUCTION)


@pytest.fixture(scope="module")
def interior() -> CityModel:
    return read(DATASET, INTERIOR)


@pytest.fixture(scope="module")
def window() -> CityModel:
    return read(DATASET, WINDOW)


@pytest.fixture(scope="module")
def point_cloud() -> CityModel:
    return read(DATASET, POINT_CLOUD)


class TestConstruction:
    def test_construction_city_model(self, construction: CityModel) -> None:
        assert_city_model(construction, (458899.5, 5438784.5, 113.5), (458912.5, 5438795.5, 120.017691))
        element = FeatureType.BuildingConstructiveElement
        expected = (
            [FeatureType.CityModel, FeatureType.Building, FeatureType.Storey]
            + [element] * 5
            + [FeatureType.Storey]
            + [element] * 6
            + [FeatureType.Appearance]
            + [FeatureType.ParameterizedTexture] * 5
            + [FeatureType.X3DMaterial] * 5
        )
        assert feature_types(construction) == names(expected)
        assert len(list(construction.iter_city_objects())) == 14

    def test_construction_building(self, construction: CityModel) -> None:
        b = building(construction)
        assert b.feature_id().as_str() == CONSTRUCTION_ID
        assert [n.value() for n in b.names()] == ["KIT FZK-Haus"]
        assert b.class_() is None
        assert [f.value() for f in b.functions()] == ["31001_1000"]
        assert list(b.usages()) == []
        assert b.roof_type().value() == "3100"
        assert (b.storeys_above_ground(), b.storeys_below_ground()) == (None, None)
        assert_height_and_occupancy(b)
        assert list(b.boundaries()) == []
        assert list(b.generic_attributes()) == []
        assert b.lod2_solid() is None
        assert b.lod2_multi_surface() is None

    def test_construction_storeys(self, construction: CityModel) -> None:
        subdivisions = list(building(construction).building_subdivisions())
        assert len(subdivisions) == 2
        for subdivision in subdivisions:
            assert subdivision.href() is None
            assert subdivision.object().feature_type() == FeatureType.Storey
        assert_storeys(construction, ["Entrance Floor", "non Entrance Floor"])
        for storey in storeys(construction):
            assert list(storey.functions()) == []
            assert list(storey.usages()) == []
            assert list(storey.boundaries()) == []
            assert storey.lod2_solid() is None

    def test_construction_round_trip(self, construction: CityModel, tmp_path: Path) -> None:
        assert_round_trip(construction, tmp_path, CONSTRUCTION_ID)


class TestInterior:
    def test_interior_city_model(self, interior: CityModel) -> None:
        assert_city_model(interior, (458900.0, 5438785.0, 113.5), (458912.0, 5438795.0, 120.017691))
        types = feature_types(interior)
        assert len(types) == 77
        assert Counter(types) == Counter(
            {
                str(FeatureType.CityModel): 1,
                str(FeatureType.Building): 1,
                str(FeatureType.Storey): 2,
                str(FeatureType.GroundSurface): 1,
                str(FeatureType.WallSurface): 8,
                str(FeatureType.RoofSurface): 2,
                str(FeatureType.BuildingRoom): 7,
                str(FeatureType.InteriorWallSurface): 27,
                str(FeatureType.CeilingSurface): 8,
                str(FeatureType.FloorSurface): 7,
                str(FeatureType.ClosureSurface): 6,
                str(FeatureType.Appearance): 1,
                str(FeatureType.ParameterizedTexture): 5,
                str(FeatureType.X3DMaterial): 1,
            }
        )
        assert len(list(interior.iter_city_objects())) == 69

    def test_interior_building(self, interior: CityModel) -> None:
        b = building(interior)
        assert b.feature_id().as_str() == TEST_BUILDING_ID
        assert [n.value() for n in b.names()] == ["KIT Test Building FZK-Haus for CityGML 3.0"]
        assert b.class_() is None
        assert b.roof_type() is None
        assert list(b.functions()) == []
        assert list(b.usages()) == []
        assert_height_and_occupancy(b)
        [attribute] = list(b.generic_attributes())
        assert (attribute.name(), attribute.as_string().value()) == ("@cityeditor:layer", "LoD2-Ausgeblendet")
        assert list(b.boundaries()) == []

    def test_interior_solid_unresolved(self, interior: CityModel) -> None:
        prop = building(interior).lod2_solid()
        assert prop.href() is None
        solid = prop.object()
        members = list(solid.exterior().members())
        assert len(members) == 11
        assert all(member.object() is None for member in members)
        with pytest.raises(Exception):
            solid.volume_3d()

    def test_interior_storey_boundaries(self, interior: CityModel) -> None:
        expected = [
            [
                (GROUND, "Ground", 120.0),
                (WALL, "Ground Floor / Wall East", 29.0),
                (WALL, "Ground Floor / Wall South", 34.80000000447035),
                (WALL, "Ground Floor / Wall West", 29.0),
                (WALL, "Ground Floor / Wall North", 34.80000000447035),
            ],
            [
                (ROOF, "Second Floor / Roof South", 69.28203022609509),
                (ROOF, "Second Floor / Roof North", 69.28203022609509),
                (WALL, "Second Floor / Wall South", 8.771279998123646),
                (WALL, "Second Floor / Wall West", 21.743155002593994),
                (WALL, "Second Floor / Wall East", 21.743155002593994),
                (WALL, "Second Floor / Wall North", 8.771279998123646),
            ],
        ]
        found = storeys(interior)
        assert len(found) == len(expected)
        for storey, surfaces in zip(found, expected):
            actual = boundary_surfaces(storey)
            assert [(t, n) for t, n, _ in actual] == [(str(t), n) for t, n, _ in surfaces]
            assert [m.object().area_3d() for _, _, m in actual] == close([a for _, _, a in surfaces])
        assert_storeys(interior, [None, None])

    def test_interior_round_trip(self, interior: CityModel, tmp_path: Path) -> None:
        assert_round_trip(interior, tmp_path, TEST_BUILDING_ID)


class TestWindow:
    def test_window_city_model(self, window: CityModel) -> None:
        assert_city_model(window, (458899.5, 5438784.5, 113.5), (458912.5, 5438795.5, 120.017691))
        types = feature_types(window)
        assert len(types) == 54
        assert Counter(types) == Counter(
            {
                str(FeatureType.CityModel): 1,
                str(FeatureType.Building): 1,
                str(FeatureType.Storey): 2,
                str(FeatureType.BuildingConstructiveElement): 18,
                str(FeatureType.Door): 5,
                str(FeatureType.Window): 11,
                str(FeatureType.Appearance): 2,
                str(FeatureType.ParameterizedTexture): 5,
                str(FeatureType.X3DMaterial): 9,
            }
        )
        assert len(list(window.iter_city_objects())) == 37

    def test_window_building(self, window: CityModel) -> None:
        b = building(window)
        assert b.feature_id().as_str() == WINDOW_ID
        assert [n.value() for n in b.names()] == ["KIT FZK-Haus"]
        assert [f.value() for f in b.functions()] == ["31001_1000"]
        assert b.roof_type().value() == "3100"
        assert list(b.boundaries()) == []
        assert_storeys(window, ["Entrance Floor", "non Entrance Floor"])

    def test_window_round_trip(self, window: CityModel, tmp_path: Path) -> None:
        assert_round_trip(window, tmp_path, WINDOW_ID)


class TestPointCloud:
    def test_point_cloud_city_model(self, point_cloud: CityModel) -> None:
        assert_city_model(point_cloud, (458900.0, 5438785.0, 113.5), (458912.0, 5438795.0, 120.017691))
        expected = (
            [FeatureType.CityModel, FeatureType.Building, FeatureType.Storey, GROUND]
            + [WALL] * 4
            + [FeatureType.Storey, ROOF, ROOF]
            + [WALL] * 4
        )
        assert feature_types(point_cloud) == names(expected)

    def test_point_cloud_storey_boundaries(self, point_cloud: CityModel) -> None:
        b = building(point_cloud)
        assert b.feature_id().as_str() == TEST_BUILDING_ID
        assert list(b.boundaries()) == []
        expected = [
            [
                (GROUND, " Ground Floor / GroundSurface"),
                (WALL, "Ground Floor / Wall East"),
                (WALL, "Ground Floor / Wall South"),
                (WALL, "Ground Floor / Wall West"),
                (WALL, "Ground Floor / Wall North"),
            ],
            [
                (ROOF, "Second Floor / Roof North"),
                (ROOF, "Second Floor / Roof South"),
                (WALL, "Second Floor / Wall South"),
                (WALL, "Second Floor / Wall West"),
                (WALL, "Second Floor / Wall East"),
                (WALL, "Second Floor / Wall North"),
            ],
        ]
        found = storeys(point_cloud)
        assert len(found) == len(expected)
        for storey, surfaces in zip(found, expected):
            actual = boundary_surfaces(storey)
            assert [(t, n) for t, n, _ in actual] == [(str(t), n) for t, n in surfaces]
            assert all(m is None for _, _, m in actual)

    def test_point_cloud_round_trip(self, point_cloud: CityModel, tmp_path: Path) -> None:
        assert_round_trip(point_cloud, tmp_path, TEST_BUILDING_ID)
