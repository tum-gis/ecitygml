"""The cases of crates/ecitygml/tests/conformance/tum-main-entrance.md."""

from pathlib import Path

import pytest

from conformance.helpers import boundaries, building, close, read
from ecitygml import (
    CityModel,
    FeatureType,
    GmlReader,
    GmlWriter,
    GroundSurface,
    HeightStatusValue,
    RoofSurface,
    WallSurface,
)

ENTRANCE = "TUM-Main-Entrance.gml"

WALL, GROUND, ROOF = (str(t) for t in (FeatureType.WallSurface, FeatureType.GroundSurface, FeatureType.RoofSurface))
BOUNDARY_TYPES = [WALL] * 10 + [GROUND] + [WALL] * 3 + [ROOF, ROOF, WALL]


@pytest.fixture(scope="module")
def entrance() -> CityModel:
    return read("tum-main-entrance", ENTRANCE)


def corner(position: object) -> tuple[float, float, float]:
    return (position.x(), position.y(), position.z())


def lod2_area(surface: object) -> float:
    """The area of a thematic surface's inline LoD2 multi surface."""
    prop = surface.lod2_multi_surface()
    assert prop.href() is None
    return prop.object().area_3d()


def feature_types(city_model: CityModel) -> list[str]:
    # Two returned FeatureType values never compare equal (only one against the class constant), hence `str`.
    return [str(f.feature_type()) for f in city_model.iter_features()]


def test_entrance_city_model(entrance: CityModel) -> None:
    assert entrance.city_objects_len() == 1
    envelope = entrance.bounded_by().envelope()
    assert corner(envelope.lower_corner()) == close((689975.68, 5335962.63, 503.0))
    assert corner(envelope.upper_corner()) == close((692025.893, 5338012.713, 581.62))
    expected = [str(FeatureType.CityModel), str(FeatureType.Building)] + BOUNDARY_TYPES
    assert feature_types(entrance) == expected
    assert len(list(entrance.iter_city_objects())) == 18


def test_entrance_building_attributes(entrance: CityModel) -> None:
    b = building(entrance)
    assert b.feature_id().as_str() == "DEBY_LOD2_4959457"
    assert list(b.names()) == []
    assert b.class_() is None
    [function] = list(b.functions())
    assert function.value() == "31001_3020"
    assert list(b.usages()) == []
    assert b.roof_type().value() == "1000"
    assert (b.storeys_above_ground(), b.storeys_below_ground()) == (4, None)

    [height] = list(b.heights())
    assert height.high_reference().value() == "topOfConstruction"
    assert height.low_reference().value() == "lowestGroundPoint"
    assert height.status() == HeightStatusValue.Measured
    assert height.length().value() == close(19.408)
    assert height.length().uom() == "urn:adv:uom:m"

    created = b.creation_date()
    assert (created.year(), created.month(), created.day()) == (2025, 1, 2)
    assert (created.hour(), created.minute()) == (0, 0)
    assert created.offset_seconds() == 3600
    assert b.bounded_by() is None
    assert list(b.occupancies()) == []
    assert list(b.building_subdivisions()) == []


def test_entrance_external_reference(entrance: CityModel) -> None:
    [reference] = list(building(entrance).external_references())
    assert reference.target_resource() == "DEBYvAAAAABTMIyA"


def test_entrance_external_reference_details(entrance: CityModel) -> None:
    [reference] = list(building(entrance).external_references())
    assert reference.information_system() == "http://repository.gdi-de.org/schemas/adv/citygml/fdv/art.htm#_9100"
    assert reference.relation_type() is None


def test_entrance_generic_attributes(entrance: CityModel) -> None:
    attributes = [(a.name(), a.as_string().value()) for a in building(entrance).generic_attributes()]
    assert attributes == [
        ("DatenquelleBodenhoehe", "1100"),
        ("DatenquelleDachhoehe", "1000"),
        ("DatenquelleLage", "1000"),
        ("Gemeindeschluessel", "09162000"),
        ("HoeheDach", "534.450"),
        ("HoeheGrund", "515.042"),
        ("Methode", "2000"),
        ("NiedrigsteTraufeDesGebaeudes", "527.312"),
        ("Grundrissaktualitaet", "2025-02-17"),
        ("Geometrietyp2DReferenz", "3000"),
    ]


def test_entrance_boundaries(entrance: CityModel) -> None:
    b = building(entrance)
    assert all(p.href() is None for p in b.boundaries())
    features = boundaries(b)
    assert [str(f.feature_type()) for f in features] == BOUNDARY_TYPES

    walls = [w for f in features if (w := WallSurface.try_from(f)) is not None]
    assert walls[0].feature_id().as_str() == "DEBY_LOD2_4959457_ca1db42f-9d12-4f41-972c-c7da1614f0a8_2"
    assert list(walls[0].names()) == []
    assert sum(lod2_area(w) for w in walls) == close(3783.3908922901974)

    roofs = [lod2_area(r) for f in features if (r := RoofSurface.try_from(f)) is not None]
    assert roofs == close([250.233154296875, 979.3291015625])
    assert sum(roofs) == close(1229.562255859375)

    grounds = [lod2_area(g) for f in features if (g := GroundSurface.try_from(f)) is not None]
    assert grounds == close([1229.562255859375])


def test_entrance_wall_triangulation(entrance: CityModel) -> None:
    wall = next(w for f in entrance.iter_features() if (w := WallSurface.try_from(f)) is not None)
    multi_surface = wall.lod2_multi_surface().object()
    assert len(list(multi_surface.surface_member())) == 1
    assert multi_surface.area_3d() == close(546.6949745937537)
    triangulation = multi_surface.triangulate()
    assert len(list(triangulation.surface().triangles())) == 4
    assert not triangulation.has_skipped()
    assert triangulation.surface().area_3d() == close(546.6949742237184)


def test_entrance_solid_unresolved(entrance: CityModel) -> None:
    prop = building(entrance).lod2_solid()
    assert prop.href() is None
    solid = prop.object()
    members = list(solid.exterior().members())
    assert len(members) == 17
    assert all(member.object() is None for member in members)
    with pytest.raises(Exception):
        solid.volume_3d()


def test_entrance_round_trip(entrance: CityModel, tmp_path: Path) -> None:
    path = tmp_path / "round-trip.gml"
    GmlWriter.from_path(str(path)).finish(entrance)
    written = GmlReader.from_path(str(path)).finish()
    assert feature_types(written) == feature_types(entrance)
    assert building(written).feature_id().as_str() == "DEBY_LOD2_4959457"

    def boundary_ids(city_model: CityModel) -> list[str]:
        return [p.object().feature_id().as_str() for p in building(city_model).boundaries()]

    assert boundary_ids(written) == boundary_ids(entrance)
