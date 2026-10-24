//! The cases of `crates/ecitygml/tests/conformance/fzk-haus-citygml-3.0.md`.

use crate::{assert_close, read};
use ecitygml::io::{CitygmlFormat, GmlReader, GmlWriter};
use ecitygml::model::building::{
    AsAbstractBuilding, AsAbstractBuildingSubdivision, Building, Storey,
};
use ecitygml::model::common::{FeatureType, HasFeatureType, IterFeatures};
use ecitygml::model::construction::AsAbstractConstruction;
use ecitygml::model::construction::enums::HeightStatusValue;
use ecitygml::model::core::refs::AbstractFeatureKindRef;
use ecitygml::model::core::{
    AbstractPointCloudKind, AbstractSpaceBoundaryKind, AsAbstractCityObject, AsAbstractFeature,
    AsAbstractSpace, AsAbstractThematicSurface, CityModel,
};
use ecitygml::model::generics::GenericAttributeKind;
use egml::model::base::{AsAbstractGml, HasAssociationAttributes};
use egml::model::feature::AsAbstractFeature as _;
use egml::model::geometry::DirectPosition;
use std::collections::BTreeMap;

const DATASET: &str = "fzk-haus-citygml-3.0";

fn building(city_model: &CityModel) -> &Building {
    city_model
        .iter_features()
        .find_map(|feature| feature.try_into().ok())
        .expect("should have a building")
}

fn storeys(city_model: &CityModel) -> Vec<&Storey> {
    city_model
        .iter_features()
        .filter_map(|feature| feature.try_into().ok())
        .collect()
}

fn first_name(feature: &impl AsAbstractGml) -> &str {
    feature.names().first().expect("should have a name").value()
}

fn feature_types(city_model: &CityModel) -> Vec<FeatureType> {
    city_model
        .iter_features()
        .map(|feature| feature.feature_type())
        .collect()
}

/// The number of features per feature type, over `iter_features`.
fn feature_type_counts(city_model: &CityModel) -> BTreeMap<FeatureType, usize> {
    let mut counts = BTreeMap::new();
    for feature_type in feature_types(city_model) {
        *counts.entry(feature_type).or_default() += 1;
    }
    counts
}

fn assert_point_close(position: &DirectPosition, expected: (f64, f64, f64)) {
    assert_close(position.x(), expected.0);
    assert_close(position.y(), expected.1);
    assert_close(position.z(), expected.2);
}

fn assert_city_model(city_model: &CityModel, lower: (f64, f64, f64), upper: (f64, f64, f64)) {
    assert_eq!(city_model.city_object_members_len(), 1);
    let envelope = city_model
        .bounded_by()
        .and_then(|shape| shape.envelope())
        .expect("should have an envelope");
    assert_point_close(envelope.lower_corner(), lower);
    assert_point_close(envelope.upper_corner(), upper);
}

/// The one height of the storey examples' buildings.
fn assert_height(building: &Building) {
    let [height] = building.heights() else {
        panic!("expected one height, got {:?}", building.heights());
    };
    assert_eq!(height.high_reference().value(), "highestRoofEdge");
    assert_eq!(height.low_reference().value(), "lowestGroundPoint");
    assert_eq!(height.status(), HeightStatusValue::Measured);
    assert_close(height.length().value(), 6.52);
    assert_eq!(height.length().uom(), "urn:adv:uom:m");
}

/// The one occupancy of the storey examples' buildings.
fn assert_occupancy(building: &Building) {
    let [occupancy] = building.occupancies() else {
        panic!("expected one occupancy, got {:?}", building.occupancies());
    };
    assert_eq!(occupancy.number_of_occupants(), 2);
}

/// The storeys' first names and classes.
fn assert_storeys(city_model: &CityModel, classes: [Option<&str>; 2]) {
    let storeys = storeys(city_model);
    assert_eq!(
        storeys.iter().map(|s| first_name(*s)).collect::<Vec<_>>(),
        ["Ground Floor", "Second Floor"]
    );
    assert_eq!(
        storeys
            .iter()
            .map(|s| s.class().map(|class| class.value()))
            .collect::<Vec<_>>(),
        classes
    );
}

/// A storey's boundaries, as thematic surfaces; fails on a reference-only boundary or another kind of boundary.
fn thematic_surfaces(storey: &Storey) -> Vec<&ecitygml::model::core::AbstractThematicSurfaceKind> {
    storey
        .boundaries()
        .iter()
        .map(|property| {
            assert!(property.href().is_none());
            match property.object().expect("should be inline") {
                AbstractSpaceBoundaryKind::AbstractThematicSurfaceKind(surface) => surface,
                other => panic!("expected a thematic surface, got {other:?}"),
            }
        })
        .collect()
}

/// Writes the city model and reads it back; asserts the same feature types in the same order and the building's id.
fn assert_round_trip(city_model: &CityModel, building_id: &str) {
    let mut data = Vec::new();
    GmlWriter::new(&mut data, CitygmlFormat::Gml)
        .finish(city_model)
        .expect("should write");
    let written = GmlReader::new(data.as_slice(), CitygmlFormat::Gml)
        .finish()
        .expect("should read");
    assert_eq!(feature_types(&written), feature_types(city_model));
    assert_eq!(building(&written).feature_id().to_string(), building_id);
}

/// Writes the city model as CityGML and reads it back.
fn round_trip(city_model: &CityModel) -> CityModel {
    let mut data = Vec::new();
    GmlWriter::new(&mut data, CitygmlFormat::Gml)
        .finish(city_model)
        .expect("should write");
    GmlReader::new(data.as_slice(), CitygmlFormat::Gml)
        .finish()
        .expect("should read")
}

fn assert_storey_details(city_model: &CityModel) {
    let storeys = storeys(city_model);
    let elements: Vec<usize> = storeys
        .iter()
        .map(|storey| storey.building_constructive_elements().len())
        .collect();
    assert_eq!(elements, [5, 6]);
    let sort_keys: Vec<Option<f64>> = storeys.iter().map(|storey| storey.sort_key()).collect();
    assert_eq!(sort_keys, [Some(1.0), Some(2.0)]);
    let elevations: Vec<Vec<(&str, &[f64])>> = storeys
        .iter()
        .map(|storey| {
            storey
                .elevations()
                .iter()
                .map(|elevation| {
                    (
                        elevation.elevation_reference().value(),
                        elevation.elevation_value().coordinates(),
                    )
                })
                .collect()
        })
        .collect();
    assert_eq!(
        elevations,
        [
            vec![("lowestGroundPoint", [0.0].as_slice())],
            vec![("lowestGroundPoint", [2.7].as_slice())]
        ]
    );
    assert!(building(city_model).elevations().is_empty());
}

fn assert_storey_rooms(city_model: &CityModel) {
    let rooms: Vec<usize> = storeys(city_model)
        .iter()
        .map(|storey| storey.building_rooms().len())
        .collect();
    assert_eq!(rooms, [6, 1]);
}

/// Per boundary of the storeys, in document order: the qualified area (value, unit, type of area) and the number of
/// points of the point cloud.
fn point_cloud_surfaces(city_model: &CityModel) -> Vec<(f64, String, String, usize)> {
    storeys(city_model)
        .into_iter()
        .flat_map(|storey| storey.boundaries())
        .map(|boundary| {
            let Some(AbstractSpaceBoundaryKind::AbstractThematicSurfaceKind(surface)) =
                boundary.object()
            else {
                panic!("expected an inline thematic surface");
            };
            let [area] = surface.areas() else {
                panic!("expected one qualified area, got {:?}", surface.areas());
            };
            let AbstractPointCloudKind::PointCloud(point_cloud) = surface
                .point_cloud()
                .and_then(|property| property.object())
                .expect("should have a point cloud");
            let points = point_cloud
                .points()
                .and_then(|property| property.object())
                .and_then(|multi_point| multi_point.point_members())
                .map_or(0, |members| members.objects().len());
            (
                area.area().value(),
                area.area().uom().to_string(),
                area.type_of_area().value().to_string(),
                points,
            )
        })
        .collect()
}

fn assert_point_cloud_surfaces(city_model: &CityModel) {
    let expected = [
        (120.0, 40),
        (29.0, 20),
        (34.8, 20),
        (29.0, 20),
        (34.8, 20),
        (69.28, 30),
        (69.28, 30),
        (8.77, 10),
        (21.74, 21),
        (21.74, 20),
        (8.77, 10),
    ];
    let surfaces = point_cloud_surfaces(city_model);
    assert_eq!(surfaces.len(), expected.len());
    for ((area, uom, type_of_area, points), (expected_area, expected_points)) in
        surfaces.iter().zip(expected)
    {
        assert_close(*area, expected_area);
        assert_eq!((uom.as_str(), type_of_area.as_str()), ("m2", "gross"));
        assert_eq!(*points, expected_points);
    }
}

mod construction {
    use super::*;

    const BUILDING_ID: &str = "_FZK-Haus-Storey-Construction_BD.DX9Xm6VLbbyLGAxG2v86";

    fn city_model() -> CityModel {
        read(
            DATASET,
            "01-FZK-Haus-LoD2-Tex-Storey-Construction-CG30-V01.gml",
        )
    }

    #[test]
    fn construction_city_model() {
        use FeatureType::{
            Appearance, Building, BuildingConstructiveElement, CityModel, ParameterizedTexture,
            Storey, X3DMaterial,
        };
        let city_model = city_model();
        assert_city_model(
            &city_model,
            (458899.5, 5438784.5, 113.5),
            (458912.5, 5438795.5, 120.017691),
        );
        let expected = [
            vec![CityModel, Building, Storey],
            vec![BuildingConstructiveElement; 5],
            vec![Storey],
            vec![BuildingConstructiveElement; 6],
            vec![Appearance],
            vec![ParameterizedTexture; 5],
            vec![X3DMaterial; 5],
        ]
        .concat();
        assert_eq!(feature_types(&city_model), expected);
        assert_eq!(city_model.iter_city_objects().count(), 14);
    }

    #[test]
    fn construction_building() {
        let city_model = city_model();
        let building = building(&city_model);
        assert_eq!(building.feature_id().to_string(), BUILDING_ID);
        assert_eq!(first_name(building), "KIT FZK-Haus");
        assert_eq!(building.names().len(), 1);
        assert!(building.class().is_none());
        assert_eq!(
            building
                .functions()
                .iter()
                .map(|f| f.value())
                .collect::<Vec<_>>(),
            ["31001_1000"]
        );
        assert!(building.usages().is_empty());
        assert_eq!(building.roof_type().map(|r| r.value()), Some("3100"));
        assert_eq!(building.storeys_above_ground(), None);
        assert_eq!(building.storeys_below_ground(), None);
        assert_height(building);
        assert_occupancy(building);
        assert!(building.boundaries().is_empty());
        assert!(building.generic_attributes().is_empty());
        assert!(building.lod2_solid().is_none());
        assert!(building.lod2_multi_surface().is_none());
    }

    #[test]
    fn construction_storeys() {
        let city_model = city_model();
        let subdivisions = building(&city_model).building_subdivisions();
        assert_eq!(subdivisions.len(), 2);
        for subdivision in subdivisions {
            assert!(subdivision.href().is_none());
            let object = subdivision.object().expect("should be inline");
            assert_eq!(
                AbstractFeatureKindRef::from(object).feature_type(),
                FeatureType::Storey
            );
        }
        assert_storeys(
            &city_model,
            [Some("Entrance Floor"), Some("non Entrance Floor")],
        );
        for storey in storeys(&city_model) {
            assert!(storey.functions().is_empty());
            assert!(storey.usages().is_empty());
            assert!(storey.boundaries().is_empty());
            assert!(storey.lod2_solid().is_none());
        }
    }

    #[test]
    fn construction_storey_details() {
        let city_model = city_model();
        assert_storey_details(&city_model);
        assert_storey_details(&round_trip(&city_model));
    }

    #[test]
    fn construction_round_trip() {
        assert_round_trip(&city_model(), BUILDING_ID);
    }
}

mod interior {
    use super::*;

    const BUILDING_ID: &str = "KIT-Test-Building-01";

    fn city_model() -> CityModel {
        read(
            DATASET,
            "04-FZK-Haus-LoD2-Tex-Storey-CG30-V01-InteriorSurface.gml",
        )
    }

    #[test]
    fn interior_city_model() {
        use FeatureType::*;
        let city_model = city_model();
        assert_city_model(
            &city_model,
            (458900.0, 5438785.0, 113.5),
            (458912.0, 5438795.0, 120.017691),
        );
        assert_eq!(feature_types(&city_model).len(), 77);
        assert_eq!(
            feature_type_counts(&city_model),
            BTreeMap::from([
                (CityModel, 1),
                (Building, 1),
                (Storey, 2),
                (GroundSurface, 1),
                (WallSurface, 8),
                (RoofSurface, 2),
                (BuildingRoom, 7),
                (InteriorWallSurface, 27),
                (CeilingSurface, 8),
                (FloorSurface, 7),
                (ClosureSurface, 6),
                (Appearance, 1),
                (ParameterizedTexture, 5),
                (X3DMaterial, 1),
            ])
        );
        assert_eq!(city_model.iter_city_objects().count(), 69);
    }

    #[test]
    fn interior_building() {
        let city_model = city_model();
        let building = building(&city_model);
        assert_eq!(building.feature_id().to_string(), BUILDING_ID);
        assert_eq!(
            building
                .names()
                .iter()
                .map(|n| n.value())
                .collect::<Vec<_>>(),
            ["KIT Test Building FZK-Haus for CityGML 3.0"]
        );
        assert!(building.class().is_none());
        assert!(building.roof_type().is_none());
        assert!(building.functions().is_empty());
        assert!(building.usages().is_empty());
        assert_height(building);
        assert_occupancy(building);
        let [attribute] = building.generic_attributes() else {
            panic!("expected one generic attribute");
        };
        let GenericAttributeKind::StringAttribute(attribute) = attribute else {
            panic!("expected a string attribute, got {attribute:?}");
        };
        assert_eq!(
            (attribute.name.as_str(), attribute.value.as_str()),
            ("@cityeditor:layer", "LoD2-Ausgeblendet")
        );
        assert!(building.boundaries().is_empty());
    }

    #[test]
    fn interior_solid_unresolved() {
        let city_model = city_model();
        let property = building(&city_model)
            .lod2_solid()
            .expect("should have an LoD2 solid");
        assert!(property.href().is_none());
        let solid = property.object().expect("should be inline");
        let shell = solid.exterior().expect("should have an exterior shell");
        assert_eq!(shell.members().len(), 11);
        assert!(
            shell
                .members()
                .iter()
                .all(|member| member.object().is_none())
        );
        assert!(solid.volume_3d().is_err());
    }

    #[test]
    fn interior_storey_boundaries() {
        use FeatureType::{GroundSurface as Ground, RoofSurface as Roof, WallSurface as Wall};
        let city_model = city_model();
        let storeys = storeys(&city_model);
        let expected: [&[(FeatureType, &str, f64)]; 2] = [
            &[
                (Ground, "Ground", 120.0),
                (Wall, "Ground Floor / Wall East", 29.0),
                (Wall, "Ground Floor / Wall South", 34.80000000447035),
                (Wall, "Ground Floor / Wall West", 29.0),
                (Wall, "Ground Floor / Wall North", 34.80000000447035),
            ],
            &[
                (Roof, "Second Floor / Roof South", 69.28203022609509),
                (Roof, "Second Floor / Roof North", 69.28203022609509),
                (Wall, "Second Floor / Wall South", 8.771279998123646),
                (Wall, "Second Floor / Wall West", 21.743155002593994),
                (Wall, "Second Floor / Wall East", 21.743155002593994),
                (Wall, "Second Floor / Wall North", 8.771279998123646),
            ],
        ];
        assert_eq!(storeys.len(), expected.len());
        for (storey, expected) in storeys.iter().zip(expected) {
            let surfaces = thematic_surfaces(storey);
            assert_eq!(surfaces.len(), expected.len());
            for (surface, (feature_type, name, area)) in surfaces.iter().zip(expected) {
                assert_eq!(
                    AbstractFeatureKindRef::from(*surface).feature_type(),
                    *feature_type
                );
                assert_eq!(first_name(*surface), *name);
                let multi_surface = surface
                    .lod2_multi_surface()
                    .and_then(|property| property.object())
                    .expect("should have an LoD2 multi surface");
                assert_close(multi_surface.area_3d().expect("should compute"), *area);
            }
        }
        assert_storeys(&city_model, [None, None]);
    }

    #[test]
    fn interior_storey_rooms() {
        let city_model = city_model();
        assert_storey_rooms(&city_model);
        assert_storey_rooms(&round_trip(&city_model));
    }

    #[test]
    fn interior_round_trip() {
        assert_round_trip(&city_model(), BUILDING_ID);
    }
}

mod window {
    use super::*;

    const BUILDING_ID: &str = "_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz";

    fn city_model() -> CityModel {
        read(
            DATASET,
            "04-FZK-Haus-LoD2-Tex-Storey-Construction-CG30-V01-Window-Interior.gml",
        )
    }

    #[test]
    fn window_city_model() {
        use FeatureType::*;
        let city_model = city_model();
        assert_city_model(
            &city_model,
            (458899.5, 5438784.5, 113.5),
            (458912.5, 5438795.5, 120.017691),
        );
        assert_eq!(feature_types(&city_model).len(), 54);
        assert_eq!(
            feature_type_counts(&city_model),
            BTreeMap::from([
                (CityModel, 1),
                (Building, 1),
                (Storey, 2),
                (BuildingConstructiveElement, 18),
                (Door, 5),
                (Window, 11),
                (Appearance, 2),
                (ParameterizedTexture, 5),
                (X3DMaterial, 9),
            ])
        );
        assert_eq!(city_model.iter_city_objects().count(), 37);
    }

    #[test]
    fn window_building() {
        let city_model = city_model();
        let building = building(&city_model);
        assert_eq!(building.feature_id().to_string(), BUILDING_ID);
        assert_eq!(
            building
                .names()
                .iter()
                .map(|n| n.value())
                .collect::<Vec<_>>(),
            ["KIT FZK-Haus"]
        );
        assert_eq!(
            building
                .functions()
                .iter()
                .map(|f| f.value())
                .collect::<Vec<_>>(),
            ["31001_1000"]
        );
        assert_eq!(building.roof_type().map(|r| r.value()), Some("3100"));
        assert!(building.boundaries().is_empty());
        assert_storeys(
            &city_model,
            [Some("Entrance Floor"), Some("non Entrance Floor")],
        );
    }

    #[test]
    fn window_round_trip() {
        assert_round_trip(&city_model(), BUILDING_ID);
    }
}

mod point_cloud {
    use super::*;

    const BUILDING_ID: &str = "KIT-Test-Building-01";

    fn city_model() -> CityModel {
        read(
            DATASET,
            "06-FZK-Haus-LoD2-Tex-Storey-CG30-V01-PointCloud-thinned.gml",
        )
    }

    #[test]
    fn point_cloud_city_model() {
        use FeatureType::{Building, CityModel, GroundSurface, RoofSurface, Storey, WallSurface};
        let city_model = city_model();
        assert_city_model(
            &city_model,
            (458900.0, 5438785.0, 113.5),
            (458912.0, 5438795.0, 120.017691),
        );
        let expected = [
            vec![CityModel, Building, Storey, GroundSurface],
            vec![WallSurface; 4],
            vec![Storey, RoofSurface, RoofSurface],
            vec![WallSurface; 4],
        ]
        .concat();
        assert_eq!(feature_types(&city_model), expected);
    }

    #[test]
    fn point_cloud_storey_boundaries() {
        use FeatureType::{GroundSurface as Ground, RoofSurface as Roof, WallSurface as Wall};
        let city_model = city_model();
        let building = building(&city_model);
        assert_eq!(building.feature_id().to_string(), BUILDING_ID);
        assert!(building.boundaries().is_empty());
        let expected: [&[(FeatureType, &str)]; 2] = [
            &[
                (Ground, " Ground Floor / GroundSurface"),
                (Wall, "Ground Floor / Wall East"),
                (Wall, "Ground Floor / Wall South"),
                (Wall, "Ground Floor / Wall West"),
                (Wall, "Ground Floor / Wall North"),
            ],
            &[
                (Roof, "Second Floor / Roof North"),
                (Roof, "Second Floor / Roof South"),
                (Wall, "Second Floor / Wall South"),
                (Wall, "Second Floor / Wall West"),
                (Wall, "Second Floor / Wall East"),
                (Wall, "Second Floor / Wall North"),
            ],
        ];
        let storeys = storeys(&city_model);
        assert_eq!(storeys.len(), expected.len());
        for (storey, expected) in storeys.iter().zip(expected) {
            let surfaces = thematic_surfaces(storey);
            assert_eq!(
                surfaces
                    .iter()
                    .map(|s| (
                        AbstractFeatureKindRef::from(*s).feature_type(),
                        first_name(*s)
                    ))
                    .collect::<Vec<_>>(),
                expected
            );
            assert!(surfaces.iter().all(|s| s.lod2_multi_surface().is_none()));
        }
    }

    #[test]
    fn point_cloud_surfaces() {
        let city_model = city_model();
        assert_point_cloud_surfaces(&city_model);
        assert_point_cloud_surfaces(&round_trip(&city_model));
    }

    #[test]
    fn point_cloud_round_trip() {
        assert_round_trip(&city_model(), BUILDING_ID);
    }
}
