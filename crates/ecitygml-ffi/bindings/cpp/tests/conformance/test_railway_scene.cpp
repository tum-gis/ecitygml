// The cases of crates/ecitygml/tests/conformance/railway-scene.md.
#include "conformance/conformance.hpp"

#include <ecitygml/AbstractCityObjectKindRef.hpp>
#include <ecitygml/AbstractCityObjectKindRefIterator.hpp>
#include <ecitygml/AbstractGeometryKind.hpp>
#include <ecitygml/AbstractGeometryProperty.hpp>
#include <ecitygml/AbstractReliefComponentKind.hpp>
#include <ecitygml/AbstractReliefComponentProperty.hpp>
#include <ecitygml/AbstractReliefComponentPropertyIterator.hpp>
#include <ecitygml/AbstractSpaceBoundaryKind.hpp>
#include <ecitygml/AbstractSpaceBoundaryProperty.hpp>
#include <ecitygml/AbstractSpaceBoundaryPropertyIterator.hpp>
#include <ecitygml/AbstractSurfacePropertyIterator.hpp>
#include <ecitygml/Bridge.hpp>
#include <ecitygml/CityFurniture.hpp>
#include <ecitygml/CityFurnitureClassValue.hpp>
#include <ecitygml/CityFurnitureFunctionValue.hpp>
#include <ecitygml/CityFurnitureFunctionValueIterator.hpp>
#include <ecitygml/CityFurnitureUsageValueIterator.hpp>
#include <ecitygml/CitygmlFormat.hpp>
#include <ecitygml/DateTime.hpp>
#include <ecitygml/DirectPosition.hpp>
#include <ecitygml/FeatureType.hpp>
#include <ecitygml/GmlReader.hpp>
#include <ecitygml/GmlWriter.hpp>
#include <ecitygml/HRef.hpp>
#include <ecitygml/Id.hpp>
#include <ecitygml/ImplicitGeometry.hpp>
#include <ecitygml/ImplicitGeometryProperty.hpp>
#include <ecitygml/LevelOfDetail.hpp>
#include <ecitygml/MimeTypeValue.hpp>
#include <ecitygml/MultiSurface.hpp>
#include <ecitygml/MultiSurfaceProperty.hpp>
#include <ecitygml/Point.hpp>
#include <ecitygml/PointProperty.hpp>
#include <ecitygml/RelativeToTerrain.hpp>
#include <ecitygml/ReliefFeature.hpp>
#include <ecitygml/SolitaryVegetationObject.hpp>
#include <ecitygml/SolitaryVegetationObjectClassValue.hpp>
#include <ecitygml/SolitaryVegetationObjectFunctionValue.hpp>
#include <ecitygml/SolitaryVegetationObjectFunctionValueIterator.hpp>
#include <ecitygml/SolitaryVegetationObjectUsageValueIterator.hpp>
#include <ecitygml/SpeciesValue.hpp>
#include <ecitygml/TinProperty.hpp>
#include <ecitygml/TinRelief.hpp>
#include <ecitygml/TransformationMatrix4x4.hpp>
#include <ecitygml/TriangleIterator.hpp>
#include <ecitygml/TriangulatedSurface.hpp>
#include <ecitygml/Tunnel.hpp>
#include <ecitygml/TunnelClassValue.hpp>
#include <ecitygml/TunnelFunctionValueIterator.hpp>
#include <ecitygml/TunnelPartPropertyIterator.hpp>
#include <ecitygml/TunnelUsageValueIterator.hpp>

#include <array>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using conformance::close;
using conformance::features;
using conformance::first_name;
using ecitygml::FeatureType;

namespace {
const std::string DATASET = "railway-scene";
const std::string FILE_NAME = "Railway_Scene_LoD3__v3-thinned.gml";
const std::string TEMPLATE_A = "#Mult_SO043561_5693_194007";
const std::string TEMPLATE_B = "#Mult_SO045475_3243_790864";
const std::set<std::string> INLINE_TEMPLATES{"Forest tree 3", "Tree1", "Forest tree 1"};
const std::set<std::string> TEMPLATE_A_TREES{"Forest tree 4", "Forest tree 9", "Forest tree 5"};
constexpr FeatureType WALL = FeatureType::WallSurface;
constexpr FeatureType ROOF = FeatureType::RoofSurface;
constexpr FeatureType GROUND = FeatureType::GroundSurface;
constexpr FeatureType CLOSURE = FeatureType::ClosureSurface;

/// The number of items of a Diplomat iterator.
template <typename Iterator>
int count(const std::unique_ptr<Iterator>& iterator) {
    int n = 0;
    while (iterator->next() != nullptr) {
        ++n;
    }
    return n;
}

/// The value of a successful result.
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

/// All features a class accepts, in document order; the model must outlive them.
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
std::vector<std::string> ids(const std::vector<const T*>& items) {
    std::vector<std::string> result;
    for (const auto* item : items) {
        result.emplace_back(item->feature_id().as_str());
    }
    return result;
}

template <typename Iterator>
std::vector<std::string> values(const std::unique_ptr<Iterator>& iterator) {
    std::vector<std::string> result;
    while (const auto* value = iterator->next()) {
        result.emplace_back(value->value());
    }
    return result;
}

/// A tree's inline LoD3 implicit geometry.
const ecitygml::ImplicitGeometry& implicit_geometry(const ecitygml::SolitaryVegetationObject& tree) {
    const auto* property = tree.lod3_implicit_representation();
    REQUIRE(property != nullptr);
    REQUIRE(property->href() == nullptr);
    REQUIRE(property->object() != nullptr);
    return *property->object();
}

/// The href of a tree's relative geometry, or none if it is inline.
std::optional<std::string> template_href(const ecitygml::SolitaryVegetationObject& tree) {
    const auto* property = implicit_geometry(tree).relative_geometry();
    if (property == nullptr || property->href() == nullptr) {
        return std::nullopt;
    }
    return property->href()->to_string();
}

double matrix(const ecitygml::ImplicitGeometry& geometry, size_t row, size_t column) {
    return ok(geometry.transformation_matrix().get(row, column));
}

std::unique_ptr<ecitygml::CityModel> read_railway() { return conformance::read(DATASET, FILE_NAME); }
}  // namespace

TEST_CASE("Railway city model", "[railway-scene]") {
    auto city_model = read_railway();
    REQUIRE(city_model->city_objects_len() == 52);
    REQUIRE(city_model->bounded_by() == nullptr);
    const auto types = feature_types(*city_model);
    REQUIRE(types.size() == 232);
    REQUIRE(types.front() == FeatureType::CityModel);
    std::map<FeatureType, int> counts;
    for (const auto type : types) {
        ++counts[type];
    }
    REQUIRE(counts == std::map<FeatureType, int>{
                          {FeatureType::CityModel, 1},
                          {FeatureType::SolitaryVegetationObject, 15},
                          {FeatureType::Tunnel, 4},
                          {FeatureType::TunnelInstallation, 8},
                          {FeatureType::Railway, 10},
                          {FeatureType::Bridge, 4},
                          {FeatureType::BridgeConstructiveElement, 3},
                          {FeatureType::BridgeInstallation, 2},
                          {FeatureType::Building, 3},
                          {FeatureType::BuildingInstallation, 56},
                          {FeatureType::CityFurniture, 11},
                          {FeatureType::CityObjectGroup, 1},
                          {FeatureType::GenericOccupiedSpace, 2},
                          {FeatureType::WaterBody, 1},
                          {FeatureType::WaterSurface, 1},
                          {FeatureType::WaterGroundSurface, 1},
                          {FeatureType::ReliefFeature, 1},
                          {FeatureType::TinRelief, 1},
                          {WALL, 33},
                          {ROOF, 12},
                          {GROUND, 7},
                          {CLOSURE, 8},
                          {FeatureType::DoorSurface, 9},
                          {FeatureType::WindowSurface, 34},
                          {FeatureType::OuterCeilingSurface, 3},
                          {FeatureType::OuterFloorSurface, 1},
                      });
    REQUIRE(count(city_model->iter_city_objects()) == 231);
}

TEST_CASE("Railway tunnels", "[railway-scene]") {
    auto city_model = read_railway();
    const std::vector<std::tuple<std::string, std::string, std::vector<FeatureType>>> expected{
        {"GMLID_BUI142242_863_347", "Tunnel KIT/KHH-3", {GROUND, WALL, ROOF, WALL, CLOSURE, CLOSURE}},
        {"GMLID_BUI336993_213_9312", "Tunnel KIT/KHH-2", {WALL, ROOF, WALL, CLOSURE, CLOSURE, GROUND}},
        {"GMLID_BUI289877_1911_4122", "Tunnel KIT/KHH-4", {WALL, GROUND, CLOSURE, WALL, ROOF, CLOSURE}},
        {"GMLID_BUI180021_673_14143", "Tunnel KIT/KHH-1", {GROUND, WALL, ROOF, CLOSURE, CLOSURE, WALL}},
    };
    const auto tunnels = all_of<ecitygml::Tunnel>(*city_model);
    REQUIRE(tunnels.size() == expected.size());
    for (size_t i = 0; i < tunnels.size(); ++i) {
        const auto& [id, name, boundaries] = expected[i];
        const auto* tunnel = tunnels[i];
        REQUIRE(tunnel->feature_id().as_str() == id);
        REQUIRE(first_name(*tunnel) == name);
        std::vector<FeatureType> types;
        auto properties = tunnel->boundaries();
        while (const auto* property = properties->next()) {
            REQUIRE(property->href() == nullptr);
            REQUIRE(property->object() != nullptr);
            types.push_back(property->object()->feature_type());
        }
        REQUIRE(types == boundaries);
        REQUIRE(tunnel->class_() == nullptr);
        REQUIRE(tunnel->functions()->next() == nullptr);
        REQUIRE(tunnel->usages()->next() == nullptr);
        REQUIRE(tunnel->tunnel_parts()->next() == nullptr);
        const auto* created = tunnel->creation_date();
        REQUIRE(created != nullptr);
        REQUIRE((created->year() == 2015 && created->month() == 3 && created->day() == 6));
        REQUIRE((created->hour() == 0 && created->minute() == 0));
        REQUIRE(created->offset_seconds() == 3600);
        REQUIRE(tunnel->relative_to_terrain() == ecitygml::RelativeToTerrain::EntirelyAboveTerrain);
    }
}

TEST_CASE("Railway trees", "[railway-scene]") {
    auto city_model = read_railway();
    using Expected = std::tuple<std::string, std::string, std::optional<std::string>, std::string, std::vector<std::string>>;
    const std::vector<Expected> expected{
        {"GMLID_SO0158953_776_12462", "Forest tree 3", "1070", "1800", {}},
        {"GMLID_SO092422_3593_9527", "Tree1", std::nullopt, "9999", {"LOD3"}},
        {"GMLID_SO0200811_525_4986", "Forest tree 1", "1060", "1640", {}},
        {"GMLID_SO0321978_1466_7441", "Forest tree 4", "1070", "1800", {}},
        {"GMLID_SO0260143_1214_1315", "Forest tree 11", "1060", "1640", {}},
        {"GMLID_SO0400934_2926_3381", "Forest tree 12", "1060", "1640", {}},
        {"GMLID_SO0124800_3522_13577", "Forest tree 13", "1060", "1640", {}},
        {"GMLID_SO0443764_1492_9667", "Forest tree 14", "1060", "1640", {}},
        {"GMLID_SO015374_872_14131", "Forest tree 2", "1060", "1640", {}},
        {"GMLID_SO081792_2341_11961", "Forest tree 10", "1060", "1640", {}},
        {"GMLID_SO0283142_1335_8999", "Forest tree 7", "1060", "1640", {}},
        {"GMLID_SO0107241_3793_12555", "Forest tree 9", "1070", "1800", {}},
        {"GMLID_SO0286258_965_2893", "Forest tree 5", "1070", "1800", {}},
        {"GMLID_SO0410128_214_10515", "Forest tree 6", "1060", "1640", {}},
        {"GMLID_SO086970_1053_8814", "Forest tree 8", "1060", "1640", {}},
    };
    const auto trees = all_of<ecitygml::SolitaryVegetationObject>(*city_model);
    REQUIRE(trees.size() == expected.size());
    for (size_t i = 0; i < trees.size(); ++i) {
        const auto& [id, name, class_value, species, functions] = expected[i];
        const auto* tree = trees[i];
        REQUIRE(tree->feature_id().as_str() == id);
        REQUIRE(first_name(*tree) == name);
        const auto* class_ = tree->class_();
        REQUIRE((class_ == nullptr ? std::nullopt : std::optional<std::string>(class_->value())) == class_value);
        REQUIRE(tree->species() != nullptr);
        REQUIRE(tree->species()->value() == species);
        REQUIRE(values(tree->functions()) == functions);
        REQUIRE(tree->usages()->next() == nullptr);
        REQUIRE(tree->lod1_implicit_representation() == nullptr);
        REQUIRE(tree->lod2_implicit_representation() == nullptr);
    }
}

TEST_CASE("Railway tree templates", "[railway-scene]") {
    auto city_model = read_railway();
    for (const auto* tree : all_of<ecitygml::SolitaryVegetationObject>(*city_model)) {
        const auto& geometry = implicit_geometry(*tree);
        REQUIRE(geometry.mime_type() == nullptr);
        const std::array<double, 4> diagonal{30.0, 30.0, 30.0, 1.0};
        for (size_t i = 0; i < diagonal.size(); ++i) {
            REQUIRE_THAT(matrix(geometry, i, i), close(diagonal[i]));
        }
        const auto name = first_name(*tree);
        const auto* property = geometry.relative_geometry();
        REQUIRE(property != nullptr);
        if (INLINE_TEMPLATES.count(name) == 1) {
            REQUIRE(property->href() == nullptr);
            REQUIRE(property->object() != nullptr);
            const auto* multi_surface = ecitygml::MultiSurface::try_from(*property->object());
            REQUIRE(multi_surface != nullptr);
            REQUIRE(count(multi_surface->surface_member()) == 1);
        } else {
            REQUIRE(property->object() == nullptr);
            REQUIRE(template_href(*tree) == (TEMPLATE_A_TREES.count(name) == 1 ? TEMPLATE_A : TEMPLATE_B));
        }
    }
}

TEST_CASE("Railway tree placement", "[railway-scene]") {
    auto city_model = read_railway();
    for (const auto* tree : all_of<ecitygml::SolitaryVegetationObject>(*city_model)) {
        const auto& geometry = implicit_geometry(*tree);
        const auto* point = geometry.reference_point().object();
        REQUIRE(point != nullptr);
        const auto& pos = point->pos();
        const auto name = first_name(*tree);
        const std::array<double, 3> reference = name == "Tree1"
                                                    ? std::array<double, 3>{-568.8000793496976, 457.60044759869743,
                                                                            105.00139681350242}
                                                    : std::array<double, 3>{-600.0, 400.0, -150.0};
        REQUIRE_THAT(pos.x(), close(reference[0]));
        REQUIRE_THAT(pos.y(), close(reference[1]));
        REQUIRE_THAT(pos.z(), close(reference[2]));
        std::optional<std::array<double, 3>> translation;
        if (name == "Tree1") {
            translation = std::array<double, 3>{0.0, 0.0, 0.0};
        } else if (name == "Forest tree 3") {
            translation = std::array<double, 3>{39.4421005419207, 220.3838834926932, 268.5013679006178};
        }
        if (translation.has_value()) {
            for (size_t row = 0; row < 3; ++row) {
                REQUIRE_THAT(matrix(geometry, row, 3), close((*translation)[row]));
            }
        }
    }
}

TEST_CASE("Railway furniture", "[railway-scene]") {
    auto city_model = read_railway();
    const std::vector<std::pair<std::string, std::string>> expected{
        {"GMLID_7431654_78949_792", "1090"},   {"GMLID_0528986_170479_94", "OTHERS"},
        {"GMLID_4323540_367099_910", "1090"},  {"GMLID_1381455_184173_656", "OTHERS"},
        {"GMLID_1429491_351612_1485", "1090"}, {"GMLID_5361967_192822_672", "1090"},
        {"GMLID_2108434_31807_876", "1090"},   {"GMLID_0373494_301709_129", "1540"},
        {"GMLID_6162422_289094_1279", "1090"}, {"GMLID_3313190_307178_612", "1090"},
        {"GMLID_855011_330784_753", "1540"},
    };
    const auto furniture = all_of<ecitygml::CityFurniture>(*city_model);
    REQUIRE(furniture.size() == expected.size());
    for (size_t i = 0; i < furniture.size(); ++i) {
        const auto* item = furniture[i];
        REQUIRE(item->feature_id().as_str() == expected[i].first);
        REQUIRE(values(item->functions()) == std::vector<std::string>{expected[i].second});
        REQUIRE(item->class_() == nullptr);
        REQUIRE(item->usages()->next() == nullptr);
        REQUIRE(item->lod3_implicit_representation() == nullptr);
        const auto* property = item->lod3_multi_surface();
        REQUIRE(property != nullptr);
        REQUIRE(property->href() == nullptr);
        REQUIRE(property->object() != nullptr);
        REQUIRE(count(property->object()->surface_member()) == 1);
    }
}

TEST_CASE("Railway relief", "[railway-scene]") {
    auto city_model = read_railway();
    const auto reliefs = all_of<ecitygml::ReliefFeature>(*city_model);
    REQUIRE(reliefs.size() == 1);
    const auto* relief = reliefs.front();
    REQUIRE(relief->feature_id().as_str() == "GMLID_TIN436865_187531_1154");
    REQUIRE(relief->names()->next() == nullptr);
    REQUIRE(relief->lod() == ecitygml::LevelOfDetail::Three);
    auto components = relief->relief_components();
    const auto* component = components->next();
    REQUIRE(component != nullptr);
    REQUIRE(components->next() == nullptr);
    REQUIRE(component->href() == nullptr);
    REQUIRE(component->object()->feature_type() == FeatureType::TinRelief);

    const auto tin_reliefs = all_of<ecitygml::TinRelief>(*city_model);
    REQUIRE(tin_reliefs.size() == 1);
    const auto* tin_relief = tin_reliefs.front();
    REQUIRE(tin_relief->feature_id().as_str() == "UUID_5aa70b07-6bbf-427b-8222-d72ed77dbfa9");
    REQUIRE(tin_relief->lod() == ecitygml::LevelOfDetail::Three);
    const auto* tin = tin_relief->tin();
    REQUIRE(tin != nullptr);
    REQUIRE(tin->href() == nullptr);
    const auto* surface = tin->object();
    REQUIRE(surface != nullptr);
    REQUIRE(count(surface->triangles()) == 1);
    REQUIRE_THAT(ok(surface->area_3d()), close(3.2750424144626247));
}

TEST_CASE("Railway buildings and bridges", "[railway-scene]") {
    auto city_model = read_railway();
    std::vector<std::tuple<std::string, std::string, int>> buildings;
    for (const auto* b : all_of<ecitygml::Building>(*city_model)) {
        buildings.emplace_back(std::string(b->feature_id().as_str()), first_name(*b), count(b->boundaries()));
    }
    REQUIRE(buildings == std::vector<std::tuple<std::string, std::string, int>>{
                             {"GMLID_BUI184698_512_898", "Station KIT/KHH-1", 13},
                             {"GMLID_BUI46739_1739_10911", "Chapel KIT/KHH-1", 19},
                             {"GMLID_BUI130363_1235_6047", "Boatshouse KIT/KHH-1", 8},
                         });
    std::vector<std::pair<std::string, std::string>> bridges;
    for (const auto* b : all_of<ecitygml::Bridge>(*city_model)) {
        bridges.emplace_back(std::string(b->feature_id().as_str()), first_name(*b));
    }
    REQUIRE(bridges == std::vector<std::pair<std::string, std::string>>{
                           {"GMLID_BUI205585_1385_1373", "Bridge KIT 4"},
                           {"GMLID_BUI51891_765_738", "Bridge KIT 3"},
                           {"GMLID_BUI100628_817_8083", "Bridge KIT 2"},
                           {"GMLID_BUI30683_572_6686", "Bridge KIT 1"},
                       });
}

TEST_CASE("Railway round trip", "[railway-scene]") {
    auto city_model = read_railway();
    auto writer = ecitygml::GmlWriter::create(ecitygml::CitygmlFormat::Gml);
    REQUIRE(writer->finish(*city_model).is_ok());
    auto written = ok(ecitygml::GmlReader::create(writer->data(), ecitygml::CitygmlFormat::Gml)->finish());
    REQUIRE(feature_types(*written) == feature_types(*city_model));
    const auto all_ids = [](const ecitygml::CityModel& model) {
        std::vector<std::string> result;
        for (const auto& part : {ids(all_of<ecitygml::Tunnel>(model)), ids(all_of<ecitygml::SolitaryVegetationObject>(model)),
                                 ids(all_of<ecitygml::CityFurniture>(model)), ids(all_of<ecitygml::Building>(model)),
                                 ids(all_of<ecitygml::Bridge>(model))}) {
            result.insert(result.end(), part.begin(), part.end());
        }
        return result;
    };
    const auto hrefs = [](const ecitygml::CityModel& model) {
        std::vector<std::optional<std::string>> result;
        for (const auto* tree : all_of<ecitygml::SolitaryVegetationObject>(model)) {
            result.push_back(template_href(*tree));
        }
        return result;
    };
    REQUIRE(all_ids(*written) == all_ids(*city_model));
    REQUIRE(hrefs(*written) == hrefs(*city_model));
}
