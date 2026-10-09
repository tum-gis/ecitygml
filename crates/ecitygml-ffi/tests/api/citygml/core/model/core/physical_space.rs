//! The AbstractPhysicalSpace and AbstractOccupiedSpace getters: terrain intersection curves and
//! implicit representations (`ImplicitGeometry`).

use crate::*;

use ecitygml_ffi::citygml::core::model::building::building::Building;
use ecitygml_ffi::citygml::io::format::CitygmlFormat;
use ecitygml_ffi::citygml::io::gml::write::GmlWriter;
use ecitygml_ffi::gml::core::model::common::geometry_type::GeometryType;
use ecitygml_ffi::gml::core::model::geometry::aggregates::multi_surface::MultiSurface;
use ecitygml_ffi::gml::core::model::geometry::primitives::line_string::LineString;
use ecitygml_ffi::gml::core::model::geometry::primitives::point::Point;

// No fixture has these; they are injected into the FZK LoD2 building after its solid. The former
// tests put the implicit representation on a tree; a building is an occupied space too.
const TERRAIN_INTERSECTION_CURVE: &str = r#"</lod2Solid>
      <lod2TerrainIntersectionCurve>
        <gml:MultiCurve>
          <gml:curveMember>
            <gml:LineString>
              <gml:posList>457842 5439083 111.8 457854 5439083 111.8</gml:posList>
            </gml:LineString>
          </gml:curveMember>
        </gml:MultiCurve>
      </lod2TerrainIntersectionCurve>"#;

fn implicit_representation(relative_geometry: &str) -> String {
    format!(
        r#"</lod2Solid>
      <lod1ImplicitRepresentation>
        <ImplicitGeometry gml:id="tree_prototype">
          <transformationMatrix>2 0 0 10 0 2 0 20 0 0 3 30 0 0 0 1</transformationMatrix>
          <mimeType>model/gltf+json</mimeType>
          <referencePoint>
            <gml:Point><gml:pos>457850 5439090 112</gml:pos></gml:Point>
          </referencePoint>
          <relativeGeometry>{relative_geometry}</relativeGeometry>
        </ImplicitGeometry>
      </lod1ImplicitRepresentation>"#
    )
}

const MULTI_SURFACE: &str = "<gml:MultiSurface><gml:surfaceMember><gml:Polygon><gml:exterior><gml:LinearRing><gml:posList>0 0 0 1 0 0 1 1 0 0 0 0</gml:posList></gml:LinearRing></gml:exterior></gml:Polygon></gml:surfaceMember></gml:MultiSurface>";
const POINT: &str = "<gml:Point><gml:pos>0 0 0</gml:pos></gml:Point>";

fn read_lod2_with(to: &str) -> Box<CityModel> {
    read_fixture_modified(
        "FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml",
        "</lod2Solid>",
        to,
    )
}

fn first_building(city_model: &CityModel) -> &Building {
    let mut features = city_model.iter_features();
    std::iter::from_fn(|| features.next())
        .find_map(|f| Building::try_from(&f))
        .unwrap()
}

#[test]
fn absent() {
    let path = format!("{FIXTURES}FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml");
    let city_model = read(path.as_bytes()).unwrap();
    let building = first_building(&city_model);
    assert!(building.lod1_terrain_intersection_curve().is_none());
    assert!(building.lod2_terrain_intersection_curve().is_none());
    assert!(building.lod3_terrain_intersection_curve().is_none());
    assert!(building.lod1_implicit_representation().is_none());
    assert!(building.lod2_implicit_representation().is_none());
    assert!(building.lod3_implicit_representation().is_none());
}

#[test]
fn terrain_intersection_curve() {
    let city_model = read_lod2_with(TERRAIN_INTERSECTION_CURVE);
    let curve = first_building(&city_model)
        .lod2_terrain_intersection_curve()
        .unwrap()
        .object()
        .unwrap();
    let line =
        LineString::try_from(curve.curve_member().next().unwrap().object().unwrap()).unwrap();
    let mut points = line.points();
    let first = points.next().unwrap();
    assert_eq!(
        (first.x(), first.y(), first.z()),
        (457842.0, 5439083.0, 111.8)
    );
    assert_eq!(points.next().unwrap().x(), 457854.0);
    assert!((curve.length_3d().unwrap() - 12.0).abs() < 1e-9);
}

#[test]
fn implicit_geometry() {
    let city_model = read_lod2_with(&implicit_representation(MULTI_SURFACE));
    let building = first_building(&city_model);
    assert!(building.lod2_implicit_representation().is_none());
    let property = building.lod1_implicit_representation().unwrap();
    assert!(property.href().is_none());
    let implicit = property.object().unwrap();

    assert_eq!(implicit.object_id().as_str(), "tree_prototype");
    assert_eq!(implicit.mime_type().unwrap().value(), "model/gltf+json");
    assert!(implicit.library_object().is_none());
    let point = implicit.reference_point().object().unwrap().pos();
    assert_eq!(
        (point.x(), point.y(), point.z()),
        (457850.0, 5439090.0, 112.0)
    );

    let matrix = implicit.transformation_matrix();
    let rows: Vec<Vec<f64>> = (0..4)
        .map(|row| {
            (0..4)
                .map(|column| matrix.get(row, column).unwrap())
                .collect()
        })
        .collect();
    assert_eq!(
        rows,
        [
            [2.0, 0.0, 0.0, 10.0],
            [0.0, 2.0, 0.0, 20.0],
            [0.0, 0.0, 3.0, 30.0],
            [0.0, 0.0, 0.0, 1.0]
        ]
    );
    let error = matrix.get(4, 0).unwrap_err();
    assert_eq!(error.kind(), ErrorKind::InvalidArgument);

    let geometry = implicit.relative_geometry().unwrap().object().unwrap();
    assert_eq!(geometry.geometry_type(), GeometryType::MultiSurface);
    let multi_surface = MultiSurface::try_from(geometry).unwrap();
    let mut members = multi_surface.surface_member();
    assert_eq!(std::iter::from_fn(|| members.next()).count(), 1);
    assert!(Point::try_from(geometry).is_none());
    assert!(!geometry.triangulate().unwrap().has_skipped());
}

#[test]
fn point_relative_geometry() {
    let city_model = read_lod2_with(&implicit_representation(POINT));
    let implicit = first_building(&city_model)
        .lod1_implicit_representation()
        .unwrap()
        .object()
        .unwrap();
    let geometry = implicit.relative_geometry().unwrap().object().unwrap();
    assert_eq!(geometry.geometry_type(), GeometryType::Point);
    let point = Point::try_from(geometry).unwrap().pos();
    assert_eq!((point.x(), point.y(), point.z()), (0.0, 0.0, 0.0));
    assert!(MultiSurface::try_from(geometry).is_none());
}

#[test]
fn write_round_trip() {
    // Both after the solid: the curve keeps the `</lod2Solid>` the fixture loses, the implicit
    // representation doesn't repeat it.
    let implicit = implicit_representation(MULTI_SURFACE);
    let implicit = implicit.strip_prefix("</lod2Solid>").unwrap();
    let model = read_lod2_with(&(TERRAIN_INTERSECTION_CURVE.to_owned() + implicit));
    let mut writer = GmlWriter::new(CitygmlFormat::Gml);
    writer.finish(&model).unwrap();
    let text = String::from_utf8(writer.data().to_vec()).unwrap();
    assert!(!text.contains("TerrainIntersectionCurveProperty"));
    assert!(!text.contains("objectId"));

    let written = GmlReader::new(writer.data(), CitygmlFormat::Gml)
        .finish()
        .unwrap();
    let building = first_building(&written);
    assert!(
        building
            .lod2_terrain_intersection_curve()
            .unwrap()
            .object()
            .is_some()
    );
    let implicit = building
        .lod1_implicit_representation()
        .unwrap()
        .object()
        .unwrap();
    assert_eq!(implicit.object_id().as_str(), "tree_prototype");
}
