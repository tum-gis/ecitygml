"""AbstractConstructionSurface, AbstractFillingSurface, AbstractReliefComponent and
AbstractVegetationObject, the abstract levels between the bound classes and their supertypes.

Ported from the former PyO3 bindings' `test_skipped_abstract_levels.py`. Filling surfaces are
`AbstractFillingSurfaceKind`s and relief components `AbstractReliefComponentKind`s, told apart by
`feature_type()` instead of `isinstance`; the concrete classes come from `try_from` on the features.
"""

from typing import Any

import pytest

from conftest import FZK_LOD2, FZK_LOD3, boundaries_of, features_of, fillings_of, objects, read_model
from ecitygml import (
    AbstractFillingSurfaceKind,
    Building,
    DoorSurface,
    FeatureType,
    GmlWriter,
    GroundSurface,
    LevelOfDetail,
    ReliefFeature,
    RoofSurface,
    SolitaryVegetationObject,
    TinRelief,
    WallSurface,
    WindowSurface,
)

ROOF_ID = "GML_875d470b-32b4-4985-a4c8-0f02caa342a2"
ROOF_WINDOW = """
          <con:fillingSurface>
            <con:WindowSurface gml:id="roof_window_1"/>
          </con:fillingSurface>"""


@pytest.fixture(scope="module")
def roof_window_model(tmp_path_factory: pytest.TempPathFactory) -> Any:
    """FZK LoD3 with a window added to a roof surface, after the roof's geometry."""
    text = FZK_LOD3.read_text()
    roof_start = text.index(f'<con:RoofSurface gml:id="{ROOF_ID}">')
    insert_at = text.index("</lod3MultiSurface>", roof_start) + len("</lod3MultiSurface>")
    path = tmp_path_factory.mktemp("filling") / "fzk_roof_window.gml"
    path.write_text(text[:insert_at] + ROOF_WINDOW + text[insert_at:])
    return read_model(path)


def roof(model: Any) -> RoofSurface:
    building = features_of(model, Building)[0]
    return next(r for r in boundaries_of(building, RoofSurface) if r.id().as_str() == ROOF_ID)


def ids(surfaces: list[Any]) -> list[str]:
    return [s.id().as_str() for s in surfaces]


class TestConstructionSurface:
    @pytest.mark.parametrize("cls", [WallSurface, RoofSurface, GroundSurface])
    def test_filling_surface_getters(self, cls: type) -> None:
        assert hasattr(cls, "filling_surfaces")
        # Rust has no door/window-specific accessors; filter `filling_surfaces` instead.
        assert not hasattr(cls, "door_surfaces") and not hasattr(cls, "window_surfaces")

    def test_wall_filling_surfaces(self, fzk_lod3_building: Building) -> None:
        walls = boundaries_of(fzk_lod3_building, WallSurface)
        fillings = [f for w in walls for f in objects(w.filling_surfaces())]
        assert sum(f.feature_type() == FeatureType.DoorSurface for f in fillings) == 2
        assert sum(f.feature_type() == FeatureType.WindowSurface for f in fillings) == 11
        assert all(isinstance(f, AbstractFillingSurfaceKind) for f in fillings)

    def test_filling_surfaces_split_by_kind(self, fzk_lod3_model: Any, fzk_lod3_building: Building) -> None:
        # Archived: filtering a wall's fillings by class equals filtering them by kind. Here the
        # doors and windows found through the walls equal those of `iter_features()`.
        walls = boundaries_of(fzk_lod3_building, WallSurface)
        doors = [d for w in walls for d in fillings_of(w, FeatureType.DoorSurface)]
        windows = [w for wall in walls for w in fillings_of(wall, FeatureType.WindowSurface)]
        assert ids(doors) == ids(features_of(fzk_lod3_model, DoorSurface))
        assert ids(windows) == ids(features_of(fzk_lod3_model, WindowSurface))

    def test_roof_window(self, roof_window_model: Any) -> None:
        roof_surface = roof(roof_window_model)
        assert ids(fillings_of(roof_surface, FeatureType.WindowSurface)) == ["roof_window_1"]
        assert fillings_of(roof_surface, FeatureType.DoorSurface) == []
        assert [f.feature_type() for f in objects(roof_surface.filling_surfaces())] == [FeatureType.WindowSurface]

    def test_roof_window_round_trip(self, roof_window_model: Any, tmp_path_factory: pytest.TempPathFactory) -> None:
        path = tmp_path_factory.mktemp("filling_written") / "written.gml"
        GmlWriter.from_path(str(path)).finish(roof_window_model)
        written = read_model(path)
        assert ids(fillings_of(roof(written), FeatureType.WindowSurface)) == ["roof_window_1"]

    def test_without_fillings(self, fzk_lod2_model: Any) -> None:
        roof_surface = features_of(fzk_lod2_model, RoofSurface)[0]
        assert list(roof_surface.filling_surfaces()) == []


class TestFillingSurface:
    @pytest.mark.parametrize("cls", [DoorSurface, WindowSurface, AbstractFillingSurfaceKind])
    def test_has_thematic_surface_getters(self, cls: type) -> None:
        assert hasattr(cls, "lod3_multi_surface") and hasattr(cls, "generic_attributes")

    @pytest.mark.parametrize("cls", [DoorSurface, WindowSurface, AbstractFillingSurfaceKind])
    def test_cannot_hold_filling_surfaces(self, cls: type) -> None:
        assert not hasattr(cls, "filling_surfaces")


RELIEF_MEMBER = """<cityObjectMember>
    <dem:ReliefFeature gml:id="relief_1">
      <dem:lod>2</dem:lod>
      <dem:reliefComponent>
        <dem:TINRelief gml:id="tin_1">
          <dem:lod>2</dem:lod>
          <dem:tin>
            <gml:TriangulatedSurface>
              <gml:patches>
                <gml:Triangle>
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:posList>0 0 0 1 0 0 0 1 0 0 0 0</gml:posList>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Triangle>
              </gml:patches>
            </gml:TriangulatedSurface>
          </dem:tin>
        </dem:TINRelief>
      </dem:reliefComponent>
    </dem:ReliefFeature>
  </cityObjectMember>
</CityModel>
"""


@pytest.fixture(scope="module")
def relief_model(tmp_path_factory: pytest.TempPathFactory) -> Any:
    text = FZK_LOD2.read_text()
    path = tmp_path_factory.mktemp("relief") / "relief.gml"
    path.write_text(text[: text.index("<cityObjectMember>")] + RELIEF_MEMBER)
    return read_model(path)


class TestReliefComponent:
    def test_tin_relief_lod(self, relief_model: Any) -> None:
        tin = features_of(relief_model, TinRelief)[0]
        assert tin.lod() == LevelOfDetail.Two
        surface = tin.tin().object()
        assert surface is not None and len(list(surface.triangles())) == 1

    def test_relief_feature_lod(self, relief_model: Any) -> None:
        relief = features_of(relief_model, ReliefFeature)[0]
        assert relief.lod() == LevelOfDetail.Two
        components = objects(relief.relief_components())
        assert [c.id().as_str() for c in components] == ["tin_1"]
        assert [c.feature_type() for c in components] == [FeatureType.TinRelief]
        assert components[0].lod() == LevelOfDetail.Two


def test_vegetation_object_level_exposes_occupied_space_getters() -> None:
    for name in ["lod1_implicit_representation", "lod1_terrain_intersection_curve", "lod1_solid"]:
        assert hasattr(SolitaryVegetationObject, name)
