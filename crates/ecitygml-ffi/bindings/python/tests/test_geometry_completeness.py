"""Geometry members are exposed as in the Rust model, never silently dropped.

Ported from the former PyO3 bindings' `test_geometry_completeness.py`, for what the Diplomat
bindings have: composite surfaces, surface patches, ring curve members, unresolved `xlink:href`
references (only `href()`), triangulation and volumes. Not ported (not in the Diplomat bindings):
resolving `xlink:href` references within a feature (the former bindings did, so e.g. the FZK LoD2
solid had a volume; here its members stay references). Differs from the former bindings: as in egml,
triangulation leaves out members that are only an `xlink:href` and lists members that fail (e.g. a
polygon without exterior) in `Triangulation.skipped()` instead of raising; skipped members aren't
warnings but entries there.
"""

from collections.abc import Callable
from pathlib import Path
from typing import Any

import pytest

from conftest import FZK_LOD2, boundaries_of, curve_points, features_of, polygons, read_model, unwrap
from ecitygml import (
    Building,
    CompositeSurface,
    ErrorKind,
    GmlWriter,
    LinearRing,
    LineString,
    MultiSurface,
    Polygon,
    PolygonPatch,
    Surface,
    Triangle,
    WallSurface,
)


def ring(z: float) -> str:
    return (
        "<gml:exterior><gml:LinearRing><gml:posList>"
        f"0 0 {z} 1 0 {z} 1 1 {z} 0 0 {z}"
        "</gml:posList></gml:LinearRing></gml:exterior>"
    )


def polygon(z: float) -> str:
    return f"<gml:Polygon>{ring(z)}</gml:Polygon>"


def member(geometry: str) -> str:
    return f"<gml:surfaceMember>{geometry}</gml:surfaceMember>"


UNRESOLVED_SURFACE = '<gml:surfaceMember xlink:href="#missing_polygon"/>'
# Four collinear vertices: earcut produces no triangles, which egml reports as a skipped member.
COLLINEAR = (
    "<gml:Polygon><gml:exterior><gml:LinearRing><gml:posList>"
    "0 0 9 1 0 9 2 0 9 3 0 9 0 0 9"
    "</gml:posList></gml:LinearRing></gml:exterior></gml:Polygon>"
)
LINE_STRING = "<gml:LineString><gml:posList>0 0 0 1 1 1</gml:posList></gml:LineString>"
LINEAR_RING = "<gml:LinearRing><gml:posList>0 0 0 1 0 0 1 1 0 0 0 0</gml:posList></gml:LinearRing>"


@pytest.fixture
def building_with(tmp_path: Path) -> Callable[..., Building]:
    """Returns a function building a model with one building holding the given geometry."""
    text = FZK_LOD2.read_text()
    header = text[: text.index("<cityObjectMember>")]
    models: list[Any] = []  # keeps the models alive for the test

    def make(surface_members: str = "", curve_members: str = "", shell_members: str = "") -> Building:
        body = ""
        if shell_members:
            body += (
                "<lod2Solid><gml:Solid><gml:exterior><gml:Shell>"
                f"{shell_members}</gml:Shell></gml:exterior></gml:Solid></lod2Solid>"
            )
        if surface_members:
            body += f"<lod2MultiSurface><gml:MultiSurface>{surface_members}</gml:MultiSurface></lod2MultiSurface>"
        if curve_members:
            body += f"<lod2MultiCurve><gml:MultiCurve>{curve_members}</gml:MultiCurve></lod2MultiCurve>"
        path = tmp_path / f"geometry_{len(models)}.gml"
        path.write_text(
            header
            + f'<cityObjectMember><bldg:Building gml:id="b">{body}</bldg:Building></cityObjectMember>'
            + "</CityModel>\n"
        )
        models.append(read_model(path))
        return features_of(models[-1], Building)[0]

    return make


COMPOSITE = f"<gml:CompositeSurface>{member(polygon(2))}{member(polygon(3))}</gml:CompositeSurface>"
SURFACE_WITH_PATCHES = (
    "<gml:Surface><gml:patches>"
    f"<gml:PolygonPatch>{ring(4)}</gml:PolygonPatch><gml:Triangle>{ring(5)}</gml:Triangle>"
    "</gml:patches></gml:Surface>"
)


def z_values(surface: MultiSurface) -> list[float]:
    return [next(iter(LinearRing.try_from(p.exterior()).points())).z() for p in polygons(surface)]


def surface_members(building: Building) -> list[Any]:
    return list(unwrap(building.lod2_multi_surface()).surface_member())


def curve_members(building: Building) -> list[Any]:
    return list(unwrap(building.lod2_multi_curve()).curve_member())


class TestPolygons:
    def test_composite_surface_members_are_flattened(self, building_with: Callable[..., Building]) -> None:
        building = building_with(member(polygon(1)) + member(COMPOSITE))
        assert z_values(unwrap(building.lod2_multi_surface())) == [1.0, 2.0, 3.0]

    def test_surface_patches(self, building_with: Callable[..., Building]) -> None:
        building = building_with(member(SURFACE_WITH_PATCHES))
        surface = Surface.try_from(surface_members(building)[0].object())
        assert isinstance(surface, Surface)
        first, second = surface.patches()
        patch, triangle = PolygonPatch.try_from(first), Triangle.try_from(second)
        assert isinstance(patch, PolygonPatch) and isinstance(triangle, Triangle)
        assert patch.exterior() is not None and next(iter(patch.exterior().points())).z() == 4.0
        assert triangle.a().z() == 5.0

    def test_unresolved_reference_is_href_only(self, building_with: Callable[..., Building]) -> None:
        inline, reference = surface_members(building_with(member(polygon(1)) + UNRESOLVED_SURFACE))
        assert inline.href() is None and Polygon.try_from(inline.object()) is not None
        assert reference.href().to_string() == "#missing_polygon"
        assert reference.object() is None

    def test_fzk_lod3_wall_composite_surfaces(self, fzk_lod3_building: Building) -> None:
        wall = boundaries_of(fzk_lod3_building, WallSurface)[0]
        surface = unwrap(wall.lod3_multi_surface())
        assert CompositeSurface.try_from(next(iter(surface.surface_member())).object()) is not None
        polys = polygons(surface)
        assert polys
        point = next(iter(LinearRing.try_from(polys[0].exterior()).points()))
        assert (point.x(), point.y(), point.z()) == (457842.0, 5439088.49240388, 115.913175911167)

    def test_inline_solid_unchanged(self, fzk_lod1_building: Building) -> None:
        assert len(polygons(unwrap(fzk_lod1_building.lod1_solid()))) == 6


class TestTriangulate:
    def test_composite_and_patches(self, building_with: Callable[..., Building]) -> None:
        building = building_with(member(COMPOSITE) + member(SURFACE_WITH_PATCHES))
        triangulation = unwrap(building.lod2_multi_surface()).triangulate()
        assert len(list(triangulation.surface().triangles())) == 4

    def test_skipped_member(self, building_with: Callable[..., Building]) -> None:
        # Archived as `test_skipped_member_warns` (a RuntimeWarning): here, an entry in `skipped()`.
        building = building_with(member(polygon(1)) + member(COLLINEAR))
        triangulation = unwrap(building.lod2_multi_surface()).triangulate()
        assert triangulation.has_skipped()
        assert len(list(triangulation.skipped())) == 1
        assert len(list(triangulation.surface().triangles())) == 1

    def test_nothing_skipped_when_complete(self, building_with: Callable[..., Building]) -> None:
        # Archived as `test_no_warning_when_complete`.
        triangulation = unwrap(building_with(member(polygon(1))).lod2_multi_surface()).triangulate()
        assert not triangulation.has_skipped()


class TestCurves:
    def test_ring_members_are_returned(self, building_with: Callable[..., Building]) -> None:
        building = building_with(
            member(polygon(1)),
            f"<gml:curveMember>{LINE_STRING}</gml:curveMember><gml:curveMember>{LINEAR_RING}</gml:curveMember>",
        )
        # egml stores rings without the repeated closing point, as for polygon rings
        assert [len(c) for c in curve_points(unwrap(building.lod2_multi_curve()))] == [2, 3]

    def test_unresolved_reference(self, building_with: Callable[..., Building]) -> None:
        building = building_with(
            member(polygon(1)),
            f'<gml:curveMember>{LINE_STRING}</gml:curveMember><gml:curveMember xlink:href="#missing_curve"/>',
        )
        line, reference = curve_members(building)
        assert LineString.try_from(line.object()) is not None
        assert reference.href().to_string() == "#missing_curve"
        assert reference.object() is None


class TestReferenceResolution:
    def test_reference_outside_feature_stays_unresolved(self, building_with: Callable[..., Building]) -> None:
        assert surface_members(building_with(member(polygon(1)) + UNRESOLVED_SURFACE))[1].object() is None

    def test_write_keeps_references(self, tmp_path: Path) -> None:
        model = read_model(FZK_LOD2)
        assert features_of(model, Building)[0].lod2_solid() is not None
        path = tmp_path / "written.gml"
        GmlWriter.from_path(str(path)).finish(model)
        text = path.read_text()
        assert text.count('xlink:href="#PolyID7350_878_759628_120742"') == 1
        assert text.count('gml:id="PolyID7350_878_759628_120742"') == 1


class TestVolume:
    def test_lod1_box_volume_matches_envelope(self, fzk_lod1_building: Building) -> None:
        solid = unwrap(fzk_lod1_building.lod1_solid())
        envelope = solid.compute_envelope()
        # The FZK LoD1 solid is an axis-aligned box, so its volume equals the envelope volume.
        assert solid.volume_3d() == pytest.approx(envelope.size_x() * envelope.size_y() * envelope.size_z())

    def test_unresolved_reference_raises(self, building_with: Callable[..., Building]) -> None:
        solid = unwrap(building_with(shell_members=member(polygon(1)) + UNRESOLVED_SURFACE).lod2_solid())
        with pytest.raises(Exception, match="missing_polygon") as raised:
            solid.volume_3d()
        assert raised.value.args[0].kind() == ErrorKind.UnresolvedReference
