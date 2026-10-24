"""The cases of crates/ecitygml/tests/conformance/fzk-haus.md."""

import pytest

from pathlib import Path

from conformance.helpers import boundaries, building, close, first_name, read
from conftest import FIXTURES
from ecitygml import (
    CityModel,
    CompositeSurface,
    DirectPosition,
    DoorSurface,
    FeatureType,
    GmlReader,
    GmlWriter,
    GroundSurface,
    HeightStatusValue,
    LinearRing,
    MeasureAttribute,
    Polygon,
    RelativeToTerrain,
    RoofSurface,
    Scale3,
    Vector3,
    WallSurface,
    WindowSurface,
)

LOD1 = "FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml"
LOD2 = "FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml"
LOD3 = "FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml"


def point(position: DirectPosition) -> tuple[float, float, float]:
    return (position.x(), position.y(), position.z())


@pytest.fixture(scope="module")
def lod1() -> CityModel:
    return read("fzk-haus", LOD1)


@pytest.fixture(scope="module")
def lod2() -> CityModel:
    return read("fzk-haus", LOD2)


@pytest.fixture(scope="module")
def lod3() -> CityModel:
    return read("fzk-haus", LOD3)


class TestLod1:
    def test_lod1_city_model(self, lod1: CityModel) -> None:
        assert lod1.city_objects_len() == 1
        envelope = lod1.bounded_by().envelope()
        lower, upper = envelope.lower_corner(), envelope.upper_corner()
        assert (lower.x(), lower.y(), lower.z()) == close((457842.0, 5439083.0, 111.8))
        assert (upper.x(), upper.y(), upper.z()) == close((457854.0, 5439093.0, 118.317669))

    def test_lod1_building_attributes(self, lod1: CityModel) -> None:
        b = building(lod1)
        assert b.feature_id().as_str() == "UUID_d281adfc-4901-0f52-540b-4cc1a9325f82"
        assert [name.value() for name in b.names()] == ["AC14-FZK-Haus"]
        assert b.class_().value() == "1000"
        assert [f.value() for f in b.functions()] == ["1000"]
        assert [u.value() for u in b.usages()] == ["1000"]
        assert b.roof_type().value() == "1030"
        assert (b.storeys_above_ground(), b.storeys_below_ground()) == (2, 0)

        date = b.date_of_construction()
        assert (date.year(), date.month(), date.day()) == (2020, 1, 1)
        assert b.date_of_demolition() is None
        [height] = list(b.heights())
        assert height.high_reference().value() == "topOfConstruction"
        assert height.low_reference().value() == "lowestGroundPoint"
        assert height.status() == HeightStatusValue.Measured
        assert height.length().value() == close(6.52)
        assert height.length().uom() == "m"
        assert list(b.occupancies()) == []
        assert list(b.building_parts()) == []

    def test_lod1_solid(self, lod1: CityModel) -> None:
        b = building(lod1)
        solid = b.lod1_solid().object()
        assert solid.volume_3d() == close(782.1228)
        triangulation = solid.triangulate()
        assert len(list(triangulation.surface().triangles())) == 12
        assert not triangulation.has_skipped()
        assert list(b.boundaries()) == []

    def test_lod1_envelope_measures(self, lod1: CityModel) -> None:
        envelope = lod1.bounded_by().envelope()
        assert (envelope.size_x(), envelope.size_y(), envelope.size_z()) == close((12.0, 10.0, 6.517669))
        assert point(envelope.center()) == close((457848.0, 5439088.0, 115.0588345))
        assert envelope.volume() == close(782.12028)
        assert envelope.contains(envelope.lower_corner())
        assert envelope.contains(envelope.upper_corner())
        assert envelope.contains(DirectPosition(457848.0, 5439088.0, 115.0))
        assert not envelope.contains(DirectPosition(457848.0, 5439088.0, 118.4))
        assert not envelope.contains(DirectPosition(457841.9, 5439088.0, 115.0))
        assert lod1.creation_date() is None

    def test_lod1_building_details(self, lod1: CityModel) -> None:
        assert sum(1 for f in lod1.iter_features() if f.feature_type() == FeatureType.Building) == 1
        b = building(lod1)
        assert b.id().as_str() == "UUID_d281adfc-4901-0f52-540b-4cc1a9325f82"
        envelope = b.bounded_by().envelope()
        assert point(envelope.lower_corner()) == close((457842.0, 5439083.0, 111.8))
        assert point(envelope.upper_corner()) == close((457854.0, 5439093.0, 118.31769))
        assert b.lod2_solid() is None
        assert b.lod0_multi_surface() is None

    def test_lod1_solid_structure(self, lod1: CityModel) -> None:
        solid = building(lod1).lod1_solid().object()
        assert list(solid.interior()) == []
        assert len(list(solid.points())) == 24
        shell = solid.exterior()
        assert shell.volume_3d() == close(782.1228)
        members = list(shell.members())
        assert len(members) == 6
        assert all(member.href() is None for member in members)
        polygons = [Polygon.try_from(member.object()) for member in members]
        assert all(list(polygon.interior()) == [] for polygon in polygons)
        rings = [LinearRing.try_from(polygon.exterior()) for polygon in polygons]
        assert [len(list(ring.points())) for ring in rings] == [4] * 6
        assert all(ring.area_3d() > 0.0 for ring in rings)
        assert point(next(iter(rings[0].points()))) == close((457842.0, 5439083.0, 111.8))
        assert rings[0].length_3d() == close(44.0)
        assert rings[0].area_3d() == close(120.0)

    def test_lod1_solid_triangulation(self, lod1: CityModel) -> None:
        solid = building(lod1).lod1_solid().object()
        triangulation = solid.triangulate()
        assert list(triangulation.skipped()) == []
        surface = triangulation.surface()
        assert surface.area_3d() == close(526.77836)
        assert len(list(surface.points())) == 36
        triangle = next(iter(surface.triangles()))
        assert triangle.a().z() == close(111.8)
        assert triangle.area() == close(60.0)
        shell = solid.exterior()
        assert len(list(shell.triangulate().surface().triangles())) == 12
        first = Polygon.try_from(next(iter(shell.members())).object())
        assert len(list(first.triangulate().surface().triangles())) == 2

    def test_lod1_apply_scale(self) -> None:
        city_model = read("fzk-haus", LOD1)
        city_model.apply_scale(Scale3(2.0, 3.0, 0.5))
        envelope = city_model.bounded_by().envelope()
        assert (envelope.size_x(), envelope.size_y(), envelope.size_z()) == close((24.0, 30.0, 3.2588345))


def walls_bounded(city_model: CityModel) -> list[bool]:
    return [w.bounded_by() is not None for f in city_model.iter_features() if (w := WallSurface.try_from(f))]


def surface_ids(city_model: CityModel) -> list[str]:
    """The `feature_id`s of the building's boundaries, then of the wall surfaces' filling surfaces."""
    ids = [p.object().feature_id().as_str() for p in building(city_model).boundaries()]
    for wall in (w for b in boundaries(building(city_model)) if (w := WallSurface.try_from(b)) is not None):
        ids += [p.object().feature_id().as_str() for p in wall.filling_surfaces()]
    return ids


def lower_corners(city_model: CityModel) -> list[tuple[float, float, float]]:
    """The lower corners of the city model's envelope and of the first wall surface's."""
    wall = next(w for f in city_model.iter_features() if (w := WallSurface.try_from(f)))
    return [
        point(city_model.bounded_by().envelope().lower_corner()),
        point(wall.bounded_by().envelope().lower_corner()),
    ]


class TestLod2:
    def test_lod2_boundary_surfaces(self, lod2: CityModel) -> None:
        features = boundaries(building(lod2))
        assert [f.feature_type() for f in features] == [
            FeatureType.WallSurface,
            FeatureType.WallSurface,
            FeatureType.WallSurface,
            FeatureType.RoofSurface,
            FeatureType.WallSurface,
            FeatureType.RoofSurface,
            FeatureType.GroundSurface,
        ]
        assert [first_name(w) for f in features if (w := WallSurface.try_from(f))] == [
            "Outer Wall 1 (West)",
            "Outer Wall 2 (South)",
            "Outer Wall 3 (East)",
            "Outer Wall 4 (North)",
        ]
        assert [first_name(r) for f in features if (r := RoofSurface.try_from(f))] == [
            "Roof 1 (North)",
            "Roof 2 (South)",
        ]
        assert [first_name(g) for f in features if (g := GroundSurface.try_from(f))] == ["Base Surface"]

    def test_lod2_surface_areas(self, lod2: CityModel) -> None:
        features = boundaries(building(lod2))

        def area(cls: type) -> float:
            surfaces = [s for f in features if (s := cls.try_from(f))]
            return sum(s.lod2_multi_surface().object().area_3d() for s in surfaces)

        assert area(WallSurface) == close(188.62887820601463)
        assert area(RoofSurface) == close(138.56406460961398)
        assert area(GroundSurface) == close(120.0)

    def test_lod2_generic_attributes(self, lod2: CityModel) -> None:
        b = building(lod2)
        area, method, landmarked = list(b.generic_attributes())
        measure = MeasureAttribute.try_from(area)
        assert area.name() == "GrossPlannedArea"
        assert measure.value().value() == close(120.0)
        assert measure.value().uom() == "m2"
        assert (method.name(), method.as_string().value()) == ("ConstructionMethod", "New Building")
        assert (landmarked.name(), landmarked.as_string().value()) == ("IsLandmarked", "NO")
        assert list(b.external_references()) == []

    def test_lod2_solid_unresolved(self, lod2: CityModel) -> None:
        solid = building(lod2).lod2_solid().object()
        with pytest.raises(Exception):
            solid.volume_3d()

    def test_lod2_building_details(self, lod2: CityModel) -> None:
        b = building(lod2)
        assert b.relative_to_terrain() == RelativeToTerrain.EntirelyAboveTerrain
        assert b.relative_to_water() is None
        created = b.creation_date()
        assert (created.year(), created.month(), created.day(), created.hour()) == (2017, 1, 23, 0)
        assert created.offset_seconds() == 3600
        assert created.timestamp() == 1485126000
        assert b.termination_date() is None
        assert b.valid_from() is None
        assert b.valid_to() is None

        assert b.class_().value() == "1000"
        assert [f.value() for f in b.functions()] == ["1000"]
        assert [u.value() for u in b.usages()] == ["1000"]
        assert b.roof_type().value() == "1030"
        assert (b.storeys_above_ground(), b.storeys_below_ground()) == (2, 0)
        date = b.date_of_construction()
        assert (date.year(), date.month(), date.day()) == (2020, 1, 1)
        assert b.date_of_demolition() is None
        [height] = list(b.heights())
        assert height.high_reference().value() == "topOfConstruction"
        assert height.low_reference().value() == "lowestGroundPoint"
        assert height.status() == HeightStatusValue.Measured
        assert height.length().value() == close(6.52)
        assert height.length().uom() == "m"

        assert list(b.occupancies()) == []
        assert list(b.related_to()) == []
        assert b.lod1_solid() is None
        assert b.bounded_by() is None
        assert b.lod1_terrain_intersection_curve() is None
        assert b.lod2_terrain_intersection_curve() is None
        assert b.lod3_terrain_intersection_curve() is None
        assert b.lod1_implicit_representation() is None
        assert b.lod2_implicit_representation() is None
        assert b.lod3_implicit_representation() is None

    def test_lod2_boundary_ids(self, lod2: CityModel) -> None:
        properties = list(building(lod2).boundaries())
        assert all(p.href() is None for p in properties)
        assert [p.object().feature_id().as_str() for p in properties] == [
            "GML_5856d7ad-5e34-498a-817b-9544bfbb1475",
            "GML_d38cf762-c29d-4491-88c9-bdc89e141978",
            "GML_8e5db638-e46a-4739-a98a-2fc2d39c9069",
            "GML_875d470b-32b4-4985-a4c8-0f02caa342a2",
            "GML_0f30f604-e70d-4dfe-ba35-853bc69609cc",
            "GML_eeb6796a-e261-4d3b-a6f2-475940cca80a",
            "GML_257a8dde-8194-4ca3-b581-abd591dcd6a3",
        ]

    def test_lod2_wall_surface(self, lod2: CityModel) -> None:
        features = boundaries(building(lod2))
        walls = [w for f in features if (w := WallSurface.try_from(f))]
        wall = walls[0]
        assert wall.id().as_str() == "GML_5856d7ad-5e34-498a-817b-9544bfbb1475"
        assert wall.lod0_multi_curve() is None
        assert wall.lod0_multi_surface() is None
        assert wall.lod1_multi_surface() is None
        assert wall.relative_to_terrain() is None
        assert wall.creation_date() is None
        assert list(wall.generic_attributes()) == []
        assert wall.bounded_by() is not None
        multi_surface = wall.lod2_multi_surface().object()
        assert len(list(multi_surface.surface_member())) == 1
        assert len(list(multi_surface.triangulate().surface().triangles())) == 3
        assert all(list(w.filling_surfaces()) == [] for w in walls)
        ground = next(g for f in features if (g := GroundSurface.try_from(f)))
        member = next(iter(ground.lod2_multi_surface().object().surface_member()))
        assert len(list(Polygon.try_from(member.object()).exterior().points())) == 4

    def test_lod2_generic_attribute_kinds(self, lod2: CityModel) -> None:
        area, method, landmarked = list(building(lod2).generic_attributes())
        assert area.as_string() is None
        assert MeasureAttribute.try_from(method) is None
        assert MeasureAttribute.try_from(landmarked) is None

    def test_lod2_city_objects(self, lod2: CityModel) -> None:
        assert [o.feature_type() for o in lod2.iter_city_objects()] == [
            FeatureType.Building,
            FeatureType.WallSurface,
            FeatureType.WallSurface,
            FeatureType.WallSurface,
            FeatureType.RoofSurface,
            FeatureType.WallSurface,
            FeatureType.RoofSurface,
            FeatureType.GroundSurface,
        ]
        types = [f.feature_type() for f in lod2.iter_features()]
        assert types[0] == FeatureType.CityModel
        assert types.count(FeatureType.CityModel) == 1

    def test_lod2_object_bounds(self) -> None:
        reader = GmlReader.from_path(str(FIXTURES / "fzk-haus" / LOD2))
        reader.with_rebuild_object_bounds(False)
        city_model = reader.finish()
        assert walls_bounded(city_model) == [False] * 4
        city_model.recompute_child_bounding_shapes()
        assert walls_bounded(city_model) == [True] * 4

    def test_lod2_apply_translation(self) -> None:
        city_model = read("fzk-haus", LOD2)
        assert lower_corners(city_model) == [close((457842.0, 5439083.0, 111.8))] * 2
        city_model.apply_translation(Vector3(-100.0, 200.0, 10.0))
        assert lower_corners(city_model) == [close((457742.0, 5439283.0, 121.8))] * 2


class TestLod3:
    def test_lod3_doors_and_windows(self, lod3: CityModel) -> None:
        features = list(lod3.iter_features())
        doors = [d for f in features if (d := DoorSurface.try_from(f))]
        assert [first_name(d) for d in doors] == ["Door West", "Door South"]
        assert sum(d.lod3_multi_surface().object().area_3d() for d in doors) == close(6.803850099444389)
        assert sum(1 for f in features if WindowSurface.try_from(f)) == 11

    def test_lod3_west_wall_fillings(self, lod3: CityModel) -> None:
        wall = WallSurface.try_from(boundaries(building(lod3))[0])
        assert first_name(wall) == "Outer Wall 1 (West)"
        fillings = [p.object() for p in wall.filling_surfaces()]
        assert [(f.feature_type(), first_name(f)) for f in fillings] == [
            (FeatureType.WindowSurface, "Window Round"),
            (FeatureType.WindowSurface, "Window North"),
            (FeatureType.DoorSurface, "Door West"),
            (FeatureType.WindowSurface, "Window South"),
        ]

    def test_lod3_building_details(self, lod3: CityModel) -> None:
        assert lod3.city_objects_len() == 1
        b = building(lod3)
        assert b.relative_to_terrain() == RelativeToTerrain.EntirelyAboveTerrain
        features = boundaries(b)
        assert [f.feature_type() for f in features] == [
            FeatureType.WallSurface,
            FeatureType.WallSurface,
            FeatureType.WallSurface,
            FeatureType.RoofSurface,
            FeatureType.WallSurface,
            FeatureType.RoofSurface,
            FeatureType.GroundSurface,
        ]
        assert all(w.lod3_multi_surface() is not None for f in features if (w := WallSurface.try_from(f)))

    def test_lod3_fillings(self, lod3: CityModel) -> None:
        features = boundaries(building(lod3))
        walls = [w for f in features if (w := WallSurface.try_from(f))]
        properties = [[p for p in w.filling_surfaces()] for w in walls]
        assert [len(p) for p in properties] == [4, 3, 3, 3]
        fillings = [p for wall in properties for p in wall]
        assert all(p.href() is None for p in fillings)
        types = [p.object().feature_type() for p in fillings]
        assert (types.count(FeatureType.DoorSurface), types.count(FeatureType.WindowSurface)) == (2, 11)
        assert all(p.object().lod3_multi_surface().object().area_3d() > 0.0 for p in fillings)
        assert all(list(r.filling_surfaces()) == [] for f in features if (r := RoofSurface.try_from(f)))

        all_features = list(lod3.iter_features())
        windows = [w for f in all_features if (w := WindowSurface.try_from(f))]
        assert sum(w.lod3_multi_surface().object().area_3d() for w in windows) == close(23.168802611529827)
        doors = [d for f in all_features if (d := DoorSurface.try_from(f))]
        assert [d.feature_id().as_str() for d in doors] == [
            "GML_c137f11d-9a8c-4126-9aeb-9a6c9b4e1cbd",
            "GML_2d6ddf04-ee56-42a1-a9b1-b47e4181a629",
        ]
        assert all(d.lod2_multi_surface() is None for d in doors)

    def test_lod3_city_objects(self, lod3: CityModel) -> None:
        objects = [o.feature_type() for o in lod3.iter_city_objects()]
        assert len(objects) == 21
        assert [
            objects.count(t)
            for t in (
                FeatureType.Building,
                FeatureType.WallSurface,
                FeatureType.RoofSurface,
                FeatureType.GroundSurface,
                FeatureType.DoorSurface,
                FeatureType.WindowSurface,
            )
        ] == [1, 4, 2, 1, 2, 11]
        types = [f.feature_type() for f in lod3.iter_features()]
        assert len(types) == 22
        assert types[0] == FeatureType.CityModel

    def test_lod3_composite_surface(self, lod3: CityModel) -> None:
        wall = WallSurface.try_from(boundaries(building(lod3))[0])
        member = next(iter(wall.lod3_multi_surface().object().surface_member()))
        composite = CompositeSurface.try_from(member.object())
        assert len(list(composite.surface_member())) == 85
        polygon = Polygon.try_from(next(iter(composite.surface_member())).object())
        start = next(iter(polygon.exterior().points()))
        assert point(start) == close((457842.0, 5439088.49240388, 115.913175911167))

    def test_lod3_round_trip(self, lod3: CityModel, tmp_path: Path) -> None:
        path = tmp_path / "round-trip.gml"
        GmlWriter.from_path(str(path)).finish(lod3)
        written = GmlReader.from_path(str(path)).finish()
        # Two returned FeatureType values never compare equal (only one against the class constant), hence `str`.
        assert [str(f.feature_type()) for f in written.iter_features()] == [
            str(f.feature_type()) for f in lod3.iter_features()
        ]
        assert building(written).feature_id().as_str() == "UUID_d281adfc-4901-0f52-540b-4cc1a9325f82"
        assert surface_ids(written) == surface_ids(lod3)
        [height] = list(building(written).heights())
        assert height.high_reference().value() == "topOfConstruction"
        assert height.low_reference().value() == "lowestGroundPoint"
        assert height.status() == HeightStatusValue.Measured
        assert (height.length().value(), height.length().uom()) == (pytest.approx(6.52, abs=1e-6), "m")
