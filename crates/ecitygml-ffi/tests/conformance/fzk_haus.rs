//! The cases of `crates/ecitygml/tests/conformance/fzk-haus.md`.

use crate::{assert_close, read};
use ecitygml_ffi::citygml::core::model::building::building::Building;
use ecitygml_ffi::citygml::core::model::common::feature_type::FeatureType;
use ecitygml_ffi::citygml::core::model::construction::door_surface::DoorSurface;
use ecitygml_ffi::citygml::core::model::construction::enums::height_status_value::HeightStatusValue;
use ecitygml_ffi::citygml::core::model::construction::ground_surface::GroundSurface;
use ecitygml_ffi::citygml::core::model::construction::roof_surface::RoofSurface;
use ecitygml_ffi::citygml::core::model::construction::wall_surface::WallSurface;
use ecitygml_ffi::citygml::core::model::construction::window_surface::WindowSurface;
use ecitygml_ffi::citygml::core::model::core::city_model::CityModel;
use ecitygml_ffi::citygml::core::model::core::enums::relative_to_terrain::RelativeToTerrain;
use ecitygml_ffi::citygml::core::model::core::refs::abstract_feature_kind_ref::AbstractFeatureKindRef;
use ecitygml_ffi::citygml::core::model::generics::measure_attribute::MeasureAttribute;
use ecitygml_ffi::citygml::io::format::CitygmlFormat;
use ecitygml_ffi::citygml::io::gml::read::GmlReader;
use ecitygml_ffi::citygml::io::gml::write::GmlWriter;
use ecitygml_ffi::gml::core::model::common::scale3::Scale3;
use ecitygml_ffi::gml::core::model::common::vector3::Vector3;
use ecitygml_ffi::gml::core::model::geometry::aggregates::multi_surface::MultiSurface;
use ecitygml_ffi::gml::core::model::geometry::complexes::composite_surface::CompositeSurface;
use ecitygml_ffi::gml::core::model::geometry::direct_position::DirectPosition;
use ecitygml_ffi::gml::core::model::geometry::primitives::linear_ring::LinearRing;
use ecitygml_ffi::gml::core::model::geometry::primitives::polygon::Polygon;

fn features(city_model: &CityModel) -> Vec<Box<AbstractFeatureKindRef<'_>>> {
    let mut features = city_model.iter_features();
    std::iter::from_fn(|| features.next()).collect()
}

fn building(city_model: &CityModel) -> &Building {
    features(city_model)
        .iter()
        .find_map(|feature| Building::try_from(feature))
        .expect("should have a building")
}

/// The building's boundaries, as features.
fn boundaries<'a>(building: &'a Building) -> Vec<Box<AbstractFeatureKindRef<'a>>> {
    let mut boundaries = building.boundaries();
    std::iter::from_fn(|| boundaries.next())
        .map(|property| {
            AbstractFeatureKindRef::from_space_boundary(property.object().expect("inline"))
        })
        .collect()
}

fn point(position: &DirectPosition) -> (f64, f64, f64) {
    (position.x(), position.y(), position.z())
}

fn assert_point_close(actual: (f64, f64, f64), expected: (f64, f64, f64)) {
    assert_close(actual.0, expected.0);
    assert_close(actual.1, expected.1);
    assert_close(actual.2, expected.2);
}

/// The number of items of a Diplomat iterator.
macro_rules! count {
    // A match keeps the temporaries the iterator borrows from alive.
    ($iterator:expr) => {
        match $iterator {
            mut iterator => std::iter::from_fn(|| iterator.next()).count(),
        }
    };
}

mod lod1 {
    use super::*;

    fn city_model() -> Box<CityModel> {
        read("fzk-haus", "FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml")
    }

    #[test]
    fn lod1_city_model() {
        let city_model = city_model();
        assert_eq!(city_model.city_objects_len(), 1);
        let envelope = city_model
            .bounded_by()
            .and_then(|shape| shape.envelope())
            .expect("should have an envelope");
        let (lower, upper) = (envelope.lower_corner(), envelope.upper_corner());
        for (actual, expected) in [
            (lower.x(), 457842.0),
            (lower.y(), 5439083.0),
            (lower.z(), 111.8),
            (upper.x(), 457854.0),
            (upper.y(), 5439093.0),
            (upper.z(), 118.317669),
        ] {
            assert_close(actual, expected);
        }
    }

    #[test]
    fn lod1_building_attributes() {
        let city_model = city_model();
        let building = building(&city_model);
        assert_eq!(
            building.feature_id().as_str(),
            "UUID_d281adfc-4901-0f52-540b-4cc1a9325f82"
        );
        let mut names = building.names();
        assert_eq!(
            std::iter::from_fn(|| names.next())
                .map(|n| n.value())
                .collect::<Vec<_>>(),
            ["AC14-FZK-Haus"]
        );
        assert_eq!(building.class().map(|class| class.value()), Some("1000"));
        let mut functions = building.functions();
        assert_eq!(
            std::iter::from_fn(|| functions.next())
                .map(|f| f.value())
                .collect::<Vec<_>>(),
            ["1000"]
        );
        let mut usages = building.usages();
        assert_eq!(
            std::iter::from_fn(|| usages.next())
                .map(|u| u.value())
                .collect::<Vec<_>>(),
            ["1000"]
        );
        assert_eq!(building.roof_type().map(|r| r.value()), Some("1030"));
        assert_eq!(building.storeys_above_ground(), Some(2));
        assert_eq!(building.storeys_below_ground(), Some(0));

        let date = building.date_of_construction().expect("should have a date");
        assert_eq!((date.year(), date.month(), date.day()), (2020, 1, 1));
        assert!(building.date_of_demolition().is_none());
        let mut heights = building.heights();
        let height = heights.next().expect("should have a height");
        assert!(heights.next().is_none());
        assert_eq!(height.high_reference().value(), "topOfConstruction");
        assert_eq!(height.low_reference().value(), "lowestGroundPoint");
        assert_eq!(height.status(), HeightStatusValue::Measured);
        assert_close(height.length().value(), 6.52);
        assert_eq!(height.length().uom(), "m");
        assert!(building.occupancies().next().is_none());
        assert!(building.building_parts().next().is_none());
    }

    #[test]
    fn lod1_solid() {
        let city_model = city_model();
        let building = building(&city_model);
        let solid = building
            .lod1_solid()
            .and_then(|property| property.object())
            .expect("should have an LoD1 solid");
        assert_close(solid.volume_3d().expect("should compute"), 782.1228);
        let triangulation = solid.triangulate().expect("should triangulate");
        let mut triangles = triangulation.surface().triangles();
        assert_eq!(std::iter::from_fn(|| triangles.next()).count(), 12);
        assert!(!triangulation.has_skipped());
        assert!(building.boundaries().next().is_none());
    }

    #[test]
    fn lod1_envelope_measures() {
        let city_model = city_model();
        let envelope = city_model
            .bounded_by()
            .and_then(|shape| shape.envelope())
            .expect("should have an envelope");
        assert_close(envelope.size_x(), 12.0);
        assert_close(envelope.size_y(), 10.0);
        assert_close(envelope.size_z(), 6.517669);
        assert_point_close(
            point(&envelope.center()),
            (457848.0, 5439088.0, 115.0588345),
        );
        assert_close(envelope.volume(), 782.12028);
        assert!(envelope.contains(envelope.lower_corner()));
        assert!(envelope.contains(envelope.upper_corner()));
        let at = |x, y, z| DirectPosition::new(x, y, z).expect("finite");
        assert!(envelope.contains(&at(457848.0, 5439088.0, 115.0)));
        assert!(!envelope.contains(&at(457848.0, 5439088.0, 118.4)));
        assert!(!envelope.contains(&at(457841.9, 5439088.0, 115.0)));
        assert!(city_model.creation_date().is_none());
    }

    #[test]
    fn lod1_building_details() {
        let city_model = city_model();
        let features = features(&city_model);
        assert_eq!(
            features
                .iter()
                .filter(|f| Building::try_from(f).is_some())
                .count(),
            1
        );
        let building = building(&city_model);
        assert_eq!(
            building.id().map(|id| id.as_str()),
            Some("UUID_d281adfc-4901-0f52-540b-4cc1a9325f82")
        );
        let envelope = building
            .bounded_by()
            .and_then(|shape| shape.envelope())
            .expect("should have an envelope");
        assert_point_close(point(envelope.lower_corner()), (457842.0, 5439083.0, 111.8));
        assert_point_close(
            point(envelope.upper_corner()),
            (457854.0, 5439093.0, 118.31769),
        );
        assert!(building.lod2_solid().is_none());
        assert!(building.lod0_multi_surface().is_none());
    }

    #[test]
    fn lod1_solid_structure() {
        let city_model = city_model();
        let solid = building(&city_model)
            .lod1_solid()
            .and_then(|property| property.object())
            .expect("should have an LoD1 solid");
        assert_eq!(count!(solid.interior()), 0);
        assert_eq!(count!(solid.points()), 24);
        let shell = solid.exterior().expect("should have an exterior shell");
        assert_close(shell.volume_3d().expect("should compute"), 782.1228);
        let mut members = shell.members();
        let members: Vec<_> = std::iter::from_fn(|| members.next()).collect();
        assert_eq!(members.len(), 6);
        let rings: Vec<&LinearRing> = members
            .iter()
            .map(|member| {
                assert!(member.href().is_none());
                let polygon =
                    Polygon::try_from(member.object().expect("inline")).expect("a polygon");
                assert_eq!(count!(polygon.interior()), 0);
                LinearRing::try_from(polygon.exterior().expect("should have an exterior"))
                    .expect("a linear ring")
            })
            .collect();
        for ring in &rings {
            assert_eq!(count!(ring.points()), 4);
            assert!(ring.area_3d() > 0.0);
        }
        assert_point_close(
            point(rings[0].points().next().expect("a point")),
            (457842.0, 5439083.0, 111.8),
        );
        assert_close(rings[0].length_3d(), 44.0);
        assert_close(rings[0].area_3d(), 120.0);
    }

    #[test]
    fn lod1_solid_triangulation() {
        let city_model = city_model();
        let solid = building(&city_model)
            .lod1_solid()
            .and_then(|property| property.object())
            .expect("should have an LoD1 solid");
        let triangulation = solid.triangulate().expect("should triangulate");
        assert!(triangulation.skipped().next().is_none());
        let surface = triangulation.surface();
        assert_close(surface.area_3d().expect("should compute"), 526.77836);
        assert_eq!(count!(surface.points()), 36);
        let triangle = surface.triangles().next().expect("a triangle");
        assert_close(triangle.a().z(), 111.8);
        assert_close(triangle.area(), 60.0);
        let shell = solid.exterior().expect("should have an exterior shell");
        assert_eq!(
            count!(
                shell
                    .triangulate()
                    .expect("should triangulate")
                    .surface()
                    .triangles()
            ),
            12
        );
        let first = Polygon::try_from(
            shell
                .members()
                .next()
                .expect("a member")
                .object()
                .expect("inline"),
        )
        .expect("a polygon");
        assert_eq!(
            count!(
                first
                    .triangulate()
                    .expect("should triangulate")
                    .surface()
                    .triangles()
            ),
            2
        );
    }

    #[test]
    fn lod1_apply_scale() {
        let mut city_model = city_model();
        city_model.apply_scale(Scale3 {
            x: 2.0,
            y: 3.0,
            z: 0.5,
        });
        let envelope = city_model
            .bounded_by()
            .and_then(|shape| shape.envelope())
            .expect("should have an envelope");
        assert_close(envelope.size_x(), 24.0);
        assert_close(envelope.size_y(), 30.0);
        assert_close(envelope.size_z(), 3.2588345);
    }
}

mod lod2 {
    use super::*;

    fn city_model() -> Box<CityModel> {
        read("fzk-haus", "FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml")
    }

    #[test]
    fn lod2_boundary_surfaces() {
        let city_model = city_model();
        let boundaries = boundaries(building(&city_model));
        assert_eq!(
            boundaries
                .iter()
                .map(|b| b.feature_type())
                .collect::<Vec<_>>(),
            [
                FeatureType::WallSurface,
                FeatureType::WallSurface,
                FeatureType::WallSurface,
                FeatureType::RoofSurface,
                FeatureType::WallSurface,
                FeatureType::RoofSurface,
                FeatureType::GroundSurface,
            ]
        );
        let walls: Vec<_> = boundaries
            .iter()
            .filter_map(|b| WallSurface::try_from(b))
            .map(|w| w.names().next().expect("named").value())
            .collect();
        let roofs: Vec<_> = boundaries
            .iter()
            .filter_map(|b| RoofSurface::try_from(b))
            .map(|r| r.names().next().expect("named").value())
            .collect();
        let grounds: Vec<_> = boundaries
            .iter()
            .filter_map(|b| GroundSurface::try_from(b))
            .map(|g| g.names().next().expect("named").value())
            .collect();
        assert_eq!(
            walls,
            [
                "Outer Wall 1 (West)",
                "Outer Wall 2 (South)",
                "Outer Wall 3 (East)",
                "Outer Wall 4 (North)"
            ]
        );
        assert_eq!(roofs, ["Roof 1 (North)", "Roof 2 (South)"]);
        assert_eq!(grounds, ["Base Surface"]);
    }

    #[test]
    fn lod2_surface_areas() {
        let city_model = city_model();
        let boundaries = boundaries(building(&city_model));
        macro_rules! lod2_area {
            ($ty:ty) => {
                boundaries
                    .iter()
                    .filter_map(|b| <$ty>::try_from(b))
                    .map(|surface| {
                        surface
                            .lod2_multi_surface()
                            .and_then(|property| property.object())
                            .expect("should have an LoD2 multi surface")
                            .area_3d()
                            .expect("should compute")
                    })
                    .sum::<f64>()
            };
        }
        assert_close(lod2_area!(WallSurface), 188.62887820601463);
        assert_close(lod2_area!(RoofSurface), 138.56406460961398);
        assert_close(lod2_area!(GroundSurface), 120.0);
    }

    #[test]
    fn lod2_generic_attributes() {
        let city_model = city_model();
        let building = building(&city_model);
        let mut attributes = building.generic_attributes();
        let attributes: Vec<_> = std::iter::from_fn(|| attributes.next()).collect();
        let [area, method, landmarked] = attributes.as_slice() else {
            panic!("expected three generic attributes");
        };
        let measure = MeasureAttribute::try_from(area).expect("should be a measure attribute");
        assert_eq!(area.name(), "GrossPlannedArea");
        assert_close(measure.value().value(), 120.0);
        assert_eq!(measure.value().uom(), "m2");
        assert_eq!(
            (method.name(), method.as_string().map(|s| s.value())),
            ("ConstructionMethod", Some("New Building"))
        );
        assert_eq!(
            (landmarked.name(), landmarked.as_string().map(|s| s.value())),
            ("IsLandmarked", Some("NO"))
        );
        assert!(building.external_references().next().is_none());
    }

    #[test]
    fn lod2_solid_unresolved() {
        let city_model = city_model();
        let solid = building(&city_model)
            .lod2_solid()
            .and_then(|property| property.object())
            .expect("should have an LoD2 solid");
        assert!(solid.volume_3d().is_err());
    }

    #[test]
    fn lod2_building_details() {
        let city_model = city_model();
        let b = building(&city_model);
        assert_eq!(
            b.relative_to_terrain(),
            Some(RelativeToTerrain::EntirelyAboveTerrain)
        );
        assert!(b.relative_to_water().is_none());
        let created = b.creation_date().expect("should have a creation date");
        assert_eq!(
            (
                created.year(),
                created.month(),
                created.day(),
                created.hour()
            ),
            (2017, 1, 23, 0)
        );
        assert_eq!(created.offset_seconds(), 3600);
        assert_eq!(created.timestamp(), 1485126000);
        assert!(b.termination_date().is_none());
        assert!(b.valid_from().is_none());
        assert!(b.valid_to().is_none());

        assert_eq!(b.class().map(|class| class.value()), Some("1000"));
        let mut functions = b.functions();
        assert_eq!(
            std::iter::from_fn(|| functions.next())
                .map(|f| f.value())
                .collect::<Vec<_>>(),
            ["1000"]
        );
        let mut usages = b.usages();
        assert_eq!(
            std::iter::from_fn(|| usages.next())
                .map(|u| u.value())
                .collect::<Vec<_>>(),
            ["1000"]
        );
        assert_eq!(b.roof_type().map(|r| r.value()), Some("1030"));
        assert_eq!(
            (b.storeys_above_ground(), b.storeys_below_ground()),
            (Some(2), Some(0))
        );
        let date = b.date_of_construction().expect("should have a date");
        assert_eq!((date.year(), date.month(), date.day()), (2020, 1, 1));
        assert!(b.date_of_demolition().is_none());
        let mut heights = b.heights();
        let height = heights.next().expect("should have a height");
        assert!(heights.next().is_none());
        assert_eq!(height.high_reference().value(), "topOfConstruction");
        assert_eq!(height.low_reference().value(), "lowestGroundPoint");
        assert_eq!(height.status(), HeightStatusValue::Measured);
        assert_close(height.length().value(), 6.52);
        assert_eq!(height.length().uom(), "m");

        assert!(b.occupancies().next().is_none());
        assert!(b.related_to().next().is_none());
        assert!(b.lod1_solid().is_none());
        assert!(b.bounded_by().is_none());
        assert!(b.lod1_terrain_intersection_curve().is_none());
        assert!(b.lod2_terrain_intersection_curve().is_none());
        assert!(b.lod3_terrain_intersection_curve().is_none());
        assert!(b.lod1_implicit_representation().is_none());
        assert!(b.lod2_implicit_representation().is_none());
        assert!(b.lod3_implicit_representation().is_none());
    }

    #[test]
    fn lod2_boundary_ids() {
        let city_model = city_model();
        let mut properties = building(&city_model).boundaries();
        let properties: Vec<_> = std::iter::from_fn(|| properties.next()).collect();
        assert!(properties.iter().all(|p| p.href().is_none()));
        assert_eq!(
            properties
                .iter()
                .map(|p| p.object().expect("inline").feature_id().as_str())
                .collect::<Vec<_>>(),
            [
                "GML_5856d7ad-5e34-498a-817b-9544bfbb1475",
                "GML_d38cf762-c29d-4491-88c9-bdc89e141978",
                "GML_8e5db638-e46a-4739-a98a-2fc2d39c9069",
                "GML_875d470b-32b4-4985-a4c8-0f02caa342a2",
                "GML_0f30f604-e70d-4dfe-ba35-853bc69609cc",
                "GML_eeb6796a-e261-4d3b-a6f2-475940cca80a",
                "GML_257a8dde-8194-4ca3-b581-abd591dcd6a3",
            ]
        );
    }

    #[test]
    fn lod2_wall_surface() {
        let city_model = city_model();
        let boundaries = boundaries(building(&city_model));
        let walls: Vec<&WallSurface> = boundaries
            .iter()
            .filter_map(|b| WallSurface::try_from(b))
            .collect();
        let wall = walls[0];
        assert_eq!(
            wall.id().map(|id| id.as_str()),
            Some("GML_5856d7ad-5e34-498a-817b-9544bfbb1475")
        );
        assert!(wall.lod0_multi_curve().is_none());
        assert!(wall.lod0_multi_surface().is_none());
        assert!(wall.lod1_multi_surface().is_none());
        assert!(wall.relative_to_terrain().is_none());
        assert!(wall.creation_date().is_none());
        assert!(wall.generic_attributes().next().is_none());
        assert!(wall.bounded_by().is_some());
        let multi_surface: &MultiSurface = wall
            .lod2_multi_surface()
            .and_then(|property| property.object())
            .expect("should have an LoD2 multi surface");
        assert_eq!(count!(multi_surface.surface_member()), 1);
        assert_eq!(
            count!(
                multi_surface
                    .triangulate()
                    .expect("should triangulate")
                    .surface()
                    .triangles()
            ),
            3
        );
        assert!(walls.iter().all(|w| w.filling_surfaces().next().is_none()));
        let ground = boundaries
            .iter()
            .find_map(|b| GroundSurface::try_from(b))
            .expect("should have a ground surface");
        let member = ground
            .lod2_multi_surface()
            .and_then(|property| property.object())
            .expect("should have an LoD2 multi surface")
            .surface_member()
            .next()
            .expect("a member");
        let ground_polygon =
            Polygon::try_from(member.object().expect("inline")).expect("a polygon");
        assert_eq!(
            count!(
                ground_polygon
                    .exterior()
                    .expect("should have an exterior")
                    .points()
            ),
            4
        );
    }

    #[test]
    fn lod2_generic_attribute_kinds() {
        let city_model = city_model();
        let mut attributes = building(&city_model).generic_attributes();
        let attributes: Vec<_> = std::iter::from_fn(|| attributes.next()).collect();
        assert!(attributes[0].as_string().is_none());
        assert!(MeasureAttribute::try_from(attributes[1]).is_none());
        assert!(MeasureAttribute::try_from(attributes[2]).is_none());
    }

    #[test]
    fn lod2_city_objects() {
        let city_model = city_model();
        let mut objects = city_model.iter_city_objects();
        assert_eq!(
            std::iter::from_fn(|| objects.next())
                .map(|o| o.feature_type())
                .collect::<Vec<_>>(),
            [
                FeatureType::Building,
                FeatureType::WallSurface,
                FeatureType::WallSurface,
                FeatureType::WallSurface,
                FeatureType::RoofSurface,
                FeatureType::WallSurface,
                FeatureType::RoofSurface,
                FeatureType::GroundSurface,
            ]
        );
        let types: Vec<FeatureType> = features(&city_model)
            .iter()
            .map(|f| f.feature_type())
            .collect();
        assert_eq!(types[0], FeatureType::CityModel);
        assert_eq!(
            types
                .iter()
                .filter(|t| **t == FeatureType::CityModel)
                .count(),
            1
        );
    }

    fn walls_bounded(city_model: &CityModel) -> Vec<bool> {
        features(city_model)
            .iter()
            .filter_map(|feature| WallSurface::try_from(feature))
            .map(|wall| wall.bounded_by().is_some())
            .collect()
    }

    #[test]
    fn lod2_object_bounds() {
        let path = format!(
            "{}/../../tests/fixtures/fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml",
            env!("CARGO_MANIFEST_DIR")
        );
        let mut reader = GmlReader::from_path(path.as_bytes()).unwrap_or_else(|_| panic!("{path}"));
        reader.with_rebuild_object_bounds(false);
        let mut city_model = reader.finish().unwrap_or_else(|_| panic!("{path}"));
        assert_eq!(walls_bounded(&city_model), [false; 4]);
        city_model.recompute_child_bounding_shapes();
        assert_eq!(walls_bounded(&city_model), [true; 4]);
    }

    /// The lower corners of the city model's envelope and of the first wall surface's.
    fn lower_corners(city_model: &CityModel) -> [(f64, f64, f64); 2] {
        let features = features(city_model);
        let wall = features
            .iter()
            .find_map(|f| WallSurface::try_from(f))
            .expect("a wall surface");
        [
            point(
                city_model
                    .bounded_by()
                    .and_then(|s| s.envelope())
                    .expect("an envelope")
                    .lower_corner(),
            ),
            point(
                wall.bounded_by()
                    .and_then(|s| s.envelope())
                    .expect("an envelope")
                    .lower_corner(),
            ),
        ]
    }

    #[test]
    fn lod2_apply_translation() {
        let mut city_model = city_model();
        for corner in lower_corners(&city_model) {
            assert_point_close(corner, (457842.0, 5439083.0, 111.8));
        }
        city_model.apply_translation(Vector3 {
            x: -100.0,
            y: 200.0,
            z: 10.0,
        });
        for corner in lower_corners(&city_model) {
            assert_point_close(corner, (457742.0, 5439283.0, 121.8));
        }
    }
}

mod lod3 {
    use super::*;

    fn city_model() -> Box<CityModel> {
        read("fzk-haus", "FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml")
    }

    #[test]
    fn lod3_doors_and_windows() {
        let city_model = city_model();
        let features = features(&city_model);
        let doors: Vec<&DoorSurface> = features
            .iter()
            .filter_map(|f| DoorSurface::try_from(f))
            .collect();
        assert_eq!(
            doors
                .iter()
                .map(|d| d.names().next().expect("named").value())
                .collect::<Vec<_>>(),
            ["Door West", "Door South"]
        );
        let area: f64 = doors
            .iter()
            .map(|door| {
                door.lod3_multi_surface()
                    .and_then(|property| property.object())
                    .expect("should have an LoD3 multi surface")
                    .area_3d()
                    .expect("should compute")
            })
            .sum();
        assert_close(area, 6.803850099444389);
        let windows = features
            .iter()
            .filter(|f| WindowSurface::try_from(f).is_some())
            .count();
        assert_eq!(windows, 11);
    }

    #[test]
    fn lod3_west_wall_fillings() {
        let city_model = city_model();
        let building = building(&city_model);
        let boundaries = boundaries(building);
        let wall = WallSurface::try_from(boundaries.first().expect("should have a boundary"))
            .expect("should be a wall surface");
        assert_eq!(
            wall.names().next().expect("named").value(),
            "Outer Wall 1 (West)"
        );
        let mut fillings = wall.filling_surfaces();
        let fillings: Vec<_> = std::iter::from_fn(|| fillings.next())
            .map(|property| property.object().expect("inline"))
            .map(|filling| {
                (
                    filling.feature_type(),
                    filling.names().next().expect("named").value(),
                )
            })
            .collect();
        assert_eq!(
            fillings,
            [
                (FeatureType::WindowSurface, "Window Round"),
                (FeatureType::WindowSurface, "Window North"),
                (FeatureType::DoorSurface, "Door West"),
                (FeatureType::WindowSurface, "Window South"),
            ]
        );
    }

    #[test]
    fn lod3_building_details() {
        let city_model = city_model();
        assert_eq!(city_model.city_objects_len(), 1);
        let b = building(&city_model);
        assert_eq!(
            b.relative_to_terrain(),
            Some(RelativeToTerrain::EntirelyAboveTerrain)
        );
        let boundaries = boundaries(b);
        assert_eq!(
            boundaries
                .iter()
                .map(|f| f.feature_type())
                .collect::<Vec<_>>(),
            [
                FeatureType::WallSurface,
                FeatureType::WallSurface,
                FeatureType::WallSurface,
                FeatureType::RoofSurface,
                FeatureType::WallSurface,
                FeatureType::RoofSurface,
                FeatureType::GroundSurface,
            ]
        );
        assert!(
            boundaries
                .iter()
                .filter_map(|f| WallSurface::try_from(f))
                .all(|wall| wall.lod3_multi_surface().is_some())
        );
    }

    #[test]
    fn lod3_fillings() {
        let city_model = city_model();
        let boundaries = boundaries(building(&city_model));
        let walls: Vec<&WallSurface> = boundaries
            .iter()
            .filter_map(|f| WallSurface::try_from(f))
            .collect();
        assert_eq!(
            walls
                .iter()
                .map(|w| count!(w.filling_surfaces()))
                .collect::<Vec<_>>(),
            [4, 3, 3, 3]
        );
        let mut doors = 0;
        let mut windows = 0;
        for wall in &walls {
            let mut properties = wall.filling_surfaces();
            while let Some(property) = properties.next() {
                assert!(property.href().is_none());
                let filling = property.object().expect("inline");
                doors += usize::from(filling.feature_type() == FeatureType::DoorSurface);
                windows += usize::from(filling.feature_type() == FeatureType::WindowSurface);
                let area = filling
                    .lod3_multi_surface()
                    .and_then(|p| p.object())
                    .expect("should have an LoD3 multi surface")
                    .area_3d()
                    .expect("should compute");
                assert!(area > 0.0);
            }
        }
        assert_eq!((doors, windows), (2, 11));
        assert!(
            boundaries
                .iter()
                .filter_map(|f| RoofSurface::try_from(f))
                .all(|roof| roof.filling_surfaces().next().is_none())
        );

        let features = features(&city_model);
        let window_area: f64 = features
            .iter()
            .filter_map(|f| WindowSurface::try_from(f))
            .map(|w| {
                w.lod3_multi_surface()
                    .and_then(|p| p.object())
                    .expect("LoD3")
                    .area_3d()
                    .expect("area")
            })
            .sum();
        assert_close(window_area, 23.168802611529827);
        let doors: Vec<&DoorSurface> = features
            .iter()
            .filter_map(|f| DoorSurface::try_from(f))
            .collect();
        assert_eq!(
            doors
                .iter()
                .map(|d| d.feature_id().as_str())
                .collect::<Vec<_>>(),
            [
                "GML_c137f11d-9a8c-4126-9aeb-9a6c9b4e1cbd",
                "GML_2d6ddf04-ee56-42a1-a9b1-b47e4181a629"
            ]
        );
        assert!(doors.iter().all(|d| d.lod2_multi_surface().is_none()));
    }

    #[test]
    fn lod3_city_objects() {
        let city_model = city_model();
        let mut objects = city_model.iter_city_objects();
        let objects: Vec<FeatureType> = std::iter::from_fn(|| objects.next())
            .map(|o| o.feature_type())
            .collect();
        assert_eq!(objects.len(), 21);
        let count = |t: FeatureType| objects.iter().filter(|o| **o == t).count();
        assert_eq!(
            [
                count(FeatureType::Building),
                count(FeatureType::WallSurface),
                count(FeatureType::RoofSurface),
                count(FeatureType::GroundSurface),
                count(FeatureType::DoorSurface),
                count(FeatureType::WindowSurface),
            ],
            [1, 4, 2, 1, 2, 11]
        );
        let types: Vec<FeatureType> = features(&city_model)
            .iter()
            .map(|f| f.feature_type())
            .collect();
        assert_eq!(types.len(), 22);
        assert_eq!(types[0], FeatureType::CityModel);
    }

    #[test]
    fn lod3_composite_surface() {
        let city_model = city_model();
        let boundaries = boundaries(building(&city_model));
        let wall = WallSurface::try_from(&boundaries[0]).expect("a wall surface");
        let multi_surface = wall
            .lod3_multi_surface()
            .and_then(|p| p.object())
            .expect("LoD3");
        let member = multi_surface.surface_member().next().expect("a member");
        let composite = CompositeSurface::try_from(member.object().expect("inline"))
            .expect("a composite surface");
        assert_eq!(count!(composite.surface_member()), 85);
        let first = composite.surface_member().next().expect("a member");
        let polygon = Polygon::try_from(first.object().expect("inline")).expect("a polygon");
        let start = polygon
            .exterior()
            .expect("an exterior")
            .points()
            .next()
            .expect("a point");
        assert_point_close(point(start), (457842.0, 5439088.49240388, 115.913175911167));
    }

    #[test]
    fn lod3_round_trip() {
        let city_model = city_model();
        let mut writer = GmlWriter::new(CitygmlFormat::Gml);
        writer
            .finish(&city_model)
            .unwrap_or_else(|_| panic!("should write"));
        let written = GmlReader::new(writer.data(), CitygmlFormat::Gml)
            .finish()
            .unwrap_or_else(|_| panic!("should read"));
        let types = |model: &CityModel| {
            features(model)
                .iter()
                .map(|f| f.feature_type())
                .collect::<Vec<_>>()
        };
        assert_eq!(types(&written), types(&city_model));
        assert_eq!(
            building(&written).feature_id().as_str(),
            "UUID_d281adfc-4901-0f52-540b-4cc1a9325f82"
        );
        assert_eq!(surface_ids(&written), surface_ids(&city_model));
        let mut heights = building(&written).heights();
        let height = heights.next().expect("should have a height");
        assert!(heights.next().is_none());
        assert_eq!(height.high_reference().value(), "topOfConstruction");
        assert_eq!(height.low_reference().value(), "lowestGroundPoint");
        assert_eq!(height.status(), HeightStatusValue::Measured);
        assert_close(height.length().value(), 6.52);
        assert_eq!(height.length().uom(), "m");
    }

    /// The `feature_id`s of the building's boundaries, then of the wall surfaces' filling surfaces.
    fn surface_ids(city_model: &CityModel) -> Vec<String> {
        let mut properties = building(city_model).boundaries();
        let mut ids: Vec<String> = std::iter::from_fn(|| properties.next())
            .map(|p| p.object().expect("inline").feature_id().as_str().to_owned())
            .collect();
        for wall in boundaries(building(city_model))
            .iter()
            .filter_map(|f| WallSurface::try_from(f))
        {
            let mut fillings = wall.filling_surfaces();
            ids.extend(
                std::iter::from_fn(|| fillings.next())
                    .map(|p| p.object().expect("inline").feature_id().as_str().to_owned()),
            );
        }
        ids
    }
}
