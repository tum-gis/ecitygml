"""The cases of crates/ecitygml/tests/conformance/ogc-citygml-3.0-encodings.md."""

from collections import Counter
from pathlib import Path
from typing import Any

import pytest

from conformance.helpers import close, read
from ecitygml import (
    AbstractFeatureKindRef,
    Bridge,
    Building,
    BuildingPart,
    BuildingUnit,
    CityModel,
    FeatureType,
    GmlReader,
    GmlWriter,
    GroundSurface,
    HeightStatusValue,
    LevelOfDetail,
    ReliefFeature,
    Road,
    RoofSurface,
    Storey,
    TinRelief,
    TrafficArea,
    WallSurface,
)

DATASET = "ogc-citygml-3.0-encodings"

WALL, ROOF, GROUND = FeatureType.WallSurface, FeatureType.RoofSurface, FeatureType.GroundSurface


def feature_types(city_model: CityModel) -> list[str]:
    # Two returned FeatureType values never compare equal (only one against the class constant), hence `str`.
    return [str(f.feature_type()) for f in city_model.iter_features()]


def names(types: list[Any]) -> list[str]:
    return [str(t) for t in types]


def all_of(city_model: CityModel, cls: Any) -> list[Any]:
    """All features of a class, in document order."""
    return [x for f in city_model.iter_features() if (x := cls.try_from(f)) is not None]


def corner(position: Any) -> tuple[float, float, float]:
    return (position.x(), position.y(), position.z())


def expect_envelope(envelope: Any, lower: tuple[float, float, float], upper: tuple[float, float, float]) -> None:
    assert corner(envelope.lower_corner()) == close(lower)
    assert corner(envelope.upper_corner()) == close(upper)


def round_trip(city_model: CityModel, tmp_path: Path) -> CityModel:
    path = tmp_path / "round-trip.gml"
    GmlWriter.from_path(str(path)).finish(city_model)
    return GmlReader.from_path(str(path)).finish()


def surfaces(space: Any) -> list[tuple[str, str, str | None, Any]]:
    """A space's boundaries as (feature type, `feature_id`, first name or None, LoD2 multi surface); all inline wall,
    roof or ground surfaces."""
    result = []
    for prop in space.boundaries():
        assert prop.href() is None
        obj = prop.object()
        feature = AbstractFeatureKindRef.from_space_boundary(obj)
        surface = WallSurface.try_from(feature) or RoofSurface.try_from(feature) or GroundSurface.try_from(feature)
        assert surface is not None, str(feature.feature_type())
        first = next((n.value() for n in surface.names()), None)
        result.append((str(feature.feature_type()), obj.feature_id().as_str(), first, surface.lod2_multi_surface()))
    return result


def lod2_area(multi_surface: Any) -> float:
    return multi_surface.object().area_3d()


def expect_height(building: Any, length: float) -> None:
    [height] = list(building.heights())
    assert height.high_reference().value() == "highestRoofEdge"
    assert height.low_reference().value() == "lowestGroundPoint"
    assert height.status() == HeightStatusValue.Measured
    assert height.length().value() == close(length)
    assert height.length().uom() == "#m"


@pytest.fixture(scope="module")
def garage() -> CityModel:
    return read(DATASET, "Building_and_garage_LOD2-EPSG25832.gml")


@pytest.fixture(scope="module")
def units() -> CityModel:
    return read(DATASET, "BuildingUnits_Storeys_xlink.gml")


@pytest.fixture(scope="module")
def road_bridge() -> CityModel:
    return read(DATASET, "Road_over_Bridge_CityGML3.0_LOD2_with_CityObjectRelations.gml")


@pytest.fixture(scope="module")
def versioning() -> CityModel:
    return read(DATASET, "historicalSuccession_CityGML_3.0_LOD2_Versioning.gml")


class TestGarage:
    def test_garage_city_model(self, garage: CityModel) -> None:
        assert garage.city_objects_len() == 2
        expect_envelope(garage.bounded_by().envelope(), (458868.0, 5438343.0, 112.0), (458892.0, 5438362.0, 117.0))
        expected = (
            [FeatureType.CityModel, FeatureType.Building, GROUND]
            + [WALL] * 4
            + [ROOF, ROOF, FeatureType.BuildingPart]
            + [WALL] * 4
            + [GROUND, ROOF, FeatureType.ReliefFeature, FeatureType.TinRelief]
        )
        assert feature_types(garage) == names(expected)
        assert len(list(garage.iter_city_objects())) == 17

    def test_garage_building(self, garage: CityModel) -> None:
        [b] = all_of(garage, Building)
        assert b.feature_id().as_str() == "GML_7b1a5a6f-ddad-4c3d-a507-3eb9ee0a8e68"
        assert [n.value() for n in b.names()] == ["Example Building LOD2"]
        assert b.class_() is None
        assert [f.value() for f in b.functions()] == ["1000"]
        assert list(b.usages()) == []
        assert b.roof_type().value() == "1030"
        assert (b.storeys_above_ground(), b.storeys_below_ground()) == (1, None)
        date = b.date_of_construction()
        assert (date.year(), date.month(), date.day()) == (1985, 1, 1)
        expect_height(b, 6.0)
        expected = [
            (GROUND, "Ground Slab", 50.0),
            (WALL, "Wall South", 30.0),
            (WALL, "Wall North", 30.0),
            (WALL, "Wall East", 20.0),
            (WALL, "Wall West", 20.0),
            (ROOF, "Roof North", 32.01562118716424),
            (ROOF, "Roof South", 32.01562118716424),
        ]
        actual = surfaces(b)
        assert [(t, n) for t, _, n, _ in actual] == [(str(t), n) for t, n, _ in expected]
        assert [lod2_area(m) for _, _, _, m in actual] == close([a for _, _, a in expected])

    def test_garage_building_part(self, garage: CityModel) -> None:
        [b] = all_of(garage, Building)
        [prop] = list(b.building_parts())
        assert prop.href() is None
        part = prop.object()
        assert part.feature_id().as_str() == "GMLID_BUI379228_1244_301"
        assert [n.value() for n in part.names()] == ["Example BuildingPart LOD2"]
        assert part.class_() is None
        assert [f.value() for f in part.functions()] == ["1630"]
        assert list(part.usages()) == []
        assert part.roof_type().value() == "1010"
        date = part.date_of_construction()
        assert (date.year(), date.month(), date.day()) == (1985, 1, 1)
        expect_height(part, 2.5)
        # The west wall's area is left out: its member is a gml:OrientableSurface, not read yet.
        expected = [
            (WALL, "Garage Wall East", 9.600000023841858),
            (WALL, "Garage Wall South", 6.25),
            (WALL, "Garage Wall West", None),
            (WALL, "Garage Wall North", 5.75),
            (GROUND, "Garage Ground Slab", 10.0),
            (ROOF, "Garage Roof", 10.012492197250394),
        ]
        actual = surfaces(part)
        assert [(t, n) for t, _, n, _ in actual] == [(str(t), n) for t, n, _ in expected]
        for (_, _, _, multi_surface), (_, _, area) in zip(actual, expected):
            if area is not None:
                assert lod2_area(multi_surface) == close(area)

    def test_garage_relief(self, garage: CityModel) -> None:
        [relief] = all_of(garage, ReliefFeature)
        assert relief.feature_id().as_str() == "GML_6bb30328-7599-4500-90ef-766fde6aa67b"
        assert [n.value() for n in relief.names()] == ["Example TIN LOD2"]
        assert relief.lod() == LevelOfDetail.Two
        [component] = list(relief.relief_components())
        assert component.href() is None
        assert component.object().feature_type() == FeatureType.TinRelief

        [tin_relief] = all_of(garage, TinRelief)
        assert tin_relief.feature_id().as_str() == "GML_4eb161b0-aa7e-4087-937c-5c4c427c7fc9"
        assert [n.value() for n in tin_relief.names()] == ["Ground"]
        assert tin_relief.lod() == LevelOfDetail.Two
        tin = tin_relief.tin()
        assert tin.href() is None
        surface = tin.object()
        assert len(list(surface.triangles())) == 12
        assert surface.area_3d() == close(399.8446647372588)

    def test_garage_round_trip(self, garage: CityModel, tmp_path: Path) -> None:
        written = round_trip(garage, tmp_path)
        assert feature_types(written) == feature_types(garage)
        ids = [x.feature_id().as_str() for cls in (Building, BuildingPart, ReliefFeature, TinRelief) for x in all_of(written, cls)]
        assert ids == [
            "GML_7b1a5a6f-ddad-4c3d-a507-3eb9ee0a8e68",
            "GMLID_BUI379228_1244_301",
            "GML_6bb30328-7599-4500-90ef-766fde6aa67b",
            "GML_4eb161b0-aa7e-4087-937c-5c4c427c7fc9",
        ]


def member_hrefs(storey: Storey) -> list[str | None]:
    """The `href`s of a storey's LoD2 surface members (None for inline members)."""
    prop = storey.lod2_multi_surface()
    assert prop.href() is None
    result = []
    for member in prop.object().surface_member():
        assert (member.object() is None) == (member.href() is not None)
        result.append(member.href().to_string() if member.href() is not None else None)
    return result


class TestUnits:
    def test_units_city_model(self, units: CityModel) -> None:
        assert units.city_objects_len() == 1
        expect_envelope(units.bounded_by().envelope(), (457841.0, 5439082.0, 111.0), (457854.0, 5439093.0, 121.0))

        def room(walls: int) -> list[Any]:
            return [FeatureType.BuildingRoom] + [FeatureType.InteriorWallSurface] * walls + [
                FeatureType.FloorSurface,
                FeatureType.CeilingSurface,
            ]

        expected = (
            [FeatureType.CityModel, FeatureType.Building]
            + [WALL] * 3
            + [ROOF, WALL, ROOF, GROUND]
            + room(8)
            + room(8)
            + room(4)
            + [FeatureType.BuildingUnit, FeatureType.BuildingUnit, FeatureType.Storey, FeatureType.Storey]
        )
        assert feature_types(units) == names(expected)
        assert len(list(units.iter_city_objects())) == 41

    def test_units_building(self, units: CityModel) -> None:
        [b] = all_of(units, Building)
        assert b.feature_id().as_str() == "building_unit_example_1"
        assert list(b.names()) == []
        assert list(b.functions()) == []
        assert list(b.usages()) == []
        assert b.class_() is None
        assert b.roof_type() is None
        expected = [
            (WALL, "Outer Wall 1 (West)", 89.375),
            (WALL, "Outer Wall 2 (South)", 81.25),
            (WALL, "Outer Wall 3 (East)", 89.375),
            (ROOF, "Roof 1 (North)", 86.53792521201326),
            (WALL, "Outer Wall 4 (North)", 81.25),
            (ROOF, "Roof 2 (South)", 86.53792521201326),
            (GROUND, "Base Surface", 143.0),
        ]
        actual = surfaces(b)
        assert [(t, n) for t, _, n, _ in actual] == [(str(t), n) for t, n, _ in expected]
        assert [lod2_area(m) for _, _, _, m in actual] == close([a for _, _, a in expected])

    def test_units_subdivisions(self, units: CityModel) -> None:
        [b] = all_of(units, Building)
        subdivisions = list(b.building_subdivisions())
        assert all(p.href() is None for p in subdivisions)
        assert [str(p.object().feature_type()) for p in subdivisions] == names(
            [FeatureType.BuildingUnit, FeatureType.BuildingUnit, FeatureType.Storey, FeatureType.Storey]
        )
        found_units = all_of(units, BuildingUnit)
        assert [u.feature_id().as_str() for u in found_units] == ["BuildingUnit_apartment1", "BuildingUnit_apartment2"]
        for unit in found_units:
            assert [f.value() for f in unit.functions()] == ["apartment"]
            assert unit.class_() is None
            assert list(unit.usages()) == []
            assert list(unit.boundaries()) == []
            assert unit.lod2_multi_surface() is None
        storeys = all_of(units, Storey)
        assert [s.feature_id().as_str() for s in storeys] == ["storey1", "storey2"]
        for storey in storeys:
            assert list(storey.names()) == []
            assert storey.class_() is None
            assert list(storey.functions()) == []
            assert list(storey.usages()) == []
            assert list(storey.boundaries()) == []

    def test_units_storey_geometry(self, units: CityModel) -> None:
        expected = [
            (
                [
                    "#Wall_1_PolyID82397_997_453711_16336011",
                    "#Wall_1_PolyID82397_997_453711_16336012",
                    "#Wall_1_PolyID82397_997_453711_163360136",
                ],
                (457841.1, 5439082.1, 111.1),
                (457853.9, 5439092.9, 113.9),
            ),
            (
                [
                    "#Wall_1_PolyID82397_997_453711_163360112",
                    "#Wall_1_PolyID82397_997_453711_163360122",
                    "#Wall_1_PolyID82397_997_453711_1633601362",
                ],
                (457841.1, 5439082.1, 114.1),
                (457853.9, 5439092.9, 116.9),
            ),
        ]
        storeys = all_of(units, Storey)
        assert len(storeys) == len(expected)
        for storey, (hrefs, lower, upper) in zip(storeys, expected):
            assert member_hrefs(storey) == [None, *hrefs, None, None]
            with pytest.raises(Exception):
                storey.lod2_multi_surface().object().area_3d()
            expect_envelope(storey.bounded_by().envelope(), lower, upper)

    def test_units_round_trip(self, units: CityModel, tmp_path: Path) -> None:
        written = round_trip(units, tmp_path)
        assert feature_types(written) == feature_types(units)
        [b] = all_of(written, Building)
        assert b.feature_id().as_str() == "building_unit_example_1"
        assert [member_hrefs(s) for s in all_of(written, Storey)] == [member_hrefs(s) for s in all_of(units, Storey)]


def relations(city_model: CityModel) -> list[tuple[str, str, str | None]]:
    """The relations of the roof surfaces and traffic areas, in document order: (city object, relation type, `href` of
    `relation_to`)."""
    result = []
    for feature in city_model.iter_features():
        obj = RoofSurface.try_from(feature) or TrafficArea.try_from(feature)
        if obj is None:
            continue
        for prop in obj.related_to():
            assert prop.href() is None
            relation = prop.object()
            assert list(relation.generic_attributes()) == []
            href = relation.relation_to().href()
            result.append(
                (obj.feature_id().as_str(), relation.relation_type().value(), href.to_string() if href else None)
            )
    return result


class TestRoadBridge:
    def test_road_bridge_city_model(self, road_bridge: CityModel) -> None:
        assert road_bridge.city_objects_len() == 2
        assert road_bridge.bounded_by() is None
        section = [
            FeatureType.Section,
            FeatureType.TrafficSpace,
            FeatureType.TrafficArea,
            FeatureType.TrafficSpace,
            FeatureType.TrafficArea,
        ]
        expected = [FeatureType.CityModel, FeatureType.Bridge, GROUND, ROOF, ROOF] + [WALL] * 4 + [FeatureType.Road] + section * 3
        assert feature_types(road_bridge) == names(expected)
        assert len(list(road_bridge.iter_city_objects())) == 24

    def test_road_bridge_bridge(self, road_bridge: CityModel) -> None:
        [bridge] = all_of(road_bridge, Bridge)
        assert bridge.feature_id().as_str() == "id_bridge1"
        assert list(bridge.names()) == []
        assert list(bridge.related_to()) == []
        expected = [
            ("id_groundsurface1", 77500.15996032),
            ("id_roofsurface1", 38750.07998016),
            ("id_roofsurface2", 38750.07998016),
            ("id_wallsurface4", 10075.02000744),
            ("id_wallsurface1", 20150.04001488),
            ("id_wallsurface2", 10075.02000744),
            ("id_wallsurface3", 20150.04001488),
        ]
        actual = surfaces(bridge)
        assert [i for _, i, _, _ in actual] == [i for i, _ in expected]
        assert [lod2_area(m) for _, _, _, m in actual] == close([a for _, a in expected])

    def test_road_bridge_road(self, road_bridge: CityModel) -> None:
        [road] = all_of(road_bridge, Road)
        assert road.feature_id().as_str() == "id_road1"
        assert list(road.related_to()) == []
        assert list(road.traffic_spaces()) == []
        assert list(road.auxiliary_traffic_spaces()) == []
        section_props = list(road.sections())
        assert all(p.href() is None for p in section_props)
        sections = [p.object() for p in section_props]
        assert [s.feature_id().as_str() for s in sections] == ["id_section1", "id_section2", "id_section3"]
        spaces = []
        for section in sections:
            for prop in section.traffic_spaces():
                assert prop.href() is None
                spaces.append(prop.object())
        numbers = [1, 2, 5, 6, 3, 4]
        assert [s.feature_id().as_str() for s in spaces] == [f"id_trafficspace{n}" for n in numbers]
        for space, number in zip(spaces, numbers):
            [boundary] = list(space.boundaries())
            assert boundary.href() is None
            area = boundary.object()
            assert area.feature_type() == FeatureType.TrafficArea
            assert area.feature_id().as_str() == f"id_trafficarea{number}"

    def test_road_bridge_relations(self, road_bridge: CityModel) -> None:
        assert relations(road_bridge) == [
            ("id_roofsurface1", "equal", "id_trafficarea5"),
            ("id_roofsurface2", "equal", "id_trafficarea6"),
            ("id_trafficarea5", "equal", "id_roofSurface1"),
            ("id_trafficarea6", "equal", "id_roofSurface2"),
        ]
        assert all(list(w.related_to()) == [] for w in all_of(road_bridge, WallSurface))
        assert all(list(g.related_to()) == [] for g in all_of(road_bridge, GroundSurface))

    def test_road_bridge_round_trip(self, road_bridge: CityModel, tmp_path: Path) -> None:
        written = round_trip(road_bridge, tmp_path)
        assert feature_types(written) == feature_types(road_bridge)
        assert [b.feature_id().as_str() for b in all_of(written, Bridge)] == ["id_bridge1"]
        assert [r.feature_id().as_str() for r in all_of(written, Road)] == ["id_road1"]
        assert relations(written) == relations(road_bridge)


def date(date_time: Any) -> tuple[int, int, int] | None:
    """(year, month, day) of a date time at 00:00 UTC."""
    if date_time is None:
        return None
    assert (date_time.hour(), date_time.minute(), date_time.offset_seconds()) == (0, 0, 0)
    return (date_time.year(), date_time.month(), date_time.day())


class TestVersioning:
    def test_versioning_city_model(self, versioning: CityModel) -> None:
        assert versioning.city_objects_len() == 4
        assert versioning.bounded_by() is None
        types = feature_types(versioning)
        assert len(types) == 60
        assert types[0] == str(FeatureType.CityModel)
        assert Counter(types) == Counter(
            {
                str(FeatureType.CityModel): 1,
                str(FeatureType.Building): 4,
                str(FeatureType.BuildingPart): 5,
                str(ROOF): 14,
                str(WALL): 31,
                str(GROUND): 5,
            }
        )
        assert len(list(versioning.iter_city_objects())) == 59

    def test_versioning_buildings(self, versioning: CityModel) -> None:
        expected = [
            ("BU_69381AL47_2000-01-01", "Building A", (2000, 1, 1), (2015, 1, 1), ["BU_69381AL47_1"]),
            ("BU_69381AL49_2000-01-01", "Building B", (2000, 1, 1), (2015, 1, 1), ["BU_69381AL49_1_2000-01-01"]),
            (
                "BU_69381AL49_2015-01-01",
                "Building B",
                (2015, 1, 1),
                None,
                ["BU_69381AL49_1_2015-01-01", "BU_69381AL49_2_2015-01-01"],
            ),
            ("BU_69381AL50_2015-01-01", "Building C", (2015, 1, 1), None, ["BU_69381AL50_1"]),
        ]
        buildings = all_of(versioning, Building)
        assert len(buildings) == len(expected)
        for b, (feature_id, name, created, terminated, parts) in zip(buildings, expected):
            assert b.feature_id().as_str() == feature_id
            assert next(iter(b.names())).value() == name
            assert date(b.creation_date()) == created
            assert date(b.termination_date()) == terminated
            part_props = list(b.building_parts())
            assert all(p.href() is None for p in part_props)
            assert [p.object().feature_id().as_str() for p in part_props] == parts
            assert list(b.heights()) == []
            assert list(b.boundaries()) == []

    def test_versioning_building_parts(self, versioning: CityModel) -> None:
        expected = [
            ("BU_69381AL47_1", 13.015, 8),
            ("BU_69381AL49_1_2000-01-01", 10.63, 9),
            ("BU_69381AL49_1_2015-01-01", 10.63, 9),
            ("BU_69381AL49_2_2015-01-01", 8.743, 7),
            ("BU_69381AL50_1", 18.215, 17),
        ]
        parts = all_of(versioning, BuildingPart)
        assert len(parts) == len(expected)
        for part, (feature_id, height, boundaries) in zip(parts, expected):
            assert part.feature_id().as_str() == feature_id
            expect_height(part, height)
            assert len(list(part.boundaries())) == boundaries
            assert part.creation_date() is None
            assert list(part.names()) == []

    def test_versioning_round_trip(self, versioning: CityModel, tmp_path: Path) -> None:
        written = round_trip(versioning, tmp_path)
        assert feature_types(written) == feature_types(versioning)

        def ids(city_model: CityModel) -> list[str]:
            return [x.feature_id().as_str() for cls in (Building, BuildingPart) for x in all_of(city_model, cls)]

        def dates(city_model: CityModel) -> list[Any]:
            return [(date(b.creation_date()), date(b.termination_date())) for b in all_of(city_model, Building)]

        assert ids(written) == ids(versioning)
        assert dates(written) == dates(versioning)
