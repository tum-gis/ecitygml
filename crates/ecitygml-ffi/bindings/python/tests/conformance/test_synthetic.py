"""The cases of crates/ecitygml/tests/conformance/synthetic.md."""

from pathlib import Path
from typing import Any

import pytest

from conformance.helpers import close, read
from conftest import read_model
from ecitygml import (
    AbstractFeatureKindRef,
    AbstractRingKind,
    Bridge,
    BridgePart,
    Building,
    CityFurniture,
    CityModel,
    ErrorKind,
    FeatureType,
    GenericAttributeSet,
    GmlWriter,
    GranularityValue,
    LinearRing,
    LineString,
    MultiSurface,
    PlantCover,
    Point,
    Polygon,
    RelativeToWater,
    RoofSurface,
    Section,
    SolitaryVegetationObject,
    TrafficDirectionValue,
    TrafficSpace,
    TriangulatedSurface,
    Tunnel,
    TunnelPart,
)

DATASET = "synthetic"


def feature_types(city_model: CityModel) -> list[str]:
    # Two returned FeatureType values never compare equal (only one against the class constant), hence `str`.
    return [str(f.feature_type()) for f in city_model.iter_features()]


def all_of(city_model: CityModel, cls: Any) -> list[Any]:
    return [x for f in city_model.iter_features() if (x := cls.try_from(f)) is not None]


def only(city_model: CityModel, cls: Any) -> Any:
    [found] = all_of(city_model, cls)
    return found


def with_id(city_model: CityModel, cls: Any, feature_id: str) -> Any:
    return next(x for x in all_of(city_model, cls) if x.feature_id().as_str() == feature_id)


def values(iterator: Any) -> list[str]:
    return [value.value() for value in iterator]


def ymd(date: Any) -> tuple[int, int, int]:
    return (date.year(), date.month(), date.day())


def round_trip(city_model: CityModel, tmp_path: Path) -> tuple[CityModel, str]:
    path = tmp_path / "written.gml"
    GmlWriter.from_path(str(path)).finish(city_model)
    return read_model(path), path.read_text()


class TestBridge:
    @pytest.fixture
    def model(self) -> CityModel:
        return read(DATASET, "bridge.gml")

    @staticmethod
    def part(bridge: Any) -> Any:
        [part] = list(bridge.bridge_parts())
        assert part.href() is None
        return part.object()

    def test_bridge_city_model(self, model: CityModel) -> None:
        assert model.city_objects_len() == 1
        assert feature_types(model) == ["FeatureType.CityModel", "FeatureType.Bridge", "FeatureType.BridgePart"]
        assert [str(o.feature_type()) for o in model.iter_city_objects()] == [
            "FeatureType.Bridge",
            "FeatureType.BridgePart",
        ]

    def test_bridge_attributes(self, model: CityModel) -> None:
        bridge = only(model, Bridge)
        assert bridge.feature_id().as_str() == "bridge_1"
        assert values(bridge.names()) == ["Synthetic bridge"]
        assert bridge.class_().value() == "1000"
        assert values(bridge.functions()) == ["1010", "1020"]
        assert values(bridge.usages()) == ["1000"]
        assert ymd(bridge.date_of_construction()) == (1990, 5, 1)
        assert list(bridge.heights()) == []
        part = self.part(bridge)
        assert part.feature_id().as_str() == "bridge_part_1"
        assert part.class_() is None
        assert list(part.functions()) == []
        assert only(model, BridgePart).feature_id().as_str() == "bridge_part_1"

    def test_bridge_is_movable(self, model: CityModel) -> None:
        bridge = only(model, Bridge)
        assert bridge.is_movable() is True
        assert self.part(bridge).is_movable() is False

    def test_bridge_code_spaces(self, model: CityModel) -> None:
        bridge = only(model, Bridge)
        assert bridge.class_().code().code_space() == "https://example.org/bridge_class"
        assert all(f.code().code_space() is None for f in bridge.functions())

    def test_bridge_round_trip(self, model: CityModel, tmp_path: Path) -> None:
        written, _ = round_trip(model, tmp_path)
        assert feature_types(written) == feature_types(model)
        bridge = only(written, Bridge)
        assert bridge.class_().value() == "1000"
        assert values(bridge.functions()) == ["1010", "1020"]
        assert ymd(bridge.date_of_construction()) == (1990, 5, 1)
        assert self.part(bridge).feature_id().as_str() == "bridge_part_1"


class TestTunnel:
    @pytest.fixture
    def model(self) -> CityModel:
        return read(DATASET, "tunnel.gml")

    @staticmethod
    def part(tunnel: Any) -> Any:
        [part] = list(tunnel.tunnel_parts())
        assert part.href() is None
        return part.object()

    def test_tunnel_city_model(self, model: CityModel) -> None:
        assert model.city_objects_len() == 1
        assert feature_types(model) == ["FeatureType.CityModel", "FeatureType.Tunnel", "FeatureType.TunnelPart"]
        assert [str(o.feature_type()) for o in model.iter_city_objects()] == [
            "FeatureType.Tunnel",
            "FeatureType.TunnelPart",
        ]

    def test_tunnel_attributes(self, model: CityModel) -> None:
        tunnel = only(model, Tunnel)
        assert tunnel.feature_id().as_str() == "tunnel_1"
        assert values(tunnel.names()) == ["Synthetic tunnel"]
        assert tunnel.class_().value() == "1000"
        assert values(tunnel.functions()) == ["1010", "1020"]
        assert values(tunnel.usages()) == ["1000"]
        assert ymd(tunnel.date_of_construction()) == (1990, 5, 1)
        assert list(tunnel.heights()) == []
        part = self.part(tunnel)
        assert part.feature_id().as_str() == "tunnel_part_1"
        assert part.class_() is None
        assert values(part.functions()) == ["1030"]
        assert only(model, TunnelPart).feature_id().as_str() == "tunnel_part_1"

    def test_tunnel_code_spaces(self, model: CityModel) -> None:
        tunnel = only(model, Tunnel)
        assert tunnel.class_().code().code_space() == "https://example.org/tunnel_class"
        assert all(f.code().code_space() is None for f in tunnel.functions())

    def test_tunnel_round_trip(self, model: CityModel, tmp_path: Path) -> None:
        written, _ = round_trip(model, tmp_path)
        assert feature_types(written) == feature_types(model)
        tunnel = only(written, Tunnel)
        assert tunnel.class_().value() == "1000"
        assert values(tunnel.functions()) == ["1010", "1020"]
        assert values(self.part(tunnel).functions()) == ["1030"]


def implicit(property: Any) -> Any:
    assert property is not None and property.href() is None
    return property.object()


class TestVegetation:
    @pytest.fixture
    def model(self) -> CityModel:
        return read(DATASET, "vegetation.gml")

    def test_vegetation_city_model(self, model: CityModel) -> None:
        assert model.city_objects_len() == 3
        assert feature_types(model) == [
            "FeatureType.CityModel",
            "FeatureType.SolitaryVegetationObject",
            "FeatureType.SolitaryVegetationObject",
            "FeatureType.PlantCover",
        ]

    def test_vegetation_tree(self, model: CityModel) -> None:
        tree = with_id(model, SolitaryVegetationObject, "tree_1")
        assert tree.class_().value() == "1000"
        assert values(tree.functions()) == ["1010"]
        assert values(tree.usages()) == ["1020"]
        assert tree.species().value() == "Quercus robur"
        assert (tree.height().value(), tree.height().uom()) == (close(12.5), "m")
        assert tree.trunk_diameter().value() == close(0.4)
        assert tree.crown_diameter().value() == close(5.5)
        assert tree.root_ball_diameter().value() == close(1.2)
        assert tree.max_root_ball_depth().value() == close(0.8)
        assert tree.lod2_implicit_representation() is None
        assert tree.lod3_implicit_representation() is None
        assert tree.lod1_solid() is None
        assert tree.lod1_terrain_intersection_curve() is None

    def test_vegetation_implicit_geometry(self, model: CityModel) -> None:
        geometry = implicit(with_id(model, SolitaryVegetationObject, "tree_1").lod1_implicit_representation())
        assert geometry.object_id().as_str() == "tree_prototype"
        assert geometry.mime_type().value() == "model/gltf+json"
        pos = geometry.reference_point().object().pos()
        assert (pos.x(), pos.y(), pos.z()) == (457850.0, 5439090.0, 112.0)
        matrix = geometry.transformation_matrix()
        assert [[matrix.get(row, column) for column in range(4)] for row in range(4)] == [
            [2.0, 0.0, 0.0, 10.0],
            [0.0, 2.0, 0.0, 20.0],
            [0.0, 0.0, 3.0, 30.0],
            [0.0, 0.0, 0.0, 1.0],
        ]
        relative = geometry.relative_geometry().object()
        assert str(relative.geometry_type()) == "GeometryType.MultiSurface"
        assert len(list(MultiSurface.try_from(relative).surface_member())) == 1
        assert Point.try_from(relative) is None
        triangulation = relative.triangulate()
        assert not triangulation.has_skipped()
        assert len(list(triangulation.surface().triangles())) == 1

    def test_vegetation_point_relative_geometry(self, model: CityModel) -> None:
        tree = with_id(model, SolitaryVegetationObject, "tree_2")
        assert tree.lod1_implicit_representation() is None
        geometry = implicit(tree.lod2_implicit_representation())
        assert geometry.object_id().as_str() == "point_prototype"
        assert geometry.mime_type() is None
        relative = geometry.relative_geometry().object()
        assert str(relative.geometry_type()) == "GeometryType.Point"
        pos = Point.try_from(relative).pos()
        assert (pos.x(), pos.y(), pos.z()) == (0.0, 0.0, 0.0)
        assert MultiSurface.try_from(relative) is None

    def test_vegetation_library_object(self, model: CityModel) -> None:
        first = implicit(with_id(model, SolitaryVegetationObject, "tree_1").lod1_implicit_representation())
        assert first.library_object() is None
        second = implicit(with_id(model, SolitaryVegetationObject, "tree_2").lod2_implicit_representation())
        assert second.library_object() == "https://example.org/trees/oak.gltf"

    def test_vegetation_plant_cover(self, model: CityModel) -> None:
        cover = only(model, PlantCover)
        assert cover.feature_id().as_str() == "cover_1"
        assert cover.class_().value() == "2000"
        assert list(cover.functions()) == [] and list(cover.usages()) == []
        assert cover.average_height().value() == close(2.5)
        assert cover.min_height().value() == close(1.0)
        assert cover.max_height().value() == close(4.0)
        assert cover.lod1_implicit_representation() is None
        feature = next(f for f in model.iter_features() if f.feature_type() == FeatureType.PlantCover)
        assert SolitaryVegetationObject.try_from(feature) is None

    def test_vegetation_code_spaces(self, model: CityModel) -> None:
        tree = with_id(model, SolitaryVegetationObject, "tree_1")
        assert tree.class_().code().code_space() == "https://example.org/tree_class"
        assert only(model, PlantCover).class_().code().code_space() is None

    def test_vegetation_round_trip(self, model: CityModel, tmp_path: Path) -> None:
        written, text = round_trip(model, tmp_path)
        assert feature_types(written) == feature_types(model)
        tree = with_id(written, SolitaryVegetationObject, "tree_1")
        assert tree.species().value() == "Quercus robur"
        assert tree.height().value() == close(12.5)
        geometry = implicit(tree.lod1_implicit_representation())
        assert geometry.object_id().as_str() == "tree_prototype"
        assert geometry.mime_type().value() == "model/gltf+json"
        assert only(written, PlantCover).average_height().value() == close(2.5)
        assert "objectId" not in text


class TestCityFurniture:
    @pytest.fixture
    def model(self) -> CityModel:
        return read(DATASET, "city-furniture.gml")

    def test_furniture_attributes(self, model: CityModel) -> None:
        furniture = only(model, CityFurniture)
        assert furniture.feature_id().as_str() == "sign_1"
        assert values(furniture.names()) == ["Vorschriftzeichen"]
        assert furniture.class_().value() == "1000"
        assert values(furniture.functions()) == ["1080"]
        assert values(furniture.usages()) == ["1090"]
        property = furniture.lod2_multi_surface()
        assert property.href() is None
        assert len(list(property.object().surface_member())) == 1
        assert furniture.lod1_implicit_representation() is None
        assert furniture.lod2_terrain_intersection_curve() is None

    def test_furniture_code_spaces(self, model: CityModel) -> None:
        code = only(model, CityFurniture).class_().code()
        assert code.code_space() == "https://example.org/furniture_class"


def roof(property: Any) -> Any:
    assert property.href() is None
    return RoofSurface.try_from(AbstractFeatureKindRef.from_space_boundary(property.object()))


def attribute_set(building: Any) -> Any:
    [attribute] = list(building.generic_attributes())
    return GenericAttributeSet.try_from(attribute)


class TestBuilding:
    @pytest.fixture
    def model(self) -> CityModel:
        return read(DATASET, "building.gml")

    def test_building_city_model(self, model: CityModel) -> None:
        assert model.city_objects_len() == 2
        assert feature_types(model) == [
            "FeatureType.CityModel",
            "FeatureType.Building",
            "FeatureType.RoofSurface",
            "FeatureType.WindowSurface",
            "FeatureType.Building",
        ]
        assert len(list(model.iter_city_objects())) == 4

    def test_building_relation(self, model: CityModel) -> None:
        [property] = list(with_id(model, Building, "building_1").related_to())
        assert property.href() is None
        relation = property.object()
        assert relation.relation_type().value() == "shared"
        assert relation.relation_to().href().to_string() == "#building_2"
        [weight] = list(relation.generic_attributes())
        assert (weight.name(), weight.as_int().value()) == ("weight", 3)

    def test_building_attribute_set(self, model: CityModel) -> None:
        attributes = attribute_set(with_id(model, Building, "building_1"))
        assert attributes.name() == "energy"
        demand, label = list(attributes.generic_attributes())
        assert (demand.name(), demand.as_double().value()) == ("demand", close(12.5))
        assert (label.name(), label.as_string().value()) == ("label", "A+")

    def test_building_construction(self, model: CityModel) -> None:
        building = with_id(model, Building, "building_1")
        assert building.relative_to_water() == RelativeToWater.EntirelyAboveWaterSurface
        assert ymd(building.date_of_construction()) == (2020, 1, 1)
        assert ymd(building.date_of_demolition()) == (2050, 12, 31)
        [occupancy] = list(building.occupancies())
        assert occupancy.number_of_occupants() == 4
        assert occupancy.interval().value() == "daytime"
        assert occupancy.occupant_type().value() == "residents"

    def test_building_boundaries(self, model: CityModel) -> None:
        first, second = list(with_id(model, Building, "building_1").boundaries())
        roof_surface = roof(first)
        assert roof_surface.feature_id().as_str() == "roof_1"
        [filling] = list(roof_surface.filling_surfaces())
        assert filling.href() is None
        window = filling.object()
        assert window.feature_type() == FeatureType.WindowSurface
        assert window.feature_id().as_str() == "roof_window_1"
        assert second.object() is None
        assert second.href().to_string() == "#missing_boundary"

    def test_building_terrain_intersection_curve(self, model: CityModel) -> None:
        building = with_id(model, Building, "building_1")
        property = building.lod2_terrain_intersection_curve()
        assert property.href() is None
        multi_curve = property.object()
        [member] = list(multi_curve.curve_member())
        assert len(list(LineString.try_from(member.object()).points())) == 2
        assert multi_curve.length_3d() == close(12.0)
        assert building.lod1_terrain_intersection_curve() is None
        assert building.lod3_terrain_intersection_curve() is None

    def test_building_round_trip(self, model: CityModel, tmp_path: Path) -> None:
        written, text = round_trip(model, tmp_path)
        assert feature_types(written) == feature_types(model)
        building = with_id(written, Building, "building_1")
        [relation] = list(building.related_to())
        assert relation.object().relation_to().href().to_string() == "#building_2"
        assert attribute_set(building).name() == "energy"
        assert ymd(building.date_of_demolition()) == (2050, 12, 31)
        [occupancy] = list(building.occupancies())
        assert (occupancy.number_of_occupants(), occupancy.interval().value(), occupancy.occupant_type().value()) == (
            4,
            "daytime",
            "residents",
        )
        first, second = list(building.boundaries())
        [filling] = list(roof(first).filling_surfaces())
        assert filling.object().feature_id().as_str() == "roof_window_1"
        assert second.href().to_string() == "#missing_boundary"
        assert building.lod2_terrain_intersection_curve().object().length_3d() == close(12.0)
        assert "TerrainIntersectionCurveProperty" not in text


class TestTransportation:
    @pytest.fixture
    def model(self) -> CityModel:
        return read(DATASET, "transportation.gml")

    def test_transportation_section(self, model: CityModel) -> None:
        section = only(model, Section)
        assert section.feature_id().as_str() == "section_1"
        assert section.traffic_direction() == TrafficDirectionValue.Both
        [occupancy] = list(section.occupancies())
        assert (occupancy.number_of_occupants(), occupancy.interval().value()) == (120, "peakHour")
        [property] = list(section.traffic_spaces())
        assert property.href() is None
        space = property.object()
        assert space.feature_id().as_str() == "space_1"
        assert space.granularity() == GranularityValue.Lane

    def test_transportation_point(self, model: CityModel) -> None:
        property = only(model, TrafficSpace).lod0_point()
        assert property.href() is None
        point = property.object()
        assert point.id().as_str() == "point_1"
        pos = point.pos()
        assert (pos.x(), pos.y(), pos.z()) == (1.5, -2.5, 3.25)
        envelope = point.compute_envelope()
        for corner in [envelope.lower_corner(), envelope.upper_corner()]:
            assert (corner.x(), corner.y(), corner.z()) == (1.5, -2.5, 3.25)

    def test_transportation_curves(self, model: CityModel) -> None:
        multi_curve = only(model, TrafficSpace).lod0_multi_curve().object()
        line, ring, reference = list(multi_curve.curve_member())
        line_kind = line.object()
        assert str(line_kind.geometry_type()) == "GeometryType.LineString"
        assert AbstractRingKind.try_from(line_kind) is None
        line_string = LineString.try_from(line_kind)
        assert len(list(line_string.points())) == 2
        assert line_string.length_3d() == close(5.0)
        ring_kind = ring.object()
        assert str(ring_kind.geometry_type()) == "GeometryType.LinearRing"
        linear_ring = LinearRing.try_from(AbstractRingKind.try_from(ring_kind))
        assert len(list(linear_ring.points())) == 3
        assert linear_ring.length_3d() == close(2.0 + 2.0**0.5)
        assert reference.object() is None
        assert reference.href().to_string() == "#missing_curve"
        with pytest.raises(Exception) as raised:
            multi_curve.length_3d()
        error = raised.value.args[0]
        assert error.kind() == ErrorKind.UnresolvedReference
        assert "#missing_curve" in str(error)


class TestGeometry:
    def test_geometry_skipped_members(self) -> None:
        model = read(DATASET, "geometry.gml")
        multi_surface = with_id(model, Building, "geometry_1").lod2_multi_surface().object()
        square, collinear, tin_kind = [m.object() for m in multi_surface.surface_member()]
        for kind, surface_id in [(square, "square"), (collinear, "collinear")]:
            assert str(kind.geometry_type()) == "GeometryType.Polygon"
            assert kind.id().as_str() == surface_id
        assert collinear.area_3d() == close(0.0)
        assert str(tin_kind.geometry_type()) == "GeometryType.TriangulatedSurface"
        assert Polygon.try_from(tin_kind) is None
        tin = TriangulatedSurface.try_from(tin_kind)
        assert tin.id().as_str() == "tin"
        assert len(list(tin.triangles())) == 2
        assert len(list(tin.surface().patches())) == 2
        assert tin.area_3d() == close(1.0)
        triangulation = multi_surface.triangulate()
        assert len(list(triangulation.surface().triangles())) == 4
        assert triangulation.has_skipped()
        [error] = list(triangulation.skipped())
        assert error.kind() == ErrorKind.InvalidArgument
        assert "earcut produced no triangles" in str(error)
