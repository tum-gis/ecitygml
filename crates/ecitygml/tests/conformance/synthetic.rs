//! The cases of `crates/ecitygml/tests/conformance/synthetic.md`.

use crate::{assert_close, read};
use ecitygml::io::{CitygmlFormat, GmlReader, GmlWriter};
use ecitygml::model::bridge::{AsAbstractBridge, Bridge, BridgePart};
use ecitygml::model::building::Building;
use ecitygml::model::city_furniture::CityFurniture;
use ecitygml::model::common::{FeatureType, HasFeatureType, IterFeatures};
use ecitygml::model::construction::{
    AsAbstractConstruction, AsAbstractConstructionSurface, RoofSurface,
};
use ecitygml::model::core::enums::RelativeToWater;
use ecitygml::model::core::refs::AbstractFeatureKindRef;
use ecitygml::model::core::{
    AsAbstractCityObject, AsAbstractFeature, AsAbstractOccupiedSpace, AsAbstractPhysicalSpace,
    AsAbstractSpace, CityModel, ImplicitGeometry,
};
use ecitygml::model::generics::GenericAttributeKind;
use ecitygml::model::transportation::enums::{GranularityValue, TrafficDirectionValue};
use ecitygml::model::transportation::{AsAbstractTransportationSpace, Section, TrafficSpace};
use ecitygml::model::tunnel::{AsAbstractTunnel, Tunnel, TunnelPart};
use ecitygml::model::vegetation::{PlantCover, SolitaryVegetationObject};
use egml::model::base::{AsAbstractGml, HasAssociationAttributes};
use egml::model::common::{ComputeEnvelope, GeometryType, HasGeometryType, Triangulate};
use egml::model::geometry::AbstractGeometryKind;
use egml::model::geometry::aggregates::AbstractGeometricAggregateKind;
use egml::model::geometry::primitives::{
    AbstractCurveKind, AbstractGeometricPrimitiveKind, AbstractSurfaceKind, SurfaceKind,
};

const DATASET: &str = "synthetic";

fn feature_types(city_model: &CityModel) -> Vec<FeatureType> {
    city_model
        .iter_features()
        .map(|feature| feature.feature_type())
        .collect()
}

fn all<'a, T>(city_model: &'a CityModel) -> Vec<&'a T>
where
    &'a T: TryFrom<AbstractFeatureKindRef<'a>>,
{
    city_model
        .iter_features()
        .filter_map(|feature| <&T>::try_from(feature).ok())
        .collect()
}

fn only<'a, T>(city_model: &'a CityModel) -> &'a T
where
    &'a T: TryFrom<AbstractFeatureKindRef<'a>>,
{
    let found = all::<T>(city_model);
    assert_eq!(found.len(), 1, "expected exactly one");
    found[0]
}

fn with_id<'a, T: AsAbstractFeature>(features: Vec<&'a T>, id: &str) -> &'a T {
    features
        .into_iter()
        .find(|feature| feature.feature_id().as_str() == id)
        .unwrap_or_else(|| panic!("no feature {id}"))
}

fn names(feature: &impl AsAbstractGml) -> Vec<&str> {
    feature.names().iter().map(|name| name.value()).collect()
}

fn round_trip(city_model: &CityModel) -> (CityModel, String) {
    let mut data = Vec::new();
    GmlWriter::new(&mut data, CitygmlFormat::Gml)
        .finish(city_model)
        .expect("should write");
    let written = GmlReader::new(data.as_slice(), CitygmlFormat::Gml)
        .finish()
        .expect("should read");
    (written, String::from_utf8(data).expect("should be UTF-8"))
}

fn ymd(date: &egml::model::xs::Date) -> (i32, u32, u32) {
    (date.year(), date.month(), date.day())
}

mod bridge {
    use super::*;

    fn city_model() -> CityModel {
        read(DATASET, "bridge.gml")
    }

    fn assert_bridge(bridge: &Bridge) {
        assert_eq!(bridge.class().map(|c| c.value()), Some("1000"));
        let functions: Vec<_> = bridge.functions().iter().map(|f| f.value()).collect();
        assert_eq!(functions, ["1010", "1020"]);
        let date = bridge.date_of_construction().expect("should have a date");
        assert_eq!(ymd(date), (1990, 5, 1));
    }

    fn part(bridge: &Bridge) -> &BridgePart {
        let [part] = bridge.bridge_parts() else {
            panic!("expected one bridge part");
        };
        assert!(part.href().is_none());
        part.object().expect("should be inline")
    }

    #[test]
    fn bridge_city_model() {
        let city_model = city_model();
        assert_eq!(city_model.city_object_members_len(), 1);
        assert_eq!(
            feature_types(&city_model),
            [
                FeatureType::CityModel,
                FeatureType::Bridge,
                FeatureType::BridgePart
            ]
        );
        let city_objects: Vec<_> = city_model
            .iter_city_objects()
            .map(|object| object.feature_type())
            .collect();
        assert_eq!(city_objects, [FeatureType::Bridge, FeatureType::BridgePart]);
    }

    #[test]
    fn bridge_attributes() {
        let city_model = city_model();
        let bridge = only::<Bridge>(&city_model);
        assert_eq!(bridge.feature_id().as_str(), "bridge_1");
        assert_eq!(names(bridge), ["Synthetic bridge"]);
        assert_bridge(bridge);
        let usages: Vec<_> = bridge.usages().iter().map(|u| u.value()).collect();
        assert_eq!(usages, ["1000"]);
        assert!(bridge.heights().is_empty());
        let part = part(bridge);
        assert_eq!(part.feature_id().as_str(), "bridge_part_1");
        assert!(part.class().is_none());
        assert!(part.functions().is_empty());
        assert_eq!(
            only::<BridgePart>(&city_model).feature_id().as_str(),
            "bridge_part_1"
        );
    }

    #[test]
    fn bridge_is_movable() {
        let city_model = city_model();
        let bridge = only::<Bridge>(&city_model);
        assert_eq!(bridge.is_movable(), Some(true));
        assert_eq!(part(bridge).is_movable(), Some(false));
    }

    #[test]
    fn bridge_code_spaces() {
        let city_model = city_model();
        let bridge = only::<Bridge>(&city_model);
        let class = bridge.class().expect("should have a class").code();
        assert_eq!(
            class.code_space().map(|uri| uri.as_str()),
            Some("https://example.org/bridge_class")
        );
        assert!(
            bridge
                .functions()
                .iter()
                .all(|f| f.code().code_space().is_none())
        );
    }

    #[test]
    fn bridge_round_trip() {
        let city_model = city_model();
        let (written, _) = round_trip(&city_model);
        assert_eq!(feature_types(&written), feature_types(&city_model));
        let bridge = only::<Bridge>(&written);
        assert_bridge(bridge);
        assert_eq!(part(bridge).feature_id().as_str(), "bridge_part_1");
    }
}

mod tunnel {
    use super::*;

    fn city_model() -> CityModel {
        read(DATASET, "tunnel.gml")
    }

    fn part(tunnel: &Tunnel) -> &TunnelPart {
        let [part] = tunnel.tunnel_parts() else {
            panic!("expected one tunnel part");
        };
        assert!(part.href().is_none());
        part.object().expect("should be inline")
    }

    /// The values of code-list values.
    macro_rules! values {
        ($values:expr) => {
            $values
                .iter()
                .map(|value| value.value())
                .collect::<Vec<_>>()
        };
    }

    #[test]
    fn tunnel_city_model() {
        let city_model = city_model();
        assert_eq!(city_model.city_object_members_len(), 1);
        assert_eq!(
            feature_types(&city_model),
            [
                FeatureType::CityModel,
                FeatureType::Tunnel,
                FeatureType::TunnelPart
            ]
        );
        let city_objects: Vec<_> = city_model
            .iter_city_objects()
            .map(|object| object.feature_type())
            .collect();
        assert_eq!(city_objects, [FeatureType::Tunnel, FeatureType::TunnelPart]);
    }

    #[test]
    fn tunnel_attributes() {
        let city_model = city_model();
        let tunnel = only::<Tunnel>(&city_model);
        assert_eq!(tunnel.feature_id().as_str(), "tunnel_1");
        assert_eq!(names(tunnel), ["Synthetic tunnel"]);
        assert_eq!(tunnel.class().map(|c| c.value()), Some("1000"));
        assert_eq!(values!(tunnel.functions()), ["1010", "1020"]);
        assert_eq!(values!(tunnel.usages()), ["1000"]);
        let date = tunnel.date_of_construction().expect("should have a date");
        assert_eq!(ymd(date), (1990, 5, 1));
        assert!(tunnel.heights().is_empty());
        let part = part(tunnel);
        assert_eq!(part.feature_id().as_str(), "tunnel_part_1");
        assert!(part.class().is_none());
        assert_eq!(values!(part.functions()), ["1030"]);
        assert_eq!(
            only::<TunnelPart>(&city_model).feature_id().as_str(),
            "tunnel_part_1"
        );
    }

    #[test]
    fn tunnel_code_spaces() {
        let city_model = city_model();
        let tunnel = only::<Tunnel>(&city_model);
        let class = tunnel.class().expect("should have a class").code();
        assert_eq!(
            class.code_space().map(|uri| uri.as_str()),
            Some("https://example.org/tunnel_class")
        );
        assert!(
            tunnel
                .functions()
                .iter()
                .all(|f| f.code().code_space().is_none())
        );
    }

    #[test]
    fn tunnel_round_trip() {
        let city_model = city_model();
        let (written, _) = round_trip(&city_model);
        assert_eq!(feature_types(&written), feature_types(&city_model));
        let tunnel = only::<Tunnel>(&written);
        assert_eq!(tunnel.class().map(|c| c.value()), Some("1000"));
        assert_eq!(values!(tunnel.functions()), ["1010", "1020"]);
        assert_eq!(values!(part(tunnel).functions()), ["1030"]);
    }
}

mod vegetation {
    use super::*;

    fn city_model() -> CityModel {
        read(DATASET, "vegetation.gml")
    }

    fn tree<'a>(city_model: &'a CityModel, id: &str) -> &'a SolitaryVegetationObject {
        with_id(all::<SolitaryVegetationObject>(city_model), id)
    }

    fn implicit(
        property: Option<&ecitygml::model::core::ImplicitGeometryProperty>,
    ) -> &ImplicitGeometry {
        let property = property.expect("should have an implicit representation");
        assert!(property.href().is_none());
        property.object().expect("should be inline")
    }

    #[test]
    fn vegetation_city_model() {
        let city_model = city_model();
        assert_eq!(city_model.city_object_members_len(), 3);
        assert_eq!(
            feature_types(&city_model),
            [
                FeatureType::CityModel,
                FeatureType::SolitaryVegetationObject,
                FeatureType::SolitaryVegetationObject,
                FeatureType::PlantCover
            ]
        );
    }

    #[test]
    fn vegetation_tree() {
        let city_model = city_model();
        let tree = tree(&city_model, "tree_1");
        assert_eq!(tree.class().map(|c| c.value()), Some("1000"));
        let functions: Vec<_> = tree.functions().iter().map(|f| f.value()).collect();
        assert_eq!(functions, ["1010"]);
        let usages: Vec<_> = tree.usages().iter().map(|u| u.value()).collect();
        assert_eq!(usages, ["1020"]);
        assert_eq!(tree.species().map(|s| s.value()), Some("Quercus robur"));
        let height = tree.height().expect("should have a height");
        assert_close(height.value, 12.5);
        assert_eq!(height.uom, "m");
        assert_close(tree.trunk_diameter().expect("diameter").value, 0.4);
        assert_close(tree.crown_diameter().expect("diameter").value, 5.5);
        assert_close(tree.root_ball_diameter().expect("diameter").value, 1.2);
        assert_close(tree.max_root_ball_depth().expect("depth").value, 0.8);
        assert!(tree.lod2_implicit_representation().is_none());
        assert!(tree.lod3_implicit_representation().is_none());
        assert!(tree.lod1_solid().is_none());
        assert!(tree.lod1_terrain_intersection_curve().is_none());
    }

    #[test]
    fn vegetation_implicit_geometry() {
        let city_model = city_model();
        let geometry = implicit(tree(&city_model, "tree_1").lod1_implicit_representation());
        assert_eq!(geometry.object_id().as_str(), "tree_prototype");
        assert_eq!(
            geometry.mime_type().map(|m| m.value()),
            Some("model/gltf+json")
        );
        let point = geometry
            .reference_point()
            .object()
            .expect("should have a reference point")
            .pos();
        assert_eq!(
            (point.x(), point.y(), point.z()),
            (457850.0, 5439090.0, 112.0)
        );
        let matrix = geometry.transformation_matrix().matrix();
        let rows = [
            [2.0, 0.0, 0.0, 10.0],
            [0.0, 2.0, 0.0, 20.0],
            [0.0, 0.0, 3.0, 30.0],
            [0.0, 0.0, 0.0, 1.0],
        ];
        for (row, values) in rows.iter().enumerate() {
            for (column, value) in values.iter().enumerate() {
                assert_close(matrix[(row, column)], *value);
            }
        }
        let relative = geometry
            .relative_geometry()
            .and_then(|property| property.object())
            .expect("should have a relative geometry");
        assert_eq!(relative.geometry_type(), GeometryType::MultiSurface);
        let AbstractGeometryKind::AbstractGeometricAggregateKind(
            AbstractGeometricAggregateKind::MultiSurface(multi_surface),
        ) = relative
        else {
            panic!("expected a multi surface");
        };
        assert_eq!(multi_surface.surface_member().len(), 1);
        let triangulation = relative.triangulate().expect("should triangulate");
        assert!(triangulation.skipped().is_empty());
        assert_eq!(triangulation.surface().triangles().len(), 1);
    }

    #[test]
    fn vegetation_point_relative_geometry() {
        let city_model = city_model();
        let tree = tree(&city_model, "tree_2");
        assert!(tree.lod1_implicit_representation().is_none());
        let geometry = implicit(tree.lod2_implicit_representation());
        assert_eq!(geometry.object_id().as_str(), "point_prototype");
        assert!(geometry.mime_type().is_none());
        let relative = geometry
            .relative_geometry()
            .and_then(|property| property.object())
            .expect("should have a relative geometry");
        assert_eq!(relative.geometry_type(), GeometryType::Point);
        let AbstractGeometryKind::AbstractGeometricPrimitiveKind(
            AbstractGeometricPrimitiveKind::Point(point),
        ) = relative
        else {
            panic!("expected a point");
        };
        let pos = point.pos();
        assert_eq!((pos.x(), pos.y(), pos.z()), (0.0, 0.0, 0.0));
    }

    #[test]
    fn vegetation_library_object() {
        let city_model = city_model();
        let first = implicit(tree(&city_model, "tree_1").lod1_implicit_representation());
        assert!(first.library_object().is_none());
        let second = implicit(tree(&city_model, "tree_2").lod2_implicit_representation());
        assert_eq!(
            second.library_object().map(|uri| uri.as_str()),
            Some("https://example.org/trees/oak.gltf")
        );
    }

    #[test]
    fn vegetation_plant_cover() {
        let city_model = city_model();
        let cover = only::<PlantCover>(&city_model);
        assert_eq!(cover.feature_id().as_str(), "cover_1");
        assert_eq!(cover.class().map(|c| c.value()), Some("2000"));
        assert!(cover.functions().is_empty());
        assert!(cover.usages().is_empty());
        assert_close(cover.average_height().expect("height").value, 2.5);
        assert_close(cover.min_height().expect("height").value, 1.0);
        assert_close(cover.max_height().expect("height").value, 4.0);
        assert!(cover.lod1_implicit_representation().is_none());
        let feature = city_model
            .iter_features()
            .find(|f| f.feature_type() == FeatureType::PlantCover)
            .expect("should have a plant cover");
        assert!(<&SolitaryVegetationObject>::try_from(feature).is_err());
    }

    #[test]
    fn vegetation_code_spaces() {
        let city_model = city_model();
        let class = tree(&city_model, "tree_1")
            .class()
            .expect("should have a class")
            .code();
        assert_eq!(
            class.code_space().map(|uri| uri.as_str()),
            Some("https://example.org/tree_class")
        );
        let cover = only::<PlantCover>(&city_model);
        assert!(cover.class().expect("class").code().code_space().is_none());
    }

    #[test]
    fn vegetation_round_trip() {
        let city_model = city_model();
        let (written, text) = round_trip(&city_model);
        assert_eq!(feature_types(&written), feature_types(&city_model));
        let tree = tree(&written, "tree_1");
        assert_eq!(tree.species().map(|s| s.value()), Some("Quercus robur"));
        assert_close(tree.height().expect("height").value, 12.5);
        let geometry = implicit(tree.lod1_implicit_representation());
        assert_eq!(geometry.object_id().as_str(), "tree_prototype");
        assert_eq!(
            geometry.mime_type().map(|m| m.value()),
            Some("model/gltf+json")
        );
        assert_close(
            only::<PlantCover>(&written)
                .average_height()
                .expect("height")
                .value,
            2.5,
        );
        assert!(!text.contains("objectId"));
    }
}

mod city_furniture {
    use super::*;

    fn city_model() -> CityModel {
        read(DATASET, "city-furniture.gml")
    }

    #[test]
    fn furniture_attributes() {
        let city_model = city_model();
        let furniture = only::<CityFurniture>(&city_model);
        assert_eq!(furniture.feature_id().as_str(), "sign_1");
        assert_eq!(names(furniture), ["Vorschriftzeichen"]);
        assert_eq!(furniture.class().map(|c| c.value()), Some("1000"));
        let functions: Vec<_> = furniture.functions().iter().map(|f| f.value()).collect();
        assert_eq!(functions, ["1080"]);
        let usages: Vec<_> = furniture.usages().iter().map(|u| u.value()).collect();
        assert_eq!(usages, ["1090"]);
        let property = furniture
            .lod2_multi_surface()
            .expect("should have an LoD2 multi surface");
        assert!(property.href().is_none());
        assert_eq!(property.object().expect("inline").surface_member().len(), 1);
        assert!(furniture.lod1_implicit_representation().is_none());
        assert!(furniture.lod2_terrain_intersection_curve().is_none());
    }

    #[test]
    fn furniture_code_spaces() {
        let city_model = city_model();
        let class = only::<CityFurniture>(&city_model)
            .class()
            .expect("should have a class")
            .code();
        assert_eq!(
            class.code_space().map(|uri| uri.as_str()),
            Some("https://example.org/furniture_class")
        );
    }
}

mod building {
    use super::*;

    fn city_model() -> CityModel {
        read(DATASET, "building.gml")
    }

    fn building(city_model: &CityModel) -> &Building {
        with_id(all::<Building>(city_model), "building_1")
    }

    #[test]
    fn building_city_model() {
        let city_model = city_model();
        assert_eq!(city_model.city_object_members_len(), 2);
        assert_eq!(
            feature_types(&city_model),
            [
                FeatureType::CityModel,
                FeatureType::Building,
                FeatureType::RoofSurface,
                FeatureType::WindowSurface,
                FeatureType::Building
            ]
        );
        assert_eq!(city_model.iter_city_objects().count(), 4);
    }

    #[test]
    fn building_relation() {
        let city_model = city_model();
        let [property] = building(&city_model).related_to() else {
            panic!("expected one relation");
        };
        assert!(property.href().is_none());
        let relation = property.object().expect("should be inline");
        assert_eq!(relation.relation_type().value(), "shared");
        assert_eq!(
            relation.relation_to().href().map(|href| href.to_string()),
            Some("#building_2".to_string())
        );
        let [GenericAttributeKind::IntAttribute(weight)] = relation.generic_attributes() else {
            panic!("expected one int attribute");
        };
        assert_eq!((weight.name.as_str(), weight.value), ("weight", 3));
    }

    #[test]
    fn building_attribute_set() {
        let city_model = city_model();
        let [GenericAttributeKind::GenericAttributeSet(set)] =
            building(&city_model).generic_attributes()
        else {
            panic!("expected one generic attribute set");
        };
        assert_eq!(set.name, "energy");
        let [
            GenericAttributeKind::DoubleAttribute(demand),
            GenericAttributeKind::StringAttribute(label),
        ] = set.generic_attributes.as_slice()
        else {
            panic!("expected a double and a string attribute");
        };
        assert_eq!(demand.name, "demand");
        assert_close(demand.value, 12.5);
        assert_eq!((label.name.as_str(), label.value.as_str()), ("label", "A+"));
    }

    #[test]
    fn building_construction() {
        let city_model = city_model();
        let building = building(&city_model);
        assert_eq!(
            building.relative_to_water(),
            Some(RelativeToWater::EntirelyAboveWaterSurface)
        );
        assert_eq!(
            ymd(building.date_of_construction().expect("date")),
            (2020, 1, 1)
        );
        assert_eq!(
            ymd(building.date_of_demolition().expect("date")),
            (2050, 12, 31)
        );
        let [occupancy] = building.occupancies() else {
            panic!("expected one occupancy");
        };
        assert_eq!(occupancy.number_of_occupants(), 4);
        assert_eq!(occupancy.interval().map(|i| i.value()), Some("daytime"));
        assert_eq!(
            occupancy.occupant_type().map(|t| t.value()),
            Some("residents")
        );
    }

    #[test]
    fn building_boundaries() {
        let city_model = city_model();
        let [roof, reference] = building(&city_model).boundaries() else {
            panic!("expected two boundaries");
        };
        assert!(roof.href().is_none());
        let roof: &RoofSurface =
            AbstractFeatureKindRef::from(roof.object().expect("should be inline"))
                .try_into()
                .expect("should be a roof surface");
        assert_eq!(roof.feature_id().as_str(), "roof_1");
        let [filling] = roof.filling_surfaces() else {
            panic!("expected one filling surface");
        };
        assert!(filling.href().is_none());
        let window = filling.object().expect("should be inline");
        assert_eq!(window.feature_type(), FeatureType::WindowSurface);
        assert_eq!(window.feature_id().as_str(), "roof_window_1");
        assert!(reference.object().is_none());
        assert_eq!(
            reference.href().map(|href| href.to_string()),
            Some("#missing_boundary".to_string())
        );
    }

    #[test]
    fn building_terrain_intersection_curve() {
        let city_model = city_model();
        let building = building(&city_model);
        let property = building
            .lod2_terrain_intersection_curve()
            .expect("should have a curve");
        assert!(property.href().is_none());
        let multi_curve = property.object().expect("should be inline");
        let [member] = multi_curve.curve_member() else {
            panic!("expected one curve member");
        };
        let AbstractCurveKind::LineString(line) = member.object().expect("inline") else {
            panic!("expected a line string");
        };
        assert_eq!(line.points().len(), 2);
        assert_close(multi_curve.length_3d().expect("should compute"), 12.0);
        assert!(building.lod1_terrain_intersection_curve().is_none());
        assert!(building.lod3_terrain_intersection_curve().is_none());
    }

    #[test]
    fn building_round_trip() {
        let city_model = city_model();
        let (written, text) = round_trip(&city_model);
        assert_eq!(feature_types(&written), feature_types(&city_model));
        let building = building(&written);
        let relation = building.related_to()[0].object().expect("inline");
        assert_eq!(
            relation.relation_to().href().map(|href| href.to_string()),
            Some("#building_2".to_string())
        );
        let [GenericAttributeKind::GenericAttributeSet(set)] = building.generic_attributes() else {
            panic!("expected one generic attribute set");
        };
        assert_eq!(set.name, "energy");
        assert_eq!(
            ymd(building.date_of_demolition().expect("date")),
            (2050, 12, 31)
        );
        let [occupancy] = building.occupancies() else {
            panic!("expected one occupancy");
        };
        assert_eq!(occupancy.number_of_occupants(), 4);
        assert_eq!(occupancy.interval().map(|i| i.value()), Some("daytime"));
        assert_eq!(
            occupancy.occupant_type().map(|t| t.value()),
            Some("residents")
        );
        let [roof, reference] = building.boundaries() else {
            panic!("expected two boundaries");
        };
        let roof: &RoofSurface = AbstractFeatureKindRef::from(roof.object().expect("inline"))
            .try_into()
            .expect("roof");
        let window = roof.filling_surfaces()[0].object().expect("inline");
        assert_eq!(window.feature_id().as_str(), "roof_window_1");
        assert_eq!(
            reference.href().map(|href| href.to_string()),
            Some("#missing_boundary".to_string())
        );
        let curve = building
            .lod2_terrain_intersection_curve()
            .and_then(|property| property.object())
            .expect("should have a curve");
        assert_close(curve.length_3d().expect("should compute"), 12.0);
        assert!(!text.contains("TerrainIntersectionCurveProperty"));
    }
}

mod transportation {
    use super::*;

    fn city_model() -> CityModel {
        read(DATASET, "transportation.gml")
    }

    fn space(city_model: &CityModel) -> &TrafficSpace {
        only::<TrafficSpace>(city_model)
    }

    #[test]
    fn transportation_section() {
        let city_model = city_model();
        let section = only::<Section>(&city_model);
        assert_eq!(section.feature_id().as_str(), "section_1");
        assert_eq!(
            section.traffic_direction(),
            Some(TrafficDirectionValue::Both)
        );
        let [occupancy] = section.occupancies() else {
            panic!("expected one occupancy");
        };
        assert_eq!(occupancy.number_of_occupants(), 120);
        assert_eq!(occupancy.interval().map(|i| i.value()), Some("peakHour"));
        let [property] = section.traffic_spaces() else {
            panic!("expected one traffic space");
        };
        assert!(property.href().is_none());
        let space = property.object().expect("should be inline");
        assert_eq!(space.feature_id().as_str(), "space_1");
        assert_eq!(*space.granularity(), GranularityValue::Lane);
    }

    #[test]
    fn transportation_point() {
        let city_model = city_model();
        let property = space(&city_model)
            .lod0_point()
            .expect("should have a point");
        assert!(property.href().is_none());
        let point = property.object().expect("should be inline");
        assert_eq!(point.id().map(|id| id.as_str()), Some("point_1"));
        let pos = point.pos();
        assert_eq!((pos.x(), pos.y(), pos.z()), (1.5, -2.5, 3.25));
        let envelope = point.compute_envelope().expect("should have an envelope");
        for corner in [envelope.lower_corner(), envelope.upper_corner()] {
            assert_eq!((corner.x(), corner.y(), corner.z()), (1.5, -2.5, 3.25));
        }
    }

    #[test]
    fn transportation_curves() {
        let city_model = city_model();
        let multi_curve = space(&city_model)
            .lod0_multi_curve()
            .and_then(|property| property.object())
            .expect("should have a multi curve");
        let [line, ring, reference] = multi_curve.curve_member() else {
            panic!("expected three curve members");
        };
        let line = line.object().expect("inline");
        assert_eq!(line.geometry_type(), GeometryType::LineString);
        let AbstractCurveKind::LineString(line_string) = line else {
            panic!("expected a line string");
        };
        assert_eq!(line_string.points().len(), 2);
        assert_close(line_string.length_3d(), 5.0);
        let ring = ring.object().expect("inline");
        assert_eq!(ring.geometry_type(), GeometryType::LinearRing);
        let AbstractCurveKind::AbstractRingKind(
            egml::model::geometry::primitives::AbstractRingKind::LinearRing(linear_ring),
        ) = ring
        else {
            panic!("expected a linear ring");
        };
        assert_eq!(linear_ring.points().len(), 3);
        assert_close(linear_ring.length_3d(), 2.0 + 2f64.sqrt());
        assert!(reference.object().is_none());
        assert_eq!(
            reference.href().map(|href| href.to_string()),
            Some("#missing_curve".to_string())
        );
        let error = multi_curve.length_3d().unwrap_err();
        assert!(
            matches!(error, egml::Error::UnresolvedCurveReference { .. }),
            "{error:?}"
        );
        assert!(error.to_string().contains("#missing_curve"), "{error}");
    }
}

mod geometry {
    use super::*;

    #[test]
    fn geometry_skipped_members() {
        let city_model = read(DATASET, "geometry.gml");
        let multi_surface = with_id(all::<Building>(&city_model), "geometry_1")
            .lod2_multi_surface()
            .and_then(|property| property.object())
            .expect("should have an LoD2 multi surface");
        let [square, collinear, tin] = multi_surface.surface_member() else {
            panic!("expected three surface members");
        };
        for (member, id) in [(square, "square"), (collinear, "collinear")] {
            let kind = member.object().expect("inline");
            assert_eq!(kind.geometry_type(), GeometryType::Polygon);
            assert_eq!(kind.id().map(|id| id.as_str()), Some(id));
        }
        assert_close(
            collinear.object().expect("inline").area_3d().expect("area"),
            0.0,
        );
        let kind = tin.object().expect("inline");
        assert_eq!(kind.geometry_type(), GeometryType::TriangulatedSurface);
        let AbstractSurfaceKind::SurfaceKind(SurfaceKind::TriangulatedSurface(tin)) = kind else {
            panic!("expected a triangulated surface");
        };
        assert_eq!(tin.id().map(|id| id.as_str()), Some("tin"));
        assert_eq!(tin.triangles().len(), 2);
        assert_eq!(tin.surface().patches().len(), 2);
        assert_close(tin.area_3d().expect("area"), 1.0);
        let triangulation = multi_surface.triangulate().expect("should triangulate");
        assert_eq!(triangulation.surface().triangles().len(), 4);
        let [error] = triangulation.skipped() else {
            panic!("expected one skipped member");
        };
        assert!(
            !matches!(
                error,
                egml::Error::UnresolvedSurfaceReference { .. }
                    | egml::Error::UnresolvedCurveReference { .. }
            ),
            "{error:?}"
        );
        assert!(
            error.to_string().contains("earcut produced no triangles"),
            "{error}"
        );
    }
}
