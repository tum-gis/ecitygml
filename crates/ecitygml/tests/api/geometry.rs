//! The cases of `geometry.md`. `solid_unresolved_reference` is scoped out (`Solid::volume_3d` skips unresolved
//! members).

use crate::{fixture, read};
use ecitygml::model::building::{Building, Storey};
use ecitygml::model::common::IterFeatures;
use ecitygml::model::construction::GroundSurface;
use ecitygml::model::core::{
    AsAbstractFeature, AsAbstractOccupiedSpace, AsAbstractSpace, AsAbstractThematicSurface,
    CityModel,
};
use ecitygml::model::relief::TinRelief;
use ecitygml::model::transportation::TrafficSpace;
use ecitygml::model::vegetation::SolitaryVegetationObject;
use egml::model::base::AsAbstractGml;
use egml::model::common::{ComputeEnvelope, GeometryType, HasGeometryType, Triangulate};
use egml::model::geometry::primitives::{
    AbstractRingKind, AbstractSurfaceKind, AbstractSurfacePatchKind, LinearRing, Polygon,
};
use egml::model::geometry::{DirectPosition, Envelope};

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

fn assert_envelope(envelope: Option<Envelope>, lower: Point, upper: Point) {
    let envelope = envelope.expect("should have an envelope");
    assert_position(envelope.lower_corner(), lower);
    assert_position(envelope.upper_corner(), upper);
}

fn all<'a, T>(city_model: &'a CityModel) -> Vec<&'a T>
where
    &'a T: TryFrom<ecitygml::model::core::refs::AbstractFeatureKindRef<'a>>,
{
    city_model
        .iter_features()
        .filter_map(|feature| <&T>::try_from(feature).ok())
        .collect()
}

fn polygon(surface: &AbstractSurfaceKind) -> &Polygon {
    match surface {
        AbstractSurfaceKind::Polygon(polygon) => polygon,
        other => panic!("expected a polygon, got {other:?}"),
    }
}

fn linear_ring(ring: &AbstractRingKind) -> &LinearRing {
    match ring {
        AbstractRingKind::LinearRing(ring) => ring,
        other => panic!("expected a linear ring, got {other:?}"),
    }
}

#[test]
fn compute_envelope() {
    let city_model = read(&fixture(FZK_LOD1));
    let solid = all::<Building>(&city_model)[0]
        .lod1_solid()
        .and_then(|property| property.object())
        .expect("should have an LoD1 solid");
    let (lower, upper) = (
        (457842.0, 5439083.0, 111.8),
        (457854.0, 5439093.0, 118.31769),
    );
    assert_envelope(solid.compute_envelope(), lower, upper);
    let shell = solid.exterior().expect("should have a shell");
    assert_envelope(shell.compute_envelope(), lower, upper);
    let triangulation = solid.triangulate().expect("should triangulate");
    assert_envelope(triangulation.surface().compute_envelope(), lower, upper);
    let first = polygon(shell.members()[0].object().expect("inline"));
    let ground = (457854.0, 5439093.0, 111.8);
    assert_envelope(first.compute_envelope(), lower, ground);
    let ring = linear_ring(first.exterior().expect("should have an exterior"));
    assert_envelope(ring.compute_envelope(), lower, ground);

    let city_model = read(&fixture(ASAM_ROAD_SHAPE));
    let space = all::<TrafficSpace>(&city_model)[0];
    let multi_curve = space
        .lod2_multi_curve()
        .and_then(|property| property.object())
        .expect("should have an LoD2 multi curve");
    let (lower, upper) = (
        (-48.38872036507727, 2.3148451158285663, 0.25),
        (-16.661414812688488, 26.674198193965925, 0.25),
    );
    assert_envelope(multi_curve.compute_envelope(), lower, upper);
    let [member] = multi_curve.curve_member() else {
        panic!("expected one curve member");
    };
    let curve = member.object().expect("inline");
    assert_envelope(curve.compute_envelope(), lower, upper);
    let solid = space
        .lod2_solid()
        .and_then(|property| property.object())
        .expect("should have an LoD2 solid");
    assert_envelope(
        solid.compute_envelope(),
        (-49.60668801898414, 0.7284798382091271, 0.05),
        (-15.44344715878162, 28.260563471585364, 4.95),
    );
    assert_eq!(solid.points().len(), 24);

    let city_model = read(&fixture(RAILWAY));
    let tree = all::<SolitaryVegetationObject>(&city_model)
        .into_iter()
        .find(|tree| tree.feature_id().as_str() == "GMLID_SO092422_3593_9527")
        .expect("should have the tree");
    let point = tree
        .lod3_implicit_representation()
        .and_then(|property| property.object())
        .expect("should have an implicit representation")
        .reference_point()
        .object()
        .expect("should have a reference point");
    let position = (-568.8000793496976, 457.60044759869743, 105.00139681350242);
    assert_envelope(point.compute_envelope(), position, position);

    let city_model = read(&fixture(OGC_GARAGE));
    let tin = all::<TinRelief>(&city_model)[0]
        .tin()
        .and_then(|property| property.object())
        .expect("should have a TIN");
    assert_envelope(
        tin.compute_envelope(),
        (458868.0, 5438343.0, 112.0),
        (458892.0, 5438362.0, 114.0),
    );
}

#[test]
fn polygon_interior_rings() {
    let city_model = read(&fixture(TUM));
    let [ground] = all::<GroundSurface>(&city_model)[..] else {
        panic!("expected one ground surface");
    };
    let multi_surface = ground
        .lod2_multi_surface()
        .and_then(|property| property.object())
        .expect("should have an LoD2 multi surface");
    let [member] = multi_surface.surface_member() else {
        panic!("expected one surface member");
    };
    let polygon = polygon(member.object().expect("inline"));
    assert_eq!(
        polygon.id().map(|id| id.as_str()),
        Some("DEBY_LOD2_4959457_2470b16f-99f0-43c3-9a27-bd4fc3822c91_2_poly")
    );
    let exterior = linear_ring(polygon.exterior().expect("should have an exterior"));
    assert_eq!(exterior.points().len(), 11);
    assert_close(exterior.area_3d(), 1371.825439453125);
    assert_close(exterior.length_3d(), 150.78554397170106);
    let [interior] = polygon.interior() else {
        panic!("expected one interior ring");
    };
    let interior = linear_ring(interior);
    assert_eq!(interior.points().len(), 4);
    assert_close(interior.area_3d(), 142.26318359375);
    assert_close(interior.length_3d(), 47.7096809282068);
    assert_close(
        polygon.area_3d().expect("should compute"),
        1229.562255859375,
    );
    assert_eq!(polygon.points().len(), 15);
    assert_envelope(
        polygon.compute_envelope(),
        (691009.16, 5335994.57, 515.042),
        (691054.07, 5336047.41, 515.042),
    );
    let triangulation = multi_surface.triangulate().expect("should triangulate");
    assert!(triangulation.skipped().is_empty());
    assert_eq!(triangulation.surface().triangles().len(), 15);
    assert_close(
        triangulation.surface().area_3d().expect("should compute"),
        1229.5620994984272,
    );
}

#[test]
fn composite_surface_and_patches() {
    let city_model = read(&fixture(OGC_ROAD_OVER_BRIDGE));
    let ground = all::<GroundSurface>(&city_model)
        .into_iter()
        .find(|ground| ground.feature_id().as_str() == "id_groundsurface1")
        .expect("should have the ground surface");
    let multi_surface = ground
        .lod2_multi_surface()
        .and_then(|property| property.object())
        .expect("should have an LoD2 multi surface");
    assert_eq!(
        multi_surface.id().map(|id| id.as_str()),
        Some("id_groundsurface1-0")
    );
    assert_close(
        multi_surface.area_3d().expect("should compute"),
        77500.15996032,
    );
    let [member] = multi_surface.surface_member() else {
        panic!("expected one surface member");
    };
    let kind = member.object().expect("inline");
    assert_eq!(kind.geometry_type(), GeometryType::CompositeSurface);
    let AbstractSurfaceKind::CompositeSurface(composite) = kind else {
        panic!("expected a composite surface");
    };
    assert_eq!(
        composite.id().map(|id| id.as_str()),
        Some("id_groundsurface1-1")
    );
    assert_close(composite.area_3d().expect("should compute"), 77500.15996032);
    assert_eq!(composite.points().len(), 6);
    assert_envelope(
        composite.compute_envelope(),
        (0.0, 0.0, 0.0),
        (393.7008, 196.8504, 0.0),
    );
    let triangulation = composite.triangulate().expect("should triangulate");
    assert!(triangulation.skipped().is_empty());
    assert_eq!(triangulation.surface().triangles().len(), 2);

    let ids = [
        "fme-gen-1a9ac79e-2880-47c7-b7c3-c9df5bc17447",
        "fme-gen-545ee504-7440-4cb6-8713-fc8ba21ac163",
    ];
    assert_eq!(composite.surface_member().len(), ids.len());
    for (member, id) in composite.surface_member().iter().zip(ids) {
        let kind = member.object().expect("inline");
        assert_eq!(kind.geometry_type(), GeometryType::Surface);
        let AbstractSurfaceKind::Surface(surface) = kind else {
            panic!("expected a surface");
        };
        assert_eq!(surface.id().map(|id| id.as_str()), Some(id));
        assert_close(surface.area_3d().expect("should compute"), 38750.07998016);
        let triangulation = surface.triangulate().expect("should triangulate");
        assert_eq!(triangulation.surface().triangles().len(), 1);
        let [AbstractSurfacePatchKind::PolygonPatch(patch)] = surface.patches() else {
            panic!("expected one polygon patch");
        };
        assert!(patch.interior().is_empty());
        let exterior = linear_ring(patch.exterior().expect("should have an exterior"));
        assert_eq!(exterior.points().len(), 3);
        assert_close(patch.area_3d().expect("should compute"), 38750.07998016);
        let triangulation = surface.patches()[0]
            .triangulate()
            .expect("should triangulate");
        assert_eq!(triangulation.surface().triangles().len(), 1);
    }
}

#[test]
fn triangle_patches() {
    let city_model = read(&fixture(OGC_GARAGE));
    let tin = all::<TinRelief>(&city_model)[0]
        .tin()
        .and_then(|property| property.object())
        .expect("should have a TIN");
    assert_eq!(tin.surface().patches().len(), 12);
    let triangle = tin.triangles()[0];
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
    let storey = all::<Storey>(&city_model)
        .into_iter()
        .find(|storey| storey.feature_id().as_str() == "storey1")
        .expect("should have the storey");
    let multi_surface = storey
        .lod2_multi_surface()
        .and_then(|property| property.object())
        .expect("should have an LoD2 multi surface");
    assert_eq!(multi_surface.surface_member().len(), 6);
    let error = multi_surface.area_3d().unwrap_err();
    assert!(
        matches!(error, egml::Error::UnresolvedSurfaceReference { .. }),
        "{error:?}"
    );
    assert!(
        error
            .to_string()
            .contains("#Wall_1_PolyID82397_997_453711_16336011"),
        "{error}"
    );
    assert_eq!(multi_surface.points().len(), 12);
    assert_envelope(
        multi_surface.compute_envelope(),
        (457841.1, 5439082.1, 111.1),
        (457853.9, 5439092.9, 113.9),
    );
    let triangulation = multi_surface.triangulate().expect("should triangulate");
    assert!(triangulation.skipped().is_empty());
    assert_eq!(triangulation.surface().triangles().len(), 6);
}

#[test]
fn triangulate_without_members() {
    let city_model = read(&fixture(FZK_LOD2));
    let solid = all::<Building>(&city_model)[0]
        .lod2_solid()
        .and_then(|property| property.object())
        .expect("should have an LoD2 solid");
    assert!(solid.points().is_empty());
    assert!(solid.compute_envelope().is_none());
    let error = solid.triangulate().unwrap_err();
    assert!(
        !matches!(
            error,
            egml::Error::UnresolvedSurfaceReference { .. }
                | egml::Error::UnresolvedCurveReference { .. }
        ),
        "{error:?}"
    );
    assert!(
        error.to_string().contains("requires at least 1 element"),
        "{error}"
    );
}
