"""The cases of crates/ecitygml/tests/api/geometry.md."""

from typing import Any

import pytest

from api.helpers import assert_error, fixture
from conftest import read_model
from ecitygml import (
    Building,
    CityModel,
    CompositeSurface,
    ErrorKind,
    GeometryType,
    GroundSurface,
    LinearRing,
    Polygon,
    PolygonPatch,
    SolitaryVegetationObject,
    Storey,
    Surface,
    TinRelief,
    TrafficSpace,
    Triangle,
)

FZK_LOD1 = fixture("fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml")
FZK_LOD2 = fixture("fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml")
TUM = fixture("tum-main-entrance/TUM-Main-Entrance.gml")
ASAM_ROAD_SHAPE = fixture("asam-opendrive/ASAM-UC_RoadShape.gml")
RAILWAY = fixture("railway-scene/Railway_Scene_LoD3__v3-thinned.gml")
OGC_GARAGE = fixture("ogc-citygml-3.0-encodings/Building_and_garage_LOD2-EPSG25832.gml")
OGC_UNITS = fixture("ogc-citygml-3.0-encodings/BuildingUnits_Storeys_xlink.gml")
OGC_ROAD_OVER_BRIDGE = fixture(
    "ogc-citygml-3.0-encodings/Road_over_Bridge_CityGML3.0_LOD2_with_CityObjectRelations.gml"
)

Point = tuple[float, float, float]


def all_of(city_model: CityModel, cls: Any) -> list[Any]:
    return [x for f in city_model.iter_features() if (x := cls.try_from(f)) is not None]


def with_id(features: list[Any], feature_id: str) -> Any:
    return next(x for x in features if x.feature_id().as_str() == feature_id)


def position(p: Any) -> Point:
    return (p.x(), p.y(), p.z())


def assert_envelope(envelope: Any, lower: Point, upper: Point) -> None:
    assert envelope is not None
    assert position(envelope.lower_corner()) == pytest.approx(lower, abs=1e-6)
    assert position(envelope.upper_corner()) == pytest.approx(upper, abs=1e-6)


def test_compute_envelope() -> None:
    city_model = read_model(FZK_LOD1)
    solid = all_of(city_model, Building)[0].lod1_solid().object()
    lower, upper = (457842.0, 5439083.0, 111.8), (457854.0, 5439093.0, 118.31769)
    assert_envelope(solid.compute_envelope(), lower, upper)
    shell = solid.exterior()
    assert_envelope(shell.compute_envelope(), lower, upper)
    assert_envelope(solid.triangulate().surface().compute_envelope(), lower, upper)
    first = Polygon.try_from(next(iter(shell.members())).object())
    ground = (457854.0, 5439093.0, 111.8)
    assert_envelope(first.compute_envelope(), lower, ground)
    assert_envelope(first.exterior().compute_envelope(), lower, ground)

    city_model = read_model(ASAM_ROAD_SHAPE)
    space = all_of(city_model, TrafficSpace)[0]
    multi_curve = space.lod2_multi_curve().object()
    lower, upper = (-48.38872036507727, 2.3148451158285663, 0.25), (-16.661414812688488, 26.674198193965925, 0.25)
    assert_envelope(multi_curve.compute_envelope(), lower, upper)
    [member] = list(multi_curve.curve_member())
    assert_envelope(member.object().compute_envelope(), lower, upper)
    solid = space.lod2_solid().object()
    assert_envelope(
        solid.compute_envelope(),
        (-49.60668801898414, 0.7284798382091271, 0.05),
        (-15.44344715878162, 28.260563471585364, 4.95),
    )
    assert len(list(solid.points())) == 24

    city_model = read_model(RAILWAY)
    tree = with_id(all_of(city_model, SolitaryVegetationObject), "GMLID_SO092422_3593_9527")
    point = tree.lod3_implicit_representation().object().reference_point().object()
    reference = (-568.8000793496976, 457.60044759869743, 105.00139681350242)
    assert_envelope(point.compute_envelope(), reference, reference)

    city_model = read_model(OGC_GARAGE)
    tin = all_of(city_model, TinRelief)[0].tin().object()
    assert_envelope(tin.compute_envelope(), (458868.0, 5438343.0, 112.0), (458892.0, 5438362.0, 114.0))


def test_polygon_interior_rings() -> None:
    city_model = read_model(TUM)
    [ground] = all_of(city_model, GroundSurface)
    multi_surface = ground.lod2_multi_surface().object()
    [member] = list(multi_surface.surface_member())
    polygon = Polygon.try_from(member.object())
    assert polygon.id().as_str() == "DEBY_LOD2_4959457_2470b16f-99f0-43c3-9a27-bd4fc3822c91_2_poly"
    exterior = LinearRing.try_from(polygon.exterior())
    assert len(list(exterior.points())) == 11
    assert exterior.area_3d() == pytest.approx(1371.825439453125, abs=1e-6)
    assert exterior.length_3d() == pytest.approx(150.78554397170106, abs=1e-6)
    [ring] = list(polygon.interior())
    interior = LinearRing.try_from(ring)
    assert len(list(interior.points())) == 4
    assert interior.area_3d() == pytest.approx(142.26318359375, abs=1e-6)
    assert interior.length_3d() == pytest.approx(47.7096809282068, abs=1e-6)
    assert polygon.area_3d() == pytest.approx(1229.562255859375, abs=1e-6)
    assert len(list(polygon.points())) == 15
    assert_envelope(polygon.compute_envelope(), (691009.16, 5335994.57, 515.042), (691054.07, 5336047.41, 515.042))
    triangulation = multi_surface.triangulate()
    assert not triangulation.has_skipped()
    assert len(list(triangulation.surface().triangles())) == 15
    assert triangulation.surface().area_3d() == pytest.approx(1229.5620994984272, abs=1e-6)


def test_composite_surface_and_patches() -> None:
    city_model = read_model(OGC_ROAD_OVER_BRIDGE)
    ground = with_id(all_of(city_model, GroundSurface), "id_groundsurface1")
    multi_surface = ground.lod2_multi_surface().object()
    assert multi_surface.id().as_str() == "id_groundsurface1-0"
    assert multi_surface.area_3d() == pytest.approx(77500.15996032, abs=1e-6)
    [member] = list(multi_surface.surface_member())
    kind = member.object()
    assert kind.geometry_type() == GeometryType.CompositeSurface
    assert Polygon.try_from(kind) is None
    composite = CompositeSurface.try_from(kind)
    assert composite.id().as_str() == "id_groundsurface1-1"
    assert composite.area_3d() == pytest.approx(77500.15996032, abs=1e-6)
    assert len(list(composite.points())) == 6
    assert_envelope(composite.compute_envelope(), (0.0, 0.0, 0.0), (393.7008, 196.8504, 0.0))
    triangulation = composite.triangulate()
    assert not triangulation.has_skipped()
    assert len(list(triangulation.surface().triangles())) == 2

    ids = ["fme-gen-1a9ac79e-2880-47c7-b7c3-c9df5bc17447", "fme-gen-545ee504-7440-4cb6-8713-fc8ba21ac163"]
    members = [m.object() for m in composite.surface_member()]
    assert len(members) == len(ids)
    for kind, surface_id in zip(members, ids):
        assert kind.geometry_type() == GeometryType.Surface
        surface = Surface.try_from(kind)
        assert surface.id().as_str() == surface_id
        assert surface.area_3d() == pytest.approx(38750.07998016, abs=1e-6)
        assert len(list(surface.triangulate().surface().triangles())) == 1
        [patch] = list(surface.patches())
        assert Triangle.try_from(patch) is None
        polygon_patch = PolygonPatch.try_from(patch)
        assert list(polygon_patch.interior()) == []
        assert len(list(LinearRing.try_from(polygon_patch.exterior()).points())) == 3
        assert patch.area_3d() == pytest.approx(38750.07998016, abs=1e-6)
        assert len(list(patch.triangulate().surface().triangles())) == 1


def test_triangle_patches() -> None:
    city_model = read_model(OGC_GARAGE)
    tin = all_of(city_model, TinRelief)[0].tin().object()
    assert len(list(tin.surface().patches())) == 12
    triangle = next(iter(tin.triangles()))
    assert position(triangle.a()) == pytest.approx((458883.0, 5438362.0, 114.0))
    assert position(triangle.b()) == pytest.approx((458868.0, 5438362.0, 112.0))
    assert position(triangle.c()) == pytest.approx((458875.0, 5438355.0, 112.0))
    assert triangle.area() == pytest.approx(53.42518132865812, abs=1e-6)
    assert triangle.exterior().geometry_type() == GeometryType.LinearRing


def test_unresolved_surface_reference() -> None:
    city_model = read_model(OGC_UNITS)
    storey = with_id(all_of(city_model, Storey), "storey1")
    multi_surface = storey.lod2_multi_surface().object()
    assert len(list(multi_surface.surface_member())) == 6
    with pytest.raises(Exception) as raised:
        multi_surface.area_3d()
    assert_error(raised, ErrorKind.UnresolvedReference, "#Wall_1_PolyID82397_997_453711_16336011")
    assert len(list(multi_surface.points())) == 12
    assert_envelope(multi_surface.compute_envelope(), (457841.1, 5439082.1, 111.1), (457853.9, 5439092.9, 113.9))
    triangulation = multi_surface.triangulate()
    assert not triangulation.has_skipped()
    assert len(list(triangulation.surface().triangles())) == 6


def test_solid_unresolved_reference() -> None:
    city_model = read_model(FZK_LOD2)
    solid = all_of(city_model, Building)[0].lod2_solid().object()
    with pytest.raises(Exception) as raised:
        solid.volume_3d()
    assert_error(raised, ErrorKind.UnresolvedReference, "#PolyID7350_878_759628_120742")


def test_triangulate_without_members() -> None:
    city_model = read_model(FZK_LOD2)
    solid = all_of(city_model, Building)[0].lod2_solid().object()
    assert list(solid.points()) == []
    assert solid.compute_envelope() is None
    with pytest.raises(Exception) as raised:
        solid.triangulate()
    assert_error(raised, ErrorKind.InvalidArgument, "requires at least 1 element")
