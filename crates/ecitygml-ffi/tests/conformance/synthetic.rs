//! The cases of `crates/ecitygml/tests/conformance/synthetic.md`.

use crate::{assert_close, read, written};
use ecitygml_ffi::citygml::core::model::bridge::bridge::Bridge;
use ecitygml_ffi::citygml::core::model::bridge::bridge_part::BridgePart;
use ecitygml_ffi::citygml::core::model::building::building::Building;
use ecitygml_ffi::citygml::core::model::city_furniture::city_furniture::CityFurniture;
use ecitygml_ffi::citygml::core::model::common::feature_type::FeatureType;
use ecitygml_ffi::citygml::core::model::construction::roof_surface::RoofSurface;
use ecitygml_ffi::citygml::core::model::core::city_model::CityModel;
use ecitygml_ffi::citygml::core::model::core::enums::relative_to_water::RelativeToWater;
use ecitygml_ffi::citygml::core::model::core::implicit_geometry::ImplicitGeometry;
use ecitygml_ffi::citygml::core::model::core::implicit_geometry_property::ImplicitGeometryProperty;
use ecitygml_ffi::citygml::core::model::core::refs::abstract_feature_kind_ref::AbstractFeatureKindRef;
use ecitygml_ffi::citygml::core::model::generics::generic_attribute_kind::GenericAttributeKind;
use ecitygml_ffi::citygml::core::model::generics::generic_attribute_set::GenericAttributeSet;
use ecitygml_ffi::citygml::core::model::transportation::enums::granularity_value::GranularityValue;
use ecitygml_ffi::citygml::core::model::transportation::enums::traffic_direction_value::TrafficDirectionValue;
use ecitygml_ffi::citygml::core::model::transportation::section::Section;
use ecitygml_ffi::citygml::core::model::transportation::traffic_space::TrafficSpace;
use ecitygml_ffi::citygml::core::model::tunnel::tunnel::Tunnel;
use ecitygml_ffi::citygml::core::model::tunnel::tunnel_part::TunnelPart;
use ecitygml_ffi::citygml::core::model::vegetation::plant_cover::PlantCover;
use ecitygml_ffi::citygml::core::model::vegetation::solitary_vegetation_object::SolitaryVegetationObject;
use ecitygml_ffi::citygml::io::format::CitygmlFormat;
use ecitygml_ffi::citygml::io::gml::read::GmlReader;
use ecitygml_ffi::citygml::io::gml::write::GmlWriter;
use ecitygml_ffi::error::ErrorKind;
use ecitygml_ffi::gml::core::model::common::geometry_type::GeometryType;
use ecitygml_ffi::gml::core::model::geometry::aggregates::multi_surface::MultiSurface;
use ecitygml_ffi::gml::core::model::geometry::primitives::abstract_ring_kind::AbstractRingKind;
use ecitygml_ffi::gml::core::model::geometry::primitives::line_string::LineString;
use ecitygml_ffi::gml::core::model::geometry::primitives::linear_ring::LinearRing;
use ecitygml_ffi::gml::core::model::geometry::primitives::point::Point;
use ecitygml_ffi::gml::core::model::geometry::primitives::polygon::Polygon;
use ecitygml_ffi::gml::core::model::geometry::primitives::triangulated_surface::TriangulatedSurface;

const DATASET: &str = "synthetic";

/// The items of a Diplomat iterator.
macro_rules! items {
    ($iterator:expr) => {
        match $iterator {
            mut iterator => std::iter::from_fn(|| iterator.next()).collect::<Vec<_>>(),
        }
    };
}

/// The values of a Diplomat iterator over code-list values.
macro_rules! values {
    ($iterator:expr) => {
        items!($iterator)
            .into_iter()
            .map(|value| value.value())
            .collect::<Vec<_>>()
    };
}

fn feature_types(city_model: &CityModel) -> Vec<FeatureType> {
    items!(city_model.iter_features())
        .iter()
        .map(|feature| feature.feature_type())
        .collect()
}

fn all<'a, T: 'a>(
    city_model: &'a CityModel,
    try_from: impl Fn(&AbstractFeatureKindRef<'a>) -> Option<&'a T>,
) -> Vec<&'a T> {
    let mut features = city_model.iter_features();
    std::iter::from_fn(|| features.next())
        .filter_map(|feature| try_from(&feature))
        .collect()
}

fn only<'a, T: 'a>(
    city_model: &'a CityModel,
    try_from: impl Fn(&AbstractFeatureKindRef<'a>) -> Option<&'a T>,
) -> &'a T {
    let found = all(city_model, try_from);
    assert_eq!(found.len(), 1, "expected exactly one");
    found[0]
}

fn round_trip(city_model: &CityModel) -> (Box<CityModel>, String) {
    let mut writer = GmlWriter::new(CitygmlFormat::Gml);
    writer.finish(city_model).unwrap();
    let text = String::from_utf8(writer.data().to_vec()).unwrap();
    let written = GmlReader::new(writer.data(), CitygmlFormat::Gml)
        .finish()
        .unwrap();
    (written, text)
}

mod bridge {
    use super::*;

    fn city_model() -> Box<CityModel> {
        read(DATASET, "bridge.gml")
    }

    fn bridge(city_model: &CityModel) -> &Bridge {
        only(city_model, |f| Bridge::try_from(f))
    }

    fn part(bridge: &Bridge) -> &BridgePart {
        let parts = items!(bridge.bridge_parts());
        assert_eq!(parts.len(), 1);
        assert!(parts[0].href().is_none());
        parts[0].object().unwrap()
    }

    fn assert_bridge(bridge: &Bridge) {
        assert_eq!(bridge.class().map(|c| c.value()), Some("1000"));
        assert_eq!(values!(bridge.functions()), ["1010", "1020"]);
        let date = bridge.date_of_construction().unwrap();
        assert_eq!((date.year(), date.month(), date.day()), (1990, 5, 1));
    }

    #[test]
    fn bridge_city_model() {
        let city_model = city_model();
        assert_eq!(city_model.city_objects_len(), 1);
        assert_eq!(
            feature_types(&city_model),
            [
                FeatureType::CityModel,
                FeatureType::Bridge,
                FeatureType::BridgePart
            ]
        );
        let city_objects: Vec<_> = items!(city_model.iter_city_objects())
            .iter()
            .map(|object| object.feature_type())
            .collect();
        assert_eq!(city_objects, [FeatureType::Bridge, FeatureType::BridgePart]);
    }

    #[test]
    fn bridge_attributes() {
        let city_model = city_model();
        let bridge = bridge(&city_model);
        assert_eq!(bridge.feature_id().as_str(), "bridge_1");
        assert_eq!(values!(bridge.names()), ["Synthetic bridge"]);
        assert_bridge(bridge);
        assert_eq!(values!(bridge.usages()), ["1000"]);
        assert!(bridge.heights().next().is_none());
        let part = part(bridge);
        assert_eq!(part.feature_id().as_str(), "bridge_part_1");
        assert!(part.class().is_none());
        assert!(part.functions().next().is_none());
        assert_eq!(
            only(&city_model, |f| BridgePart::try_from(f))
                .feature_id()
                .as_str(),
            "bridge_part_1"
        );
    }

    #[test]
    fn bridge_is_movable() {
        let city_model = city_model();
        let bridge = bridge(&city_model);
        assert_eq!(bridge.is_movable(), Some(true));
        assert_eq!(part(bridge).is_movable(), Some(false));
    }

    #[test]
    fn bridge_code_spaces() {
        let city_model = city_model();
        let bridge = bridge(&city_model);
        assert_eq!(
            bridge.class().unwrap().code().code_space(),
            Some("https://example.org/bridge_class")
        );
        assert!(
            items!(bridge.functions())
                .iter()
                .all(|f| f.code().code_space().is_none())
        );
    }

    #[test]
    fn bridge_round_trip() {
        let city_model = city_model();
        let (written, _) = round_trip(&city_model);
        assert_eq!(feature_types(&written), feature_types(&city_model));
        let bridge = bridge(&written);
        assert_bridge(bridge);
        assert_eq!(part(bridge).feature_id().as_str(), "bridge_part_1");
    }
}

mod tunnel {
    use super::*;

    fn city_model() -> Box<CityModel> {
        read(DATASET, "tunnel.gml")
    }

    fn tunnel(city_model: &CityModel) -> &Tunnel {
        only(city_model, |f| Tunnel::try_from(f))
    }

    fn part(tunnel: &Tunnel) -> &TunnelPart {
        let parts = items!(tunnel.tunnel_parts());
        assert_eq!(parts.len(), 1);
        assert!(parts[0].href().is_none());
        parts[0].object().unwrap()
    }

    #[test]
    fn tunnel_city_model() {
        let city_model = city_model();
        assert_eq!(city_model.city_objects_len(), 1);
        assert_eq!(
            feature_types(&city_model),
            [
                FeatureType::CityModel,
                FeatureType::Tunnel,
                FeatureType::TunnelPart
            ]
        );
        let city_objects: Vec<_> = items!(city_model.iter_city_objects())
            .iter()
            .map(|object| object.feature_type())
            .collect();
        assert_eq!(city_objects, [FeatureType::Tunnel, FeatureType::TunnelPart]);
    }

    #[test]
    fn tunnel_attributes() {
        let city_model = city_model();
        let tunnel = tunnel(&city_model);
        assert_eq!(tunnel.feature_id().as_str(), "tunnel_1");
        assert_eq!(values!(tunnel.names()), ["Synthetic tunnel"]);
        assert_eq!(tunnel.class().map(|c| c.value()), Some("1000"));
        assert_eq!(values!(tunnel.functions()), ["1010", "1020"]);
        assert_eq!(values!(tunnel.usages()), ["1000"]);
        let date = tunnel.date_of_construction().unwrap();
        assert_eq!((date.year(), date.month(), date.day()), (1990, 5, 1));
        assert!(tunnel.heights().next().is_none());
        let part = part(tunnel);
        assert_eq!(part.feature_id().as_str(), "tunnel_part_1");
        assert!(part.class().is_none());
        assert_eq!(values!(part.functions()), ["1030"]);
        assert_eq!(
            only(&city_model, |f| TunnelPart::try_from(f))
                .feature_id()
                .as_str(),
            "tunnel_part_1"
        );
    }

    #[test]
    fn tunnel_code_spaces() {
        let city_model = city_model();
        let tunnel = tunnel(&city_model);
        assert_eq!(
            tunnel.class().unwrap().code().code_space(),
            Some("https://example.org/tunnel_class")
        );
        assert!(
            items!(tunnel.functions())
                .iter()
                .all(|f| f.code().code_space().is_none())
        );
    }

    #[test]
    fn tunnel_round_trip() {
        let city_model = city_model();
        let (written, _) = round_trip(&city_model);
        assert_eq!(feature_types(&written), feature_types(&city_model));
        let tunnel = tunnel(&written);
        assert_eq!(tunnel.class().map(|c| c.value()), Some("1000"));
        assert_eq!(values!(tunnel.functions()), ["1010", "1020"]);
        assert_eq!(values!(part(tunnel).functions()), ["1030"]);
    }
}

mod vegetation {
    use super::*;

    fn city_model() -> Box<CityModel> {
        read(DATASET, "vegetation.gml")
    }

    fn tree<'a>(city_model: &'a CityModel, id: &str) -> &'a SolitaryVegetationObject {
        all(city_model, |f| SolitaryVegetationObject::try_from(f))
            .into_iter()
            .find(|tree| tree.feature_id().as_str() == id)
            .unwrap()
    }

    fn implicit(property: Option<&ImplicitGeometryProperty>) -> &ImplicitGeometry {
        let property = property.unwrap();
        assert!(property.href().is_none());
        property.object().unwrap()
    }

    #[test]
    fn vegetation_city_model() {
        let city_model = city_model();
        assert_eq!(city_model.city_objects_len(), 3);
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
        assert_eq!(values!(tree.functions()), ["1010"]);
        assert_eq!(values!(tree.usages()), ["1020"]);
        assert_eq!(tree.species().map(|s| s.value()), Some("Quercus robur"));
        let height = tree.height().unwrap();
        assert_close(height.value(), 12.5);
        assert_eq!(height.uom(), "m");
        assert_close(tree.trunk_diameter().unwrap().value(), 0.4);
        assert_close(tree.crown_diameter().unwrap().value(), 5.5);
        assert_close(tree.root_ball_diameter().unwrap().value(), 1.2);
        assert_close(tree.max_root_ball_depth().unwrap().value(), 0.8);
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
        let point = geometry.reference_point().object().unwrap().pos();
        assert_eq!(
            (point.x(), point.y(), point.z()),
            (457850.0, 5439090.0, 112.0)
        );
        let matrix = geometry.transformation_matrix();
        let rows = [
            [2.0, 0.0, 0.0, 10.0],
            [0.0, 2.0, 0.0, 20.0],
            [0.0, 0.0, 3.0, 30.0],
            [0.0, 0.0, 0.0, 1.0],
        ];
        for (row, values) in rows.iter().enumerate() {
            for (column, value) in values.iter().enumerate() {
                assert_close(matrix.get(row, column).unwrap(), *value);
            }
        }
        let relative = geometry.relative_geometry().unwrap().object().unwrap();
        assert_eq!(relative.geometry_type(), GeometryType::MultiSurface);
        let multi_surface = MultiSurface::try_from(relative).unwrap();
        assert_eq!(items!(multi_surface.surface_member()).len(), 1);
        assert!(Point::try_from(relative).is_none());
        let triangulation = relative.triangulate().unwrap();
        assert!(!triangulation.has_skipped());
        assert_eq!(items!(triangulation.surface().triangles()).len(), 1);
    }

    #[test]
    fn vegetation_point_relative_geometry() {
        let city_model = city_model();
        let tree = tree(&city_model, "tree_2");
        assert!(tree.lod1_implicit_representation().is_none());
        let geometry = implicit(tree.lod2_implicit_representation());
        assert_eq!(geometry.object_id().as_str(), "point_prototype");
        assert!(geometry.mime_type().is_none());
        let relative = geometry.relative_geometry().unwrap().object().unwrap();
        assert_eq!(relative.geometry_type(), GeometryType::Point);
        let pos = Point::try_from(relative).unwrap().pos();
        assert_eq!((pos.x(), pos.y(), pos.z()), (0.0, 0.0, 0.0));
        assert!(MultiSurface::try_from(relative).is_none());
    }

    #[test]
    fn vegetation_library_object() {
        let city_model = city_model();
        let first = implicit(tree(&city_model, "tree_1").lod1_implicit_representation());
        assert!(first.library_object().is_none());
        let second = implicit(tree(&city_model, "tree_2").lod2_implicit_representation());
        assert_eq!(
            second.library_object(),
            Some("https://example.org/trees/oak.gltf")
        );
    }

    #[test]
    fn vegetation_plant_cover() {
        let city_model = city_model();
        let cover = only(&city_model, |f| PlantCover::try_from(f));
        assert_eq!(cover.feature_id().as_str(), "cover_1");
        assert_eq!(cover.class().map(|c| c.value()), Some("2000"));
        assert!(cover.functions().next().is_none());
        assert!(cover.usages().next().is_none());
        assert_close(cover.average_height().unwrap().value(), 2.5);
        assert_close(cover.min_height().unwrap().value(), 1.0);
        assert_close(cover.max_height().unwrap().value(), 4.0);
        assert!(cover.lod1_implicit_representation().is_none());
        let features = items!(city_model.iter_features());
        let feature = features
            .iter()
            .find(|f| f.feature_type() == FeatureType::PlantCover)
            .unwrap();
        assert!(SolitaryVegetationObject::try_from(feature).is_none());
    }

    #[test]
    fn vegetation_code_spaces() {
        let city_model = city_model();
        let class = tree(&city_model, "tree_1").class().unwrap().code();
        assert_eq!(class.code_space(), Some("https://example.org/tree_class"));
        let cover = only(&city_model, |f| PlantCover::try_from(f));
        assert!(cover.class().unwrap().code().code_space().is_none());
    }

    #[test]
    fn vegetation_round_trip() {
        let city_model = city_model();
        let (written, text) = round_trip(&city_model);
        assert_eq!(feature_types(&written), feature_types(&city_model));
        let tree = tree(&written, "tree_1");
        assert_eq!(tree.species().map(|s| s.value()), Some("Quercus robur"));
        assert_close(tree.height().unwrap().value(), 12.5);
        let geometry = implicit(tree.lod1_implicit_representation());
        assert_eq!(geometry.object_id().as_str(), "tree_prototype");
        assert_eq!(
            geometry.mime_type().map(|m| m.value()),
            Some("model/gltf+json")
        );
        let cover = only(&written, |f| PlantCover::try_from(f));
        assert_close(cover.average_height().unwrap().value(), 2.5);
        assert!(!text.contains("objectId"));
    }
}

mod city_furniture {
    use super::*;

    fn city_model() -> Box<CityModel> {
        read(DATASET, "city-furniture.gml")
    }

    #[test]
    fn furniture_attributes() {
        let city_model = city_model();
        let furniture = only(&city_model, |f| CityFurniture::try_from(f));
        assert_eq!(furniture.feature_id().as_str(), "sign_1");
        assert_eq!(values!(furniture.names()), ["Vorschriftzeichen"]);
        assert_eq!(furniture.class().map(|c| c.value()), Some("1000"));
        assert_eq!(values!(furniture.functions()), ["1080"]);
        assert_eq!(values!(furniture.usages()), ["1090"]);
        let property = furniture.lod2_multi_surface().unwrap();
        assert!(property.href().is_none());
        assert_eq!(items!(property.object().unwrap().surface_member()).len(), 1);
        assert!(furniture.lod1_implicit_representation().is_none());
        assert!(furniture.lod2_terrain_intersection_curve().is_none());
    }

    #[test]
    fn furniture_code_spaces() {
        let city_model = city_model();
        let furniture = only(&city_model, |f| CityFurniture::try_from(f));
        assert_eq!(
            furniture.class().unwrap().code().code_space(),
            Some("https://example.org/furniture_class")
        );
    }
}

mod building {
    use super::*;

    fn city_model() -> Box<CityModel> {
        read(DATASET, "building.gml")
    }

    fn building(city_model: &CityModel) -> &Building {
        all(city_model, |f| Building::try_from(f))
            .into_iter()
            .find(|b| b.feature_id().as_str() == "building_1")
            .unwrap()
    }

    fn attribute_set(building: &Building) -> &GenericAttributeSet {
        let attributes: Vec<&GenericAttributeKind> = items!(building.generic_attributes());
        assert_eq!(attributes.len(), 1);
        GenericAttributeSet::try_from(attributes[0]).unwrap()
    }

    fn roof(
        property: &ecitygml_ffi::citygml::core::model::core::abstract_space_boundary_property::AbstractSpaceBoundaryProperty,
    ) -> &RoofSurface {
        assert!(property.href().is_none());
        let feature = AbstractFeatureKindRef::from_space_boundary(property.object().unwrap());
        // The feature borrows from the model, not from `feature`.
        let roof: &RoofSurface = RoofSurface::try_from(&feature).unwrap();
        roof
    }

    #[test]
    fn building_city_model() {
        let city_model = city_model();
        assert_eq!(city_model.city_objects_len(), 2);
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
        assert_eq!(items!(city_model.iter_city_objects()).len(), 4);
    }

    #[test]
    fn building_relation() {
        let city_model = city_model();
        let relations = items!(building(&city_model).related_to());
        assert_eq!(relations.len(), 1);
        assert!(relations[0].href().is_none());
        let relation = relations[0].object().unwrap();
        assert_eq!(relation.relation_type().value(), "shared");
        let href = relation.relation_to().href().unwrap();
        assert_eq!(written(|w| href.to_string(w)), "#building_2");
        let attributes: Vec<&GenericAttributeKind> = items!(relation.generic_attributes());
        assert_eq!(attributes.len(), 1);
        let weight = attributes[0].as_int().unwrap();
        assert_eq!((attributes[0].name(), weight.value()), ("weight", 3));
    }

    #[test]
    fn building_attribute_set() {
        let city_model = city_model();
        let set = attribute_set(building(&city_model));
        assert_eq!(set.name(), "energy");
        let attributes: Vec<&GenericAttributeKind> = items!(set.generic_attributes());
        assert_eq!(attributes.len(), 2);
        assert_eq!(attributes[0].name(), "demand");
        assert_close(attributes[0].as_double().unwrap().value(), 12.5);
        assert_eq!(attributes[1].name(), "label");
        assert_eq!(attributes[1].as_string().unwrap().value(), "A+");
    }

    #[test]
    fn building_construction() {
        let city_model = city_model();
        let building = building(&city_model);
        assert_eq!(
            building.relative_to_water(),
            Some(RelativeToWater::EntirelyAboveWaterSurface)
        );
        let built = building.date_of_construction().unwrap();
        assert_eq!((built.year(), built.month(), built.day()), (2020, 1, 1));
        let demolished = building.date_of_demolition().unwrap();
        assert_eq!(
            (demolished.year(), demolished.month(), demolished.day()),
            (2050, 12, 31)
        );
        let occupancies = items!(building.occupancies());
        assert_eq!(occupancies.len(), 1);
        assert_eq!(occupancies[0].number_of_occupants(), 4);
        assert_eq!(
            occupancies[0].interval().map(|i| i.value()),
            Some("daytime")
        );
        assert_eq!(
            occupancies[0].occupant_type().map(|t| t.value()),
            Some("residents")
        );
    }

    #[test]
    fn building_boundaries() {
        let city_model = city_model();
        let boundaries = items!(building(&city_model).boundaries());
        assert_eq!(boundaries.len(), 2);
        let roof = roof(boundaries[0]);
        assert_eq!(roof.feature_id().as_str(), "roof_1");
        let fillings = items!(roof.filling_surfaces());
        assert_eq!(fillings.len(), 1);
        assert!(fillings[0].href().is_none());
        let window = fillings[0].object().unwrap();
        assert_eq!(window.feature_type(), FeatureType::WindowSurface);
        assert_eq!(window.feature_id().as_str(), "roof_window_1");
        assert!(boundaries[1].object().is_none());
        let href = boundaries[1].href().unwrap();
        assert_eq!(written(|w| href.to_string(w)), "#missing_boundary");
    }

    #[test]
    fn building_terrain_intersection_curve() {
        let city_model = city_model();
        let building = building(&city_model);
        let property = building.lod2_terrain_intersection_curve().unwrap();
        assert!(property.href().is_none());
        let multi_curve = property.object().unwrap();
        let members = items!(multi_curve.curve_member());
        assert_eq!(members.len(), 1);
        let line = LineString::try_from(members[0].object().unwrap()).unwrap();
        assert_eq!(items!(line.points()).len(), 2);
        assert_close(multi_curve.length_3d().unwrap(), 12.0);
        assert!(building.lod1_terrain_intersection_curve().is_none());
        assert!(building.lod3_terrain_intersection_curve().is_none());
    }

    #[test]
    fn building_round_trip() {
        let city_model = city_model();
        let (written_model, text) = round_trip(&city_model);
        assert_eq!(feature_types(&written_model), feature_types(&city_model));
        let building = building(&written_model);
        let relations = items!(building.related_to());
        let href = relations[0].object().unwrap().relation_to().href().unwrap();
        assert_eq!(written(|w| href.to_string(w)), "#building_2");
        assert_eq!(attribute_set(building).name(), "energy");
        let demolished = building.date_of_demolition().unwrap();
        assert_eq!(
            (demolished.year(), demolished.month(), demolished.day()),
            (2050, 12, 31)
        );
        let occupancies = items!(building.occupancies());
        assert_eq!(occupancies.len(), 1);
        assert_eq!(occupancies[0].number_of_occupants(), 4);
        assert_eq!(
            occupancies[0].interval().map(|i| i.value()),
            Some("daytime")
        );
        assert_eq!(
            occupancies[0].occupant_type().map(|t| t.value()),
            Some("residents")
        );
        let boundaries = items!(building.boundaries());
        let fillings = items!(roof(boundaries[0]).filling_surfaces());
        assert_eq!(
            fillings[0].object().unwrap().feature_id().as_str(),
            "roof_window_1"
        );
        let href = boundaries[1].href().unwrap();
        assert_eq!(written(|w| href.to_string(w)), "#missing_boundary");
        let curve = building
            .lod2_terrain_intersection_curve()
            .unwrap()
            .object()
            .unwrap();
        assert_close(curve.length_3d().unwrap(), 12.0);
        assert!(!text.contains("TerrainIntersectionCurveProperty"));
    }
}

mod transportation {
    use super::*;

    fn city_model() -> Box<CityModel> {
        read(DATASET, "transportation.gml")
    }

    fn space(city_model: &CityModel) -> &TrafficSpace {
        only(city_model, |f| TrafficSpace::try_from(f))
    }

    #[test]
    fn transportation_section() {
        let city_model = city_model();
        let section = only(&city_model, |f| Section::try_from(f));
        assert_eq!(section.feature_id().as_str(), "section_1");
        assert_eq!(
            section.traffic_direction(),
            Some(TrafficDirectionValue::Both)
        );
        let occupancies = items!(section.occupancies());
        assert_eq!(occupancies.len(), 1);
        assert_eq!(occupancies[0].number_of_occupants(), 120);
        assert_eq!(
            occupancies[0].interval().map(|i| i.value()),
            Some("peakHour")
        );
        let spaces = items!(section.traffic_spaces());
        assert_eq!(spaces.len(), 1);
        assert!(spaces[0].href().is_none());
        let space = spaces[0].object().unwrap();
        assert_eq!(space.feature_id().as_str(), "space_1");
        assert_eq!(space.granularity(), GranularityValue::Lane);
    }

    #[test]
    fn transportation_point() {
        let city_model = city_model();
        let property = space(&city_model).lod0_point().unwrap();
        assert!(property.href().is_none());
        let point = property.object().unwrap();
        assert_eq!(point.id().map(|id| id.as_str()), Some("point_1"));
        let pos = point.pos();
        assert_eq!((pos.x(), pos.y(), pos.z()), (1.5, -2.5, 3.25));
        let envelope = point.compute_envelope().unwrap();
        for corner in [envelope.lower_corner(), envelope.upper_corner()] {
            assert_eq!((corner.x(), corner.y(), corner.z()), (1.5, -2.5, 3.25));
        }
    }

    #[test]
    fn transportation_curves() {
        let city_model = city_model();
        let multi_curve = space(&city_model)
            .lod0_multi_curve()
            .unwrap()
            .object()
            .unwrap();
        let members = items!(multi_curve.curve_member());
        assert_eq!(members.len(), 3);
        let line = members[0].object().unwrap();
        assert_eq!(line.geometry_type(), GeometryType::LineString);
        assert!(AbstractRingKind::try_from(line).is_none());
        let line_string = LineString::try_from(line).unwrap();
        assert_eq!(items!(line_string.points()).len(), 2);
        assert_close(line_string.length_3d(), 5.0);
        let ring = members[1].object().unwrap();
        assert_eq!(ring.geometry_type(), GeometryType::LinearRing);
        let linear_ring = LinearRing::try_from(AbstractRingKind::try_from(ring).unwrap()).unwrap();
        assert_eq!(items!(linear_ring.points()).len(), 3);
        assert_close(linear_ring.length_3d(), 2.0 + 2f64.sqrt());
        assert!(members[2].object().is_none());
        let href = members[2].href().unwrap();
        assert_eq!(written(|w| href.to_string(w)), "#missing_curve");
        let error = multi_curve.length_3d().unwrap_err();
        assert_eq!(error.kind(), ErrorKind::UnresolvedReference);
        assert!(written(|w| error.message(w)).contains("#missing_curve"));
    }
}

mod geometry {
    use super::*;

    #[test]
    fn geometry_skipped_members() {
        let city_model = read(DATASET, "geometry.gml");
        let multi_surface = all(&city_model, |f| Building::try_from(f))
            .into_iter()
            .find(|b| b.feature_id().as_str() == "geometry_1")
            .unwrap()
            .lod2_multi_surface()
            .unwrap()
            .object()
            .unwrap();
        let members: Vec<_> = items!(multi_surface.surface_member())
            .into_iter()
            .map(|member| member.object().unwrap())
            .collect();
        assert_eq!(members.len(), 3);
        for (kind, id) in members[..2].iter().zip(["square", "collinear"]) {
            assert_eq!(kind.geometry_type(), GeometryType::Polygon);
            assert_eq!(kind.id().map(|id| id.as_str()), Some(id));
        }
        assert_close(members[1].area_3d().unwrap(), 0.0);
        assert_eq!(
            members[2].geometry_type(),
            GeometryType::TriangulatedSurface
        );
        assert!(Polygon::try_from(members[2]).is_none());
        let tin = TriangulatedSurface::try_from(members[2]).unwrap();
        assert_eq!(tin.id().map(|id| id.as_str()), Some("tin"));
        assert_eq!(items!(tin.triangles()).len(), 2);
        assert_eq!(items!(tin.surface().patches()).len(), 2);
        assert_close(tin.area_3d().unwrap(), 1.0);
        let triangulation = multi_surface.triangulate().unwrap();
        assert_eq!(items!(triangulation.surface().triangles()).len(), 4);
        assert!(triangulation.has_skipped());
        let skipped = items!(triangulation.skipped());
        assert_eq!(skipped.len(), 1);
        assert_eq!(skipped[0].kind(), ErrorKind::InvalidArgument);
        assert!(written(|w| skipped[0].message(w)).contains("earcut produced no triangles"));
    }
}
