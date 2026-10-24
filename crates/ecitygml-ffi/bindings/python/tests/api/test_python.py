"""The cases of crates/ecitygml/tests/api/python.md: the Python bindings' dynamic typing."""

from collections.abc import Callable
from typing import Any

import pytest

from api.helpers import fixture
from conftest import read_model
from ecitygml import (
    AbstractFeatureKindRef,
    AbstractFillingSurfaceKind,
    AbstractRingKind,
    AuxiliaryTrafficArea,
    AuxiliaryTrafficSpace,
    Bridge,
    BridgePart,
    Building,
    BuildingUnit,
    CityFurniture,
    CityModel,
    CityObjectRelation,
    DirectPosition,
    DoorSurface,
    Envelope,
    ExternalReference,
    FeatureType,
    GmlReader,
    GroundSurface,
    Height,
    ImplicitGeometry,
    Intersection,
    LevelOfDetail,
    LinearRing,
    MultiCurve,
    MultiSurface,
    Occupancy,
    PlantCover,
    Polygon,
    ReliefFeature,
    Road,
    RoofSurface,
    Section,
    Solid,
    SolitaryVegetationObject,
    Storey,
    TinRelief,
    TrafficArea,
    TrafficSpace,
    Triangle,
    TriangulatedSurface,
    Tunnel,
    TunnelPart,
    WallSurface,
    WindowSurface,
)

FZK_LOD1 = fixture("fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml")
FZK_LOD2 = fixture("fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml")
FZK_LOD3 = fixture("fzk-haus/FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml")
TUM = fixture("tum-main-entrance/TUM-Main-Entrance.gml")
ASAM_ROAD_SHAPE = fixture("asam-opendrive/ASAM-UC_RoadShape.gml")
ASAM_JUNCTION = fixture("asam-opendrive/ASAM-Ex_Bidirectional_Junction.gml")


def synthetic(name: str) -> str:
    return fixture(f"synthetic/{name}")


def features(city_model: CityModel, cls: Any) -> list[Any]:
    """The features `cls.try_from` accepts, in document order."""
    return [x for f in city_model.iter_features() if (x := cls.try_from(f)) is not None]


def by_id(city_model: CityModel, cls: Any, feature_id: str) -> Any:
    return next(x for x in features(city_model, cls) if x.feature_id().as_str() == feature_id)


def objects(properties: Any) -> list[Any]:
    """The objects of properties, all of which must be present."""
    result = [p.object() for p in properties]
    assert result and all(o is not None for o in result)
    return result


def obj(prop: Any) -> Any:
    assert prop is not None and prop.object() is not None
    return prop.object()


def boundaries(space: Any, cls: Any) -> list[Any]:
    return [
        x
        for boundary in objects(space.boundaries())
        if (x := cls.try_from(AbstractFeatureKindRef.from_space_boundary(boundary))) is not None
    ]


def first_polygon(solid: Solid) -> Polygon:
    return next(p for s in objects(solid.exterior().members()) if (p := Polygon.try_from(s)) is not None)


# `python_return_types`: (file, values from the city model, class); every case keeps its city model referenced.
def fzk_lod1_values(m: CityModel) -> dict[str, list[Any]]:
    building = features(m, Building)[0]
    solid = obj(building.lod1_solid())
    triangle = next(iter(solid.triangulate().surface().triangles()))
    exterior = first_polygon(solid).exterior()
    first_point = next(iter(solid.points()))
    return {
        "solid": [solid],
        "positions": [*solid.points(), triangle.a(), triangle.b(), triangle.c()],
        "ring": [exterior],
        "linear_ring": [LinearRing.try_from(exterior)],
        "envelopes": [solid.compute_envelope(), first_polygon(solid).compute_envelope()],
        "contains": [building.bounded_by().envelope().contains(first_point)],
        "triangulated": [solid.triangulate().surface()],
        "triangles": list(solid.triangulate().surface().triangles()),
    }


RETURN_TYPES: list[tuple[str, str, Callable[[CityModel], list[Any]], type]] = [
    ("fzk_lod2_city_model", FZK_LOD2, lambda m: [m], CityModel),
    ("fzk_lod2_heights", FZK_LOD2, lambda m: list(features(m, Building)[0].heights()), Height),
    ("fzk_lod1_solid", FZK_LOD1, lambda m: fzk_lod1_values(m)["solid"], Solid),
    ("fzk_lod1_positions", FZK_LOD1, lambda m: fzk_lod1_values(m)["positions"], DirectPosition),
    ("fzk_lod1_ring", FZK_LOD1, lambda m: fzk_lod1_values(m)["ring"], AbstractRingKind),
    ("fzk_lod1_linear_ring", FZK_LOD1, lambda m: fzk_lod1_values(m)["linear_ring"], LinearRing),
    ("fzk_lod1_envelopes", FZK_LOD1, lambda m: fzk_lod1_values(m)["envelopes"], Envelope),
    ("fzk_lod1_contains", FZK_LOD1, lambda m: fzk_lod1_values(m)["contains"], bool),
    ("fzk_lod1_triangulated", FZK_LOD1, lambda m: fzk_lod1_values(m)["triangulated"], TriangulatedSurface),
    ("fzk_lod1_triangles", FZK_LOD1, lambda m: fzk_lod1_values(m)["triangles"], Triangle),
    (
        "fzk_lod3_multi_surfaces",
        FZK_LOD3,
        lambda m: [obj(features(m, cls)[0].lod3_multi_surface()) for cls in (WallSurface, DoorSurface, WindowSurface)],
        MultiSurface,
    ),
    (
        "fzk_lod3_filling_surfaces",
        FZK_LOD3,
        lambda m: [f for wall in features(m, WallSurface) for f in (p.object() for p in wall.filling_surfaces())],
        AbstractFillingSurfaceKind,
    ),
    ("tum_external_references", TUM, lambda m: list(features(m, Building)[0].external_references()), ExternalReference),
    ("asam_junction_sections", ASAM_JUNCTION, lambda m: objects(features(m, Road)[0].sections()), Section),
    (
        "asam_junction_intersections",
        ASAM_JUNCTION,
        lambda m: objects(features(m, Road)[0].intersections()),
        Intersection,
    ),
    (
        "asam_junction_traffic_spaces",
        ASAM_JUNCTION,
        lambda m: objects(objects(features(m, Road)[0].sections())[0].traffic_spaces()),
        TrafficSpace,
    ),
    (
        "asam_junction_multi_curve",
        ASAM_JUNCTION,
        lambda m: [obj(objects(objects(features(m, Road)[0].sections())[0].traffic_spaces())[0].lod2_multi_curve())],
        MultiCurve,
    ),
    (
        "asam_road_shape_auxiliary_traffic_spaces",
        ASAM_ROAD_SHAPE,
        lambda m: objects(objects(features(m, Road)[0].sections())[0].auxiliary_traffic_spaces()),
        AuxiliaryTrafficSpace,
    ),
    (
        "synthetic_occupancies",
        synthetic("building.gml"),
        lambda m: list(by_id(m, Building, "building_1").occupancies()),
        Occupancy,
    ),
    (
        "synthetic_relations",
        synthetic("building.gml"),
        lambda m: objects(by_id(m, Building, "building_1").related_to()),
        CityObjectRelation,
    ),
    (
        "synthetic_terrain_intersection_curve",
        synthetic("building.gml"),
        lambda m: [obj(by_id(m, Building, "building_1").lod2_terrain_intersection_curve())],
        MultiCurve,
    ),
    (
        "synthetic_bridge_parts",
        synthetic("bridge.gml"),
        lambda m: objects(features(m, Bridge)[0].bridge_parts()),
        BridgePart,
    ),
    (
        "synthetic_tunnel_parts",
        synthetic("tunnel.gml"),
        lambda m: objects(features(m, Tunnel)[0].tunnel_parts()),
        TunnelPart,
    ),
    (
        "synthetic_implicit_geometry",
        synthetic("vegetation.gml"),
        lambda m: [obj(by_id(m, SolitaryVegetationObject, "tree_1").lod1_implicit_representation())],
        ImplicitGeometry,
    ),
]


@pytest.mark.parametrize(("path", "values", "cls"), [r[1:] for r in RETURN_TYPES], ids=[r[0] for r in RETURN_TYPES])
def test_python_return_types(path: str, values: Callable[[CityModel], list[Any]], cls: type) -> None:
    city_model = GmlReader.from_path(path).finish()
    found = values(city_model)
    assert found
    assert all(isinstance(value, cls) for value in found), [type(value) for value in found]


# `python_class_getters`
def lods(prefix: str, levels: range) -> list[str]:
    return [f"lod{lod}_{prefix}" for lod in levels]


FEATURE = [
    "id",
    "bounded_by",
    "creation_date",
    "termination_date",
    "valid_from",
    "valid_to",
    "relative_to_terrain",
    "relative_to_water",
    "external_references",
    "generic_attributes",
    "related_to",
]
SPACE_GEOMETRY = [
    *lods("solid", range(1, 4)),
    *lods("multi_surface", range(0, 4)),
    *lods("multi_curve", range(0, 4)),
]
# `lod1_multi_surface` and `lod1_multi_curve` aren't CityGML space properties.
SPACE_GEOMETRY = [name for name in SPACE_GEOMETRY if name not in ("lod1_multi_surface", "lod1_multi_curve")]
TERRAIN_INTERSECTION_CURVES = lods("terrain_intersection_curve", range(1, 4))
IMPLICIT_REPRESENTATIONS = lods("implicit_representation", range(1, 4))
CONSTRUCTION = ["date_of_construction", "date_of_demolition", "heights", "occupancies"]
CLASSIFIED = ["class_", "functions", "usages"]
BUILDING = ["roof_type", "storeys_above_ground", "storeys_below_ground", "building_subdivisions"]
TRANSPORTATION_SPACE = ["traffic_direction", "occupancies", "traffic_spaces", "auxiliary_traffic_spaces"]
THEMATIC_SURFACE = ["generic_attributes", "lod0_multi_curve", *lods("multi_surface", range(0, 4))]

CONSTRUCTIONS = [Building, Bridge, BridgePart, Tunnel, TunnelPart]
OTHER_OCCUPIED_SPACES = [CityFurniture, SolitaryVegetationObject, PlantCover]
OCCUPIED_SPACES = CONSTRUCTIONS + OTHER_OCCUPIED_SPACES
UNOCCUPIED_SPACES = [Road, Section, Intersection, TrafficSpace, AuxiliaryTrafficSpace]
SPACES = OCCUPIED_SPACES + UNOCCUPIED_SPACES
LOGICAL_SPACES = [Storey, BuildingUnit]
CONSTRUCTION_SURFACES = [WallSurface, RoofSurface, GroundSurface]
FILLING_SURFACES = [DoorSurface, WindowSurface, AbstractFillingSurfaceKind]
THEMATIC_SURFACES = CONSTRUCTION_SURFACES + [DoorSurface, WindowSurface, TrafficArea, AuxiliaryTrafficArea]
FEATURES = SPACES + LOGICAL_SPACES + THEMATIC_SURFACES + [ReliefFeature, TinRelief]

# (row, classes, getters they have, getters they lack)
CLASS_GETTERS: list[tuple[str, list[type], list[str], list[str]]] = [
    ("features", FEATURES, FEATURE, []),
    ("spaces", SPACES, SPACE_GEOMETRY + TERRAIN_INTERSECTION_CURVES, []),
    ("occupied_spaces", OCCUPIED_SPACES, IMPLICIT_REPRESENTATIONS, []),
    ("unoccupied_spaces", UNOCCUPIED_SPACES, [], IMPLICIT_REPRESENTATIONS),
    ("constructions", CONSTRUCTIONS, CONSTRUCTION + CLASSIFIED, []),
    ("other_occupied_spaces", OTHER_OCCUPIED_SPACES, [], CONSTRUCTION),
    ("building", [Building], BUILDING, []),
    ("bridges", [Bridge, BridgePart], ["is_movable"], ["roof_type", "storeys_above_ground"]),
    ("tunnels", [Tunnel, TunnelPart], [], ["is_movable"]),
    ("transportation_spaces", [Road, Section, Intersection], TRANSPORTATION_SPACE, []),
    ("traffic_spaces", [TrafficSpace, AuxiliaryTrafficSpace], [], ["traffic_spaces", "auxiliary_traffic_spaces"]),
    ("logical_spaces", LOGICAL_SPACES, SPACE_GEOMETRY + CLASSIFIED, TERRAIN_INTERSECTION_CURVES),
    ("thematic_surfaces", THEMATIC_SURFACES, THEMATIC_SURFACE, []),
    ("filling_surfaces", FILLING_SURFACES, ["lod3_multi_surface", "generic_attributes"], ["filling_surfaces"]),
    ("construction_surfaces", CONSTRUCTION_SURFACES, ["filling_surfaces"], ["door_surfaces", "window_surfaces"]),
]


@pytest.mark.parametrize(
    ("classes", "has", "lacks"), [r[1:] for r in CLASS_GETTERS], ids=[r[0] for r in CLASS_GETTERS]
)
def test_python_class_getters(classes: list[type], has: list[str], lacks: list[str]) -> None:
    missing = [(cls.__name__, name) for cls in classes for name in has if not hasattr(cls, name)]
    present = [(cls.__name__, name) for cls in classes for name in lacks if hasattr(cls, name)]
    assert (missing, present) == ([], [])


# `python_enums`
FEATURE_TYPES = [
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


def test_python_enums() -> None:
    assert FeatureType.Building == FeatureType.Building
    assert FeatureType.Road != FeatureType.Building
    assert LevelOfDetail.One == LevelOfDetail.One
    assert LevelOfDetail.One != LevelOfDetail.Two
    levels = [LevelOfDetail.Zero, LevelOfDetail.One, LevelOfDetail.Two, LevelOfDetail.Three]
    assert [level.value for level in levels] == [0, 1, 2, 3]
    assert "Building" in repr(FeatureType.Building)
    assert "One" in repr(LevelOfDetail.One)
    assert [name for name in FEATURE_TYPES if not hasattr(FeatureType, name)] == []


# `python_value_types`
def test_python_value_types() -> None:
    asam = read_model(ASAM_ROAD_SHAPE)
    attributes = [a for space in features(asam, TrafficSpace) for a in space.generic_attributes()]
    ints = [a.as_int().value() for a in attributes if a.as_int() is not None]
    doubles = [a.as_double().value() for a in attributes if a.as_double() is not None]
    assert ints or doubles
    assert all(type(value) is int for value in ints)
    assert all(type(value) is float for value in doubles)

    fzk = read_model(FZK_LOD2)
    wall = features(fzk, WallSurface)[0]
    lifespan = ["creation_date", "termination_date", "valid_from", "valid_to"]
    assert [getattr(wall, name)() for name in lifespan] == [None] * len(lifespan)

    junction = read_model(ASAM_JUNCTION)
    road = features(junction, Road)[0]
    assert [getattr(road, name)() for name in SPACE_GEOMETRY] == [None] * len(SPACE_GEOMETRY)

    tum = read_model(TUM)
    assert next(iter(features(tum, Building)[0].external_references())).relation_type() is None
