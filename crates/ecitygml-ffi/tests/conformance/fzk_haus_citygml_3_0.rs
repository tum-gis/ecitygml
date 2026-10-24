//! The cases of `crates/ecitygml/tests/conformance/fzk-haus-citygml-3.0.md`.

use crate::{assert_close, read};
use ecitygml_ffi::citygml::core::model::building::building::Building;
use ecitygml_ffi::citygml::core::model::building::storey::Storey;
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
use ecitygml_ffi::gml::core::model::basic_types::code::CodeIterator;
use ecitygml_ffi::gml::core::model::geometry::aggregates::multi_surface_property::MultiSurfaceProperty;
use ecitygml_ffi::gml::core::model::geometry::direct_position::DirectPosition;

const DATASET: &str = "fzk-haus-citygml-3.0";

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

fn building(city_model: &CityModel) -> &Building {
    features(city_model)
        .iter()
        .find_map(|feature| Building::try_from(feature))
        .expect("should have a building")
}

fn storeys(city_model: &CityModel) -> Vec<&Storey> {
    features(city_model)
        .iter()
        .filter_map(|feature| Storey::try_from(feature))
        .collect()
}

fn first_name(names: Box<CodeIterator<'_>>) -> &str {
    items!(names).first().expect("should have a name").value()
}

fn feature_types(city_model: &CityModel) -> Vec<FeatureType> {
    features(city_model)
        .iter()
        .map(|feature| feature.feature_type())
        .collect()
}

/// Asserts the number of features per feature type, over `iter_features`, and that there are no others.
fn assert_feature_type_counts(city_model: &CityModel, expected: &[(FeatureType, usize)]) {
    let types = feature_types(city_model);
    for (feature_type, count) in expected {
        assert_eq!(
            types.iter().filter(|t| *t == feature_type).count(),
            *count,
            "{feature_type:?}"
        );
    }
    assert_eq!(
        types.len(),
        expected.iter().map(|(_, count)| count).sum::<usize>()
    );
}

fn assert_point_close(position: &DirectPosition, expected: (f64, f64, f64)) {
    assert_close(position.x(), expected.0);
    assert_close(position.y(), expected.1);
    assert_close(position.z(), expected.2);
}

fn assert_city_model(city_model: &CityModel, lower: (f64, f64, f64), upper: (f64, f64, f64)) {
    assert_eq!(city_model.city_objects_len(), 1);
    let envelope = city_model
        .bounded_by()
        .and_then(|shape| shape.envelope())
        .expect("should have an envelope");
    assert_point_close(envelope.lower_corner(), lower);
    assert_point_close(envelope.upper_corner(), upper);
}

/// The one height of the storey examples' buildings.
fn assert_height(building: &Building) {
    let heights = items!(building.heights());
    let [height] = heights[..] else {
        panic!("expected one height");
    };
    assert_eq!(height.high_reference().value(), "highestRoofEdge");
    assert_eq!(height.low_reference().value(), "lowestGroundPoint");
    assert_eq!(height.status(), HeightStatusValue::Measured);
    assert_close(height.length().value(), 6.52);
    assert_eq!(height.length().uom(), "urn:adv:uom:m");
}

/// The one occupancy of the storey examples' buildings.
fn assert_occupancy(building: &Building) {
    let occupancies = items!(building.occupancies());
    let [occupancy] = occupancies[..] else {
        panic!("expected one occupancy");
    };
    assert_eq!(occupancy.number_of_occupants(), 2);
}

/// The storeys' first names and classes.
fn assert_storeys(city_model: &CityModel, classes: [Option<&str>; 2]) {
    let storeys = storeys(city_model);
    assert_eq!(
        storeys
            .iter()
            .map(|s| first_name(s.names()))
            .collect::<Vec<_>>(),
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

/// A storey's boundaries as (feature type, first name, LoD2 multi surface); fails on a reference-only boundary or
/// one that is no wall, roof or ground surface.
fn boundary_surfaces(storey: &Storey) -> Vec<(FeatureType, &str, Option<&MultiSurfaceProperty>)> {
    items!(storey.boundaries())
        .into_iter()
        .map(|property| {
            assert!(property.href().is_none());
            let feature = AbstractFeatureKindRef::from_space_boundary(
                property.object().expect("should be inline"),
            );
            let feature_type = feature.feature_type();
            if let Some(wall) = WallSurface::try_from(&feature) {
                (
                    feature_type,
                    first_name(wall.names()),
                    wall.lod2_multi_surface(),
                )
            } else if let Some(roof) = RoofSurface::try_from(&feature) {
                (
                    feature_type,
                    first_name(roof.names()),
                    roof.lod2_multi_surface(),
                )
            } else if let Some(ground) = GroundSurface::try_from(&feature) {
                (
                    feature_type,
                    first_name(ground.names()),
                    ground.lod2_multi_surface(),
                )
            } else {
                panic!("unexpected boundary {feature_type:?}")
            }
        })
        .collect()
}

/// Writes the city model and reads it back; asserts the same feature types in the same order and the building's id.
fn assert_round_trip(city_model: &CityModel, building_id: &str) {
    let mut writer = GmlWriter::new(CitygmlFormat::Gml);
    writer
        .finish(city_model)
        .unwrap_or_else(|_| panic!("should write"));
    let written = GmlReader::new(writer.data(), CitygmlFormat::Gml)
        .finish()
        .unwrap_or_else(|_| panic!("should read"));
    assert_eq!(feature_types(&written), feature_types(city_model));
    assert_eq!(building(&written).feature_id().as_str(), building_id);
}

mod construction {
    use super::*;

    const BUILDING_ID: &str = "_FZK-Haus-Storey-Construction_BD.DX9Xm6VLbbyLGAxG2v86";

    fn city_model() -> Box<CityModel> {
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
        assert_eq!(items!(city_model.iter_city_objects()).len(), 14);
    }

    #[test]
    fn construction_building() {
        let city_model = city_model();
        let building = building(&city_model);
        assert_eq!(building.feature_id().as_str(), BUILDING_ID);
        assert_eq!(
            items!(building.names())
                .iter()
                .map(|n| n.value())
                .collect::<Vec<_>>(),
            ["KIT FZK-Haus"]
        );
        assert!(building.class().is_none());
        assert_eq!(
            items!(building.functions())
                .iter()
                .map(|f| f.value())
                .collect::<Vec<_>>(),
            ["31001_1000"]
        );
        assert!(building.usages().next().is_none());
        assert_eq!(building.roof_type().map(|r| r.value()), Some("3100"));
        assert_eq!(building.storeys_above_ground(), None);
        assert_eq!(building.storeys_below_ground(), None);
        assert_height(building);
        assert_occupancy(building);
        assert!(building.boundaries().next().is_none());
        assert!(building.generic_attributes().next().is_none());
        assert!(building.lod2_solid().is_none());
        assert!(building.lod2_multi_surface().is_none());
    }

    #[test]
    fn construction_storeys() {
        let city_model = city_model();
        let subdivisions = items!(building(&city_model).building_subdivisions());
        assert_eq!(subdivisions.len(), 2);
        for subdivision in subdivisions {
            assert!(subdivision.href().is_none());
            let object = subdivision.object().expect("should be inline");
            assert_eq!(object.feature_type(), FeatureType::Storey);
        }
        assert_storeys(
            &city_model,
            [Some("Entrance Floor"), Some("non Entrance Floor")],
        );
        for storey in storeys(&city_model) {
            assert!(storey.functions().next().is_none());
            assert!(storey.usages().next().is_none());
            assert!(storey.boundaries().next().is_none());
            assert!(storey.lod2_solid().is_none());
        }
    }

    #[test]
    fn construction_round_trip() {
        assert_round_trip(&city_model(), BUILDING_ID);
    }
}

mod interior {
    use super::*;

    const BUILDING_ID: &str = "KIT-Test-Building-01";

    fn city_model() -> Box<CityModel> {
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
        assert_feature_type_counts(
            &city_model,
            &[
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
            ],
        );
        assert_eq!(items!(city_model.iter_city_objects()).len(), 69);
    }

    #[test]
    fn interior_building() {
        let city_model = city_model();
        let building = building(&city_model);
        assert_eq!(building.feature_id().as_str(), BUILDING_ID);
        assert_eq!(
            items!(building.names())
                .iter()
                .map(|n| n.value())
                .collect::<Vec<_>>(),
            ["KIT Test Building FZK-Haus for CityGML 3.0"]
        );
        assert!(building.class().is_none());
        assert!(building.roof_type().is_none());
        assert!(building.functions().next().is_none());
        assert!(building.usages().next().is_none());
        assert_height(building);
        assert_occupancy(building);
        let attributes = items!(building.generic_attributes());
        let [attribute] = attributes[..] else {
            panic!("expected one generic attribute");
        };
        assert_eq!(
            (attribute.name(), attribute.as_string().map(|s| s.value())),
            ("@cityeditor:layer", Some("LoD2-Ausgeblendet"))
        );
        assert!(building.boundaries().next().is_none());
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
        let members = items!(shell.members());
        assert_eq!(members.len(), 11);
        assert!(members.iter().all(|member| member.object().is_none()));
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
            let surfaces = boundary_surfaces(storey);
            assert_eq!(surfaces.len(), expected.len());
            for ((feature_type, name, multi_surface), (expected_type, expected_name, area)) in
                surfaces.iter().zip(expected)
            {
                assert_eq!(feature_type, expected_type);
                assert_eq!(name, expected_name);
                let multi_surface = multi_surface
                    .and_then(|property| property.object())
                    .expect("should have an LoD2 multi surface");
                assert_close(multi_surface.area_3d().expect("should compute"), *area);
            }
        }
        assert_storeys(&city_model, [None, None]);
    }

    #[test]
    fn interior_round_trip() {
        assert_round_trip(&city_model(), BUILDING_ID);
    }
}

mod window {
    use super::*;

    const BUILDING_ID: &str = "_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz";

    fn city_model() -> Box<CityModel> {
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
        assert_feature_type_counts(
            &city_model,
            &[
                (CityModel, 1),
                (Building, 1),
                (Storey, 2),
                (BuildingConstructiveElement, 18),
                (Door, 5),
                (Window, 11),
                (Appearance, 2),
                (ParameterizedTexture, 5),
                (X3DMaterial, 9),
            ],
        );
        assert_eq!(items!(city_model.iter_city_objects()).len(), 37);
    }

    #[test]
    fn window_building() {
        let city_model = city_model();
        let building = building(&city_model);
        assert_eq!(building.feature_id().as_str(), BUILDING_ID);
        assert_eq!(
            items!(building.names())
                .iter()
                .map(|n| n.value())
                .collect::<Vec<_>>(),
            ["KIT FZK-Haus"]
        );
        assert_eq!(
            items!(building.functions())
                .iter()
                .map(|f| f.value())
                .collect::<Vec<_>>(),
            ["31001_1000"]
        );
        assert_eq!(building.roof_type().map(|r| r.value()), Some("3100"));
        assert!(building.boundaries().next().is_none());
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

    fn city_model() -> Box<CityModel> {
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
        assert_eq!(building.feature_id().as_str(), BUILDING_ID);
        assert!(building.boundaries().next().is_none());
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
            let surfaces = boundary_surfaces(storey);
            assert_eq!(
                surfaces
                    .iter()
                    .map(|(feature_type, name, _)| (*feature_type, *name))
                    .collect::<Vec<_>>(),
                expected
            );
            assert!(
                surfaces
                    .iter()
                    .all(|(_, _, multi_surface)| multi_surface.is_none())
            );
        }
    }

    #[test]
    fn point_cloud_round_trip() {
        assert_round_trip(&city_model(), BUILDING_ID);
    }
}
