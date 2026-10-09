"""The AbstractPhysicalSpace and AbstractOccupiedSpace getters: terrain intersection curves and
implicit representations.

Ported from the former PyO3 bindings' `test_physical_space.py`. The former tests put the implicit
representation on a solitary vegetation object, which isn't bound; here it is on the FZK building
(an occupied space too). `relative_geometry().object()` is an `AbstractGeometryKind`, converted
with `MultiSurface.try_from`, `Point.try_from` and the like. `transformation_matrix()` is a
`TransformationMatrix4x4` read with `get(row, column)`. Not ported: the `NotImplementedError` for
unbound relative geometries (the kind has `geometry_type()` for any geometry).
"""

from pathlib import Path
from typing import Any

import pytest

from conftest import FZK_LOD2, curve_points, features_of, objects, polygons, read_model, unwrap
from ecitygml import Building, CityModel, GeometryType, GmlWriter, ImplicitGeometry, MultiCurve, MultiSurface, Point

TERRAIN_INTERSECTION_CURVE = """</lod2Solid>
      <{element}>
        <gml:MultiCurve>
          <gml:curveMember>
            <gml:LineString>
              <gml:posList>457842 5439083 111.8 457854 5439083 111.8</gml:posList>
            </gml:LineString>
          </gml:curveMember>
        </gml:MultiCurve>
      </{element}>"""

IMPLICIT_REPRESENTATION = """
      <lod1ImplicitRepresentation>
        <ImplicitGeometry gml:id="tree_prototype">
          <transformationMatrix>2 0 0 10 0 2 0 20 0 0 3 30 0 0 0 1</transformationMatrix>
          <mimeType>model/gltf+json</mimeType>
          <referencePoint>
            <gml:Point><gml:pos>457850 5439090 112</gml:pos></gml:Point>
          </referencePoint>
          <relativeGeometry>{relative_geometry}</relativeGeometry>
        </ImplicitGeometry>
      </lod1ImplicitRepresentation>"""

MULTI_SURFACE = """
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon>
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:posList>0 0 0 1 0 0 1 1 0 0 0 0</gml:posList>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          """

POINT = "<gml:Point><gml:pos>0 0 0</gml:pos></gml:Point>"


def fzk_with(tmp_path: Path, *, tic_element: str | None = None, relative_geometry: str | None = None) -> CityModel:
    """Reads a copy of the FZK LoD2 file with a terrain intersection curve and/or an implicit
    representation after the building's solid; keep the model referenced."""
    text = FZK_LOD2.read_text()
    assert text.count("</lod2Solid>") == 1
    injected = "</lod2Solid>"
    if tic_element is not None:
        injected = TERRAIN_INTERSECTION_CURVE.format(element=tic_element)
    if relative_geometry is not None:
        injected += IMPLICIT_REPRESENTATION.format(relative_geometry=relative_geometry)
    path = tmp_path / "fzk_extended.gml"
    path.write_text(text.replace("</lod2Solid>", injected))
    return read_model(path)


def coords(position: Any) -> tuple[float, float, float]:
    return (position.x(), position.y(), position.z())


@pytest.fixture(scope="module")
def plain_building() -> Any:
    model = read_model(FZK_LOD2)
    return model, features_of(model, Building)[0]


@pytest.fixture(scope="module")
def multi_surface_model(tmp_path_factory: pytest.TempPathFactory) -> CityModel:
    return fzk_with(tmp_path_factory.mktemp("implicit"), relative_geometry=MULTI_SURFACE)


@pytest.fixture(scope="module")
def implicit(multi_surface_model: CityModel) -> ImplicitGeometry:
    return unwrap(features_of(multi_surface_model, Building)[0].lod1_implicit_representation())


class TestTerrainIntersectionCurve:
    def test_absent(self, plain_building: Any) -> None:
        _, building = plain_building
        assert building.lod1_terrain_intersection_curve() is None
        assert building.lod2_terrain_intersection_curve() is None
        assert building.lod3_terrain_intersection_curve() is None

    def test_converted_to_multi_curve(self, tmp_path: Path) -> None:
        model = fzk_with(tmp_path, tic_element="lod2TerrainIntersectionCurve")
        curve = unwrap(features_of(model, Building)[0].lod2_terrain_intersection_curve())
        assert isinstance(curve, MultiCurve)
        assert [[coords(p) for p in c] for c in curve_points(curve)] == [
            [(457842.0, 5439083.0, 111.8), (457854.0, 5439083.0, 111.8)]
        ]


class TestImplicitRepresentation:
    def test_absent(self, plain_building: Any) -> None:
        _, building = plain_building
        assert building.lod1_implicit_representation() is None
        assert building.lod2_implicit_representation() is None
        assert building.lod3_implicit_representation() is None

    def test_implicit_geometry(self, multi_surface_model: CityModel, implicit: ImplicitGeometry) -> None:
        assert features_of(multi_surface_model, Building)[0].lod2_implicit_representation() is None
        assert isinstance(implicit, ImplicitGeometry)
        assert implicit.mime_type() is not None
        assert implicit.mime_type().value() == "model/gltf+json"
        assert implicit.library_object() is None
        assert coords(unwrap(implicit.reference_point()).pos()) == (457850.0, 5439090.0, 112.0)

    def test_transformation_matrix_rows(self, implicit: ImplicitGeometry) -> None:
        matrix = implicit.transformation_matrix()
        assert [[matrix.get(row, column) for column in range(4)] for row in range(4)] == [
            [2.0, 0.0, 0.0, 10.0],
            [0.0, 2.0, 0.0, 20.0],
            [0.0, 0.0, 3.0, 30.0],
            [0.0, 0.0, 0.0, 1.0],
        ]

    def test_transformation_matrix_index_out_of_range(self, implicit: ImplicitGeometry) -> None:
        with pytest.raises(Exception, match="out of range"):
            implicit.transformation_matrix().get(4, 0)

    def test_relative_geometry(self, implicit: ImplicitGeometry) -> None:
        geometry = unwrap(implicit.relative_geometry())
        assert geometry.geometry_type() == GeometryType.MultiSurface
        multi_surface = MultiSurface.try_from(geometry)
        assert isinstance(multi_surface, MultiSurface)
        assert len(polygons(multi_surface)) == 1
        assert Point.try_from(geometry) is None

    def test_point_relative_geometry(self, tmp_path: Path) -> None:
        model = fzk_with(tmp_path, relative_geometry=POINT)
        implicit = unwrap(features_of(model, Building)[0].lod1_implicit_representation())
        point = Point.try_from(unwrap(implicit.relative_geometry()))
        assert isinstance(point, Point) and coords(point.pos()) == (0.0, 0.0, 0.0)

    def test_object_id_from_gml_id(self, implicit: ImplicitGeometry) -> None:
        assert implicit.object_id().as_str() == "tree_prototype"


def test_write_round_trip(tmp_path: Path) -> None:
    source = fzk_with(tmp_path, tic_element="lod2TerrainIntersectionCurve", relative_geometry=MULTI_SURFACE)
    written = tmp_path / "written.gml"
    GmlWriter.from_path(str(written)).finish(source)
    text = written.read_text()
    assert "TerrainIntersectionCurveProperty" not in text
    assert "objectId" not in text

    model = read_model(written)
    building = features_of(model, Building)[0]
    curve = unwrap(building.lod2_terrain_intersection_curve())
    implicit = unwrap(building.lod1_implicit_representation())
    assert len(curve_points(curve)) == 1
    assert implicit.object_id().as_str() == "tree_prototype"
