"""Fixtures and helpers for the tests ported from the former PyO3 bindings to the Diplomat
bindings.

The former API exposed properties, Python class hierarchies and filters such as
`model.iter_features(Building)`; the Diplomat bindings mirror the Rust API instead, so the helpers
below translate: `features_of(model, Building)` is `Building.try_from` over `iter_features()`,
`boundaries_of(space, WallSurface)` converts boundaries with
`AbstractFeatureKindRef.from_space_boundary`, `city_objects_of(model, Road)` converts
`iter_city_objects()` with `AbstractFeatureKindRef.from_city_object`, and properties are unwrapped
with `.object()`.

Objects obtained through `try_from` don't keep their city model alive, so every object here is
derived from a module-scoped model fixture, which pytest keeps referenced.
"""

from collections.abc import Iterable
from pathlib import Path
from typing import Any

import pytest

from ecitygml import (
    AbstractFeatureKindRef,
    AbstractRingKind,
    Building,
    CityModel,
    CompositeSurface,
    FeatureType,
    GmlReader,
    LinearRing,
    LineString,
    MultiSurface,
    Polygon,
    Road,
    Shell,
    Solid,
)

FIXTURES = Path(__file__).parents[5] / "tests" / "fixtures"

FZK_LOD1 = FIXTURES / "FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml"
FZK_LOD2 = FIXTURES / "FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml"
FZK_LOD3 = FIXTURES / "FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml"
TUM = FIXTURES / "TUM-Main-Entrance.gml"
ASAM_JUNCTION = FIXTURES / "ASAM-Ex_Bidirectional_Junction.gml"
ASAM_ROAD = FIXTURES / "ASAM-UC_RoadShape.gml"


def read_model(path: Path | str) -> CityModel:
    """`GmlReader::from_path(path)?.finish()`, as in Rust."""
    return GmlReader.from_path(str(path)).finish()


def read_injected(tmp_path: Path, fixture: Path, anchor: str, replacement: str) -> CityModel:
    """Reads a copy of `fixture` with its single `anchor` replaced; keep the model referenced."""
    text = fixture.read_text()
    assert text.count(anchor) == 1
    path = tmp_path / fixture.name
    path.write_text(text.replace(anchor, replacement))
    return read_model(path)


def features_of(model: CityModel, cls: Any) -> list[Any]:
    """The features of `model` that `cls.try_from` accepts, in document order."""
    return [x for f in model.iter_features() if (x := cls.try_from(f)) is not None]


def city_objects_of(model: CityModel, cls: Any) -> list[Any]:
    """The city objects of `model` that `cls.try_from` accepts, in document order."""
    return [
        x
        for city_object in model.iter_city_objects()
        if (x := cls.try_from(AbstractFeatureKindRef.from_city_object(city_object))) is not None
    ]


def objects(properties: Iterable[Any]) -> list[Any]:
    """The objects of properties, all of which must be present."""
    result = [p.object() for p in properties]
    assert all(o is not None for o in result)
    return result


def boundaries_of(space: Any, cls: Any) -> list[Any]:
    """The boundaries of `space` that `cls.try_from` accepts, e.g. its wall surfaces."""
    return [
        x
        for boundary in objects(space.boundaries())
        if (x := cls.try_from(AbstractFeatureKindRef.from_space_boundary(boundary))) is not None
    ]


def fillings_of(surface: Any, feature_type: FeatureType) -> list[Any]:
    """The filling surfaces (doors or windows) of a construction surface with that feature type."""
    return [f for f in objects(surface.filling_surfaces()) if f.feature_type() == feature_type]


def polygons(geometry: Solid | Shell | MultiSurface | CompositeSurface) -> list[Polygon]:
    """All polygons of a surface geometry, flattening shells and composite surfaces."""
    if isinstance(geometry, Solid):
        exterior = geometry.exterior()
        return [] if exterior is None else polygons(exterior)
    members = geometry.members() if isinstance(geometry, Shell) else geometry.surface_member()
    result: list[Polygon] = []
    for surface in objects(members):
        if (polygon := Polygon.try_from(surface)) is not None:
            result.append(polygon)
        elif (nested := CompositeSurface.try_from(surface) or Shell.try_from(surface)) is not None:
            result.extend(polygons(nested))
    return result


def curve_points(multi_curve: Any) -> list[list[Any]]:
    """The points of each line string and linear ring member of a multi curve."""
    result = []
    for curve in objects(multi_curve.curve_member()):
        if (line := LineString.try_from(curve)) is not None:
            result.append(list(line.points()))
        elif (ring := AbstractRingKind.try_from(curve)) is not None:
            if (linear := LinearRing.try_from(ring)) is not None:
                result.append(list(linear.points()))
    return result


def unwrap(prop: Any) -> Any:
    """The object of a property that must be present."""
    assert prop is not None and prop.object() is not None
    return prop.object()


@pytest.fixture(scope="module")
def fzk_lod1_model() -> CityModel:
    return read_model(FZK_LOD1)


@pytest.fixture(scope="module")
def fzk_lod2_model() -> CityModel:
    return read_model(FZK_LOD2)


@pytest.fixture(scope="module")
def fzk_lod3_model() -> CityModel:
    return read_model(FZK_LOD3)


@pytest.fixture(scope="module")
def tum_model() -> CityModel:
    return read_model(TUM)


@pytest.fixture(scope="module")
def asam_junction_model() -> CityModel:
    return read_model(ASAM_JUNCTION)


@pytest.fixture(scope="module")
def asam_road_model() -> CityModel:
    return read_model(ASAM_ROAD)


@pytest.fixture(scope="module")
def fzk_lod1_building(fzk_lod1_model: CityModel) -> Building:
    return features_of(fzk_lod1_model, Building)[0]


@pytest.fixture(scope="module")
def fzk_lod2_building(fzk_lod2_model: CityModel) -> Building:
    return features_of(fzk_lod2_model, Building)[0]


@pytest.fixture(scope="module")
def fzk_lod3_building(fzk_lod3_model: CityModel) -> Building:
    return features_of(fzk_lod3_model, Building)[0]


@pytest.fixture(scope="module")
def tum_building(tum_model: CityModel) -> Building:
    return features_of(tum_model, Building)[0]


@pytest.fixture(scope="module")
def asam_junction_road(asam_junction_model: CityModel) -> Road:
    return features_of(asam_junction_model, Road)[0]


@pytest.fixture(scope="module")
def asam_road_shape_road(asam_road_model: CityModel) -> Road:
    return features_of(asam_road_model, Road)[0]


@pytest.fixture(scope="module")
def asam_section(asam_junction_road: Road) -> Any:
    return objects(asam_junction_road.sections())[0]


@pytest.fixture(scope="module")
def asam_road_section(asam_road_shape_road: Road) -> Any:
    return objects(asam_road_shape_road.sections())[0]


@pytest.fixture(scope="module")
def fzk_lod1_solid(fzk_lod1_building: Building) -> Any:
    return unwrap(fzk_lod1_building.lod1_solid())
