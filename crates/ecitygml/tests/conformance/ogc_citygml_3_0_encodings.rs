//! The cases of `crates/ecitygml/tests/conformance/ogc-citygml-3.0-encodings.md`.

use crate::{assert_close, read};
use ecitygml::io::{CitygmlFormat, GmlReader, GmlWriter};
use ecitygml::model::building::{
    AsAbstractBuilding, AsAbstractBuildingSubdivision, Building, BuildingPart, BuildingUnit, Storey,
};
use ecitygml::model::common::{FeatureType, HasFeatureType, IterFeatures, LevelOfDetail};
use ecitygml::model::construction::enums::HeightStatusValue;
use ecitygml::model::construction::{
    AsAbstractConstruction, GroundSurface, RoofSurface, WallSurface,
};
use ecitygml::model::core::refs::AbstractFeatureKindRef;
use ecitygml::model::core::{
    AbstractSpaceBoundaryKind, AsAbstractCityObject, AsAbstractFeature,
    AsAbstractFeatureWithLifespan, AsAbstractSpace, AsAbstractThematicSurface, CityModel,
};
use ecitygml::model::relief::{AsAbstractReliefComponent, ReliefFeature, TinRelief};
use ecitygml::model::transportation::{
    AsAbstractTransportationSpace, Road, Section, TrafficArea, TrafficSpace,
};
use egml::model::base::{AsAbstractGml, HasAssociationAttributes};
use egml::model::feature::AsAbstractFeature as _;
use egml::model::geometry::{DirectPosition, Envelope};
use std::collections::BTreeMap;

const DATASET: &str = "ogc-citygml-3.0-encodings";

fn feature_types(city_model: &CityModel) -> Vec<FeatureType> {
    city_model
        .iter_features()
        .map(|feature| feature.feature_type())
        .collect()
}

/// All features of a type, in document order.
fn all<'a, T>(city_model: &'a CityModel) -> Vec<&'a T>
where
    &'a T: TryFrom<AbstractFeatureKindRef<'a>>,
{
    city_model
        .iter_features()
        .filter_map(|feature| feature.try_into().ok())
        .collect()
}

fn names(feature: &impl AsAbstractGml) -> Vec<&str> {
    feature.names().iter().map(|name| name.value()).collect()
}

fn first_name(feature: &impl AsAbstractGml) -> &str {
    feature.names().first().expect("should have a name").value()
}

fn assert_point_close(position: &DirectPosition, expected: (f64, f64, f64)) {
    assert_close(position.x(), expected.0);
    assert_close(position.y(), expected.1);
    assert_close(position.z(), expected.2);
}

fn assert_envelope(envelope: &Envelope, lower: (f64, f64, f64), upper: (f64, f64, f64)) {
    assert_point_close(envelope.lower_corner(), lower);
    assert_point_close(envelope.upper_corner(), upper);
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

/// A space's boundaries as thematic surfaces; fails on a reference-only boundary or another kind of boundary.
fn thematic_surfaces(
    space: &impl AsAbstractSpace,
) -> Vec<&ecitygml::model::core::AbstractThematicSurfaceKind> {
    space
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

/// The area of a thematic surface's LoD2 multi surface.
fn lod2_area(surface: &impl AsAbstractThematicSurface) -> f64 {
    surface
        .lod2_multi_surface()
        .and_then(|property| property.object())
        .expect("should have an LoD2 multi surface")
        .area_3d()
        .expect("should compute")
}

/// Asserts a building's or part's one height.
fn assert_height(building: &impl AsAbstractConstruction, length: f64) {
    let [height] = building.heights() else {
        panic!("expected one height, got {:?}", building.heights());
    };
    assert_eq!(height.high_reference().value(), "highestRoofEdge");
    assert_eq!(height.low_reference().value(), "lowestGroundPoint");
    assert_eq!(height.status(), HeightStatusValue::Measured);
    assert_close(height.length().value(), length);
    assert_eq!(height.length().uom(), "#m");
}

mod garage {
    use super::*;

    fn city_model() -> CityModel {
        read(DATASET, "Building_and_garage_LOD2-EPSG25832.gml")
    }

    fn building(city_model: &CityModel) -> &Building {
        let [building] = all::<Building>(city_model)[..] else {
            panic!("expected one building");
        };
        building
    }

    #[test]
    fn garage_city_model() {
        use FeatureType::*;
        let city_model = city_model();
        assert_eq!(city_model.city_object_members_len(), 2);
        assert_envelope(
            city_model
                .bounded_by()
                .and_then(|shape| shape.envelope())
                .expect("should have an envelope"),
            (458868.0, 5438343.0, 112.0),
            (458892.0, 5438362.0, 117.0),
        );
        let expected = [
            vec![CityModel, Building, GroundSurface],
            vec![WallSurface; 4],
            vec![RoofSurface, RoofSurface, BuildingPart],
            vec![WallSurface; 4],
            vec![GroundSurface, RoofSurface, ReliefFeature, TinRelief],
        ]
        .concat();
        assert_eq!(feature_types(&city_model), expected);
        assert_eq!(city_model.iter_city_objects().count(), 17);
    }

    #[test]
    fn garage_building() {
        use FeatureType::{GroundSurface as Ground, RoofSurface as Roof, WallSurface as Wall};
        let city_model = city_model();
        let building = building(&city_model);
        assert_eq!(
            building.feature_id().to_string(),
            "GML_7b1a5a6f-ddad-4c3d-a507-3eb9ee0a8e68"
        );
        assert_eq!(names(building), ["Example Building LOD2"]);
        assert!(building.class().is_none());
        assert_eq!(
            building
                .functions()
                .iter()
                .map(|f| f.value())
                .collect::<Vec<_>>(),
            ["1000"]
        );
        assert!(building.usages().is_empty());
        assert_eq!(building.roof_type().map(|r| r.value()), Some("1030"));
        assert_eq!(building.storeys_above_ground(), Some(1));
        assert_eq!(building.storeys_below_ground(), None);
        let date = building.date_of_construction().expect("should have a date");
        assert_eq!((date.year(), date.month(), date.day()), (1985, 1, 1));
        assert_height(building, 6.0);

        let expected = [
            (Ground, "Ground Slab", 50.0),
            (Wall, "Wall South", 30.0),
            (Wall, "Wall North", 30.0),
            (Wall, "Wall East", 20.0),
            (Wall, "Wall West", 20.0),
            (Roof, "Roof North", 32.01562118716424),
            (Roof, "Roof South", 32.01562118716424),
        ];
        let surfaces = thematic_surfaces(building);
        assert_eq!(surfaces.len(), expected.len());
        for (surface, (feature_type, name, area)) in surfaces.iter().zip(expected) {
            assert_eq!(
                AbstractFeatureKindRef::from(*surface).feature_type(),
                feature_type
            );
            assert_eq!(first_name(*surface), name);
            assert_close(lod2_area(*surface), area);
        }
    }

    #[test]
    fn garage_building_part() {
        use FeatureType::{GroundSurface as Ground, RoofSurface as Roof, WallSurface as Wall};
        let city_model = city_model();
        let [property] = building(&city_model).building_parts() else {
            panic!("expected one building part");
        };
        assert!(property.href().is_none());
        let part = property.object().expect("should be inline");
        assert_eq!(part.feature_id().to_string(), "GMLID_BUI379228_1244_301");
        assert_eq!(names(part), ["Example BuildingPart LOD2"]);
        assert!(part.class().is_none());
        assert_eq!(
            part.functions()
                .iter()
                .map(|f| f.value())
                .collect::<Vec<_>>(),
            ["1630"]
        );
        assert!(part.usages().is_empty());
        assert_eq!(part.roof_type().map(|r| r.value()), Some("1010"));
        let date = part.date_of_construction().expect("should have a date");
        assert_eq!((date.year(), date.month(), date.day()), (1985, 1, 1));
        assert_height(part, 2.5);

        // The west wall's area is left out: its member is a gml:OrientableSurface, not read yet.
        let expected = [
            (Wall, "Garage Wall East", Some(9.600000023841858)),
            (Wall, "Garage Wall South", Some(6.25)),
            (Wall, "Garage Wall West", None),
            (Wall, "Garage Wall North", Some(5.75)),
            (Ground, "Garage Ground Slab", Some(10.0)),
            (Roof, "Garage Roof", Some(10.012492197250394)),
        ];
        let surfaces = thematic_surfaces(part);
        assert_eq!(surfaces.len(), expected.len());
        for (surface, (feature_type, name, area)) in surfaces.iter().zip(expected) {
            assert_eq!(
                AbstractFeatureKindRef::from(*surface).feature_type(),
                feature_type
            );
            assert_eq!(first_name(*surface), name);
            if let Some(area) = area {
                assert_close(lod2_area(*surface), area);
            }
        }
    }

    #[test]
    fn garage_relief() {
        let city_model = city_model();
        let [relief] = all::<ReliefFeature>(&city_model)[..] else {
            panic!("expected one relief feature");
        };
        assert_eq!(
            relief.feature_id().to_string(),
            "GML_6bb30328-7599-4500-90ef-766fde6aa67b"
        );
        assert_eq!(names(relief), ["Example TIN LOD2"]);
        assert_eq!(relief.lod(), LevelOfDetail::Two);
        let [component] = relief.relief_components() else {
            panic!("expected one relief component");
        };
        assert!(component.href().is_none());
        let component = component.object().expect("should be inline");
        assert_eq!(
            AbstractFeatureKindRef::from(component).feature_type(),
            FeatureType::TinRelief
        );

        let [tin_relief] = all::<TinRelief>(&city_model)[..] else {
            panic!("expected one TIN relief");
        };
        assert_eq!(
            tin_relief.feature_id().to_string(),
            "GML_4eb161b0-aa7e-4087-937c-5c4c427c7fc9"
        );
        assert_eq!(names(tin_relief), ["Ground"]);
        assert_eq!(tin_relief.lod(), LevelOfDetail::Two);
        let tin = tin_relief.tin().expect("should have a TIN");
        assert!(tin.href().is_none());
        let surface = tin.object().expect("should be inline");
        assert_eq!(surface.triangles().len(), 12);
        assert_close(
            surface.area_3d().expect("should compute"),
            399.8446647372588,
        );
    }

    #[test]
    fn garage_round_trip() {
        let city_model = city_model();
        let written = round_trip(&city_model);
        assert_eq!(feature_types(&written), feature_types(&city_model));
        let ids = |model: &CityModel| -> Vec<String> {
            let mut ids: Vec<String> = all::<Building>(model)
                .iter()
                .map(|b| b.feature_id().to_string())
                .collect();
            ids.extend(
                all::<BuildingPart>(model)
                    .iter()
                    .map(|p| p.feature_id().to_string()),
            );
            ids.extend(
                all::<ReliefFeature>(model)
                    .iter()
                    .map(|r| r.feature_id().to_string()),
            );
            ids.extend(
                all::<TinRelief>(model)
                    .iter()
                    .map(|t| t.feature_id().to_string()),
            );
            ids
        };
        assert_eq!(
            ids(&written),
            [
                "GML_7b1a5a6f-ddad-4c3d-a507-3eb9ee0a8e68",
                "GMLID_BUI379228_1244_301",
                "GML_6bb30328-7599-4500-90ef-766fde6aa67b",
                "GML_4eb161b0-aa7e-4087-937c-5c4c427c7fc9",
            ]
        );
    }
}

mod units {
    use super::*;

    fn city_model() -> CityModel {
        read(DATASET, "BuildingUnits_Storeys_xlink.gml")
    }

    /// The `href`s of a storey's LoD2 surface members (`None` for inline members).
    fn member_hrefs(storey: &Storey) -> Vec<Option<String>> {
        let property = storey
            .lod2_multi_surface()
            .expect("should have an LoD2 multi surface");
        assert!(property.href().is_none());
        property
            .object()
            .expect("should be inline")
            .surface_member()
            .iter()
            .map(|member| {
                assert_eq!(member.object().is_none(), member.href().is_some());
                member.href().map(|href| href.to_string())
            })
            .collect()
    }

    #[test]
    fn units_city_model() {
        use FeatureType::*;
        let city_model = city_model();
        assert_eq!(city_model.city_object_members_len(), 1);
        assert_envelope(
            city_model
                .bounded_by()
                .and_then(|shape| shape.envelope())
                .expect("should have an envelope"),
            (457841.0, 5439082.0, 111.0),
            (457854.0, 5439093.0, 121.0),
        );
        let room = |walls: usize| {
            [
                vec![BuildingRoom],
                vec![InteriorWallSurface; walls],
                vec![FloorSurface, CeilingSurface],
            ]
            .concat()
        };
        let expected = [
            vec![CityModel, Building],
            vec![WallSurface; 3],
            vec![RoofSurface, WallSurface, RoofSurface, GroundSurface],
            room(8),
            room(8),
            room(4),
            vec![BuildingUnit, BuildingUnit, Storey, Storey],
        ]
        .concat();
        assert_eq!(feature_types(&city_model), expected);
        assert_eq!(city_model.iter_city_objects().count(), 41);
    }

    #[test]
    fn units_building() {
        use FeatureType::{GroundSurface as Ground, RoofSurface as Roof, WallSurface as Wall};
        let city_model = city_model();
        let [building] = all::<Building>(&city_model)[..] else {
            panic!("expected one building");
        };
        assert_eq!(building.feature_id().to_string(), "building_unit_example_1");
        assert!(building.names().is_empty());
        assert!(building.functions().is_empty());
        assert!(building.usages().is_empty());
        assert!(building.class().is_none());
        assert!(building.roof_type().is_none());
        let expected = [
            (Wall, "Outer Wall 1 (West)", 89.375),
            (Wall, "Outer Wall 2 (South)", 81.25),
            (Wall, "Outer Wall 3 (East)", 89.375),
            (Roof, "Roof 1 (North)", 86.53792521201326),
            (Wall, "Outer Wall 4 (North)", 81.25),
            (Roof, "Roof 2 (South)", 86.53792521201326),
            (Ground, "Base Surface", 143.0),
        ];
        let surfaces = thematic_surfaces(building);
        assert_eq!(surfaces.len(), expected.len());
        for (surface, (feature_type, name, area)) in surfaces.iter().zip(expected) {
            assert_eq!(
                AbstractFeatureKindRef::from(*surface).feature_type(),
                feature_type
            );
            assert_eq!(first_name(*surface), name);
            assert_close(lod2_area(*surface), area);
        }
    }

    #[test]
    fn units_subdivisions() {
        let city_model = city_model();
        let [building] = all::<Building>(&city_model)[..] else {
            panic!("expected one building");
        };
        let types: Vec<FeatureType> = building
            .building_subdivisions()
            .iter()
            .map(|property| {
                assert!(property.href().is_none());
                AbstractFeatureKindRef::from(property.object().expect("should be inline"))
                    .feature_type()
            })
            .collect();
        assert_eq!(
            types,
            [
                FeatureType::BuildingUnit,
                FeatureType::BuildingUnit,
                FeatureType::Storey,
                FeatureType::Storey
            ]
        );

        let units = all::<BuildingUnit>(&city_model);
        assert_eq!(
            units
                .iter()
                .map(|u| u.feature_id().to_string())
                .collect::<Vec<_>>(),
            ["BuildingUnit_apartment1", "BuildingUnit_apartment2"]
        );
        for unit in units {
            assert_eq!(
                unit.functions()
                    .iter()
                    .map(|f| f.value())
                    .collect::<Vec<_>>(),
                ["apartment"]
            );
            assert!(unit.class().is_none());
            assert!(unit.usages().is_empty());
            assert!(unit.boundaries().is_empty());
            assert!(unit.lod2_multi_surface().is_none());
        }

        let storeys = all::<Storey>(&city_model);
        assert_eq!(
            storeys
                .iter()
                .map(|s| s.feature_id().to_string())
                .collect::<Vec<_>>(),
            ["storey1", "storey2"]
        );
        for storey in storeys {
            assert!(storey.names().is_empty());
            assert!(storey.class().is_none());
            assert!(storey.functions().is_empty());
            assert!(storey.usages().is_empty());
            assert!(storey.boundaries().is_empty());
        }
    }

    #[test]
    fn units_storey_geometry() {
        let city_model = city_model();
        let storeys = all::<Storey>(&city_model);
        let expected = [
            (
                [
                    "#Wall_1_PolyID82397_997_453711_16336011",
                    "#Wall_1_PolyID82397_997_453711_16336012",
                    "#Wall_1_PolyID82397_997_453711_163360136",
                ],
                (457841.1, 5439082.1, 111.1),
                (457853.9, 5439092.9, 113.9),
            ),
            (
                [
                    "#Wall_1_PolyID82397_997_453711_163360112",
                    "#Wall_1_PolyID82397_997_453711_163360122",
                    "#Wall_1_PolyID82397_997_453711_1633601362",
                ],
                (457841.1, 5439082.1, 114.1),
                (457853.9, 5439092.9, 116.9),
            ),
        ];
        assert_eq!(storeys.len(), expected.len());
        for (storey, (hrefs, lower, upper)) in storeys.iter().zip(expected) {
            let [a, b, c] = hrefs.map(|href| Some(href.to_string()));
            assert_eq!(member_hrefs(storey), [None, a, b, c, None, None]);
            let multi_surface = storey
                .lod2_multi_surface()
                .and_then(|property| property.object())
                .expect("should be inline");
            assert!(multi_surface.area_3d().is_err());
            assert_envelope(
                storey
                    .bounded_by()
                    .and_then(|shape| shape.envelope())
                    .expect("should have an envelope"),
                lower,
                upper,
            );
        }
    }

    #[test]
    fn units_round_trip() {
        let city_model = city_model();
        let written = round_trip(&city_model);
        assert_eq!(feature_types(&written), feature_types(&city_model));
        let [building] = all::<Building>(&written)[..] else {
            panic!("expected one building");
        };
        assert_eq!(building.feature_id().to_string(), "building_unit_example_1");
        let hrefs = |model: &CityModel| -> Vec<Vec<Option<String>>> {
            all::<Storey>(model)
                .iter()
                .map(|s| member_hrefs(s))
                .collect()
        };
        assert_eq!(hrefs(&written), hrefs(&city_model));
    }
}

mod road_bridge {
    use super::*;
    use ecitygml::model::bridge::Bridge;

    fn city_model() -> CityModel {
        read(
            DATASET,
            "Road_over_Bridge_CityGML3.0_LOD2_with_CityObjectRelations.gml",
        )
    }

    /// The relations of the roof surfaces and traffic areas, in document order: (city object, relation type, `href`
    /// of `relation_to`).
    fn relations(city_model: &CityModel) -> Vec<(String, String, Option<String>)> {
        city_model
            .iter_features()
            .filter_map(|feature| {
                let related_to = if let Ok(roof) = <&RoofSurface>::try_from(feature) {
                    roof.related_to()
                } else if let Ok(area) = <&TrafficArea>::try_from(feature) {
                    area.related_to()
                } else {
                    return None;
                };
                Some((feature.feature_id().to_string(), related_to))
            })
            .flat_map(|(id, related_to)| {
                related_to.iter().map(move |property| {
                    assert!(property.href().is_none());
                    let relation = property.object().expect("should be inline");
                    assert!(relation.generic_attributes().is_empty());
                    (
                        id.clone(),
                        relation.relation_type().value().to_string(),
                        relation.relation_to().href().map(|href| href.to_string()),
                    )
                })
            })
            .collect()
    }

    #[test]
    fn road_bridge_city_model() {
        use FeatureType::*;
        let city_model = city_model();
        assert_eq!(city_model.city_object_members_len(), 2);
        assert!(city_model.bounded_by().is_none());
        let section = [
            Section,
            TrafficSpace,
            TrafficArea,
            TrafficSpace,
            TrafficArea,
        ];
        let expected = [
            vec![CityModel, Bridge, GroundSurface, RoofSurface, RoofSurface],
            vec![WallSurface; 4],
            vec![Road],
            section.to_vec(),
            section.to_vec(),
            section.to_vec(),
        ]
        .concat();
        assert_eq!(feature_types(&city_model), expected);
        assert_eq!(city_model.iter_city_objects().count(), 24);
    }

    #[test]
    fn road_bridge_bridge() {
        let city_model = city_model();
        let [bridge] = all::<Bridge>(&city_model)[..] else {
            panic!("expected one bridge");
        };
        assert_eq!(bridge.feature_id().to_string(), "id_bridge1");
        assert!(bridge.names().is_empty());
        assert!(bridge.related_to().is_empty());
        let expected = [
            ("id_groundsurface1", 77500.15996032),
            ("id_roofsurface1", 38750.07998016),
            ("id_roofsurface2", 38750.07998016),
            ("id_wallsurface4", 10075.02000744),
            ("id_wallsurface1", 20150.04001488),
            ("id_wallsurface2", 10075.02000744),
            ("id_wallsurface3", 20150.04001488),
        ];
        let surfaces = thematic_surfaces(bridge);
        assert_eq!(surfaces.len(), expected.len());
        for (surface, (id, area)) in surfaces.iter().zip(expected) {
            assert_eq!(
                AbstractFeatureKindRef::from(*surface)
                    .feature_id()
                    .to_string(),
                id
            );
            assert_close(lod2_area(*surface), area);
        }
    }

    #[test]
    fn road_bridge_road() {
        let city_model = city_model();
        let [road] = all::<Road>(&city_model)[..] else {
            panic!("expected one road");
        };
        assert_eq!(road.feature_id().to_string(), "id_road1");
        assert!(road.related_to().is_empty());
        assert!(road.traffic_spaces().is_empty());
        assert!(road.auxiliary_traffic_spaces().is_empty());
        let sections: Vec<&Section> = road
            .sections()
            .iter()
            .map(|property| {
                assert!(property.href().is_none());
                property.object().expect("should be inline")
            })
            .collect();
        assert_eq!(
            sections
                .iter()
                .map(|s| s.feature_id().to_string())
                .collect::<Vec<_>>(),
            ["id_section1", "id_section2", "id_section3"]
        );
        let spaces: Vec<&TrafficSpace> = sections
            .iter()
            .flat_map(|section| section.traffic_spaces())
            .map(|property| {
                assert!(property.href().is_none());
                property.object().expect("should be inline")
            })
            .collect();
        let numbers = [1, 2, 5, 6, 3, 4];
        assert_eq!(spaces.len(), numbers.len());
        for (space, number) in spaces.iter().zip(numbers) {
            assert_eq!(
                space.feature_id().to_string(),
                format!("id_trafficspace{number}")
            );
            let [boundary] = space.boundaries() else {
                panic!("expected one boundary");
            };
            assert!(boundary.href().is_none());
            let area = AbstractFeatureKindRef::from(boundary.object().expect("should be inline"));
            assert_eq!(area.feature_type(), FeatureType::TrafficArea);
            assert_eq!(
                area.feature_id().to_string(),
                format!("id_trafficarea{number}")
            );
        }
    }

    #[test]
    fn road_bridge_relations() {
        let city_model = city_model();
        let expected = [
            ("id_roofsurface1", "id_trafficarea5"),
            ("id_roofsurface2", "id_trafficarea6"),
            ("id_trafficarea5", "id_roofSurface1"),
            ("id_trafficarea6", "id_roofSurface2"),
        ]
        .map(|(object, href)| {
            (
                object.to_string(),
                "equal".to_string(),
                Some(href.to_string()),
            )
        });
        assert_eq!(relations(&city_model), expected);
        assert!(
            all::<WallSurface>(&city_model)
                .iter()
                .all(|wall| wall.related_to().is_empty())
        );
        assert!(
            all::<GroundSurface>(&city_model)
                .iter()
                .all(|ground| ground.related_to().is_empty())
        );
    }

    #[test]
    fn road_bridge_round_trip() {
        let city_model = city_model();
        let written = round_trip(&city_model);
        assert_eq!(feature_types(&written), feature_types(&city_model));
        let [bridge] = all::<Bridge>(&written)[..] else {
            panic!("expected one bridge");
        };
        assert_eq!(bridge.feature_id().to_string(), "id_bridge1");
        let [road] = all::<Road>(&written)[..] else {
            panic!("expected one road");
        };
        assert_eq!(road.feature_id().to_string(), "id_road1");
        assert_eq!(relations(&written), relations(&city_model));
    }
}

mod versioning {
    use super::*;

    fn city_model() -> CityModel {
        read(
            DATASET,
            "historicalSuccession_CityGML_3.0_LOD2_Versioning.gml",
        )
    }

    /// A building's `feature_id`, first name, creation and termination date, and its parts' `feature_id`s.
    type ExpectedBuilding = (
        &'static str,
        &'static str,
        (i32, u32, u32),
        Option<(i32, u32, u32)>,
        &'static [&'static str],
    );

    /// (year, month, day) of a date time at 00:00 UTC.
    fn date(date_time: Option<&egml::model::xs::DateTime>) -> Option<(i32, u32, u32)> {
        date_time.map(|d| {
            assert_eq!((d.hour(), d.minute(), d.offset_seconds()), (0, 0, 0));
            (d.year(), d.month(), d.day())
        })
    }

    #[test]
    fn versioning_city_model() {
        use FeatureType::*;
        let city_model = city_model();
        assert_eq!(city_model.city_object_members_len(), 4);
        assert!(city_model.bounded_by().is_none());
        let types = feature_types(&city_model);
        assert_eq!(types.len(), 60);
        assert_eq!(types[0], CityModel);
        let mut counts = BTreeMap::new();
        for feature_type in types {
            *counts.entry(feature_type).or_insert(0) += 1;
        }
        assert_eq!(
            counts,
            BTreeMap::from([
                (CityModel, 1),
                (Building, 4),
                (BuildingPart, 5),
                (RoofSurface, 14),
                (WallSurface, 31),
                (GroundSurface, 5),
            ])
        );
        assert_eq!(city_model.iter_city_objects().count(), 59);
    }

    #[test]
    fn versioning_buildings() {
        let city_model = city_model();
        let expected: [ExpectedBuilding; 4] = [
            (
                "BU_69381AL47_2000-01-01",
                "Building A",
                (2000, 1, 1),
                Some((2015, 1, 1)),
                &["BU_69381AL47_1"],
            ),
            (
                "BU_69381AL49_2000-01-01",
                "Building B",
                (2000, 1, 1),
                Some((2015, 1, 1)),
                &["BU_69381AL49_1_2000-01-01"],
            ),
            (
                "BU_69381AL49_2015-01-01",
                "Building B",
                (2015, 1, 1),
                None,
                &["BU_69381AL49_1_2015-01-01", "BU_69381AL49_2_2015-01-01"],
            ),
            (
                "BU_69381AL50_2015-01-01",
                "Building C",
                (2015, 1, 1),
                None,
                &["BU_69381AL50_1"],
            ),
        ];
        let buildings = all::<Building>(&city_model);
        assert_eq!(buildings.len(), expected.len());
        for (building, (id, name, created, terminated, parts)) in buildings.iter().zip(expected) {
            assert_eq!(building.feature_id().to_string(), id);
            assert_eq!(first_name(*building), name);
            assert_eq!(date(building.creation_date()), Some(created));
            assert_eq!(date(building.termination_date()), terminated);
            let part_ids: Vec<String> = building
                .building_parts()
                .iter()
                .map(|property| {
                    assert!(property.href().is_none());
                    property
                        .object()
                        .expect("should be inline")
                        .feature_id()
                        .to_string()
                })
                .collect();
            assert_eq!(part_ids, parts);
            assert!(building.heights().is_empty());
            assert!(building.boundaries().is_empty());
        }
    }

    #[test]
    fn versioning_building_parts() {
        let city_model = city_model();
        let expected = [
            ("BU_69381AL47_1", 13.015, 8),
            ("BU_69381AL49_1_2000-01-01", 10.63, 9),
            ("BU_69381AL49_1_2015-01-01", 10.63, 9),
            ("BU_69381AL49_2_2015-01-01", 8.743, 7),
            ("BU_69381AL50_1", 18.215, 17),
        ];
        let parts = all::<BuildingPart>(&city_model);
        assert_eq!(parts.len(), expected.len());
        for (part, (id, height, boundaries)) in parts.iter().zip(expected) {
            assert_eq!(part.feature_id().to_string(), id);
            assert_height(*part, height);
            assert_eq!(part.boundaries().len(), boundaries);
            assert!(part.creation_date().is_none());
            assert!(part.names().is_empty());
        }
    }

    #[test]
    fn versioning_round_trip() {
        let city_model = city_model();
        let written = round_trip(&city_model);
        assert_eq!(feature_types(&written), feature_types(&city_model));
        let ids = |model: &CityModel| -> Vec<String> {
            let mut ids: Vec<String> = all::<Building>(model)
                .iter()
                .map(|b| b.feature_id().to_string())
                .collect();
            ids.extend(
                all::<BuildingPart>(model)
                    .iter()
                    .map(|p| p.feature_id().to_string()),
            );
            ids
        };
        assert_eq!(ids(&written), ids(&city_model));
        let dates = |model: &CityModel| -> Vec<_> {
            all::<Building>(model)
                .iter()
                .map(|b| (date(b.creation_date()), date(b.termination_date())))
                .collect()
        };
        assert_eq!(dates(&written), dates(&city_model));
    }
}
