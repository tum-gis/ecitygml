//! The cases of `crates/ecitygml/tests/conformance/fzk-haus.md`.

use crate::{assert_close, read};
use ecitygml::model::building::{AsAbstractBuilding, Building};
use ecitygml::model::common::{FeatureType, HasFeatureType, IterFeatures};
use ecitygml::model::construction::enums::HeightStatusValue;
use ecitygml::model::construction::{
    AsAbstractConstruction, AsAbstractConstructionSurface, DoorSurface, GroundSurface, RoofSurface,
    WallSurface, WindowSurface,
};
use ecitygml::model::core::enums::RelativeToTerrain;
use ecitygml::model::core::refs::AbstractFeatureKindRef;
use ecitygml::model::core::{
    AsAbstractCityObject, AsAbstractFeature, AsAbstractFeatureWithLifespan,
    AsAbstractOccupiedSpace, AsAbstractPhysicalSpace, AsAbstractSpace, AsAbstractThematicSurface,
    CityModel,
};
use ecitygml::model::generics::GenericAttributeKind;
use egml::model::base::{AsAbstractGml, HasAssociationAttributes};
use egml::model::common::{ApplyTransform, Triangulate};
use egml::model::feature::AsAbstractFeature as _;
use egml::model::geometry::DirectPosition;
use egml::model::geometry::primitives::{
    AbstractRingKind, AbstractSurfaceKind, LinearRing, Polygon,
};
use nalgebra::{Scale3, Vector3};

fn building(city_model: &CityModel) -> &Building {
    city_model
        .iter_features()
        .find_map(|feature| feature.try_into().ok())
        .expect("should have a building")
}

fn first_name(feature: &impl AsAbstractGml) -> &str {
    feature.names().first().expect("should have a name").value()
}

/// The building's boundaries, as features.
fn boundaries(building: &Building) -> Vec<AbstractFeatureKindRef<'_>> {
    building
        .boundaries()
        .iter()
        .filter_map(|property| property.object())
        .map(AbstractFeatureKindRef::from)
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

/// The area of a thematic surface's LoD2 multi surface.
fn lod2_area(surface: &impl AsAbstractThematicSurface) -> f64 {
    surface
        .lod2_multi_surface()
        .and_then(|property| property.object())
        .expect("should have an LoD2 multi surface")
        .area_3d()
        .expect("should compute")
}

mod lod1 {
    use super::*;

    fn city_model() -> CityModel {
        read("fzk-haus", "FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml")
    }

    #[test]
    fn lod1_city_model() {
        let city_model = city_model();
        assert_eq!(city_model.city_object_members_len(), 1);
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
            building.feature_id().to_string(),
            "UUID_d281adfc-4901-0f52-540b-4cc1a9325f82"
        );
        assert_eq!(
            building
                .names()
                .iter()
                .map(|name| name.value())
                .collect::<Vec<_>>(),
            ["AC14-FZK-Haus"]
        );
        assert_eq!(building.class().map(|class| class.value()), Some("1000"));
        assert_eq!(
            building
                .functions()
                .iter()
                .map(|f| f.value())
                .collect::<Vec<_>>(),
            ["1000"]
        );
        assert_eq!(
            building
                .usages()
                .iter()
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
        let [height] = building.heights() else {
            panic!("expected one height, got {:?}", building.heights());
        };
        assert_eq!(height.high_reference().value(), "topOfConstruction");
        assert_eq!(height.low_reference().value(), "lowestGroundPoint");
        assert_eq!(height.status(), HeightStatusValue::Measured);
        assert_close(height.length().value(), 6.52);
        assert_eq!(height.length().uom(), "m");
        assert!(building.occupancies().is_empty());
        assert!(building.building_parts().is_empty());
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
        assert_eq!(triangulation.surface().triangles().len(), 12);
        assert!(!triangulation.has_skipped());
        assert!(building.boundaries().is_empty());
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
        let buildings = city_model
            .iter_features()
            .filter(|feature| <&Building>::try_from(*feature).is_ok())
            .count();
        assert_eq!(buildings, 1);
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
        assert!(solid.interior().is_empty());
        assert_eq!(solid.points().len(), 24);
        let shell = solid.exterior().expect("should have an exterior shell");
        assert_close(shell.volume_3d().expect("should compute"), 782.1228);
        assert_eq!(shell.members().len(), 6);
        for member in shell.members() {
            assert!(member.href().is_none());
            let polygon = polygon(member.object().expect("inline"));
            assert!(polygon.interior().is_empty());
            let ring = linear_ring(polygon.exterior().expect("should have an exterior"));
            assert_eq!(ring.points().len(), 4);
            assert!(ring.area_3d() > 0.0);
        }
        let first = linear_ring(
            polygon(shell.members()[0].object().expect("inline"))
                .exterior()
                .expect("should have an exterior"),
        );
        assert_point_close(point(&first.points()[0]), (457842.0, 5439083.0, 111.8));
        assert_close(first.length_3d(), 44.0);
        assert_close(first.area_3d(), 120.0);
    }

    #[test]
    fn lod1_solid_triangulation() {
        let city_model = city_model();
        let solid = building(&city_model)
            .lod1_solid()
            .and_then(|property| property.object())
            .expect("should have an LoD1 solid");
        let triangulation = solid.triangulate().expect("should triangulate");
        assert!(triangulation.skipped().is_empty());
        let surface = triangulation.surface();
        assert_close(surface.area_3d().expect("should compute"), 526.77836);
        assert_eq!(surface.points().len(), 36);
        let triangle = surface.triangles()[0];
        assert_close(triangle.a().z(), 111.8);
        assert_close(triangle.area(), 60.0);
        let shell = solid.exterior().expect("should have an exterior shell");
        assert_eq!(
            shell
                .triangulate()
                .expect("should triangulate")
                .surface()
                .triangles()
                .len(),
            12
        );
        let first = polygon(shell.members()[0].object().expect("inline"));
        assert_eq!(
            first
                .triangulate()
                .expect("should triangulate")
                .surface()
                .triangles()
                .len(),
            2
        );
    }

    #[test]
    fn lod1_apply_scale() {
        let mut city_model = city_model();
        city_model.apply_scale(Scale3::new(2.0, 3.0, 0.5));
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

    fn city_model() -> CityModel {
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
        let walls: Vec<&WallSurface> = boundaries
            .iter()
            .filter_map(|b| (*b).try_into().ok())
            .collect();
        let roofs: Vec<&RoofSurface> = boundaries
            .iter()
            .filter_map(|b| (*b).try_into().ok())
            .collect();
        let grounds: Vec<&GroundSurface> = boundaries
            .iter()
            .filter_map(|b| (*b).try_into().ok())
            .collect();
        assert_eq!(
            walls.iter().map(|w| first_name(*w)).collect::<Vec<_>>(),
            [
                "Outer Wall 1 (West)",
                "Outer Wall 2 (South)",
                "Outer Wall 3 (East)",
                "Outer Wall 4 (North)"
            ]
        );
        assert_eq!(
            roofs.iter().map(|r| first_name(*r)).collect::<Vec<_>>(),
            ["Roof 1 (North)", "Roof 2 (South)"]
        );
        assert_eq!(
            grounds.iter().map(|g| first_name(*g)).collect::<Vec<_>>(),
            ["Base Surface"]
        );
    }

    #[test]
    fn lod2_surface_areas() {
        let city_model = city_model();
        let boundaries = boundaries(building(&city_model));
        let walls: f64 = boundaries
            .iter()
            .filter_map(|b| <&WallSurface>::try_from(*b).ok())
            .map(lod2_area)
            .sum();
        let roofs: f64 = boundaries
            .iter()
            .filter_map(|b| <&RoofSurface>::try_from(*b).ok())
            .map(lod2_area)
            .sum();
        let grounds: f64 = boundaries
            .iter()
            .filter_map(|b| <&GroundSurface>::try_from(*b).ok())
            .map(lod2_area)
            .sum();
        assert_close(walls, 188.62887820601463);
        assert_close(roofs, 138.56406460961398);
        assert_close(grounds, 120.0);
    }

    #[test]
    fn lod2_generic_attributes() {
        let city_model = city_model();
        let building = building(&city_model);
        let [area, method, landmarked] = building.generic_attributes() else {
            panic!("expected three generic attributes");
        };
        let GenericAttributeKind::MeasureAttribute(area) = area else {
            panic!("expected a measure attribute, got {area:?}");
        };
        assert_eq!(area.name, "GrossPlannedArea");
        assert_close(area.value.value, 120.0);
        assert_eq!(area.value.uom, "m2");
        let GenericAttributeKind::StringAttribute(method) = method else {
            panic!("expected a string attribute, got {method:?}");
        };
        assert_eq!(
            (method.name.as_str(), method.value.as_str()),
            ("ConstructionMethod", "New Building")
        );
        let GenericAttributeKind::StringAttribute(landmarked) = landmarked else {
            panic!("expected a string attribute, got {landmarked:?}");
        };
        assert_eq!(
            (landmarked.name.as_str(), landmarked.value.as_str()),
            ("IsLandmarked", "NO")
        );
        assert!(building.external_references().is_empty());
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
        assert_eq!(created.as_chrono().timestamp(), 1485126000);
        assert!(b.termination_date().is_none());
        assert!(b.valid_from().is_none());
        assert!(b.valid_to().is_none());

        assert_eq!(b.class().map(|class| class.value()), Some("1000"));
        assert_eq!(
            b.functions().iter().map(|f| f.value()).collect::<Vec<_>>(),
            ["1000"]
        );
        assert_eq!(
            b.usages().iter().map(|u| u.value()).collect::<Vec<_>>(),
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
        let [height] = b.heights() else {
            panic!("expected one height");
        };
        assert_eq!(height.high_reference().value(), "topOfConstruction");
        assert_eq!(height.low_reference().value(), "lowestGroundPoint");
        assert_eq!(height.status(), HeightStatusValue::Measured);
        assert_close(height.length().value(), 6.52);
        assert_eq!(height.length().uom(), "m");

        assert!(b.occupancies().is_empty());
        assert!(b.related_to().is_empty());
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
        let properties = building(&city_model).boundaries();
        assert!(properties.iter().all(|property| property.href().is_none()));
        assert_eq!(
            boundaries(building(&city_model))
                .iter()
                .map(|b| b.feature_id().to_string())
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
            .filter_map(|b| (*b).try_into().ok())
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
        assert!(wall.generic_attributes().is_empty());
        assert!(wall.bounded_by().is_some());
        let multi_surface = wall
            .lod2_multi_surface()
            .and_then(|property| property.object())
            .expect("should have an LoD2 multi surface");
        assert_eq!(multi_surface.surface_member().len(), 1);
        assert_eq!(
            multi_surface
                .triangulate()
                .expect("should triangulate")
                .surface()
                .triangles()
                .len(),
            3
        );
        assert!(walls.iter().all(|w| w.filling_surfaces().is_empty()));
        let ground: &GroundSurface = boundaries
            .iter()
            .find_map(|b| (*b).try_into().ok())
            .expect("should have a ground surface");
        let ground_polygon = polygon(
            ground
                .lod2_multi_surface()
                .and_then(|property| property.object())
                .expect("should have an LoD2 multi surface")
                .surface_member()[0]
                .object()
                .expect("inline"),
        );
        assert_eq!(
            linear_ring(ground_polygon.exterior().expect("should have an exterior"))
                .points()
                .len(),
            4
        );
    }

    #[test]
    fn lod2_generic_attribute_kinds() {
        let city_model = city_model();
        let [area, method, landmarked] = building(&city_model).generic_attributes() else {
            panic!("expected three generic attributes");
        };
        assert!(!matches!(area, GenericAttributeKind::StringAttribute(_)));
        assert!(!matches!(method, GenericAttributeKind::MeasureAttribute(_)));
        assert!(!matches!(
            landmarked,
            GenericAttributeKind::MeasureAttribute(_)
        ));
    }

    #[test]
    fn lod2_city_objects() {
        let city_model = city_model();
        assert_eq!(
            city_model
                .iter_city_objects()
                .map(|object| object.feature_type())
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
        let types: Vec<FeatureType> = city_model
            .iter_features()
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
        city_model
            .iter_features()
            .filter_map(|feature| <&WallSurface>::try_from(feature).ok())
            .map(|wall| wall.bounded_by().is_some())
            .collect()
    }

    #[test]
    fn lod2_object_bounds() {
        let path = format!(
            "{}/../../tests/fixtures/fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml",
            env!("CARGO_MANIFEST_DIR")
        );
        let mut city_model = ecitygml::io::GmlReader::from_path(&path)
            .expect("should open")
            .with_rebuild_object_bounds(false)
            .finish()
            .expect("should read");
        assert_eq!(walls_bounded(&city_model), [false; 4]);
        city_model.recompute_child_bounding_shapes();
        assert_eq!(walls_bounded(&city_model), [true; 4]);
    }

    /// The lower corners of the city model's envelope and of the first wall surface's.
    fn lower_corners(city_model: &CityModel) -> [(f64, f64, f64); 2] {
        let wall: &WallSurface = city_model
            .iter_features()
            .find_map(|feature| feature.try_into().ok())
            .expect("should have a wall surface");
        let corner = |envelope: Option<&egml::model::geometry::Envelope>| {
            point(envelope.expect("should have an envelope").lower_corner())
        };
        [
            corner(city_model.bounded_by().and_then(|shape| shape.envelope())),
            corner(wall.bounded_by().and_then(|shape| shape.envelope())),
        ]
    }

    #[test]
    fn lod2_apply_translation() {
        let mut city_model = city_model();
        for corner in lower_corners(&city_model) {
            assert_point_close(corner, (457842.0, 5439083.0, 111.8));
        }
        city_model.apply_translation(Vector3::new(-100.0, 200.0, 10.0));
        for corner in lower_corners(&city_model) {
            assert_point_close(corner, (457742.0, 5439283.0, 121.8));
        }
    }
}

mod lod3 {
    use super::*;

    fn city_model() -> CityModel {
        read("fzk-haus", "FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml")
    }

    #[test]
    fn lod3_doors_and_windows() {
        let city_model = city_model();
        let doors: Vec<&DoorSurface> = city_model
            .iter_features()
            .filter_map(|feature| feature.try_into().ok())
            .collect();
        assert_eq!(
            doors.iter().map(|d| first_name(*d)).collect::<Vec<_>>(),
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
        let windows = city_model
            .iter_features()
            .filter(|feature| <&WindowSurface>::try_from(*feature).is_ok())
            .count();
        assert_eq!(windows, 11);
    }

    #[test]
    fn lod3_west_wall_fillings() {
        let city_model = city_model();
        let first = building(&city_model)
            .boundaries()
            .first()
            .and_then(|property| property.object())
            .expect("should have a boundary");
        let wall: &WallSurface = AbstractFeatureKindRef::from(first)
            .try_into()
            .expect("should be a wall surface");
        assert_eq!(first_name(wall), "Outer Wall 1 (West)");
        let fillings: Vec<(FeatureType, &str)> = wall
            .filling_surfaces()
            .iter()
            .filter_map(|property| property.object())
            .map(|filling| (filling.feature_type(), first_name(filling)))
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
        assert_eq!(city_model.city_object_members_len(), 1);
        let b = building(&city_model);
        assert_eq!(
            b.relative_to_terrain(),
            Some(RelativeToTerrain::EntirelyAboveTerrain)
        );
        let boundaries = boundaries(b);
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
        assert!(
            boundaries
                .iter()
                .filter_map(|b| <&WallSurface>::try_from(*b).ok())
                .all(|wall| wall.lod3_multi_surface().is_some())
        );
    }

    #[test]
    fn lod3_fillings() {
        let city_model = city_model();
        let boundaries = boundaries(building(&city_model));
        let walls: Vec<&WallSurface> = boundaries
            .iter()
            .filter_map(|b| (*b).try_into().ok())
            .collect();
        assert_eq!(
            walls
                .iter()
                .map(|w| w.filling_surfaces().len())
                .collect::<Vec<_>>(),
            [4, 3, 3, 3]
        );
        let fillings: Vec<_> = walls.iter().flat_map(|w| w.filling_surfaces()).collect();
        assert!(fillings.iter().all(|property| property.href().is_none()));
        let kinds: Vec<_> = fillings
            .iter()
            .map(|p| p.object().expect("inline"))
            .collect();
        assert_eq!(
            kinds
                .iter()
                .filter(|k| k.feature_type() == FeatureType::DoorSurface)
                .count(),
            2
        );
        assert_eq!(
            kinds
                .iter()
                .filter(|k| k.feature_type() == FeatureType::WindowSurface)
                .count(),
            11
        );
        assert!(kinds.iter().all(|filling| {
            filling
                .lod3_multi_surface()
                .and_then(|property| property.object())
                .expect("should have an LoD3 multi surface")
                .area_3d()
                .expect("should compute")
                > 0.0
        }));
        assert!(
            boundaries
                .iter()
                .filter_map(|b| <&RoofSurface>::try_from(*b).ok())
                .all(|roof| roof.filling_surfaces().is_empty())
        );

        let windows: f64 = city_model
            .iter_features()
            .filter_map(|feature| <&WindowSurface>::try_from(feature).ok())
            .map(|window| {
                window
                    .lod3_multi_surface()
                    .and_then(|property| property.object())
                    .expect("should have an LoD3 multi surface")
                    .area_3d()
                    .expect("should compute")
            })
            .sum();
        assert_close(windows, 23.168802611529827);
        let doors: Vec<&DoorSurface> = city_model
            .iter_features()
            .filter_map(|feature| feature.try_into().ok())
            .collect();
        assert_eq!(
            doors
                .iter()
                .map(|d| d.feature_id().to_string())
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
        let objects: Vec<FeatureType> = city_model
            .iter_city_objects()
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
        let features: Vec<FeatureType> = city_model
            .iter_features()
            .map(|f| f.feature_type())
            .collect();
        assert_eq!(features.len(), 22);
        assert_eq!(features[0], FeatureType::CityModel);
    }

    #[test]
    fn lod3_composite_surface() {
        let city_model = city_model();
        let boundaries = boundaries(building(&city_model));
        let wall: &WallSurface = boundaries[0].try_into().expect("should be a wall surface");
        let multi_surface = wall
            .lod3_multi_surface()
            .and_then(|property| property.object())
            .expect("should have an LoD3 multi surface");
        let AbstractSurfaceKind::CompositeSurface(composite) =
            multi_surface.surface_member()[0].object().expect("inline")
        else {
            panic!("expected a composite surface");
        };
        assert_eq!(composite.surface_member().len(), 85);
        let first = polygon(composite.surface_member()[0].object().expect("inline"));
        let ring = linear_ring(first.exterior().expect("should have an exterior"));
        assert_point_close(
            point(&ring.points()[0]),
            (457842.0, 5439088.49240388, 115.913175911167),
        );
    }

    #[test]
    fn lod3_round_trip() {
        let city_model = city_model();
        let mut data = Vec::new();
        ecitygml::io::GmlWriter::new(&mut data, ecitygml::io::CitygmlFormat::Gml)
            .finish(&city_model)
            .expect("should write");
        let written =
            ecitygml::io::GmlReader::new(data.as_slice(), ecitygml::io::CitygmlFormat::Gml)
                .finish()
                .expect("should read");
        let types = |model: &CityModel| {
            model
                .iter_features()
                .map(|f| f.feature_type())
                .collect::<Vec<_>>()
        };
        assert_eq!(types(&written), types(&city_model));
        assert_eq!(
            building(&written).feature_id().to_string(),
            "UUID_d281adfc-4901-0f52-540b-4cc1a9325f82"
        );
        assert_eq!(surface_ids(&written), surface_ids(&city_model));
        let [height] = building(&written).heights() else {
            panic!("expected one height");
        };
        assert_eq!(height.high_reference().value(), "topOfConstruction");
        assert_eq!(height.low_reference().value(), "lowestGroundPoint");
        assert_eq!(height.status(), HeightStatusValue::Measured);
        assert_close(height.length().value(), 6.52);
        assert_eq!(height.length().uom(), "m");
    }

    /// The `feature_id`s of the building's boundaries, then of the wall surfaces' filling surfaces.
    fn surface_ids(city_model: &CityModel) -> Vec<String> {
        let boundaries = boundaries(building(city_model));
        let mut ids: Vec<String> = boundaries
            .iter()
            .map(|b| b.feature_id().to_string())
            .collect();
        for wall in boundaries
            .iter()
            .filter_map(|b| <&WallSurface>::try_from(*b).ok())
        {
            ids.extend(
                wall.filling_surfaces()
                    .iter()
                    .map(|p| p.object().expect("inline").feature_id().to_string()),
            );
        }
        ids
    }
}
