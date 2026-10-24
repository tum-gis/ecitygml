//! The cases of `geometry.md`.

use crate::*;

use ecitygml_ffi::citygml::core::model::building::building::Building;
use ecitygml_ffi::citygml::core::model::building::storey::Storey;
use ecitygml_ffi::citygml::core::model::construction::ground_surface::GroundSurface;
use ecitygml_ffi::citygml::core::model::core::refs::abstract_feature_kind_ref::AbstractFeatureKindRef;
use ecitygml_ffi::citygml::core::model::relief::tin_relief::TinRelief;
use ecitygml_ffi::citygml::core::model::transportation::traffic_space::TrafficSpace;
use ecitygml_ffi::citygml::core::model::vegetation::solitary_vegetation_object::SolitaryVegetationObject;
use ecitygml_ffi::gml::core::model::common::geometry_type::GeometryType;
use ecitygml_ffi::gml::core::model::geometry::complexes::composite_surface::CompositeSurface;
use ecitygml_ffi::gml::core::model::geometry::direct_position::DirectPosition;
use ecitygml_ffi::gml::core::model::geometry::envelope::Envelope;
use ecitygml_ffi::gml::core::model::geometry::primitives::linear_ring::LinearRing;
use ecitygml_ffi::gml::core::model::geometry::primitives::polygon::Polygon;
use ecitygml_ffi::gml::core::model::geometry::primitives::polygon_patch::PolygonPatch;
use ecitygml_ffi::gml::core::model::geometry::primitives::surface::Surface;
use ecitygml_ffi::gml::core::model::geometry::primitives::triangle::Triangle;

const FZK_LOD1: &str = "fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml";
const FZK_LOD2: &str = "fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml";
const TUM: &str = "tum-main-entrance/TUM-Main-Entrance.gml";
const ASAM_ROAD_SHAPE: &str = "asam-opendrive/ASAM-UC_RoadShape.gml";
const RAILWAY: &str = "railway-scene/Railway_Scene_LoD3__v3-thinned.gml";
const OGC_GARAGE: &str = "ogc-citygml-3.0-encodings/Building_and_garage_LOD2-EPSG25832.gml";
const OGC_UNITS: &str = "ogc-citygml-3.0-encodings/BuildingUnits_Storeys_xlink.gml";
const OGC_ROAD_OVER_BRIDGE: &str =
    "ogc-citygml-3.0-encodings/Road_over_Bridge_CityGML3.0_LOD2_with_CityObjectRelations.gml";

type Point = (f64, f64, f64);

fn assert_close(actual: f64, expected: f64) {
    assert!(
        (actual - expected).abs() <= 1e-6,
        "{actual} is not within 1e-6 of {expected}"
    );
}

fn assert_position(actual: &DirectPosition, expected: Point) {
    assert_close(actual.x(), expected.0);
    assert_close(actual.y(), expected.1);
    assert_close(actual.z(), expected.2);
}

fn assert_envelope(envelope: Option<Box<Envelope>>, lower: Point, upper: Point) {
    let envelope = envelope.expect("should have an envelope");
    assert_position(envelope.lower_corner(), lower);
    assert_position(envelope.upper_corner(), upper);
}

/// The number of items of a Diplomat iterator.
macro_rules! count {
    ($iterator:expr) => {
        match $iterator {
            mut iterator => std::iter::from_fn(|| iterator.next()).count(),
        }
    };
}

/// The features that `try_from` accepts.
fn all<'a, T: 'a>(
    city_model: &'a CityModel,
    try_from: impl Fn(&AbstractFeatureKindRef<'a>) -> Option<&'a T>,
) -> Vec<&'a T> {
    let mut features = city_model.iter_features();
    std::iter::from_fn(|| features.next())
        .filter_map(|feature| try_from(&feature))
        .collect()
}

#[test]
fn compute_envelope() {
    let city_model = read(&fixture(FZK_LOD1));
    let solid = all(&city_model, |f| Building::try_from(f))[0]
        .lod1_solid()
        .unwrap()
        .object()
        .unwrap();
    let (lower, upper) = (
        (457842.0, 5439083.0, 111.8),
        (457854.0, 5439093.0, 118.31769),
    );
    assert_envelope(solid.compute_envelope(), lower, upper);
    let shell = solid.exterior().unwrap();
    assert_envelope(shell.compute_envelope(), lower, upper);
    let triangulation = solid.triangulate().unwrap();
    assert_envelope(triangulation.surface().compute_envelope(), lower, upper);
    let first = Polygon::try_from(shell.members().next().unwrap().object().unwrap()).unwrap();
    let ground = (457854.0, 5439093.0, 111.8);
    assert_envelope(first.compute_envelope(), lower, ground);
    assert_envelope(first.exterior().unwrap().compute_envelope(), lower, ground);

    let city_model = read(&fixture(ASAM_ROAD_SHAPE));
    let space = all(&city_model, |f| TrafficSpace::try_from(f))[0];
    let multi_curve = space.lod2_multi_curve().unwrap().object().unwrap();
    let (lower, upper) = (
        (-48.38872036507727, 2.3148451158285663, 0.25),
        (-16.661414812688488, 26.674198193965925, 0.25),
    );
    assert_envelope(multi_curve.compute_envelope(), lower, upper);
    let mut members = multi_curve.curve_member();
    let curve = members.next().unwrap().object().unwrap();
    assert!(members.next().is_none());
    assert_envelope(curve.compute_envelope(), lower, upper);
    let solid = space.lod2_solid().unwrap().object().unwrap();
    assert_envelope(
        solid.compute_envelope(),
        (-49.60668801898414, 0.7284798382091271, 0.05),
        (-15.44344715878162, 28.260563471585364, 4.95),
    );
    assert_eq!(count!(solid.points()), 24);

    let city_model = read(&fixture(RAILWAY));
    let tree = all(&city_model, |f| SolitaryVegetationObject::try_from(f))
        .into_iter()
        .find(|tree| tree.feature_id().as_str() == "GMLID_SO092422_3593_9527")
        .unwrap();
    let implicit = tree
        .lod3_implicit_representation()
        .unwrap()
        .object()
        .unwrap();
    let point = implicit.reference_point().object().unwrap();
    let position = (-568.8000793496976, 457.60044759869743, 105.00139681350242);
    assert_envelope(point.compute_envelope(), position, position);

    let city_model = read(&fixture(OGC_GARAGE));
    let tin = all(&city_model, |f| TinRelief::try_from(f))[0]
        .tin()
        .unwrap()
        .object()
        .unwrap();
    assert_envelope(
        tin.compute_envelope(),
        (458868.0, 5438343.0, 112.0),
        (458892.0, 5438362.0, 114.0),
    );
}

#[test]
fn polygon_interior_rings() {
    let city_model = read(&fixture(TUM));
    let grounds = all(&city_model, |f| GroundSurface::try_from(f));
    assert_eq!(grounds.len(), 1);
    let multi_surface = grounds[0].lod2_multi_surface().unwrap().object().unwrap();
    let mut members = multi_surface.surface_member();
    let polygon = Polygon::try_from(members.next().unwrap().object().unwrap()).unwrap();
    assert!(members.next().is_none());
    assert_eq!(
        polygon.id().map(|id| id.as_str()),
        Some("DEBY_LOD2_4959457_2470b16f-99f0-43c3-9a27-bd4fc3822c91_2_poly")
    );
    let exterior = LinearRing::try_from(polygon.exterior().unwrap()).unwrap();
    assert_eq!(count!(exterior.points()), 11);
    assert_close(exterior.area_3d(), 1371.825439453125);
    assert_close(exterior.length_3d(), 150.78554397170106);
    let mut interiors = polygon.interior();
    let interior = LinearRing::try_from(interiors.next().unwrap()).unwrap();
    assert!(interiors.next().is_none());
    assert_eq!(count!(interior.points()), 4);
    assert_close(interior.area_3d(), 142.26318359375);
    assert_close(interior.length_3d(), 47.7096809282068);
    assert_close(polygon.area_3d().unwrap(), 1229.562255859375);
    assert_eq!(count!(polygon.points()), 15);
    assert_envelope(
        polygon.compute_envelope(),
        (691009.16, 5335994.57, 515.042),
        (691054.07, 5336047.41, 515.042),
    );
    let triangulation = multi_surface.triangulate().unwrap();
    assert!(!triangulation.has_skipped());
    assert_eq!(count!(triangulation.surface().triangles()), 15);
    assert_close(
        triangulation.surface().area_3d().unwrap(),
        1229.5620994984272,
    );
}

#[test]
fn composite_surface_and_patches() {
    let city_model = read(&fixture(OGC_ROAD_OVER_BRIDGE));
    let ground = all(&city_model, |f| GroundSurface::try_from(f))
        .into_iter()
        .find(|ground| ground.feature_id().as_str() == "id_groundsurface1")
        .unwrap();
    let multi_surface = ground.lod2_multi_surface().unwrap().object().unwrap();
    assert_eq!(
        multi_surface.id().map(|id| id.as_str()),
        Some("id_groundsurface1-0")
    );
    assert_close(multi_surface.area_3d().unwrap(), 77500.15996032);
    let mut members = multi_surface.surface_member();
    let kind = members.next().unwrap().object().unwrap();
    assert!(members.next().is_none());
    assert_eq!(kind.geometry_type(), GeometryType::CompositeSurface);
    assert!(Polygon::try_from(kind).is_none());
    let composite = CompositeSurface::try_from(kind).unwrap();
    assert_eq!(
        composite.id().map(|id| id.as_str()),
        Some("id_groundsurface1-1")
    );
    assert_close(composite.area_3d().unwrap(), 77500.15996032);
    assert_eq!(count!(composite.points()), 6);
    assert_envelope(
        composite.compute_envelope(),
        (0.0, 0.0, 0.0),
        (393.7008, 196.8504, 0.0),
    );
    let triangulation = composite.triangulate().unwrap();
    assert!(!triangulation.has_skipped());
    assert_eq!(count!(triangulation.surface().triangles()), 2);

    let ids = [
        "fme-gen-1a9ac79e-2880-47c7-b7c3-c9df5bc17447",
        "fme-gen-545ee504-7440-4cb6-8713-fc8ba21ac163",
    ];
    let mut members = composite.surface_member();
    for id in ids {
        let kind = members.next().unwrap().object().unwrap();
        assert_eq!(kind.geometry_type(), GeometryType::Surface);
        let surface = Surface::try_from(kind).unwrap();
        assert_eq!(surface.id().map(|id| id.as_str()), Some(id));
        assert_close(surface.area_3d().unwrap(), 38750.07998016);
        assert_eq!(
            count!(surface.triangulate().unwrap().surface().triangles()),
            1
        );
        let mut patches = surface.patches();
        let patch = patches.next().unwrap();
        assert!(patches.next().is_none());
        assert!(Triangle::try_from(patch).is_none());
        let polygon_patch = PolygonPatch::try_from(patch).unwrap();
        assert_eq!(count!(polygon_patch.interior()), 0);
        let exterior = LinearRing::try_from(polygon_patch.exterior().unwrap()).unwrap();
        assert_eq!(count!(exterior.points()), 3);
        assert_close(patch.area_3d().unwrap(), 38750.07998016);
        assert_eq!(
            count!(patch.triangulate().unwrap().surface().triangles()),
            1
        );
    }
    assert!(members.next().is_none());
}

#[test]
fn triangle_patches() {
    let city_model = read(&fixture(OGC_GARAGE));
    let tin = all(&city_model, |f| TinRelief::try_from(f))[0]
        .tin()
        .unwrap()
        .object()
        .unwrap();
    assert_eq!(count!(tin.surface().patches()), 12);
    let triangle = tin.triangles().next().unwrap();
    assert_position(triangle.a(), (458883.0, 5438362.0, 114.0));
    assert_position(triangle.b(), (458868.0, 5438362.0, 112.0));
    assert_position(triangle.c(), (458875.0, 5438355.0, 112.0));
    assert_close(triangle.area(), 53.42518132865812);
    assert_eq!(
        triangle.exterior().geometry_type(),
        GeometryType::LinearRing
    );
}

#[test]
fn unresolved_surface_reference() {
    let city_model = read(&fixture(OGC_UNITS));
    let storey = all(&city_model, |f| Storey::try_from(f))
        .into_iter()
        .find(|storey| storey.feature_id().as_str() == "storey1")
        .unwrap();
    let multi_surface = storey.lod2_multi_surface().unwrap().object().unwrap();
    assert_eq!(count!(multi_surface.surface_member()), 6);
    let error = multi_surface.area_3d().unwrap_err();
    assert_error(
        &error,
        ErrorKind::UnresolvedReference,
        "#Wall_1_PolyID82397_997_453711_16336011",
    );
    assert_eq!(count!(multi_surface.points()), 12);
    assert_envelope(
        multi_surface.compute_envelope(),
        (457841.1, 5439082.1, 111.1),
        (457853.9, 5439092.9, 113.9),
    );
    let triangulation = multi_surface.triangulate().unwrap();
    assert!(!triangulation.has_skipped());
    assert_eq!(count!(triangulation.surface().triangles()), 6);
}

#[test]
fn solid_unresolved_reference() {
    let city_model = read(&fixture(FZK_LOD2));
    let solid = all(&city_model, |f| Building::try_from(f))[0]
        .lod2_solid()
        .unwrap()
        .object()
        .unwrap();
    let error = solid.volume_3d().unwrap_err();
    assert_error(
        &error,
        ErrorKind::UnresolvedReference,
        "#PolyID7350_878_759628_120742",
    );
}

#[test]
fn triangulate_without_members() {
    let city_model = read(&fixture(FZK_LOD2));
    let solid = all(&city_model, |f| Building::try_from(f))[0]
        .lod2_solid()
        .unwrap()
        .object()
        .unwrap();
    assert_eq!(count!(solid.points()), 0);
    assert!(solid.compute_envelope().is_none());
    let error = solid.triangulate().err().unwrap();
    assert_error(
        &error,
        ErrorKind::InvalidArgument,
        "requires at least 1 element",
    );
}
