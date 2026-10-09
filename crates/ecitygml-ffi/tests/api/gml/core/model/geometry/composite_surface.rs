//! `CompositeSurface`, `Surface` with its patches (`PolygonPatch`, `Triangle`), and ring curve members.

use crate::*;

use ecitygml_ffi::citygml::core::model::building::building::Building;
use ecitygml_ffi::citygml::core::model::construction::wall_surface::WallSurface;
use ecitygml_ffi::citygml::core::model::core::refs::abstract_feature_kind_ref::AbstractFeatureKindRef;
use ecitygml_ffi::gml::core::model::common::geometry_type::GeometryType;
use ecitygml_ffi::gml::core::model::geometry::complexes::composite_surface::CompositeSurface;
use ecitygml_ffi::gml::core::model::geometry::primitives::abstract_ring_kind::AbstractRingKind;
use ecitygml_ffi::gml::core::model::geometry::primitives::line_string::LineString;
use ecitygml_ffi::gml::core::model::geometry::primitives::linear_ring::LinearRing;
use ecitygml_ffi::gml::core::model::geometry::primitives::polygon::Polygon;
use ecitygml_ffi::gml::core::model::geometry::primitives::polygon_patch::PolygonPatch;
use ecitygml_ffi::gml::core::model::geometry::primitives::surface::Surface;
use ecitygml_ffi::gml::core::model::geometry::primitives::triangle::Triangle;

fn ring(z: f64) -> String {
    format!(
        "<gml:exterior><gml:LinearRing><gml:posList>0 0 {z} 1 0 {z} 1 1 {z} 0 0 {z}</gml:posList></gml:LinearRing></gml:exterior>"
    )
}

fn polygon(z: f64) -> String {
    format!("<gml:Polygon>{}</gml:Polygon>", ring(z))
}

fn member(geometry: &str) -> String {
    format!("<gml:surfaceMember>{geometry}</gml:surfaceMember>")
}

/// FZK LoD1 with a lod2 multi surface (and optionally a lod2 multi curve) on the building.
fn read_with(surface_members: &str, curve_members: &str) -> Box<CityModel> {
    let curve = if curve_members.is_empty() {
        String::new()
    } else {
        format!("<lod2MultiCurve><gml:MultiCurve>{curve_members}</gml:MultiCurve></lod2MultiCurve>")
    };
    read_modified(
        "<lod1Solid>",
        &format!(
            "<lod2MultiSurface><gml:MultiSurface>{surface_members}</gml:MultiSurface></lod2MultiSurface>{curve}<lod1Solid>"
        ),
    )
}

fn first_building(city_model: &CityModel) -> &Building {
    let mut features = city_model.iter_features();
    std::iter::from_fn(|| features.next())
        .find_map(|feature| Building::try_from(&feature))
        .unwrap()
}

/// The first exterior z of each polygon member, flattening composite surfaces.
fn z_values(
    members: &mut ecitygml_ffi::gml::core::model::geometry::primitives::abstract_surface_property::AbstractSurfacePropertyIterator,
) -> Vec<f64> {
    let mut result = Vec::new();
    while let Some(member) = members.next() {
        let surface = member.object().unwrap();
        if let Some(polygon) = Polygon::try_from(surface) {
            result.push(polygon.exterior().unwrap().points().next().unwrap().z());
        } else if let Some(composite) = CompositeSurface::try_from(surface) {
            result.extend(z_values(&mut composite.surface_member()));
        }
    }
    result
}

#[test]
fn composite_surface_members() {
    let composite = format!(
        "<gml:CompositeSurface>{}{}</gml:CompositeSurface>",
        member(&polygon(2.0)),
        member(&polygon(3.0))
    );
    let city_model = read_with(&(member(&polygon(1.0)) + &member(&composite)), "");
    let multi_surface = first_building(&city_model)
        .lod2_multi_surface()
        .unwrap()
        .object()
        .unwrap();
    assert_eq!(
        z_values(&mut multi_surface.surface_member()),
        [1.0, 2.0, 3.0]
    );

    let mut members = multi_surface.surface_member();
    members.next();
    let surface = members.next().unwrap().object().unwrap();
    assert_eq!(surface.geometry_type(), GeometryType::CompositeSurface);
    let composite = CompositeSurface::try_from(surface).unwrap();
    assert!(Polygon::try_from(surface).is_none());
    assert!((composite.area_3d().unwrap() - 1.0).abs() < 1e-9);
    let mut points = composite.points();
    assert_eq!(std::iter::from_fn(|| points.next()).count(), 6);
    assert!(composite.compute_envelope().is_some());
}

#[test]
fn surface_patches() {
    let surface = format!(
        "<gml:Surface><gml:patches><gml:PolygonPatch>{}</gml:PolygonPatch><gml:Triangle>{}</gml:Triangle></gml:patches></gml:Surface>",
        ring(4.0),
        ring(5.0)
    );
    let city_model = read_with(&member(&surface), "");
    let multi_surface = first_building(&city_model)
        .lod2_multi_surface()
        .unwrap()
        .object()
        .unwrap();
    let kind = multi_surface
        .surface_member()
        .next()
        .unwrap()
        .object()
        .unwrap();
    assert_eq!(kind.geometry_type(), GeometryType::Surface);
    let surface = Surface::try_from(kind).unwrap();
    assert!((surface.area_3d().unwrap() - 1.0).abs() < 1e-9);

    let mut patches = surface.patches();
    let first = patches.next().unwrap();
    let second = patches.next().unwrap();
    assert!(patches.next().is_none());

    let patch = PolygonPatch::try_from(first).unwrap();
    assert!(Triangle::try_from(first).is_none());
    assert_eq!(patch.exterior().unwrap().points().next().unwrap().z(), 4.0);
    assert!(patch.interior().next().is_none());
    assert!((patch.area_3d().unwrap() - 0.5).abs() < 1e-9);

    let triangle = Triangle::try_from(second).unwrap();
    assert_eq!(triangle.a().z(), 5.0);
    assert_eq!((triangle.b().x(), triangle.c().y()), (1.0, 1.0));
    assert!((triangle.area() - 0.5).abs() < 1e-9);
    assert_eq!(
        triangle.exterior().geometry_type(),
        GeometryType::LinearRing
    );
    assert!((second.area_3d().unwrap() - 0.5).abs() < 1e-9);
}

#[test]
fn ring_curve_members() {
    let line = "<gml:LineString><gml:posList>0 0 0 1 1 1</gml:posList></gml:LineString>";
    let linear_ring =
        "<gml:LinearRing><gml:posList>0 0 0 1 0 0 1 1 0 0 0 0</gml:posList></gml:LinearRing>";
    let city_model = read_with(
        &member(&polygon(1.0)),
        &format!(
            "<gml:curveMember>{line}</gml:curveMember><gml:curveMember>{linear_ring}</gml:curveMember>"
        ),
    );
    let multi_curve = first_building(&city_model)
        .lod2_multi_curve()
        .unwrap()
        .object()
        .unwrap();
    let mut members = multi_curve.curve_member();
    let line = members.next().unwrap().object().unwrap();
    let ring = members.next().unwrap().object().unwrap();
    assert!(AbstractRingKind::try_from(line).is_none());
    let mut line_points = LineString::try_from(line).unwrap().points();
    assert_eq!(std::iter::from_fn(|| line_points.next()).count(), 2);

    let ring = AbstractRingKind::try_from(ring).unwrap();
    // egml stores rings without the repeated closing position.
    let mut points = LinearRing::try_from(ring).unwrap().points();
    assert_eq!(std::iter::from_fn(|| points.next()).count(), 3);
    assert!((ring.length_3d() - (2.0 + 2f64.sqrt())).abs() < 1e-9);
}

#[test]
fn fzk_lod3_wall_composite_surfaces() {
    let path = format!("{FIXTURES}FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml");
    let city_model = read(path.as_bytes()).unwrap();
    let mut boundaries = first_building(&city_model).boundaries();
    let wall = std::iter::from_fn(|| boundaries.next())
        .find_map(|property| {
            let feature = AbstractFeatureKindRef::from_space_boundary(property.object().unwrap());
            WallSurface::try_from(&feature)
        })
        .unwrap();
    let multi_surface = wall.lod3_multi_surface().unwrap().object().unwrap();
    let first = multi_surface
        .surface_member()
        .next()
        .unwrap()
        .object()
        .unwrap();
    let composite = CompositeSurface::try_from(first).unwrap();
    let polygon = composite.surface_member().next().unwrap().object().unwrap();
    let point = Polygon::try_from(polygon)
        .unwrap()
        .exterior()
        .unwrap()
        .points()
        .next()
        .unwrap();
    assert_eq!(
        (point.x(), point.y(), point.z()),
        (457842.0, 5439088.49240388, 115.913175911167)
    );
}
