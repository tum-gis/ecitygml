"""Every class exposes the getters of its abstract CityGML types.

Ported from the former PyO3 bindings' `test_abstract_types.py`, for the classes and getters the
Diplomat bindings have, plus `PlantCover`. Not ported (not in the Diplomat bindings):
`feature_type` on concrete classes (only feature refs and kinds have it).
"""

from typing import Any

import pytest

import ecitygml
from conftest import ASAM_JUNCTION, ASAM_ROAD, FZK_LOD2, FZK_LOD3, TUM, features_of, read_model, unwrap
from ecitygml import (
    AuxiliaryTrafficArea,
    AuxiliaryTrafficSpace,
    Bridge,
    BridgePart,
    Building,
    BuildingUnit,
    CityFurniture,
    DoorSurface,
    FeatureType,
    GroundSurface,
    Intersection,
    PlantCover,
    ReliefFeature,
    Road,
    RoofSurface,
    Section,
    SolitaryVegetationObject,
    Storey,
    TinRelief,
    TrafficArea,
    TrafficSpace,
    Tunnel,
    TunnelPart,
    WallSurface,
    WindowSurface,
)

ABSTRACT_FEATURE = ["id", "bounded_by"]
ABSTRACT_FEATURE_WITH_LIFESPAN = ["creation_date", "termination_date", "valid_from", "valid_to"]
ABSTRACT_CITY_OBJECT = [
    "relative_to_terrain",
    "relative_to_water",
    "external_references",
    "generic_attributes",
    "related_to",
]
ABSTRACT_PHYSICAL_SPACE = [
    "lod1_terrain_intersection_curve",
    "lod2_terrain_intersection_curve",
    "lod3_terrain_intersection_curve",
]
ABSTRACT_CONSTRUCTION = ["date_of_construction", "date_of_demolition", "heights", "occupancies"]
ABSTRACT_BUILDING = [
    "class_",
    "functions",
    "usages",
    "roof_type",
    "storeys_above_ground",
    "storeys_below_ground",
    "building_subdivisions",
]
ABSTRACT_BUILDING_SUBDIVISION = ["class_", "functions", "usages"]
ABSTRACT_BRIDGE = ["class_", "functions", "usages", "is_movable"]
ABSTRACT_TUNNEL = ["class_", "functions", "usages"]
ABSTRACT_TRANSPORTATION_SPACE = [
    "traffic_direction",
    "occupancies",
    "traffic_spaces",
    "auxiliary_traffic_spaces",
]
ABSTRACT_SPACE = [
    "lod1_solid",
    "lod2_solid",
    "lod3_solid",
    "lod0_multi_surface",
    "lod2_multi_surface",
    "lod3_multi_surface",
    "lod0_multi_curve",
    "lod2_multi_curve",
    "lod3_multi_curve",
]
ABSTRACT_OCCUPIED_SPACE = [
    "lod1_implicit_representation",
    "lod2_implicit_representation",
    "lod3_implicit_representation",
]
ABSTRACT_THEMATIC_SURFACE = [
    "lod0_multi_curve",
    "lod0_multi_surface",
    "lod1_multi_surface",
    "lod2_multi_surface",
    "lod3_multi_surface",
]

SPACES = [
    Bridge,
    BridgePart,
    Tunnel,
    TunnelPart,
    Building,
    CityFurniture,
    SolitaryVegetationObject,
    PlantCover,
    Road,
    Section,
    Intersection,
    TrafficSpace,
    AuxiliaryTrafficSpace,
]
CONSTRUCTIONS = [Building, Bridge, BridgePart, Tunnel, TunnelPart]
OCCUPIED_SPACES = CONSTRUCTIONS + [CityFurniture, SolitaryVegetationObject, PlantCover]
UNOCCUPIED_SPACES = [Road, Section, Intersection, TrafficSpace, AuxiliaryTrafficSpace]
THEMATIC_SURFACES = [
    WallSurface,
    RoofSurface,
    GroundSurface,
    DoorSurface,
    WindowSurface,
    TrafficArea,
    AuxiliaryTrafficArea,
]
LOGICAL_SPACES = [Storey, BuildingUnit]
FEATURES = SPACES + LOGICAL_SPACES + THEMATIC_SURFACES + [ReliefFeature, TinRelief]


def missing(cls: type, names: list[str]) -> list[str]:
    return [name for name in names if not hasattr(cls, name)]


@pytest.mark.parametrize("cls", FEATURES, ids=lambda c: c.__name__)
def test_features_expose_abstract_feature_getters(cls: type) -> None:
    assert missing(cls, ABSTRACT_FEATURE) == []


@pytest.mark.parametrize("cls", FEATURES, ids=lambda c: c.__name__)
def test_features_expose_abstract_feature_with_lifespan_getters(cls: type) -> None:
    assert missing(cls, ABSTRACT_FEATURE_WITH_LIFESPAN) == []


@pytest.mark.parametrize("cls", FEATURES, ids=lambda c: c.__name__)
def test_features_expose_abstract_city_object_getters(cls: type) -> None:
    assert missing(cls, ABSTRACT_CITY_OBJECT) == []


@pytest.mark.parametrize("cls", SPACES, ids=lambda c: c.__name__)
def test_spaces_expose_abstract_space_getters(cls: type) -> None:
    assert missing(cls, ABSTRACT_SPACE) == []


@pytest.mark.parametrize("cls", SPACES, ids=lambda c: c.__name__)
def test_spaces_expose_abstract_physical_space_getters(cls: type) -> None:
    assert missing(cls, ABSTRACT_PHYSICAL_SPACE) == []


@pytest.mark.parametrize("cls", OCCUPIED_SPACES, ids=lambda c: c.__name__)
def test_occupied_spaces_expose_abstract_occupied_space_getters(cls: type) -> None:
    assert missing(cls, ABSTRACT_OCCUPIED_SPACE) == []


@pytest.mark.parametrize("cls", CONSTRUCTIONS, ids=lambda c: c.__name__)
def test_constructions_expose_abstract_construction_getters(cls: type) -> None:
    assert missing(cls, ABSTRACT_CONSTRUCTION) == []


def test_building_exposes_abstract_building_getters() -> None:
    assert missing(Building, ABSTRACT_BUILDING) == []


@pytest.mark.parametrize("cls", LOGICAL_SPACES, ids=lambda c: c.__name__)
def test_logical_spaces_expose_space_getters(cls: type) -> None:
    assert missing(cls, ABSTRACT_SPACE + ABSTRACT_BUILDING_SUBDIVISION) == []


@pytest.mark.parametrize("cls", LOGICAL_SPACES, ids=lambda c: c.__name__)
def test_logical_spaces_are_not_physical(cls: type) -> None:
    assert not any(hasattr(cls, name) for name in ABSTRACT_PHYSICAL_SPACE)


@pytest.mark.parametrize("cls", [CityFurniture, SolitaryVegetationObject, PlantCover], ids=lambda c: c.__name__)
def test_other_occupied_spaces_lack_construction_getters(cls: type) -> None:
    assert not any(hasattr(cls, name) for name in ABSTRACT_CONSTRUCTION)


@pytest.mark.parametrize("cls", [Bridge, BridgePart], ids=lambda c: c.__name__)
def test_bridges_expose_abstract_bridge_getters(cls: type) -> None:
    assert missing(cls, ABSTRACT_BRIDGE) == []


@pytest.mark.parametrize("cls", [Tunnel, TunnelPart], ids=lambda c: c.__name__)
def test_tunnels_expose_abstract_tunnel_getters(cls: type) -> None:
    assert missing(cls, ABSTRACT_TUNNEL) == []


def test_tunnels_lack_bridge_only_getters() -> None:
    assert not hasattr(Tunnel, "is_movable") and not hasattr(TunnelPart, "is_movable")


def test_bridges_lack_building_only_getters() -> None:
    assert not hasattr(Bridge, "roof_type") and not hasattr(Bridge, "storeys_above_ground")


@pytest.mark.parametrize("cls", [Road, Section, Intersection], ids=lambda c: c.__name__)
def test_transportation_spaces_expose_abstract_transportation_space_getters(cls: type) -> None:
    assert missing(cls, ABSTRACT_TRANSPORTATION_SPACE) == []


@pytest.mark.parametrize("cls", [TrafficSpace, AuxiliaryTrafficSpace], ids=lambda c: c.__name__)
def test_traffic_spaces_are_not_transportation_spaces(cls: type) -> None:
    assert not hasattr(cls, "traffic_spaces") and not hasattr(cls, "auxiliary_traffic_spaces")


@pytest.mark.parametrize("cls", UNOCCUPIED_SPACES, ids=lambda c: c.__name__)
def test_unoccupied_spaces_lack_implicit_representations(cls: type) -> None:
    assert not any(hasattr(cls, name) for name in ABSTRACT_OCCUPIED_SPACE)


@pytest.mark.parametrize("cls", THEMATIC_SURFACES, ids=lambda c: c.__name__)
def test_thematic_surfaces_expose_thematic_surface_getters(cls: type) -> None:
    assert missing(cls, ABSTRACT_THEMATIC_SURFACE) == []


@pytest.mark.parametrize("path", [FZK_LOD3, TUM, ASAM_ROAD], ids=["fzk", "tum", "asam_road"])
def test_feature_type_matches_class(path: Any) -> None:
    # Archived as `feature.feature_type == FeatureType.<class name>`: here, the class named after
    # each feature's type accepts it. `iter_features()` also yields the city model, as in Rust.
    model = read_model(path)
    for feature in model.iter_features():
        name = str(feature.feature_type()).removeprefix("FeatureType.")
        if feature.feature_type() == FeatureType.CityModel:
            continue
        assert getattr(ecitygml, name).try_from(feature) is not None, name


@pytest.mark.parametrize("cls", [TrafficSpace, AuxiliaryTrafficSpace])
def test_traffic_space_lod2_solid(cls: Any) -> None:
    model = read_model(ASAM_ROAD)
    spaces = features_of(model, cls)
    assert len(spaces) == 2
    for space in spaces:
        assert unwrap(space.lod2_solid()).compute_envelope() is not None


def test_absent_geometry_is_none() -> None:
    model = read_model(ASAM_JUNCTION)
    road = features_of(model, Road)[0]
    assert all(getattr(road, name)() is None for name in ABSTRACT_SPACE)


def creation(building: Building) -> tuple[int, int, int, int, int]:
    date_time = building.creation_date()
    return (date_time.year(), date_time.month(), date_time.day(), date_time.hour(), date_time.offset_seconds())


class TestLifespan:
    @pytest.mark.parametrize(
        ("path", "expected"),
        [(FZK_LOD2, (2017, 1, 23)), (TUM, (2025, 1, 2))],
        ids=["fzk", "tum"],
    )
    def test_creation_date(self, path: Any, expected: tuple[int, int, int]) -> None:
        model = read_model(path)
        building = features_of(model, Building)[0]
        # Midnight at UTC+1.
        assert creation(building) == (*expected, 0, 3600)

    def test_creation_date_is_timezone_aware(self, fzk_lod2_building: Building) -> None:
        assert fzk_lod2_building.creation_date().offset_seconds() == 3600

    def test_absent_dates_are_none(self, fzk_lod2_building: Building) -> None:
        assert fzk_lod2_building.termination_date() is None
        assert fzk_lod2_building.valid_from() is None
        assert fzk_lod2_building.valid_to() is None

    def test_thematic_surface_without_dates(self, fzk_lod2_model: Any) -> None:
        wall = features_of(fzk_lod2_model, WallSurface)[0]
        assert all(getattr(wall, name)() is None for name in ABSTRACT_FEATURE_WITH_LIFESPAN)
