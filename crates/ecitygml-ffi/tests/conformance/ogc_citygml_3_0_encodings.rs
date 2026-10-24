//! The cases of `crates/ecitygml/tests/conformance/ogc-citygml-3.0-encodings.md`.

use crate::{assert_close, read, written};
use ecitygml_ffi::citygml::core::model::bridge::bridge::Bridge;
use ecitygml_ffi::citygml::core::model::building::building::Building;
use ecitygml_ffi::citygml::core::model::building::building_part::BuildingPart;
use ecitygml_ffi::citygml::core::model::building::building_unit::BuildingUnit;
use ecitygml_ffi::citygml::core::model::building::storey::Storey;
use ecitygml_ffi::citygml::core::model::common::feature_type::FeatureType;
use ecitygml_ffi::citygml::core::model::common::level_of_detail::LevelOfDetail;
use ecitygml_ffi::citygml::core::model::construction::enums::height_status_value::HeightStatusValue;
use ecitygml_ffi::citygml::core::model::construction::ground_surface::GroundSurface;
use ecitygml_ffi::citygml::core::model::construction::height::HeightIterator;
use ecitygml_ffi::citygml::core::model::construction::roof_surface::RoofSurface;
use ecitygml_ffi::citygml::core::model::construction::wall_surface::WallSurface;
use ecitygml_ffi::citygml::core::model::core::abstract_space_boundary_property::AbstractSpaceBoundaryPropertyIterator;
use ecitygml_ffi::citygml::core::model::core::city_model::CityModel;
use ecitygml_ffi::citygml::core::model::core::city_object_relation_property::CityObjectRelationPropertyIterator;
use ecitygml_ffi::citygml::core::model::core::refs::abstract_feature_kind_ref::AbstractFeatureKindRef;
use ecitygml_ffi::citygml::core::model::relief::relief_feature::ReliefFeature;
use ecitygml_ffi::citygml::core::model::relief::tin_relief::TinRelief;
use ecitygml_ffi::citygml::core::model::transportation::road::Road;
use ecitygml_ffi::citygml::core::model::transportation::traffic_area::TrafficArea;
use ecitygml_ffi::citygml::io::format::CitygmlFormat;
use ecitygml_ffi::citygml::io::gml::read::GmlReader;
use ecitygml_ffi::citygml::io::gml::write::GmlWriter;
use ecitygml_ffi::gml::core::model::basic_types::code::CodeIterator;
use ecitygml_ffi::gml::core::model::geometry::aggregates::multi_surface_property::MultiSurfaceProperty;
use ecitygml_ffi::gml::core::model::geometry::direct_position::DirectPosition;
use ecitygml_ffi::gml::core::model::geometry::envelope::Envelope;
use ecitygml_ffi::gml::core::model::xs::date_time::DateTime;

const DATASET: &str = "ogc-citygml-3.0-encodings";

/// All items of a Diplomat iterator.
macro_rules! items {
    // A match keeps the temporaries the iterator borrows from alive.
    ($iterator:expr) => {
        match $iterator {
            mut iterator => std::iter::from_fn(|| iterator.next()).collect::<Vec<_>>(),
        }
    };
}

fn features(city_model: &CityModel) -> Vec<Box<AbstractFeatureKindRef<'_>>> {
    items!(city_model.iter_features())
}

fn feature_types(city_model: &CityModel) -> Vec<FeatureType> {
    features(city_model)
        .iter()
        .map(|feature| feature.feature_type())
        .collect()
}

fn names(names: Box<CodeIterator<'_>>) -> Vec<&str> {
    items!(names).into_iter().map(|name| name.value()).collect()
}

/// The first of the names, if any.
fn first_name(names: Box<CodeIterator<'_>>) -> Option<&str> {
    items!(names).first().map(|name| name.value())
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

fn round_trip(city_model: &CityModel) -> Box<CityModel> {
    let mut writer = GmlWriter::new(CitygmlFormat::Gml);
    writer
        .finish(city_model)
        .unwrap_or_else(|_| panic!("should write"));
    GmlReader::new(writer.data(), CitygmlFormat::Gml)
        .finish()
        .unwrap_or_else(|_| panic!("should read"))
}

/// The area of an inline LoD2 multi surface.
fn lod2_area(property: Option<&MultiSurfaceProperty>) -> f64 {
    property
        .and_then(|property| property.object())
        .expect("should have an LoD2 multi surface")
        .area_3d()
        .expect("should compute")
}

/// A space's boundaries as (feature type, `feature_id`, first name or none, LoD2 multi surface), all inline wall,
/// roof or ground surfaces.
fn surfaces(
    boundaries: Box<AbstractSpaceBoundaryPropertyIterator<'_>>,
) -> Vec<(
    FeatureType,
    String,
    Option<&str>,
    Option<&MultiSurfaceProperty>,
)> {
    items!(boundaries)
        .into_iter()
        .map(|property| {
            assert!(property.href().is_none());
            let object = property.object().expect("should be inline");
            let id = object.feature_id().as_str().to_owned();
            let feature = AbstractFeatureKindRef::from_space_boundary(object);
            let feature_type = feature.feature_type();
            if let Some(wall) = WallSurface::try_from(&feature) {
                (
                    feature_type,
                    id,
                    first_name(wall.names()),
                    wall.lod2_multi_surface(),
                )
            } else if let Some(roof) = RoofSurface::try_from(&feature) {
                (
                    feature_type,
                    id,
                    first_name(roof.names()),
                    roof.lod2_multi_surface(),
                )
            } else if let Some(ground) = GroundSurface::try_from(&feature) {
                (
                    feature_type,
                    id,
                    first_name(ground.names()),
                    ground.lod2_multi_surface(),
                )
            } else {
                panic!("unexpected boundary {feature_type:?}")
            }
        })
        .collect()
}

/// Asserts a building's or part's one height.
fn assert_height(heights: Box<HeightIterator<'_>>, length: f64) {
    let heights = items!(heights);
    let [height] = heights[..] else {
        panic!("expected one height");
    };
    assert_eq!(height.high_reference().value(), "highestRoofEdge");
    assert_eq!(height.low_reference().value(), "lowestGroundPoint");
    assert_eq!(height.status(), HeightStatusValue::Measured);
    assert_close(height.length().value(), length);
    assert_eq!(height.length().uom(), "#m");
}

mod garage {
    use super::*;

    fn city_model() -> Box<CityModel> {
        read(DATASET, "Building_and_garage_LOD2-EPSG25832.gml")
    }

    fn building(city_model: &CityModel) -> &Building {
        let buildings: Vec<&Building> = features(city_model)
            .iter()
            .filter_map(|f| Building::try_from(f))
            .collect();
        let [building] = buildings[..] else {
            panic!("expected one building");
        };
        building
    }

    #[test]
    fn garage_city_model() {
        use FeatureType::*;
        let city_model = city_model();
        assert_eq!(city_model.city_objects_len(), 2);
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
        assert_eq!(items!(city_model.iter_city_objects()).len(), 17);
    }

    #[test]
    fn garage_building() {
        use FeatureType::{GroundSurface as Ground, RoofSurface as Roof, WallSurface as Wall};
        let city_model = city_model();
        let building = building(&city_model);
        assert_eq!(
            building.feature_id().as_str(),
            "GML_7b1a5a6f-ddad-4c3d-a507-3eb9ee0a8e68"
        );
        assert_eq!(names(building.names()), ["Example Building LOD2"]);
        assert!(building.class().is_none());
        assert_eq!(
            items!(building.functions())
                .iter()
                .map(|f| f.value())
                .collect::<Vec<_>>(),
            ["1000"]
        );
        assert!(building.usages().next().is_none());
        assert_eq!(building.roof_type().map(|r| r.value()), Some("1030"));
        assert_eq!(building.storeys_above_ground(), Some(1));
        assert_eq!(building.storeys_below_ground(), None);
        let date = building.date_of_construction().expect("should have a date");
        assert_eq!((date.year(), date.month(), date.day()), (1985, 1, 1));
        assert_height(building.heights(), 6.0);

        let expected = [
            (Ground, "Ground Slab", 50.0),
            (Wall, "Wall South", 30.0),
            (Wall, "Wall North", 30.0),
            (Wall, "Wall East", 20.0),
            (Wall, "Wall West", 20.0),
            (Roof, "Roof North", 32.01562118716424),
            (Roof, "Roof South", 32.01562118716424),
        ];
        let surfaces = surfaces(building.boundaries());
        assert_eq!(surfaces.len(), expected.len());
        for ((feature_type, _, name, multi_surface), (want_type, want_name, area)) in
            surfaces.into_iter().zip(expected)
        {
            assert_eq!(feature_type, want_type);
            assert_eq!(name, Some(want_name));
            assert_close(lod2_area(multi_surface), area);
        }
    }

    #[test]
    fn garage_building_part() {
        use FeatureType::{GroundSurface as Ground, RoofSurface as Roof, WallSurface as Wall};
        let city_model = city_model();
        let parts = items!(building(&city_model).building_parts());
        let [property] = parts[..] else {
            panic!("expected one building part");
        };
        assert!(property.href().is_none());
        let part = property.object().expect("should be inline");
        assert_eq!(part.feature_id().as_str(), "GMLID_BUI379228_1244_301");
        assert_eq!(names(part.names()), ["Example BuildingPart LOD2"]);
        assert!(part.class().is_none());
        assert_eq!(
            items!(part.functions())
                .iter()
                .map(|f| f.value())
                .collect::<Vec<_>>(),
            ["1630"]
        );
        assert!(part.usages().next().is_none());
        assert_eq!(part.roof_type().map(|r| r.value()), Some("1010"));
        let date = part.date_of_construction().expect("should have a date");
        assert_eq!((date.year(), date.month(), date.day()), (1985, 1, 1));
        assert_height(part.heights(), 2.5);

        // The west wall's area is left out: its member is a gml:OrientableSurface, not read yet.
        let expected = [
            (Wall, "Garage Wall East", Some(9.600000023841858)),
            (Wall, "Garage Wall South", Some(6.25)),
            (Wall, "Garage Wall West", None),
            (Wall, "Garage Wall North", Some(5.75)),
            (Ground, "Garage Ground Slab", Some(10.0)),
            (Roof, "Garage Roof", Some(10.012492197250394)),
        ];
        let surfaces = surfaces(part.boundaries());
        assert_eq!(surfaces.len(), expected.len());
        for ((feature_type, _, name, multi_surface), (want_type, want_name, area)) in
            surfaces.into_iter().zip(expected)
        {
            assert_eq!(feature_type, want_type);
            assert_eq!(name, Some(want_name));
            if let Some(area) = area {
                assert_close(lod2_area(multi_surface), area);
            }
        }
    }

    #[test]
    fn garage_relief() {
        let city_model = city_model();
        let features = features(&city_model);
        let reliefs: Vec<&ReliefFeature> = features
            .iter()
            .filter_map(|f| ReliefFeature::try_from(f))
            .collect();
        let [relief] = reliefs[..] else {
            panic!("expected one relief feature");
        };
        assert_eq!(
            relief.feature_id().as_str(),
            "GML_6bb30328-7599-4500-90ef-766fde6aa67b"
        );
        assert_eq!(names(relief.names()), ["Example TIN LOD2"]);
        assert_eq!(relief.lod(), LevelOfDetail::Two);
        let components = items!(relief.relief_components());
        let [component] = components[..] else {
            panic!("expected one relief component");
        };
        assert!(component.href().is_none());
        assert_eq!(
            component.object().expect("should be inline").feature_type(),
            FeatureType::TinRelief
        );

        let tin_reliefs: Vec<&TinRelief> = features
            .iter()
            .filter_map(|f| TinRelief::try_from(f))
            .collect();
        let [tin_relief] = tin_reliefs[..] else {
            panic!("expected one TIN relief");
        };
        assert_eq!(
            tin_relief.feature_id().as_str(),
            "GML_4eb161b0-aa7e-4087-937c-5c4c427c7fc9"
        );
        assert_eq!(names(tin_relief.names()), ["Ground"]);
        assert_eq!(tin_relief.lod(), LevelOfDetail::Two);
        let tin = tin_relief.tin().expect("should have a TIN");
        assert!(tin.href().is_none());
        let surface = tin.object().expect("should be inline");
        assert_eq!(items!(surface.triangles()).len(), 12);
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
        let features = features(&written);
        let mut ids: Vec<&str> = Vec::new();
        ids.extend(
            features
                .iter()
                .filter_map(|f| Building::try_from(f))
                .map(|b| b.feature_id().as_str()),
        );
        ids.extend(
            features
                .iter()
                .filter_map(|f| BuildingPart::try_from(f))
                .map(|p| p.feature_id().as_str()),
        );
        ids.extend(
            features
                .iter()
                .filter_map(|f| ReliefFeature::try_from(f))
                .map(|r| r.feature_id().as_str()),
        );
        ids.extend(
            features
                .iter()
                .filter_map(|f| TinRelief::try_from(f))
                .map(|t| t.feature_id().as_str()),
        );
        assert_eq!(
            ids,
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

    fn city_model() -> Box<CityModel> {
        read(DATASET, "BuildingUnits_Storeys_xlink.gml")
    }

    fn storeys(city_model: &CityModel) -> Vec<&Storey> {
        features(city_model)
            .iter()
            .filter_map(|f| Storey::try_from(f))
            .collect()
    }

    /// The `href`s of a storey's LoD2 surface members (`None` for inline members).
    fn member_hrefs(storey: &Storey) -> Vec<Option<String>> {
        let property = storey
            .lod2_multi_surface()
            .expect("should have an LoD2 multi surface");
        assert!(property.href().is_none());
        items!(
            property
                .object()
                .expect("should be inline")
                .surface_member()
        )
        .into_iter()
        .map(|member| {
            assert_eq!(member.object().is_none(), member.href().is_some());
            member.href().map(|href| written(|w| href.to_string(w)))
        })
        .collect()
    }

    #[test]
    fn units_city_model() {
        use FeatureType::*;
        let city_model = city_model();
        assert_eq!(city_model.city_objects_len(), 1);
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
        assert_eq!(items!(city_model.iter_city_objects()).len(), 41);
    }

    #[test]
    fn units_building() {
        use FeatureType::{GroundSurface as Ground, RoofSurface as Roof, WallSurface as Wall};
        let city_model = city_model();
        let features = features(&city_model);
        let building = features
            .iter()
            .find_map(|f| Building::try_from(f))
            .expect("should have a building");
        assert_eq!(building.feature_id().as_str(), "building_unit_example_1");
        assert!(building.names().next().is_none());
        assert!(building.functions().next().is_none());
        assert!(building.usages().next().is_none());
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
        let surfaces = surfaces(building.boundaries());
        assert_eq!(surfaces.len(), expected.len());
        for ((feature_type, _, name, multi_surface), (want_type, want_name, area)) in
            surfaces.into_iter().zip(expected)
        {
            assert_eq!(feature_type, want_type);
            assert_eq!(name, Some(want_name));
            assert_close(lod2_area(multi_surface), area);
        }
    }

    #[test]
    fn units_subdivisions() {
        let city_model = city_model();
        let features = features(&city_model);
        let building = features
            .iter()
            .find_map(|f| Building::try_from(f))
            .expect("should have a building");
        let types: Vec<FeatureType> = items!(building.building_subdivisions())
            .into_iter()
            .map(|property| {
                assert!(property.href().is_none());
                property.object().expect("should be inline").feature_type()
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

        let units: Vec<&BuildingUnit> = features
            .iter()
            .filter_map(|f| BuildingUnit::try_from(f))
            .collect();
        assert_eq!(
            units
                .iter()
                .map(|u| u.feature_id().as_str())
                .collect::<Vec<_>>(),
            ["BuildingUnit_apartment1", "BuildingUnit_apartment2"]
        );
        for unit in units {
            assert_eq!(
                items!(unit.functions())
                    .iter()
                    .map(|f| f.value())
                    .collect::<Vec<_>>(),
                ["apartment"]
            );
            assert!(unit.class().is_none());
            assert!(unit.usages().next().is_none());
            assert!(unit.boundaries().next().is_none());
            assert!(unit.lod2_multi_surface().is_none());
        }

        let storeys = storeys(&city_model);
        assert_eq!(
            storeys
                .iter()
                .map(|s| s.feature_id().as_str())
                .collect::<Vec<_>>(),
            ["storey1", "storey2"]
        );
        for storey in storeys {
            assert!(storey.names().next().is_none());
            assert!(storey.class().is_none());
            assert!(storey.functions().next().is_none());
            assert!(storey.usages().next().is_none());
            assert!(storey.boundaries().next().is_none());
        }
    }

    #[test]
    fn units_storey_geometry() {
        let city_model = city_model();
        let storeys = storeys(&city_model);
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
        let features = features(&written);
        let building = features
            .iter()
            .find_map(|f| Building::try_from(f))
            .expect("should have a building");
        assert_eq!(building.feature_id().as_str(), "building_unit_example_1");
        let hrefs = |model: &CityModel| -> Vec<Vec<Option<String>>> {
            storeys(model).iter().map(|s| member_hrefs(s)).collect()
        };
        assert_eq!(hrefs(&written), hrefs(&city_model));
    }
}

mod road_bridge {
    use super::*;

    fn city_model() -> Box<CityModel> {
        read(
            DATASET,
            "Road_over_Bridge_CityGML3.0_LOD2_with_CityObjectRelations.gml",
        )
    }

    fn relation_list(
        id: &str,
        related_to: Box<CityObjectRelationPropertyIterator<'_>>,
    ) -> Vec<(String, String, Option<String>)> {
        items!(related_to)
            .into_iter()
            .map(|property| {
                assert!(property.href().is_none());
                let relation = property.object().expect("should be inline");
                assert!(relation.generic_attributes().next().is_none());
                (
                    id.to_owned(),
                    relation.relation_type().value().to_owned(),
                    relation
                        .relation_to()
                        .href()
                        .map(|href| written(|w| href.to_string(w))),
                )
            })
            .collect()
    }

    /// The relations of the roof surfaces and traffic areas, in document order: (city object, relation type, `href`
    /// of `relation_to`).
    fn relations(city_model: &CityModel) -> Vec<(String, String, Option<String>)> {
        features(city_model)
            .iter()
            .flat_map(|feature| {
                if let Some(roof) = RoofSurface::try_from(feature) {
                    relation_list(roof.feature_id().as_str(), roof.related_to())
                } else if let Some(area) = TrafficArea::try_from(feature) {
                    relation_list(area.feature_id().as_str(), area.related_to())
                } else {
                    Vec::new()
                }
            })
            .collect()
    }

    #[test]
    fn road_bridge_city_model() {
        use FeatureType::*;
        let city_model = city_model();
        assert_eq!(city_model.city_objects_len(), 2);
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
        assert_eq!(items!(city_model.iter_city_objects()).len(), 24);
    }

    #[test]
    fn road_bridge_bridge() {
        let city_model = city_model();
        let features = features(&city_model);
        let bridge = features
            .iter()
            .find_map(|f| Bridge::try_from(f))
            .expect("should have a bridge");
        assert_eq!(bridge.feature_id().as_str(), "id_bridge1");
        assert!(bridge.names().next().is_none());
        assert!(bridge.related_to().next().is_none());
        let expected = [
            ("id_groundsurface1", 77500.15996032),
            ("id_roofsurface1", 38750.07998016),
            ("id_roofsurface2", 38750.07998016),
            ("id_wallsurface4", 10075.02000744),
            ("id_wallsurface1", 20150.04001488),
            ("id_wallsurface2", 10075.02000744),
            ("id_wallsurface3", 20150.04001488),
        ];
        let surfaces = surfaces(bridge.boundaries());
        assert_eq!(surfaces.len(), expected.len());
        for ((_, id, _, multi_surface), (want_id, area)) in surfaces.into_iter().zip(expected) {
            assert_eq!(id, want_id);
            assert_close(lod2_area(multi_surface), area);
        }
    }

    #[test]
    fn road_bridge_road() {
        let city_model = city_model();
        let features = features(&city_model);
        let road = features
            .iter()
            .find_map(|f| Road::try_from(f))
            .expect("should have a road");
        assert_eq!(road.feature_id().as_str(), "id_road1");
        assert!(road.related_to().next().is_none());
        assert!(road.traffic_spaces().next().is_none());
        assert!(road.auxiliary_traffic_spaces().next().is_none());
        let sections: Vec<_> = items!(road.sections())
            .into_iter()
            .map(|property| {
                assert!(property.href().is_none());
                property.object().expect("should be inline")
            })
            .collect();
        assert_eq!(
            sections
                .iter()
                .map(|s| s.feature_id().as_str())
                .collect::<Vec<_>>(),
            ["id_section1", "id_section2", "id_section3"]
        );
        let spaces: Vec<_> = sections
            .iter()
            .flat_map(|section| items!(section.traffic_spaces()))
            .map(|property| {
                assert!(property.href().is_none());
                property.object().expect("should be inline")
            })
            .collect();
        let numbers = [1, 2, 5, 6, 3, 4];
        assert_eq!(spaces.len(), numbers.len());
        for (space, number) in spaces.iter().zip(numbers) {
            assert_eq!(
                space.feature_id().as_str(),
                format!("id_trafficspace{number}")
            );
            let boundaries = items!(space.boundaries());
            let [boundary] = boundaries[..] else {
                panic!("expected one boundary");
            };
            assert!(boundary.href().is_none());
            let area = boundary.object().expect("should be inline");
            assert_eq!(area.feature_type(), FeatureType::TrafficArea);
            assert_eq!(
                area.feature_id().as_str(),
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
        .map(|(object, href)| (object.to_owned(), "equal".to_owned(), Some(href.to_owned())));
        assert_eq!(relations(&city_model), expected);
        let features = features(&city_model);
        for feature in &features {
            if let Some(wall) = WallSurface::try_from(feature) {
                assert!(wall.related_to().next().is_none());
            }
            if let Some(ground) = GroundSurface::try_from(feature) {
                assert!(ground.related_to().next().is_none());
            }
        }
    }

    #[test]
    fn road_bridge_round_trip() {
        let city_model = city_model();
        let written = round_trip(&city_model);
        assert_eq!(feature_types(&written), feature_types(&city_model));
        let features = features(&written);
        let bridges: Vec<&str> = features
            .iter()
            .filter_map(|f| Bridge::try_from(f))
            .map(|b| b.feature_id().as_str())
            .collect();
        assert_eq!(bridges, ["id_bridge1"]);
        let roads: Vec<&str> = features
            .iter()
            .filter_map(|f| Road::try_from(f))
            .map(|r| r.feature_id().as_str())
            .collect();
        assert_eq!(roads, ["id_road1"]);
        assert_eq!(relations(&written), relations(&city_model));
    }
}

mod versioning {
    use super::*;

    fn city_model() -> Box<CityModel> {
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
    fn date(date_time: Option<&DateTime>) -> Option<(i32, u32, u32)> {
        date_time.map(|d| {
            assert_eq!((d.hour(), d.minute(), d.offset_seconds()), (0, 0, 0));
            (d.year(), d.month(), d.day())
        })
    }

    fn buildings(city_model: &CityModel) -> Vec<&Building> {
        features(city_model)
            .iter()
            .filter_map(|f| Building::try_from(f))
            .collect()
    }

    #[test]
    fn versioning_city_model() {
        use FeatureType::*;
        let city_model = city_model();
        assert_eq!(city_model.city_objects_len(), 4);
        assert!(city_model.bounded_by().is_none());
        let types = feature_types(&city_model);
        assert_eq!(types.len(), 60);
        assert_eq!(types[0], CityModel);
        for (feature_type, count) in [
            (CityModel, 1),
            (Building, 4),
            (BuildingPart, 5),
            (RoofSurface, 14),
            (WallSurface, 31),
            (GroundSurface, 5),
        ] {
            assert_eq!(
                types.iter().filter(|t| **t == feature_type).count(),
                count,
                "{feature_type:?}"
            );
        }
        assert_eq!(items!(city_model.iter_city_objects()).len(), 59);
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
        let buildings = buildings(&city_model);
        assert_eq!(buildings.len(), expected.len());
        for (building, (id, name, created, terminated, parts)) in buildings.iter().zip(expected) {
            assert_eq!(building.feature_id().as_str(), id);
            assert_eq!(names(building.names()).first(), Some(&name));
            assert_eq!(date(building.creation_date()), Some(created));
            assert_eq!(date(building.termination_date()), terminated);
            let part_ids: Vec<&str> = items!(building.building_parts())
                .into_iter()
                .map(|property| {
                    assert!(property.href().is_none());
                    property
                        .object()
                        .expect("should be inline")
                        .feature_id()
                        .as_str()
                })
                .collect();
            assert_eq!(part_ids, parts);
            assert!(building.heights().next().is_none());
            assert!(building.boundaries().next().is_none());
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
        let features = features(&city_model);
        let parts: Vec<&BuildingPart> = features
            .iter()
            .filter_map(|f| BuildingPart::try_from(f))
            .collect();
        assert_eq!(parts.len(), expected.len());
        for (part, (id, height, boundaries)) in parts.iter().zip(expected) {
            assert_eq!(part.feature_id().as_str(), id);
            assert_height(part.heights(), height);
            assert_eq!(items!(part.boundaries()).len(), boundaries);
            assert!(part.creation_date().is_none());
            assert!(part.names().next().is_none());
        }
    }

    #[test]
    fn versioning_round_trip() {
        let city_model = city_model();
        let written = round_trip(&city_model);
        assert_eq!(feature_types(&written), feature_types(&city_model));
        let ids = |model: &CityModel| -> Vec<String> {
            let features = features(model);
            let mut ids: Vec<String> = features
                .iter()
                .filter_map(|f| Building::try_from(f))
                .map(|b| b.feature_id().as_str().to_owned())
                .collect();
            ids.extend(
                features
                    .iter()
                    .filter_map(|f| BuildingPart::try_from(f))
                    .map(|p| p.feature_id().as_str().to_owned()),
            );
            ids
        };
        assert_eq!(ids(&written), ids(&city_model));
        let dates = |model: &CityModel| -> Vec<_> {
            buildings(model)
                .iter()
                .map(|b| (date(b.creation_date()), date(b.termination_date())))
                .collect()
        };
        assert_eq!(dates(&written), dates(&city_model));
    }
}
