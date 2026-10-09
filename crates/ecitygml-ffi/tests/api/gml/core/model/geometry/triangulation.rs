//! `triangulate()`, `Triangulation` and `TriangulatedSurface`.

use crate::*;

use ecitygml_ffi::citygml::core::model::building::building::Building;
use ecitygml_ffi::gml::core::model::geometry::primitives::polygon::Polygon;
use ecitygml_ffi::gml::core::model::geometry::primitives::surface::Surface;
use ecitygml_ffi::gml::core::model::geometry::primitives::triangulated_surface::TriangulatedSurface;

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

/// FZK LoD1 with a lod2 multi surface of the given members on the building.
fn read_with(surface_members: &str) -> Box<CityModel> {
    read_modified(
        "<lod1Solid>",
        &format!(
            "<lod2MultiSurface><gml:MultiSurface>{surface_members}</gml:MultiSurface></lod2MultiSurface><lod1Solid>"
        ),
    )
}

fn first_building(city_model: &CityModel) -> &Building {
    let mut features = city_model.iter_features();
    std::iter::from_fn(|| features.next())
        .find_map(|feature| Building::try_from(&feature))
        .unwrap()
}

fn triangle_count(surface: &TriangulatedSurface) -> usize {
    let mut triangles = surface.triangles();
    std::iter::from_fn(|| triangles.next()).count()
}

#[test]
fn solid() {
    let path = format!("{FIXTURES}FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml");
    let city_model = read(path.as_bytes()).unwrap();
    let solid = first_building(&city_model)
        .lod1_solid()
        .unwrap()
        .object()
        .unwrap();

    let triangulation = solid.triangulate().unwrap();
    assert!(!triangulation.has_skipped());
    assert!(triangulation.skipped().next().is_none());
    let surface = triangulation.surface();
    assert_eq!(triangle_count(surface), 12);
    // 2 * (12 * 10 + 12 * 6.51769 + 10 * 6.51769)
    assert!((surface.area_3d().unwrap() - 526.77836).abs() < 1e-3);
    assert!(surface.compute_envelope().is_some());
    let mut points = surface.points();
    assert_eq!(std::iter::from_fn(|| points.next()).count(), 36);

    let triangle = surface.triangles().next().unwrap();
    assert!(triangle.area() > 0.0);
    assert_eq!(triangle.a().z(), 111.8);

    // The shell and its polygons triangulate the same.
    let shell = solid.exterior().unwrap();
    assert_eq!(triangle_count(shell.triangulate().unwrap().surface()), 12);
    let mut members = shell.members();
    let polygon = Polygon::try_from(members.next().unwrap().object().unwrap()).unwrap();
    assert_eq!(triangle_count(polygon.triangulate().unwrap().surface()), 2);
}

#[test]
fn composite_surfaces_and_patches() {
    let composite = format!(
        "<gml:CompositeSurface>{}{}</gml:CompositeSurface>",
        member(&polygon(2.0)),
        member(&polygon(3.0))
    );
    let surface = format!(
        "<gml:Surface><gml:patches><gml:PolygonPatch>{}</gml:PolygonPatch><gml:Triangle>{}</gml:Triangle></gml:patches></gml:Surface>",
        ring(4.0),
        ring(5.0)
    );
    let city_model = read_with(&(member(&composite) + &member(&surface)));
    let multi_surface = first_building(&city_model)
        .lod2_multi_surface()
        .unwrap()
        .object()
        .unwrap();
    let triangulation = multi_surface.triangulate().unwrap();
    assert!(!triangulation.has_skipped());
    assert_eq!(triangle_count(triangulation.surface()), 4);

    let mut members = multi_surface.surface_member();
    let composite = members.next().unwrap().object().unwrap();
    assert_eq!(
        triangle_count(composite.triangulate().unwrap().surface()),
        2
    );
    let surface = Surface::try_from(members.next().unwrap().object().unwrap()).unwrap();
    assert_eq!(triangle_count(surface.triangulate().unwrap().surface()), 2);
    let mut patches = surface.patches();
    let patch = patches.next().unwrap();
    assert_eq!(triangle_count(patch.triangulate().unwrap().surface()), 1);
}

#[test]
fn skipped_members() {
    // Four collinear vertices: no triangles, which egml reports as a skipped member.
    let collinear = "<gml:Polygon><gml:exterior><gml:LinearRing><gml:posList>0 0 9 1 0 9 2 0 9 3 0 9 0 0 9</gml:posList></gml:LinearRing></gml:exterior></gml:Polygon>";
    let city_model = read_with(&(member(&polygon(1.0)) + &member(collinear)));
    let multi_surface = first_building(&city_model)
        .lod2_multi_surface()
        .unwrap()
        .object()
        .unwrap();
    let triangulation = multi_surface.triangulate().unwrap();
    assert_eq!(triangle_count(triangulation.surface()), 1);
    assert!(triangulation.has_skipped());
    let mut skipped = triangulation.skipped();
    let error = skipped.next().unwrap();
    assert!(skipped.next().is_none());
    assert_eq!(error.kind(), ErrorKind::InvalidArgument);
    assert!(!written(|w| error.message(w)).is_empty());
}

#[test]
fn href_only_members_are_left_out() {
    // As in egml, members that are only an `xlink:href` are left out, without a skipped entry.
    let city_model = read_with(
        &(member(&polygon(1.0)) + "<gml:surfaceMember xlink:href=\"#missing_polygon\"/>"),
    );
    let multi_surface = first_building(&city_model)
        .lod2_multi_surface()
        .unwrap()
        .object()
        .unwrap();
    let triangulation = multi_surface.triangulate().unwrap();
    assert_eq!(triangle_count(triangulation.surface()), 1);
    assert!(!triangulation.has_skipped());
}

#[test]
fn triangulated_surface_member() {
    let tin = format!(
        "<gml:TriangulatedSurface><gml:patches><gml:Triangle>{}</gml:Triangle><gml:Triangle>{}</gml:Triangle></gml:patches></gml:TriangulatedSurface>",
        ring(6.0),
        ring(7.0)
    );
    let city_model = read_with(&member(&tin));
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
    assert!(Polygon::try_from(kind).is_none());
    let tin = TriangulatedSurface::try_from(kind).unwrap();
    assert_eq!(triangle_count(tin), 2);
    assert!((tin.area_3d().unwrap() - 1.0).abs() < 1e-9);
    let mut patches = tin.surface().patches();
    assert_eq!(std::iter::from_fn(|| patches.next()).count(), 2);
    assert_eq!(triangle_count(kind.triangulate().unwrap().surface()), 2);
}
