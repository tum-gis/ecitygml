//! The cases of `crates/ecitygml/tests/conformance/tum-main-entrance.md`.

use crate::{assert_close, read};
use ecitygml_ffi::citygml::core::model::building::building::Building;
use ecitygml_ffi::citygml::core::model::common::feature_type::FeatureType;
use ecitygml_ffi::citygml::core::model::construction::enums::height_status_value::HeightStatusValue;
use ecitygml_ffi::citygml::core::model::construction::ground_surface::GroundSurface;
use ecitygml_ffi::citygml::core::model::construction::roof_surface::RoofSurface;
use ecitygml_ffi::citygml::core::model::construction::wall_surface::WallSurface;
use ecitygml_ffi::citygml::core::model::core::city_model::CityModel;
use ecitygml_ffi::citygml::core::model::core::refs::abstract_feature_kind_ref::AbstractFeatureKindRef;
use ecitygml_ffi::citygml::io::format::CitygmlFormat;
use ecitygml_ffi::citygml::io::gml::read::GmlReader;
use ecitygml_ffi::citygml::io::gml::write::GmlWriter;
use ecitygml_ffi::gml::core::model::geometry::aggregates::multi_surface_property::MultiSurfaceProperty;
use ecitygml_ffi::gml::core::model::geometry::direct_position::DirectPosition;

/// All items of a Diplomat iterator.
macro_rules! items {
    // A match keeps the temporaries the iterator borrows from alive.
    ($iterator:expr) => {
        match $iterator {
            mut iterator => std::iter::from_fn(|| iterator.next()).collect::<Vec<_>>(),
        }
    };
}

fn city_model() -> Box<CityModel> {
    read("tum-main-entrance", "TUM-Main-Entrance.gml")
}

fn features(city_model: &CityModel) -> Vec<Box<AbstractFeatureKindRef<'_>>> {
    items!(city_model.iter_features())
}

fn building(city_model: &CityModel) -> &Building {
    features(city_model)
        .iter()
        .find_map(|feature| Building::try_from(feature))
        .expect("should have a building")
}

fn feature_types(city_model: &CityModel) -> Vec<FeatureType> {
    features(city_model)
        .iter()
        .map(|feature| feature.feature_type())
        .collect()
}

/// The building's boundaries, as features; fails on a reference-only boundary.
fn boundaries(building: &Building) -> Vec<Box<AbstractFeatureKindRef<'_>>> {
    items!(building.boundaries())
        .into_iter()
        .map(|property| {
            assert!(property.href().is_none());
            AbstractFeatureKindRef::from_space_boundary(
                property.object().expect("should be inline"),
            )
        })
        .collect()
}

/// The area of an inline LoD2 multi surface.
fn lod2_area(property: Option<&MultiSurfaceProperty>) -> f64 {
    let property = property.expect("should have an LoD2 multi surface");
    assert!(property.href().is_none());
    property
        .object()
        .expect("should be inline")
        .area_3d()
        .expect("should compute")
}

fn assert_point_close(position: &DirectPosition, expected: (f64, f64, f64)) {
    assert_close(position.x(), expected.0);
    assert_close(position.y(), expected.1);
    assert_close(position.z(), expected.2);
}

/// `count` times the feature type.
fn repeated(feature_type: FeatureType, count: usize) -> Vec<FeatureType> {
    vec![feature_type; count]
}

#[test]
fn entrance_city_model() {
    use FeatureType::{Building, CityModel, GroundSurface, RoofSurface, WallSurface};
    let city_model = city_model();
    assert_eq!(city_model.city_objects_len(), 1);
    let envelope = city_model
        .bounded_by()
        .and_then(|shape| shape.envelope())
        .expect("should have an envelope");
    assert_point_close(envelope.lower_corner(), (689975.68, 5335962.63, 503.0));
    assert_point_close(envelope.upper_corner(), (692025.893, 5338012.713, 581.62));
    let expected = [
        vec![CityModel, Building],
        repeated(WallSurface, 10),
        vec![GroundSurface],
        repeated(WallSurface, 3),
        vec![RoofSurface, RoofSurface, WallSurface],
    ]
    .concat();
    assert_eq!(feature_types(&city_model), expected);
    assert_eq!(items!(city_model.iter_city_objects()).len(), 18);
}

#[test]
fn entrance_building_attributes() {
    let city_model = city_model();
    let building = building(&city_model);
    assert_eq!(building.feature_id().as_str(), "DEBY_LOD2_4959457");
    assert!(building.names().next().is_none());
    assert!(building.class().is_none());
    let functions = items!(building.functions());
    let [function] = functions[..] else {
        panic!("expected one function");
    };
    assert_eq!(function.value(), "31001_3020");
    assert!(building.usages().next().is_none());
    assert_eq!(building.roof_type().map(|r| r.value()), Some("1000"));
    assert_eq!(building.storeys_above_ground(), Some(4));
    assert_eq!(building.storeys_below_ground(), None);

    let heights = items!(building.heights());
    let [height] = heights[..] else {
        panic!("expected one height");
    };
    assert_eq!(height.high_reference().value(), "topOfConstruction");
    assert_eq!(height.low_reference().value(), "lowestGroundPoint");
    assert_eq!(height.status(), HeightStatusValue::Measured);
    assert_close(height.length().value(), 19.408);
    assert_eq!(height.length().uom(), "urn:adv:uom:m");

    let created = building
        .creation_date()
        .expect("should have a creation date");
    assert_eq!(
        (created.year(), created.month(), created.day()),
        (2025, 1, 2)
    );
    assert_eq!((created.hour(), created.minute()), (0, 0));
    assert_eq!(created.offset_seconds(), 3600);
    assert!(building.bounded_by().is_none());
    assert!(building.occupancies().next().is_none());
    assert!(building.building_subdivisions().next().is_none());
}

#[test]
fn entrance_external_reference() {
    let city_model = city_model();
    let references = items!(building(&city_model).external_references());
    let [reference] = references[..] else {
        panic!("expected one external reference");
    };
    assert_eq!(reference.target_resource(), "DEBYvAAAAABTMIyA");
}

#[test]
fn entrance_external_reference_details() {
    let city_model = city_model();
    let references = items!(building(&city_model).external_references());
    let [reference] = references[..] else {
        panic!("expected one external reference");
    };
    assert_eq!(
        reference.information_system(),
        Some("http://repository.gdi-de.org/schemas/adv/citygml/fdv/art.htm#_9100")
    );
    assert!(reference.relation_type().is_none());
}

#[test]
fn entrance_generic_attributes() {
    let city_model = city_model();
    let attributes: Vec<(&str, &str)> = items!(building(&city_model).generic_attributes())
        .into_iter()
        .map(|attribute| {
            let value = attribute
                .as_string()
                .expect("should be a string attribute")
                .value();
            (attribute.name(), value)
        })
        .collect();
    assert_eq!(
        attributes,
        [
            ("DatenquelleBodenhoehe", "1100"),
            ("DatenquelleDachhoehe", "1000"),
            ("DatenquelleLage", "1000"),
            ("Gemeindeschluessel", "09162000"),
            ("HoeheDach", "534.450"),
            ("HoeheGrund", "515.042"),
            ("Methode", "2000"),
            ("NiedrigsteTraufeDesGebaeudes", "527.312"),
            ("Grundrissaktualitaet", "2025-02-17"),
            ("Geometrietyp2DReferenz", "3000"),
        ]
    );
}

#[test]
fn entrance_boundaries() {
    use FeatureType::{GroundSurface as Ground, RoofSurface as Roof, WallSurface as Wall};
    let city_model = city_model();
    let boundaries = boundaries(building(&city_model));
    let expected = [
        repeated(Wall, 10),
        vec![Ground],
        repeated(Wall, 3),
        vec![Roof, Roof, Wall],
    ]
    .concat();
    assert_eq!(
        boundaries
            .iter()
            .map(|b| b.feature_type())
            .collect::<Vec<_>>(),
        expected
    );

    let walls: Vec<&WallSurface> = boundaries
        .iter()
        .filter_map(|b| WallSurface::try_from(b))
        .collect();
    assert_eq!(
        walls[0].feature_id().as_str(),
        "DEBY_LOD2_4959457_ca1db42f-9d12-4f41-972c-c7da1614f0a8_2"
    );
    assert!(walls[0].names().next().is_none());
    assert_close(
        walls
            .iter()
            .map(|w| lod2_area(w.lod2_multi_surface()))
            .sum(),
        3783.3908922901974,
    );

    let roofs: Vec<f64> = boundaries
        .iter()
        .filter_map(|b| RoofSurface::try_from(b))
        .map(|r| lod2_area(r.lod2_multi_surface()))
        .collect();
    let [first, second] = roofs[..] else {
        panic!("expected two roof surfaces");
    };
    assert_close(first, 250.233154296875);
    assert_close(second, 979.3291015625);
    assert_close(first + second, 1229.562255859375);

    let grounds: Vec<f64> = boundaries
        .iter()
        .filter_map(|b| GroundSurface::try_from(b))
        .map(|g| lod2_area(g.lod2_multi_surface()))
        .collect();
    let [ground] = grounds[..] else {
        panic!("expected one ground surface");
    };
    assert_close(ground, 1229.562255859375);
}

#[test]
fn entrance_wall_triangulation() {
    let city_model = city_model();
    let features = features(&city_model);
    let wall = features
        .iter()
        .find_map(|feature| WallSurface::try_from(feature))
        .expect("should have a wall surface");
    let multi_surface = wall
        .lod2_multi_surface()
        .and_then(|property| property.object())
        .expect("should have an LoD2 multi surface");
    assert_eq!(items!(multi_surface.surface_member()).len(), 1);
    assert_close(
        multi_surface.area_3d().expect("should compute"),
        546.6949745937537,
    );
    let triangulation = multi_surface.triangulate().expect("should triangulate");
    assert_eq!(items!(triangulation.surface().triangles()).len(), 4);
    assert!(!triangulation.has_skipped());
    assert_close(
        triangulation.surface().area_3d().expect("should compute"),
        546.6949742237184,
    );
}

#[test]
fn entrance_solid_unresolved() {
    let city_model = city_model();
    let property = building(&city_model)
        .lod2_solid()
        .expect("should have an LoD2 solid");
    assert!(property.href().is_none());
    let solid = property.object().expect("should be inline");
    let shell = solid.exterior().expect("should have an exterior shell");
    let members = items!(shell.members());
    assert_eq!(members.len(), 17);
    assert!(members.iter().all(|member| member.object().is_none()));
    assert!(solid.volume_3d().is_err());
}

#[test]
fn entrance_round_trip() {
    let city_model = city_model();
    let mut writer = GmlWriter::new(CitygmlFormat::Gml);
    writer
        .finish(&city_model)
        .unwrap_or_else(|_| panic!("should write"));
    let written = GmlReader::new(writer.data(), CitygmlFormat::Gml)
        .finish()
        .unwrap_or_else(|_| panic!("should read"));
    assert_eq!(feature_types(&written), feature_types(&city_model));
    assert_eq!(
        building(&written).feature_id().as_str(),
        "DEBY_LOD2_4959457"
    );
    let boundary_ids = |model: &CityModel| -> Vec<String> {
        items!(building(model).boundaries())
            .into_iter()
            .map(|p| p.object().expect("inline").feature_id().as_str().to_owned())
            .collect()
    };
    assert_eq!(boundary_ids(&written), boundary_ids(&city_model));
}
