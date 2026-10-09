"""Geometry types: DirectPosition, Envelope, LinearRing, Polygon, Solid and MultiSurface.

Ported from the former PyO3 bindings' `test_geometry.py`. Not ported (not in the Diplomat
bindings): `DirectPosition.coords`, `repr`. `triangulate()` returns a `Triangulation`; the former
`TriangulatedSurface` is its `surface()`. A polygon's `exterior()` is an `AbstractRingKind`; the former
`LinearRing` is `LinearRing.try_from(exterior)`.
"""

import pytest

from conftest import boundaries_of, polygons, unwrap
from ecitygml import (
    AbstractRingKind,
    Building,
    DirectPosition,
    Envelope,
    LinearRing,
    Polygon,
    Solid,
    Triangle,
    TriangulatedSurface,
    WallSurface,
)


class TestDirectPosition:
    def test_x_y_z_values(self, fzk_lod1_solid: Solid) -> None:
        point = next(iter(fzk_lod1_solid.points()))
        assert point.x() == pytest.approx(457842.0)
        assert point.y() == pytest.approx(5439083.0)
        assert point.z() == pytest.approx(111.8)

    def test_points_are_direct_positions(self, fzk_lod1_solid: Solid) -> None:
        assert all(isinstance(p, DirectPosition) for p in fzk_lod1_solid.points())


def envelope(building: Building) -> Envelope:
    return building.bounded_by().envelope()


class TestEnvelope:
    def test_size_x(self, fzk_lod1_building: Building) -> None:
        assert envelope(fzk_lod1_building).size_x() == pytest.approx(12.0)

    def test_size_y(self, fzk_lod1_building: Building) -> None:
        assert envelope(fzk_lod1_building).size_y() == pytest.approx(10.0)

    def test_size_z(self, fzk_lod1_building: Building) -> None:
        assert envelope(fzk_lod1_building).size_z() == pytest.approx(6.5, abs=0.1)

    def test_lower_corner(self, fzk_lod1_building: Building) -> None:
        corner = envelope(fzk_lod1_building).lower_corner()
        assert (corner.x(), corner.y(), corner.z()) == pytest.approx((457842.0, 5439083.0, 111.8))

    def test_upper_corner_x(self, fzk_lod1_building: Building) -> None:
        assert envelope(fzk_lod1_building).upper_corner().x() == pytest.approx(457854.0)

    def test_volume_positive(self, fzk_lod1_building: Building) -> None:
        assert envelope(fzk_lod1_building).volume() > 0

    def test_contains_returns_bool(self, fzk_lod1_building: Building) -> None:
        # Archived with the first exterior point of the LoD1 solid's first polygon.
        point = next(iter(unwrap(fzk_lod1_building.lod1_solid()).points()))
        assert isinstance(envelope(fzk_lod1_building).contains(point), bool)


def exterior(solid: Solid) -> LinearRing:
    """The exterior ring of the solid's first polygon."""
    return LinearRing.try_from(polygons(solid)[0].exterior())


class TestLinearRing:
    def test_points_are_direct_positions(self, fzk_lod1_solid: Solid) -> None:
        ring = exterior(fzk_lod1_solid)
        assert isinstance(ring, LinearRing)
        for point in ring.points():
            assert isinstance(point, DirectPosition)

    def test_point_count(self, fzk_lod1_solid: Solid) -> None:
        assert len(list(exterior(fzk_lod1_solid).points())) == 4


class TestPolygon:
    def test_exterior_is_linear_ring(self, fzk_lod1_solid: Solid) -> None:
        ring = polygons(fzk_lod1_solid)[0].exterior()
        assert isinstance(ring, AbstractRingKind)
        assert isinstance(LinearRing.try_from(ring), LinearRing)

    def test_no_interior_rings(self, fzk_lod1_solid: Solid) -> None:
        assert list(polygons(fzk_lod1_solid)[0].interior()) == []

    def test_compute_envelope_of_solid_polygon(self, fzk_lod1_solid: Solid) -> None:
        assert isinstance(polygons(fzk_lod1_solid)[0].compute_envelope(), Envelope)

    def test_compute_envelope_returns_envelope(self, fzk_lod2_building: Building) -> None:
        # Archived on a polygon of the LoD1 solid, whose polygons need `Shell`.
        wall = boundaries_of(fzk_lod2_building, WallSurface)[0]
        assert isinstance(polygons(unwrap(wall.lod2_multi_surface()))[0].compute_envelope(), Envelope)


class TestSolid:
    def test_polygon_count(self, fzk_lod1_solid: Solid) -> None:
        assert len(polygons(fzk_lod1_solid)) == 6

    def test_polygons_are_polygon_instances(self, fzk_lod1_solid: Solid) -> None:
        for polygon in polygons(fzk_lod1_solid):
            assert isinstance(polygon, Polygon)

    def test_triangulate_returns_triangulated_surface(self, fzk_lod1_solid: Solid) -> None:
        assert isinstance(fzk_lod1_solid.triangulate().surface(), TriangulatedSurface)

    def test_triangulate_count(self, fzk_lod1_solid: Solid) -> None:
        assert len(list(fzk_lod1_solid.triangulate().surface().triangles())) == 12

    def test_point_count(self, fzk_lod1_solid: Solid) -> None:
        # Archived as 6 polygons with 4 exterior points each.
        assert len(list(fzk_lod1_solid.points())) == 24

    def test_compute_envelope_returns_envelope(self, fzk_lod1_solid: Solid) -> None:
        assert isinstance(fzk_lod1_solid.compute_envelope(), Envelope)


class TestTriangulatedSurface:
    def test_triangles_are_triangle_instances(self, fzk_lod1_solid: Solid) -> None:
        triangulation = fzk_lod1_solid.triangulate()
        for triangle in triangulation.surface().triangles():
            assert isinstance(triangle, Triangle)

    def test_compute_envelope_returns_envelope(self, fzk_lod1_solid: Solid) -> None:
        triangulation = fzk_lod1_solid.triangulate()
        assert isinstance(triangulation.surface().compute_envelope(), Envelope)

    def test_triangle_vertices_are_direct_positions(self, fzk_lod1_solid: Solid) -> None:
        triangulation = fzk_lod1_solid.triangulate()
        triangle = next(iter(triangulation.surface().triangles()))
        assert isinstance(triangle.a(), DirectPosition)
        assert isinstance(triangle.b(), DirectPosition)
        assert isinstance(triangle.c(), DirectPosition)


class TestMultiSurface:
    def test_polygons_are_polygon_instances(self, fzk_lod2_building: Building) -> None:
        wall = boundaries_of(fzk_lod2_building, WallSurface)[0]
        for polygon in polygons(unwrap(wall.lod2_multi_surface())):
            assert isinstance(polygon, Polygon)

    def test_triangulate_returns_triangulated_surface(self, fzk_lod2_building: Building) -> None:
        wall = boundaries_of(fzk_lod2_building, WallSurface)[0]
        triangulation = unwrap(wall.lod2_multi_surface()).triangulate()
        assert isinstance(triangulation.surface(), TriangulatedSurface)

    def test_compute_envelope_returns_envelope(self, fzk_lod2_building: Building) -> None:
        wall = boundaries_of(fzk_lod2_building, WallSurface)[0]
        assert isinstance(unwrap(wall.lod2_multi_surface()).compute_envelope(), Envelope)
