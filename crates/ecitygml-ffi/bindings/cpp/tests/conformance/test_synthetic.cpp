// The cases of crates/ecitygml/tests/conformance/synthetic.md.
#include "conformance.hpp"

#include <catch2/matchers/catch_matchers_string.hpp>

#include <ecitygml/AbstractCityObjectKindRef.hpp>
#include <ecitygml/AbstractCityObjectKindRefIterator.hpp>
#include <ecitygml/AbstractCurveKind.hpp>
#include <ecitygml/AbstractCurveProperty.hpp>
#include <ecitygml/AbstractCurvePropertyIterator.hpp>
#include <ecitygml/AbstractFeatureKindRef.hpp>
#include <ecitygml/AbstractFeatureKindRefIterator.hpp>
#include <ecitygml/AbstractFillingSurfaceKind.hpp>
#include <ecitygml/AbstractFillingSurfaceProperty.hpp>
#include <ecitygml/AbstractFillingSurfacePropertyIterator.hpp>
#include <ecitygml/AbstractGeometryKind.hpp>
#include <ecitygml/AbstractGeometryProperty.hpp>
#include <ecitygml/AbstractRingKind.hpp>
#include <ecitygml/AbstractSurfaceKind.hpp>
#include <ecitygml/AbstractSurfacePatchKindIterator.hpp>
#include <ecitygml/AbstractSurfaceProperty.hpp>
#include <ecitygml/AbstractSurfacePropertyIterator.hpp>
#include <ecitygml/Bridge.hpp>
#include <ecitygml/BridgeClassValue.hpp>
#include <ecitygml/BridgeFunctionValue.hpp>
#include <ecitygml/BridgeFunctionValueIterator.hpp>
#include <ecitygml/BridgePart.hpp>
#include <ecitygml/BridgePartProperty.hpp>
#include <ecitygml/BridgePartPropertyIterator.hpp>
#include <ecitygml/BridgeUsageValue.hpp>
#include <ecitygml/BridgeUsageValueIterator.hpp>
#include <ecitygml/CityFurniture.hpp>
#include <ecitygml/CityFurnitureClassValue.hpp>
#include <ecitygml/CityFurnitureFunctionValue.hpp>
#include <ecitygml/CityFurnitureFunctionValueIterator.hpp>
#include <ecitygml/CityFurnitureUsageValue.hpp>
#include <ecitygml/CityFurnitureUsageValueIterator.hpp>
#include <ecitygml/CityObjectRelation.hpp>
#include <ecitygml/CityObjectRelationProperty.hpp>
#include <ecitygml/CityObjectRelationPropertyIterator.hpp>
#include <ecitygml/CitygmlFormat.hpp>
#include <ecitygml/Date.hpp>
#include <ecitygml/DirectPosition.hpp>
#include <ecitygml/DirectPositionIterator.hpp>
#include <ecitygml/DoubleAttribute.hpp>
#include <ecitygml/Envelope.hpp>
#include <ecitygml/Error.hpp>
#include <ecitygml/ErrorKind.hpp>
#include <ecitygml/GenericAttributeKind.hpp>
#include <ecitygml/GenericAttributeKindIterator.hpp>
#include <ecitygml/GenericAttributeSet.hpp>
#include <ecitygml/GeometryType.hpp>
#include <ecitygml/GmlReader.hpp>
#include <ecitygml/GmlWriter.hpp>
#include <ecitygml/GranularityValue.hpp>
#include <ecitygml/HRef.hpp>
#include <ecitygml/HeightIterator.hpp>
#include <ecitygml/Id.hpp>
#include <ecitygml/ImplicitGeometry.hpp>
#include <ecitygml/ImplicitGeometryProperty.hpp>
#include <ecitygml/IntAttribute.hpp>
#include <ecitygml/IntervalValue.hpp>
#include <ecitygml/Length.hpp>
#include <ecitygml/LineString.hpp>
#include <ecitygml/LinearRing.hpp>
#include <ecitygml/MimeTypeValue.hpp>
#include <ecitygml/MultiCurve.hpp>
#include <ecitygml/MultiCurveProperty.hpp>
#include <ecitygml/MultiSurface.hpp>
#include <ecitygml/MultiSurfaceProperty.hpp>
#include <ecitygml/Occupancy.hpp>
#include <ecitygml/OccupancyIterator.hpp>
#include <ecitygml/OccupantTypeValue.hpp>
#include <ecitygml/PlantCover.hpp>
#include <ecitygml/PlantCoverClassValue.hpp>
#include <ecitygml/Point.hpp>
#include <ecitygml/PointProperty.hpp>
#include <ecitygml/Polygon.hpp>
#include <ecitygml/Reference.hpp>
#include <ecitygml/RelationTypeValue.hpp>
#include <ecitygml/RelativeToWater.hpp>
#include <ecitygml/RoofSurface.hpp>
#include <ecitygml/Section.hpp>
#include <ecitygml/SolitaryVegetationObject.hpp>
#include <ecitygml/SolitaryVegetationObjectClassValue.hpp>
#include <ecitygml/SolitaryVegetationObjectFunctionValue.hpp>
#include <ecitygml/SolitaryVegetationObjectFunctionValueIterator.hpp>
#include <ecitygml/SolitaryVegetationObjectUsageValue.hpp>
#include <ecitygml/SolitaryVegetationObjectUsageValueIterator.hpp>
#include <ecitygml/SpeciesValue.hpp>
#include <ecitygml/StringAttribute.hpp>
#include <ecitygml/Surface.hpp>
#include <ecitygml/TrafficDirectionValue.hpp>
#include <ecitygml/TrafficSpace.hpp>
#include <ecitygml/TrafficSpaceProperty.hpp>
#include <ecitygml/TrafficSpacePropertyIterator.hpp>
#include <ecitygml/TransformationMatrix4x4.hpp>
#include <ecitygml/TriangleIterator.hpp>
#include <ecitygml/TriangulatedSurface.hpp>
#include <ecitygml/Triangulation.hpp>
#include <ecitygml/TriangulationSkippedIterator.hpp>
#include <ecitygml/Tunnel.hpp>
#include <ecitygml/TunnelClassValue.hpp>
#include <ecitygml/TunnelFunctionValue.hpp>
#include <ecitygml/TunnelFunctionValueIterator.hpp>
#include <ecitygml/TunnelPart.hpp>
#include <ecitygml/TunnelPartProperty.hpp>
#include <ecitygml/TunnelPartPropertyIterator.hpp>
#include <ecitygml/TunnelUsageValue.hpp>
#include <ecitygml/TunnelUsageValueIterator.hpp>

#include <cmath>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using Catch::Matchers::ContainsSubstring;
using conformance::close;
using conformance::features;
using ecitygml::ErrorKind;
using ecitygml::FeatureType;
using ecitygml::GeometryType;

namespace {
const std::string DATASET = "synthetic";

std::unique_ptr<ecitygml::CityModel> read_file(const std::string& file) { return conformance::read(DATASET, file); }

template <typename Iterator>
int count(const std::unique_ptr<Iterator>& iterator) {
    int n = 0;
    while (iterator->next() != nullptr) {
        ++n;
    }
    return n;
}

template <typename Result>
auto ok(Result result) {
    REQUIRE(result.is_ok());
    return std::move(result).ok().value();
}

std::vector<FeatureType> feature_types(const ecitygml::CityModel& city_model) {
    std::vector<FeatureType> result;
    for (const auto& feature : features(city_model)) {
        result.push_back(feature->feature_type());
    }
    return result;
}

std::vector<FeatureType> city_object_types(const ecitygml::CityModel& city_model) {
    std::vector<FeatureType> result;
    auto iterator = city_model.iter_city_objects();
    while (auto object = iterator->next()) {
        result.push_back(object->feature_type());
    }
    return result;
}

template <typename T>
std::vector<const T*> all_of(const ecitygml::CityModel& city_model) {
    std::vector<const T*> result;
    auto iterator = city_model.iter_features();
    while (auto feature = iterator->next()) {
        if (const auto* x = T::try_from(*feature)) {
            result.push_back(x);
        }
    }
    return result;
}

template <typename T>
const T& only(const ecitygml::CityModel& city_model) {
    const auto found = all_of<T>(city_model);
    REQUIRE(found.size() == 1);
    return *found[0];
}

template <typename T>
const T& with_id(const ecitygml::CityModel& city_model, const std::string& id) {
    for (const auto* x : all_of<T>(city_model)) {
        if (x->feature_id().as_str() == id) {
            return *x;
        }
    }
    FAIL("no feature " << id);
    throw;
}

template <typename Iterator>
std::vector<std::string> values(const std::unique_ptr<Iterator>& iterator) {
    std::vector<std::string> result;
    while (const auto* value = iterator->next()) {
        result.emplace_back(value->value());
    }
    return result;
}

std::tuple<int32_t, uint32_t, uint32_t> ymd(const ecitygml::Date* date) {
    REQUIRE(date != nullptr);
    return {date->year(), date->month(), date->day()};
}

std::pair<std::unique_ptr<ecitygml::CityModel>, std::string> round_trip(const ecitygml::CityModel& city_model) {
    auto writer = ecitygml::GmlWriter::create(ecitygml::CitygmlFormat::Gml);
    REQUIRE(writer->finish(city_model).is_ok());
    const auto data = writer->data();
    std::string text(reinterpret_cast<const char*>(data.data()), data.size());
    return {ok(ecitygml::GmlReader::create(data, ecitygml::CitygmlFormat::Gml)->finish()), text};
}

const ecitygml::ImplicitGeometry& implicit(const ecitygml::ImplicitGeometryProperty* property) {
    REQUIRE(property != nullptr);
    REQUIRE(property->href() == nullptr);
    REQUIRE(property->object() != nullptr);
    return *property->object();
}

template <typename Feature, typename Property>
const Feature& single_inline(std::unique_ptr<Property> iterator) {
    const auto* property = iterator->next();
    REQUIRE(property != nullptr);
    REQUIRE(iterator->next() == nullptr);
    REQUIRE(property->href() == nullptr);
    REQUIRE(property->object() != nullptr);
    return *property->object();
}

const ecitygml::RoofSurface& roof(const ecitygml::AbstractSpaceBoundaryProperty& property) {
    REQUIRE(property.href() == nullptr);
    auto feature = ecitygml::AbstractFeatureKindRef::from_space_boundary(*property.object());
    const auto* roof_surface = ecitygml::RoofSurface::try_from(*feature);
    REQUIRE(roof_surface != nullptr);
    return *roof_surface;
}

const ecitygml::GenericAttributeSet& attribute_set(const ecitygml::Building& building) {
    auto attributes = building.generic_attributes();
    const auto* attribute = attributes->next();
    REQUIRE(attribute != nullptr);
    REQUIRE(attributes->next() == nullptr);
    const auto* set = ecitygml::GenericAttributeSet::try_from(*attribute);
    REQUIRE(set != nullptr);
    return *set;
}

std::vector<const ecitygml::AbstractSpaceBoundaryProperty*> boundary_properties(const ecitygml::Building& building) {
    std::vector<const ecitygml::AbstractSpaceBoundaryProperty*> result;
    auto iterator = building.boundaries();
    while (const auto* property = iterator->next()) {
        result.push_back(property);
    }
    return result;
}
}  // namespace

// bridge.gml

TEST_CASE("Bridge city model", "[synthetic]") {
    auto city_model = read_file("bridge.gml");
    REQUIRE(city_model->city_objects_len() == 1);
    REQUIRE(feature_types(*city_model) == std::vector{FeatureType(FeatureType::CityModel), FeatureType(FeatureType::Bridge), FeatureType(FeatureType::BridgePart)});
    REQUIRE(city_object_types(*city_model) == std::vector{FeatureType(FeatureType::Bridge), FeatureType(FeatureType::BridgePart)});
}

TEST_CASE("Bridge attributes", "[synthetic]") {
    auto city_model = read_file("bridge.gml");
    const auto& bridge = only<ecitygml::Bridge>(*city_model);
    REQUIRE(bridge.feature_id().as_str() == "bridge_1");
    REQUIRE(values(bridge.names()) == std::vector<std::string>{"Synthetic bridge"});
    REQUIRE(bridge.class_()->value() == "1000");
    REQUIRE(values(bridge.functions()) == std::vector<std::string>{"1010", "1020"});
    REQUIRE(values(bridge.usages()) == std::vector<std::string>{"1000"});
    REQUIRE(ymd(bridge.date_of_construction()) == std::tuple<int32_t, uint32_t, uint32_t>{1990, 5, 1});
    REQUIRE(count(bridge.heights()) == 0);
    const auto& part = single_inline<ecitygml::BridgePart>(bridge.bridge_parts());
    REQUIRE(part.feature_id().as_str() == "bridge_part_1");
    REQUIRE(part.class_() == nullptr);
    REQUIRE(count(part.functions()) == 0);
    REQUIRE(only<ecitygml::BridgePart>(*city_model).feature_id().as_str() == "bridge_part_1");
}

TEST_CASE("Bridge is movable", "[synthetic]") {
    auto city_model = read_file("bridge.gml");
    const auto& bridge = only<ecitygml::Bridge>(*city_model);
    REQUIRE(bridge.is_movable() == std::optional<bool>(true));
    REQUIRE(single_inline<ecitygml::BridgePart>(bridge.bridge_parts()).is_movable() == std::optional<bool>(false));
}

TEST_CASE("Bridge code spaces", "[synthetic]") {
    auto city_model = read_file("bridge.gml");
    const auto& bridge = only<ecitygml::Bridge>(*city_model);
    REQUIRE(bridge.class_()->code().code_space() == "https://example.org/bridge_class");
    auto functions = bridge.functions();
    while (const auto* function = functions->next()) {
        REQUIRE_FALSE(function->code().code_space().has_value());
    }
}

TEST_CASE("Bridge round trip", "[synthetic]") {
    auto city_model = read_file("bridge.gml");
    auto [written, text] = round_trip(*city_model);
    REQUIRE(feature_types(*written) == feature_types(*city_model));
    const auto& bridge = only<ecitygml::Bridge>(*written);
    REQUIRE(bridge.class_()->value() == "1000");
    REQUIRE(values(bridge.functions()) == std::vector<std::string>{"1010", "1020"});
    REQUIRE(ymd(bridge.date_of_construction()) == std::tuple<int32_t, uint32_t, uint32_t>{1990, 5, 1});
    REQUIRE(single_inline<ecitygml::BridgePart>(bridge.bridge_parts()).feature_id().as_str() == "bridge_part_1");
}

// tunnel.gml

TEST_CASE("Tunnel city model", "[synthetic]") {
    auto city_model = read_file("tunnel.gml");
    REQUIRE(city_model->city_objects_len() == 1);
    REQUIRE(feature_types(*city_model) == std::vector{FeatureType(FeatureType::CityModel), FeatureType(FeatureType::Tunnel), FeatureType(FeatureType::TunnelPart)});
    REQUIRE(city_object_types(*city_model) == std::vector{FeatureType(FeatureType::Tunnel), FeatureType(FeatureType::TunnelPart)});
}

TEST_CASE("Tunnel attributes", "[synthetic]") {
    auto city_model = read_file("tunnel.gml");
    const auto& tunnel = only<ecitygml::Tunnel>(*city_model);
    REQUIRE(tunnel.feature_id().as_str() == "tunnel_1");
    REQUIRE(values(tunnel.names()) == std::vector<std::string>{"Synthetic tunnel"});
    REQUIRE(tunnel.class_()->value() == "1000");
    REQUIRE(values(tunnel.functions()) == std::vector<std::string>{"1010", "1020"});
    REQUIRE(values(tunnel.usages()) == std::vector<std::string>{"1000"});
    REQUIRE(ymd(tunnel.date_of_construction()) == std::tuple<int32_t, uint32_t, uint32_t>{1990, 5, 1});
    REQUIRE(count(tunnel.heights()) == 0);
    const auto& part = single_inline<ecitygml::TunnelPart>(tunnel.tunnel_parts());
    REQUIRE(part.feature_id().as_str() == "tunnel_part_1");
    REQUIRE(part.class_() == nullptr);
    REQUIRE(values(part.functions()) == std::vector<std::string>{"1030"});
    REQUIRE(only<ecitygml::TunnelPart>(*city_model).feature_id().as_str() == "tunnel_part_1");
}

TEST_CASE("Tunnel code spaces", "[synthetic]") {
    auto city_model = read_file("tunnel.gml");
    const auto& tunnel = only<ecitygml::Tunnel>(*city_model);
    REQUIRE(tunnel.class_()->code().code_space() == "https://example.org/tunnel_class");
    auto functions = tunnel.functions();
    while (const auto* function = functions->next()) {
        REQUIRE_FALSE(function->code().code_space().has_value());
    }
}

TEST_CASE("Tunnel round trip", "[synthetic]") {
    auto city_model = read_file("tunnel.gml");
    auto [written, text] = round_trip(*city_model);
    REQUIRE(feature_types(*written) == feature_types(*city_model));
    const auto& tunnel = only<ecitygml::Tunnel>(*written);
    REQUIRE(tunnel.class_()->value() == "1000");
    REQUIRE(values(tunnel.functions()) == std::vector<std::string>{"1010", "1020"});
    REQUIRE(values(single_inline<ecitygml::TunnelPart>(tunnel.tunnel_parts()).functions()) == std::vector<std::string>{"1030"});
}

// vegetation.gml

TEST_CASE("Vegetation city model", "[synthetic]") {
    auto city_model = read_file("vegetation.gml");
    REQUIRE(city_model->city_objects_len() == 3);
    REQUIRE(feature_types(*city_model) == std::vector{FeatureType(FeatureType::CityModel), FeatureType(FeatureType::SolitaryVegetationObject),
                                                      FeatureType(FeatureType::SolitaryVegetationObject), FeatureType(FeatureType::PlantCover)});
}

TEST_CASE("Vegetation tree", "[synthetic]") {
    auto city_model = read_file("vegetation.gml");
    const auto& tree = with_id<ecitygml::SolitaryVegetationObject>(*city_model, "tree_1");
    REQUIRE(tree.class_()->value() == "1000");
    REQUIRE(values(tree.functions()) == std::vector<std::string>{"1010"});
    REQUIRE(values(tree.usages()) == std::vector<std::string>{"1020"});
    REQUIRE(tree.species()->value() == "Quercus robur");
    REQUIRE_THAT(tree.height()->value(), close(12.5));
    REQUIRE(tree.height()->uom() == "m");
    REQUIRE_THAT(tree.trunk_diameter()->value(), close(0.4));
    REQUIRE_THAT(tree.crown_diameter()->value(), close(5.5));
    REQUIRE_THAT(tree.root_ball_diameter()->value(), close(1.2));
    REQUIRE_THAT(tree.max_root_ball_depth()->value(), close(0.8));
    REQUIRE(tree.lod2_implicit_representation() == nullptr);
    REQUIRE(tree.lod3_implicit_representation() == nullptr);
    REQUIRE(tree.lod1_solid() == nullptr);
    REQUIRE(tree.lod1_terrain_intersection_curve() == nullptr);
}

TEST_CASE("Vegetation implicit geometry", "[synthetic]") {
    auto city_model = read_file("vegetation.gml");
    const auto& geometry = implicit(with_id<ecitygml::SolitaryVegetationObject>(*city_model, "tree_1").lod1_implicit_representation());
    REQUIRE(geometry.object_id().as_str() == "tree_prototype");
    REQUIRE(geometry.mime_type()->value() == "model/gltf+json");
    const auto& pos = geometry.reference_point().object()->pos();
    REQUIRE(std::tuple{pos.x(), pos.y(), pos.z()} == std::tuple{457850.0, 5439090.0, 112.0});
    const double rows[4][4] = {{2, 0, 0, 10}, {0, 2, 0, 20}, {0, 0, 3, 30}, {0, 0, 0, 1}};
    for (size_t row = 0; row < 4; ++row) {
        for (size_t column = 0; column < 4; ++column) {
            REQUIRE_THAT(ok(geometry.transformation_matrix().get(row, column)), close(rows[row][column]));
        }
    }
    const auto* relative = geometry.relative_geometry()->object();
    REQUIRE(relative->geometry_type() == GeometryType::MultiSurface);
    REQUIRE(count(ecitygml::MultiSurface::try_from(*relative)->surface_member()) == 1);
    REQUIRE(ecitygml::Point::try_from(*relative) == nullptr);
    auto triangulation = ok(relative->triangulate());
    REQUIRE_FALSE(triangulation->has_skipped());
    REQUIRE(count(triangulation->surface().triangles()) == 1);
}

TEST_CASE("Vegetation point relative geometry", "[synthetic]") {
    auto city_model = read_file("vegetation.gml");
    const auto& tree = with_id<ecitygml::SolitaryVegetationObject>(*city_model, "tree_2");
    REQUIRE(tree.lod1_implicit_representation() == nullptr);
    const auto& geometry = implicit(tree.lod2_implicit_representation());
    REQUIRE(geometry.object_id().as_str() == "point_prototype");
    REQUIRE(geometry.mime_type() == nullptr);
    const auto* relative = geometry.relative_geometry()->object();
    REQUIRE(relative->geometry_type() == GeometryType::Point);
    const auto& pos = ecitygml::Point::try_from(*relative)->pos();
    REQUIRE(std::tuple{pos.x(), pos.y(), pos.z()} == std::tuple{0.0, 0.0, 0.0});
    REQUIRE(ecitygml::MultiSurface::try_from(*relative) == nullptr);
}

TEST_CASE("Vegetation library object", "[synthetic]") {
    auto city_model = read_file("vegetation.gml");
    const auto& first = implicit(with_id<ecitygml::SolitaryVegetationObject>(*city_model, "tree_1").lod1_implicit_representation());
    REQUIRE_FALSE(first.library_object().has_value());
    const auto& second = implicit(with_id<ecitygml::SolitaryVegetationObject>(*city_model, "tree_2").lod2_implicit_representation());
    REQUIRE(second.library_object() == "https://example.org/trees/oak.gltf");
}

TEST_CASE("Vegetation plant cover", "[synthetic]") {
    auto city_model = read_file("vegetation.gml");
    const auto& cover = only<ecitygml::PlantCover>(*city_model);
    REQUIRE(cover.feature_id().as_str() == "cover_1");
    REQUIRE(cover.class_()->value() == "2000");
    REQUIRE(count(cover.functions()) == 0);
    REQUIRE(count(cover.usages()) == 0);
    REQUIRE_THAT(cover.average_height()->value(), close(2.5));
    REQUIRE_THAT(cover.min_height()->value(), close(1.0));
    REQUIRE_THAT(cover.max_height()->value(), close(4.0));
    REQUIRE(cover.lod1_implicit_representation() == nullptr);
    for (const auto& feature : features(*city_model)) {
        if (feature->feature_type() == FeatureType::PlantCover) {
            REQUIRE(ecitygml::SolitaryVegetationObject::try_from(*feature) == nullptr);
        }
    }
}

TEST_CASE("Vegetation code spaces", "[synthetic]") {
    auto city_model = read_file("vegetation.gml");
    const auto& tree = with_id<ecitygml::SolitaryVegetationObject>(*city_model, "tree_1");
    REQUIRE(tree.class_()->code().code_space() == "https://example.org/tree_class");
    REQUIRE_FALSE(only<ecitygml::PlantCover>(*city_model).class_()->code().code_space().has_value());
}

TEST_CASE("Vegetation round trip", "[synthetic]") {
    auto city_model = read_file("vegetation.gml");
    auto [written, text] = round_trip(*city_model);
    REQUIRE(feature_types(*written) == feature_types(*city_model));
    const auto& tree = with_id<ecitygml::SolitaryVegetationObject>(*written, "tree_1");
    REQUIRE(tree.species()->value() == "Quercus robur");
    REQUIRE_THAT(tree.height()->value(), close(12.5));
    const auto& geometry = implicit(tree.lod1_implicit_representation());
    REQUIRE(geometry.object_id().as_str() == "tree_prototype");
    REQUIRE(geometry.mime_type()->value() == "model/gltf+json");
    REQUIRE_THAT(only<ecitygml::PlantCover>(*written).average_height()->value(), close(2.5));
    REQUIRE(text.find("objectId") == std::string::npos);
}

// city-furniture.gml

TEST_CASE("Furniture attributes", "[synthetic]") {
    auto city_model = read_file("city-furniture.gml");
    const auto& furniture = only<ecitygml::CityFurniture>(*city_model);
    REQUIRE(furniture.feature_id().as_str() == "sign_1");
    REQUIRE(values(furniture.names()) == std::vector<std::string>{"Vorschriftzeichen"});
    REQUIRE(furniture.class_()->value() == "1000");
    REQUIRE(values(furniture.functions()) == std::vector<std::string>{"1080"});
    REQUIRE(values(furniture.usages()) == std::vector<std::string>{"1090"});
    const auto* property = furniture.lod2_multi_surface();
    REQUIRE(property != nullptr);
    REQUIRE(property->href() == nullptr);
    REQUIRE(count(property->object()->surface_member()) == 1);
    REQUIRE(furniture.lod1_implicit_representation() == nullptr);
    REQUIRE(furniture.lod2_terrain_intersection_curve() == nullptr);
}

TEST_CASE("Furniture code spaces", "[synthetic]") {
    auto city_model = read_file("city-furniture.gml");
    REQUIRE(only<ecitygml::CityFurniture>(*city_model).class_()->code().code_space() == "https://example.org/furniture_class");
}

// building.gml

TEST_CASE("Building city model", "[synthetic]") {
    auto city_model = read_file("building.gml");
    REQUIRE(city_model->city_objects_len() == 2);
    REQUIRE(feature_types(*city_model) == std::vector{FeatureType(FeatureType::CityModel), FeatureType(FeatureType::Building),
                                                      FeatureType(FeatureType::RoofSurface), FeatureType(FeatureType::WindowSurface),
                                                      FeatureType(FeatureType::Building)});
    REQUIRE(city_object_types(*city_model).size() == 4);
}

TEST_CASE("Building relation", "[synthetic]") {
    auto city_model = read_file("building.gml");
    const auto& relation = single_inline<ecitygml::CityObjectRelation>(with_id<ecitygml::Building>(*city_model, "building_1").related_to());
    REQUIRE(relation.relation_type().value() == "shared");
    REQUIRE(relation.relation_to().href()->to_string() == "#building_2");
    auto attributes = relation.generic_attributes();
    const auto* weight = attributes->next();
    REQUIRE(weight != nullptr);
    REQUIRE(attributes->next() == nullptr);
    REQUIRE(weight->name() == "weight");
    REQUIRE(weight->as_int()->value() == 3);
}

TEST_CASE("Building attribute set", "[synthetic]") {
    auto city_model = read_file("building.gml");
    const auto& set = attribute_set(with_id<ecitygml::Building>(*city_model, "building_1"));
    REQUIRE(set.name() == "energy");
    auto attributes = set.generic_attributes();
    const auto* demand = attributes->next();
    const auto* label = attributes->next();
    REQUIRE(attributes->next() == nullptr);
    REQUIRE(demand->name() == "demand");
    REQUIRE_THAT(demand->as_double()->value(), close(12.5));
    REQUIRE(label->name() == "label");
    REQUIRE(label->as_string()->value() == "A+");
}

TEST_CASE("Building construction", "[synthetic]") {
    auto city_model = read_file("building.gml");
    const auto& building = with_id<ecitygml::Building>(*city_model, "building_1");
    REQUIRE(building.relative_to_water() == ecitygml::RelativeToWater::EntirelyAboveWaterSurface);
    REQUIRE(ymd(building.date_of_construction()) == std::tuple<int32_t, uint32_t, uint32_t>{2020, 1, 1});
    REQUIRE(ymd(building.date_of_demolition()) == std::tuple<int32_t, uint32_t, uint32_t>{2050, 12, 31});
    auto occupancies = building.occupancies();
    const auto* occupancy = occupancies->next();
    REQUIRE(occupancy != nullptr);
    REQUIRE(occupancies->next() == nullptr);
    REQUIRE(occupancy->number_of_occupants() == 4);
    REQUIRE(occupancy->interval()->value() == "daytime");
    REQUIRE(occupancy->occupant_type()->value() == "residents");
}

TEST_CASE("Building boundaries", "[synthetic]") {
    auto city_model = read_file("building.gml");
    const auto boundaries = boundary_properties(with_id<ecitygml::Building>(*city_model, "building_1"));
    REQUIRE(boundaries.size() == 2);
    const auto& roof_surface = roof(*boundaries[0]);
    REQUIRE(roof_surface.feature_id().as_str() == "roof_1");
    const auto& window = single_inline<ecitygml::AbstractFillingSurfaceKind>(roof_surface.filling_surfaces());
    REQUIRE(window.feature_type() == FeatureType::WindowSurface);
    REQUIRE(window.feature_id().as_str() == "roof_window_1");
    REQUIRE(boundaries[1]->object() == nullptr);
    REQUIRE(boundaries[1]->href()->to_string() == "#missing_boundary");
}

TEST_CASE("Building terrain intersection curve", "[synthetic]") {
    auto city_model = read_file("building.gml");
    const auto& building = with_id<ecitygml::Building>(*city_model, "building_1");
    const auto* property = building.lod2_terrain_intersection_curve();
    REQUIRE(property != nullptr);
    REQUIRE(property->href() == nullptr);
    const auto* multi_curve = property->object();
    auto members = multi_curve->curve_member();
    const auto* member = members->next();
    REQUIRE(members->next() == nullptr);
    REQUIRE(count(ecitygml::LineString::try_from(*member->object())->points()) == 2);
    REQUIRE_THAT(ok(multi_curve->length_3d()), close(12.0));
    REQUIRE(building.lod1_terrain_intersection_curve() == nullptr);
    REQUIRE(building.lod3_terrain_intersection_curve() == nullptr);
}

TEST_CASE("Building round trip", "[synthetic]") {
    auto city_model = read_file("building.gml");
    auto [written, text] = round_trip(*city_model);
    REQUIRE(feature_types(*written) == feature_types(*city_model));
    const auto& building = with_id<ecitygml::Building>(*written, "building_1");
    const auto& relation = single_inline<ecitygml::CityObjectRelation>(building.related_to());
    REQUIRE(relation.relation_to().href()->to_string() == "#building_2");
    REQUIRE(attribute_set(building).name() == "energy");
    REQUIRE(ymd(building.date_of_demolition()) == std::tuple<int32_t, uint32_t, uint32_t>{2050, 12, 31});
    auto occupancies = building.occupancies();
    const auto* occupancy = occupancies->next();
    REQUIRE(occupancy != nullptr);
    REQUIRE(occupancies->next() == nullptr);
    REQUIRE(occupancy->number_of_occupants() == 4);
    REQUIRE(occupancy->interval()->value() == "daytime");
    REQUIRE(occupancy->occupant_type()->value() == "residents");
    const auto boundaries = boundary_properties(building);
    const auto& window = single_inline<ecitygml::AbstractFillingSurfaceKind>(roof(*boundaries[0]).filling_surfaces());
    REQUIRE(window.feature_id().as_str() == "roof_window_1");
    REQUIRE(boundaries[1]->href()->to_string() == "#missing_boundary");
    REQUIRE_THAT(ok(building.lod2_terrain_intersection_curve()->object()->length_3d()), close(12.0));
    REQUIRE(text.find("TerrainIntersectionCurveProperty") == std::string::npos);
}

// transportation.gml

TEST_CASE("Transportation section", "[synthetic]") {
    auto city_model = read_file("transportation.gml");
    const auto& section = only<ecitygml::Section>(*city_model);
    REQUIRE(section.feature_id().as_str() == "section_1");
    REQUIRE(section.traffic_direction() == ecitygml::TrafficDirectionValue::Both);
    auto occupancies = section.occupancies();
    const auto* occupancy = occupancies->next();
    REQUIRE(occupancies->next() == nullptr);
    REQUIRE(occupancy->number_of_occupants() == 120);
    REQUIRE(occupancy->interval()->value() == "peakHour");
    const auto& space = single_inline<ecitygml::TrafficSpace>(section.traffic_spaces());
    REQUIRE(space.feature_id().as_str() == "space_1");
    REQUIRE(space.granularity() == ecitygml::GranularityValue::Lane);
}

TEST_CASE("Transportation point", "[synthetic]") {
    auto city_model = read_file("transportation.gml");
    const auto* property = only<ecitygml::TrafficSpace>(*city_model).lod0_point();
    REQUIRE(property != nullptr);
    REQUIRE(property->href() == nullptr);
    const auto* point = property->object();
    REQUIRE(point->id()->as_str() == "point_1");
    const auto& pos = point->pos();
    REQUIRE(std::tuple{pos.x(), pos.y(), pos.z()} == std::tuple{1.5, -2.5, 3.25});
    auto envelope = point->compute_envelope();
    REQUIRE(envelope != nullptr);
    for (const auto* corner : {&envelope->lower_corner(), &envelope->upper_corner()}) {
        REQUIRE(std::tuple{corner->x(), corner->y(), corner->z()} == std::tuple{1.5, -2.5, 3.25});
    }
}

TEST_CASE("Transportation curves", "[synthetic]") {
    auto city_model = read_file("transportation.gml");
    const auto* multi_curve = only<ecitygml::TrafficSpace>(*city_model).lod0_multi_curve()->object();
    std::vector<const ecitygml::AbstractCurveProperty*> members;
    auto iterator = multi_curve->curve_member();
    while (const auto* member = iterator->next()) {
        members.push_back(member);
    }
    REQUIRE(members.size() == 3);
    const auto* line = members[0]->object();
    REQUIRE(line->geometry_type() == GeometryType::LineString);
    REQUIRE(ecitygml::AbstractRingKind::try_from(*line) == nullptr);
    const auto* line_string = ecitygml::LineString::try_from(*line);
    REQUIRE(count(line_string->points()) == 2);
    REQUIRE_THAT(line_string->length_3d(), close(5.0));
    const auto* ring = members[1]->object();
    REQUIRE(ring->geometry_type() == GeometryType::LinearRing);
    const auto* linear_ring = ecitygml::LinearRing::try_from(*ecitygml::AbstractRingKind::try_from(*ring));
    REQUIRE(count(linear_ring->points()) == 3);
    REQUIRE_THAT(linear_ring->length_3d(), close(2.0 + std::sqrt(2.0)));
    REQUIRE(members[2]->object() == nullptr);
    REQUIRE(members[2]->href()->to_string() == "#missing_curve");
    auto length = multi_curve->length_3d();
    REQUIRE(length.is_err());
    const auto error = std::move(length).err().value();
    REQUIRE(error->kind() == ErrorKind::UnresolvedReference);
    REQUIRE_THAT(error->message(), ContainsSubstring("#missing_curve"));
}

// geometry.gml

TEST_CASE("Geometry skipped members", "[synthetic]") {
    auto city_model = read_file("geometry.gml");
    const auto* multi_surface = with_id<ecitygml::Building>(*city_model, "geometry_1").lod2_multi_surface()->object();
    std::vector<const ecitygml::AbstractSurfaceKind*> members;
    auto iterator = multi_surface->surface_member();
    while (const auto* member = iterator->next()) {
        members.push_back(member->object());
    }
    REQUIRE(members.size() == 3);
    for (const auto& [kind, id] : {std::pair{members[0], "square"}, std::pair{members[1], "collinear"}}) {
        REQUIRE(kind->geometry_type() == GeometryType::Polygon);
        REQUIRE(kind->id()->as_str() == id);
    }
    REQUIRE_THAT(ok(members[1]->area_3d()), close(0.0));
    REQUIRE(members[2]->geometry_type() == GeometryType::TriangulatedSurface);
    REQUIRE(ecitygml::Polygon::try_from(*members[2]) == nullptr);
    const auto* tin = ecitygml::TriangulatedSurface::try_from(*members[2]);
    REQUIRE(tin != nullptr);
    REQUIRE(tin->id()->as_str() == "tin");
    REQUIRE(count(tin->triangles()) == 2);
    REQUIRE(count(tin->surface().patches()) == 2);
    REQUIRE_THAT(ok(tin->area_3d()), close(1.0));
    auto triangulation = ok(multi_surface->triangulate());
    REQUIRE(count(triangulation->surface().triangles()) == 4);
    REQUIRE(triangulation->has_skipped());
    auto skipped = triangulation->skipped();
    auto error = skipped->next();
    REQUIRE(error != nullptr);
    REQUIRE(skipped->next() == nullptr);
    REQUIRE(error->kind() == ErrorKind::InvalidArgument);
    REQUIRE_THAT(error->message(), ContainsSubstring("earcut produced no triangles"));
}
