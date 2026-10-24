//! The cases of `crates/ecitygml/tests/conformance/tum-main-entrance.md`.

use crate::{assert_close, read};
use ecitygml::io::{CitygmlFormat, GmlReader, GmlWriter};
use ecitygml::model::building::{AsAbstractBuilding, Building};
use ecitygml::model::common::{FeatureType, HasFeatureType, IterFeatures};
use ecitygml::model::construction::enums::HeightStatusValue;
use ecitygml::model::construction::{
    AsAbstractConstruction, GroundSurface, RoofSurface, WallSurface,
};
use ecitygml::model::core::refs::AbstractFeatureKindRef;
use ecitygml::model::core::{
    AsAbstractCityObject, AsAbstractFeature, AsAbstractFeatureWithLifespan, AsAbstractSpace,
    AsAbstractThematicSurface, CityModel,
};
use ecitygml::model::generics::GenericAttributeKind;
use egml::model::base::{AsAbstractGml, HasAssociationAttributes};
use egml::model::common::Triangulate;
use egml::model::feature::AsAbstractFeature as _;
use egml::model::geometry::DirectPosition;

fn city_model() -> CityModel {
    read("tum-main-entrance", "TUM-Main-Entrance.gml")
}

fn building(city_model: &CityModel) -> &Building {
    city_model
        .iter_features()
        .find_map(|feature| feature.try_into().ok())
        .expect("should have a building")
}

fn feature_types(city_model: &CityModel) -> Vec<FeatureType> {
    city_model
        .iter_features()
        .map(|feature| feature.feature_type())
        .collect()
}

/// The building's boundaries, as features; fails on a reference-only boundary.
fn boundaries(building: &Building) -> Vec<AbstractFeatureKindRef<'_>> {
    building
        .boundaries()
        .iter()
        .map(|property| {
            assert!(property.href().is_none());
            AbstractFeatureKindRef::from(property.object().expect("should be inline"))
        })
        .collect()
}

/// The area of an inline LoD2 multi surface of a thematic surface.
fn lod2_area(surface: &impl AsAbstractThematicSurface) -> f64 {
    let property = surface
        .lod2_multi_surface()
        .expect("should have an LoD2 multi surface");
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
    assert_eq!(city_model.city_object_members_len(), 1);
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
    assert_eq!(city_model.iter_city_objects().count(), 18);
}

#[test]
fn entrance_building_attributes() {
    let city_model = city_model();
    let building = building(&city_model);
    assert_eq!(building.feature_id().to_string(), "DEBY_LOD2_4959457");
    assert!(building.names().is_empty());
    assert!(building.class().is_none());
    let [function] = building.functions() else {
        panic!("expected one function, got {:?}", building.functions());
    };
    assert_eq!(function.value(), "31001_3020");
    assert!(building.usages().is_empty());
    assert_eq!(building.roof_type().map(|r| r.value()), Some("1000"));
    assert_eq!(building.storeys_above_ground(), Some(4));
    assert_eq!(building.storeys_below_ground(), None);

    let [height] = building.heights() else {
        panic!("expected one height, got {:?}", building.heights());
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
    assert!(building.occupancies().is_empty());
    assert!(building.building_subdivisions().is_empty());
}

#[test]
fn entrance_external_reference() {
    let city_model = city_model();
    let [reference] = building(&city_model).external_references() else {
        panic!("expected one external reference");
    };
    assert_eq!(reference.target_resource.as_str(), "DEBYvAAAAABTMIyA");
}

#[test]
fn entrance_external_reference_details() {
    let city_model = city_model();
    let [reference] = building(&city_model).external_references() else {
        panic!("expected one external reference");
    };
    assert_eq!(
        reference
            .information_system
            .as_ref()
            .map(|uri| uri.as_str()),
        Some("http://repository.gdi-de.org/schemas/adv/citygml/fdv/art.htm#_9100")
    );
    assert!(reference.relation_type.is_none());
}

#[test]
fn entrance_generic_attributes() {
    let city_model = city_model();
    let attributes: Vec<(&str, &str)> = building(&city_model)
        .generic_attributes()
        .iter()
        .map(|attribute| match attribute {
            GenericAttributeKind::StringAttribute(a) => (a.name.as_str(), a.value.as_str()),
            other => panic!("expected a string attribute, got {other:?}"),
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
        .filter_map(|b| (*b).try_into().ok())
        .collect();
    assert_eq!(
        walls[0].feature_id().to_string(),
        "DEBY_LOD2_4959457_ca1db42f-9d12-4f41-972c-c7da1614f0a8_2"
    );
    assert!(walls[0].names().is_empty());
    assert_close(
        walls.iter().map(|w| lod2_area(*w)).sum(),
        3783.3908922901974,
    );

    let roofs: Vec<f64> = boundaries
        .iter()
        .filter_map(|b| <&RoofSurface>::try_from(*b).ok())
        .map(lod2_area)
        .collect();
    let [first, second] = roofs[..] else {
        panic!("expected two roof surfaces");
    };
    assert_close(first, 250.233154296875);
    assert_close(second, 979.3291015625);
    assert_close(first + second, 1229.562255859375);

    let grounds: Vec<f64> = boundaries
        .iter()
        .filter_map(|b| <&GroundSurface>::try_from(*b).ok())
        .map(lod2_area)
        .collect();
    let [ground] = grounds[..] else {
        panic!("expected one ground surface");
    };
    assert_close(ground, 1229.562255859375);
}

#[test]
fn entrance_wall_triangulation() {
    let city_model = city_model();
    let wall: &WallSurface = city_model
        .iter_features()
        .find_map(|feature| feature.try_into().ok())
        .expect("should have a wall surface");
    let multi_surface = wall
        .lod2_multi_surface()
        .and_then(|property| property.object())
        .expect("should have an LoD2 multi surface");
    assert_eq!(multi_surface.surface_member().len(), 1);
    assert_close(
        multi_surface.area_3d().expect("should compute"),
        546.6949745937537,
    );
    let triangulation = multi_surface.triangulate().expect("should triangulate");
    assert_eq!(triangulation.surface().triangles().len(), 4);
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
    assert_eq!(shell.members().len(), 17);
    assert!(
        shell
            .members()
            .iter()
            .all(|member| member.object().is_none())
    );
    assert!(solid.volume_3d().is_err());
}

#[test]
fn entrance_round_trip() {
    let city_model = city_model();
    let mut data = Vec::new();
    GmlWriter::new(&mut data, CitygmlFormat::Gml)
        .finish(&city_model)
        .expect("should write");
    let written = GmlReader::new(data.as_slice(), CitygmlFormat::Gml)
        .finish()
        .expect("should read");
    assert_eq!(feature_types(&written), feature_types(&city_model));
    assert_eq!(
        building(&written).feature_id().to_string(),
        "DEBY_LOD2_4959457"
    );
    let boundary_ids = |model: &CityModel| -> Vec<String> {
        boundaries(building(model))
            .iter()
            .map(|b| b.feature_id().to_string())
            .collect()
    };
    assert_eq!(boundary_ids(&written), boundary_ids(&city_model));
}
