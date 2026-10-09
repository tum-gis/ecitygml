"""Building and its thematic surfaces across LoD1, LoD2, LoD3 and the TUM Main Entrance dataset.

Ported from the former PyO3 bindings' `test_building.py`. Not ported (not in the Diplomat
bindings): `repr`. `triangulate()` returns a `Triangulation`, whose `surface()` has the triangles.
"""

from typing import Any

import pytest

from conftest import boundaries_of, features_of, fillings_of, polygons, unwrap
from ecitygml import (
    Building,
    DoorSurface,
    FeatureType,
    GroundSurface,
    MultiSurface,
    RoofSurface,
    Solid,
    WallSurface,
    WindowSurface,
)


class TestBuildingLoD1:
    def test_id(self, fzk_lod1_building: Building) -> None:
        assert fzk_lod1_building.id().as_str() == "UUID_d281adfc-4901-0f52-540b-4cc1a9325f82"

    def test_feature_type(self, fzk_lod1_model: Any) -> None:
        types = [f.feature_type() for f in fzk_lod1_model.iter_features() if Building.try_from(f)]
        assert types == [FeatureType.Building]

    def test_storeys_above_ground(self, fzk_lod1_building: Building) -> None:
        assert fzk_lod1_building.storeys_above_ground() == 2

    def test_storeys_below_ground(self, fzk_lod1_building: Building) -> None:
        assert fzk_lod1_building.storeys_below_ground() == 0

    def test_bounded_by_lower_corner(self, fzk_lod1_building: Building) -> None:
        corner = fzk_lod1_building.bounded_by().envelope().lower_corner()
        assert (corner.x(), corner.y(), corner.z()) == pytest.approx((457842.0, 5439083.0, 111.8))

    def test_lod1_solid_present(self, fzk_lod1_building: Building) -> None:
        assert isinstance(unwrap(fzk_lod1_building.lod1_solid()), Solid)

    def test_lod2_solid_absent(self, fzk_lod1_building: Building) -> None:
        assert fzk_lod1_building.lod2_solid() is None

    def test_lod0_multi_surface_absent(self, fzk_lod1_building: Building) -> None:
        assert fzk_lod1_building.lod0_multi_surface() is None

    def test_no_thematic_surfaces(self, fzk_lod1_building: Building) -> None:
        assert boundaries_of(fzk_lod1_building, WallSurface) == []
        assert boundaries_of(fzk_lod1_building, RoofSurface) == []
        assert boundaries_of(fzk_lod1_building, GroundSurface) == []


class TestBuildingLoD2:
    def test_wall_surface_count(self, fzk_lod2_building: Building) -> None:
        assert len(boundaries_of(fzk_lod2_building, WallSurface)) == 4

    def test_roof_surface_count(self, fzk_lod2_building: Building) -> None:
        assert len(boundaries_of(fzk_lod2_building, RoofSurface)) == 2

    def test_ground_surface_count(self, fzk_lod2_building: Building) -> None:
        assert len(boundaries_of(fzk_lod2_building, GroundSurface)) == 1

    def test_lod1_solid_absent(self, fzk_lod2_building: Building) -> None:
        assert fzk_lod2_building.lod1_solid() is None

    def test_wall_surface_type(self, fzk_lod2_building: Building) -> None:
        assert isinstance(boundaries_of(fzk_lod2_building, WallSurface)[0], WallSurface)

    def test_roof_surface_type(self, fzk_lod2_building: Building) -> None:
        assert isinstance(boundaries_of(fzk_lod2_building, RoofSurface)[0], RoofSurface)

    def test_ground_surface_type(self, fzk_lod2_building: Building) -> None:
        assert isinstance(boundaries_of(fzk_lod2_building, GroundSurface)[0], GroundSurface)

    def test_wall_has_id(self, fzk_lod2_building: Building) -> None:
        assert boundaries_of(fzk_lod2_building, WallSurface)[0].id().as_str() != ""

    def test_wall_lod2_multi_surface(self, fzk_lod2_building: Building) -> None:
        wall = boundaries_of(fzk_lod2_building, WallSurface)[0]
        assert isinstance(unwrap(wall.lod2_multi_surface()), MultiSurface)

    def test_wall_lod2_polygon_count(self, fzk_lod2_building: Building) -> None:
        wall = boundaries_of(fzk_lod2_building, WallSurface)[0]
        assert len(polygons(unwrap(wall.lod2_multi_surface()))) == 1

    def test_wall_lod2_multi_surface_can_triangulate(self, fzk_lod2_building: Building) -> None:
        wall = boundaries_of(fzk_lod2_building, WallSurface)[0]
        triangulation = unwrap(wall.lod2_multi_surface()).triangulate()
        assert len(list(triangulation.surface().triangles())) > 0

    def test_wall_lod0_multi_surface_absent(self, fzk_lod2_building: Building) -> None:
        assert boundaries_of(fzk_lod2_building, WallSurface)[0].lod0_multi_surface() is None

    def test_ground_polygon_exterior_point_count(self, fzk_lod2_building: Building) -> None:
        # Archived: `exterior.points`; `points()` also has interior rings, which the ground lacks.
        ground = boundaries_of(fzk_lod2_building, GroundSurface)[0]
        assert len(list(polygons(unwrap(ground.lod2_multi_surface()))[0].points())) >= 4

    def test_wall_no_door_or_window_surfaces(self, fzk_lod2_building: Building) -> None:
        for wall in boundaries_of(fzk_lod2_building, WallSurface):
            assert fillings_of(wall, FeatureType.DoorSurface) == []
            assert fillings_of(wall, FeatureType.WindowSurface) == []

    def test_bounded_by_is_none(self, fzk_lod2_building: Building) -> None:
        assert fzk_lod2_building.bounded_by() is None


class TestBuildingLoD3:
    def test_wall_surface_count(self, fzk_lod3_building: Building) -> None:
        assert len(boundaries_of(fzk_lod3_building, WallSurface)) == 4

    def test_first_wall_door_count(self, fzk_lod3_building: Building) -> None:
        wall = boundaries_of(fzk_lod3_building, WallSurface)[0]
        assert len(fillings_of(wall, FeatureType.DoorSurface)) == 1

    def test_first_wall_window_count(self, fzk_lod3_building: Building) -> None:
        wall = boundaries_of(fzk_lod3_building, WallSurface)[0]
        assert len(fillings_of(wall, FeatureType.WindowSurface)) == 3

    def test_door_surface_type(self, fzk_lod3_model: Any) -> None:
        # Filling surfaces are AbstractFillingSurfaceKind; the concrete type comes from the features.
        assert all(isinstance(d, DoorSurface) for d in features_of(fzk_lod3_model, DoorSurface))

    def test_window_surface_type(self, fzk_lod3_model: Any) -> None:
        assert all(isinstance(w, WindowSurface) for w in features_of(fzk_lod3_model, WindowSurface))

    def test_door_has_id(self, fzk_lod3_building: Building) -> None:
        wall = boundaries_of(fzk_lod3_building, WallSurface)[0]
        assert fillings_of(wall, FeatureType.DoorSurface)[0].id().as_str() != ""

    def test_door_lod3_multi_surface(self, fzk_lod3_building: Building) -> None:
        wall = boundaries_of(fzk_lod3_building, WallSurface)[0]
        door = fillings_of(wall, FeatureType.DoorSurface)[0]
        assert isinstance(unwrap(door.lod3_multi_surface()), MultiSurface)

    def test_window_lod3_multi_surface(self, fzk_lod3_building: Building) -> None:
        wall = boundaries_of(fzk_lod3_building, WallSurface)[0]
        window = fillings_of(wall, FeatureType.WindowSurface)[0]
        assert isinstance(unwrap(window.lod3_multi_surface()), MultiSurface)

    def test_wall_lod3_multi_surface(self, fzk_lod3_building: Building) -> None:
        wall = boundaries_of(fzk_lod3_building, WallSurface)[0]
        assert isinstance(unwrap(wall.lod3_multi_surface()), MultiSurface)

    def test_total_door_count(self, fzk_lod3_building: Building) -> None:
        walls = boundaries_of(fzk_lod3_building, WallSurface)
        assert sum(len(fillings_of(w, FeatureType.DoorSurface)) for w in walls) == 2

    def test_total_window_count(self, fzk_lod3_building: Building) -> None:
        walls = boundaries_of(fzk_lod3_building, WallSurface)
        assert sum(len(fillings_of(w, FeatureType.WindowSurface)) for w in walls) == 11


class TestTumBuilding:
    def test_id(self, tum_building: Building) -> None:
        assert tum_building.id().as_str() == "DEBY_LOD2_4959457"

    def test_feature_type(self, tum_model: Any) -> None:
        types = [f.feature_type() for f in tum_model.iter_features() if Building.try_from(f)]
        assert types == [FeatureType.Building]

    def test_wall_surface_count(self, tum_building: Building) -> None:
        assert len(boundaries_of(tum_building, WallSurface)) == 14

    def test_roof_surface_count(self, tum_building: Building) -> None:
        assert len(boundaries_of(tum_building, RoofSurface)) == 2

    def test_ground_surface_count(self, tum_building: Building) -> None:
        assert len(boundaries_of(tum_building, GroundSurface)) == 1

    def test_bounded_by_is_none(self, tum_building: Building) -> None:
        assert tum_building.bounded_by() is None

    def test_wall_lod2_multi_surface(self, tum_building: Building) -> None:
        wall = boundaries_of(tum_building, WallSurface)[0]
        assert isinstance(unwrap(wall.lod2_multi_surface()), MultiSurface)
        assert len(polygons(unwrap(wall.lod2_multi_surface()))) >= 1

    def test_wall_can_triangulate(self, tum_building: Building) -> None:
        wall = boundaries_of(tum_building, WallSurface)[0]
        triangulation = unwrap(wall.lod2_multi_surface()).triangulate()
        assert len(list(triangulation.surface().triangles())) > 0
