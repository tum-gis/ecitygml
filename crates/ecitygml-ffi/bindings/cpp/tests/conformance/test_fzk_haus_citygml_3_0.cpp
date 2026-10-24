// The cases of crates/ecitygml/tests/conformance/fzk-haus-citygml-3.0.md.
#include "conformance/conformance.hpp"

#include <ecitygml/AbstractBuildingSubdivisionKind.hpp>
#include <ecitygml/AbstractBuildingSubdivisionProperty.hpp>
#include <ecitygml/AbstractBuildingSubdivisionPropertyIterator.hpp>
#include <ecitygml/AbstractCityObjectKindRef.hpp>
#include <ecitygml/AbstractCityObjectKindRefIterator.hpp>
#include <ecitygml/AbstractSurfaceProperty.hpp>
#include <ecitygml/AbstractSurfacePropertyIterator.hpp>
#include <ecitygml/BoundingShape.hpp>
#include <ecitygml/BuildingFunctionValue.hpp>
#include <ecitygml/BuildingFunctionValueIterator.hpp>
#include <ecitygml/BuildingSubdivisionClassValue.hpp>
#include <ecitygml/BuildingSubdivisionFunctionValueIterator.hpp>
#include <ecitygml/BuildingSubdivisionUsageValueIterator.hpp>
#include <ecitygml/BuildingUsageValueIterator.hpp>
#include <ecitygml/CitygmlFormat.hpp>
#include <ecitygml/DirectPosition.hpp>
#include <ecitygml/Envelope.hpp>
#include <ecitygml/FeatureType.hpp>
#include <ecitygml/GenericAttributeKind.hpp>
#include <ecitygml/GenericAttributeKindIterator.hpp>
#include <ecitygml/GmlReader.hpp>
#include <ecitygml/GmlWriter.hpp>
#include <ecitygml/GroundSurface.hpp>
#include <ecitygml/Height.hpp>
#include <ecitygml/HeightIterator.hpp>
#include <ecitygml/HeightStatusValue.hpp>
#include <ecitygml/Id.hpp>
#include <ecitygml/Length.hpp>
#include <ecitygml/MultiSurface.hpp>
#include <ecitygml/MultiSurfaceProperty.hpp>
#include <ecitygml/Occupancy.hpp>
#include <ecitygml/OccupancyIterator.hpp>
#include <ecitygml/RoofSurface.hpp>
#include <ecitygml/RoofTypeValue.hpp>
#include <ecitygml/Shell.hpp>
#include <ecitygml/Solid.hpp>
#include <ecitygml/SolidProperty.hpp>
#include <ecitygml/Storey.hpp>
#include <ecitygml/StringAttribute.hpp>
#include <ecitygml/WallSurface.hpp>

#include <array>
#include <map>
#include <optional>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using conformance::building;
using conformance::close;
using conformance::features;
using conformance::first_name;
using ecitygml::FeatureType;

namespace {
const std::string DATASET = "fzk-haus-citygml-3.0";
const std::string CONSTRUCTION = "01-FZK-Haus-LoD2-Tex-Storey-Construction-CG30-V01.gml";
const std::string INTERIOR = "04-FZK-Haus-LoD2-Tex-Storey-CG30-V01-InteriorSurface.gml";
const std::string WINDOW = "04-FZK-Haus-LoD2-Tex-Storey-Construction-CG30-V01-Window-Interior.gml";
const std::string POINT_CLOUD = "06-FZK-Haus-LoD2-Tex-Storey-CG30-V01-PointCloud-thinned.gml";

const std::string CONSTRUCTION_ID = "_FZK-Haus-Storey-Construction_BD.DX9Xm6VLbbyLGAxG2v86";
const std::string TEST_BUILDING_ID = "KIT-Test-Building-01";
const std::string WINDOW_ID = "_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz";

using Point = std::array<double, 3>;

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

void require_point_close(const ecitygml::DirectPosition& position, const Point& expected) {
    REQUIRE_THAT(position.x(), close(expected[0]));
    REQUIRE_THAT(position.y(), close(expected[1]));
    REQUIRE_THAT(position.z(), close(expected[2]));
}

std::vector<FeatureType> feature_types(const ecitygml::CityModel& city_model) {
    std::vector<FeatureType> result;
    for (const auto& feature : features(city_model)) {
        result.push_back(feature->feature_type());
    }
    return result;
}

/// `n` times the feature type, appended.
void append(std::vector<FeatureType>& types, FeatureType type, size_t n) { types.insert(types.end(), n, type); }

/// The number of features per feature type, over `iter_features`.
std::map<FeatureType, int> feature_type_counts(const ecitygml::CityModel& city_model) {
    std::map<FeatureType, int> counts;
    for (const auto type : feature_types(city_model)) {
        ++counts[type];
    }
    return counts;
}

/// The storeys, in document order; the model must outlive them.
std::vector<const ecitygml::Storey*> storeys(const ecitygml::CityModel& city_model) {
    std::vector<const ecitygml::Storey*> result;
    auto iterator = city_model.iter_features();
    while (auto feature = iterator->next()) {
        if (const auto* storey = ecitygml::Storey::try_from(*feature)) {
            result.push_back(storey);
        }
    }
    return result;
}

void require_city_model(const ecitygml::CityModel& city_model, const Point& lower, const Point& upper) {
    REQUIRE(city_model.city_objects_len() == 1);
    const auto* envelope = city_model.bounded_by()->envelope();
    require_point_close(envelope->lower_corner(), lower);
    require_point_close(envelope->upper_corner(), upper);
}

/// The one height and occupancy of the storey examples' buildings.
void require_height_and_occupancy(const ecitygml::Building& building) {
    auto heights = building.heights();
    const auto* height = heights->next();
    REQUIRE(height != nullptr);
    REQUIRE(heights->next() == nullptr);
    REQUIRE(height->high_reference().value() == "highestRoofEdge");
    REQUIRE(height->low_reference().value() == "lowestGroundPoint");
    REQUIRE(height->status() == ecitygml::HeightStatusValue::Measured);
    REQUIRE_THAT(height->length().value(), close(6.52));
    REQUIRE(height->length().uom() == "urn:adv:uom:m");
    auto occupancies = building.occupancies();
    const auto* occupancy = occupancies->next();
    REQUIRE(occupancy != nullptr);
    REQUIRE(occupancies->next() == nullptr);
    REQUIRE(occupancy->number_of_occupants() == 2);
}

/// The storeys' first names and classes.
void require_storeys(const ecitygml::CityModel& city_model, const std::vector<std::optional<std::string>>& classes) {
    std::vector<std::string> names;
    std::vector<std::optional<std::string>> actual_classes;
    for (const auto* storey : storeys(city_model)) {
        names.push_back(first_name(*storey));
        const auto* class_ = storey->class_();
        actual_classes.push_back(class_ == nullptr ? std::nullopt : std::optional<std::string>(class_->value()));
    }
    REQUIRE(names == std::vector<std::string>{"Ground Floor", "Second Floor"});
    REQUIRE(actual_classes == classes);
}

struct Surface {
    FeatureType type;
    std::string name;
    const ecitygml::MultiSurfaceProperty* lod2_multi_surface;
};

/// A storey's boundaries; all inline wall, roof or ground surfaces. The model must outlive them.
std::vector<Surface> boundary_surfaces(const ecitygml::Storey& storey) {
    std::vector<Surface> result;
    auto properties = storey.boundaries();
    while (const auto* property = properties->next()) {
        REQUIRE(property->href() == nullptr);
        REQUIRE(property->object() != nullptr);
        const auto feature = ecitygml::AbstractFeatureKindRef::from_space_boundary(*property->object());
        if (const auto* wall = ecitygml::WallSurface::try_from(*feature)) {
            result.push_back({feature->feature_type(), first_name(*wall), wall->lod2_multi_surface()});
        } else if (const auto* roof = ecitygml::RoofSurface::try_from(*feature)) {
            result.push_back({feature->feature_type(), first_name(*roof), roof->lod2_multi_surface()});
        } else if (const auto* ground = ecitygml::GroundSurface::try_from(*feature)) {
            result.push_back({feature->feature_type(), first_name(*ground), ground->lod2_multi_surface()});
        } else {
            FAIL("unexpected boundary");
        }
    }
    return result;
}

/// Writes the city model and reads it back: the same feature types in the same order and the building's id.
void require_round_trip(const ecitygml::CityModel& city_model, const std::string& building_id) {
    auto writer = ecitygml::GmlWriter::create(ecitygml::CitygmlFormat::Gml);
    REQUIRE(writer->finish(city_model).is_ok());
    auto written = ok(ecitygml::GmlReader::create(writer->data(), ecitygml::CitygmlFormat::Gml)->finish());
    REQUIRE(feature_types(*written) == feature_types(city_model));
    REQUIRE(building(*written)->feature_id().as_str() == building_id);
}
}  // namespace

TEST_CASE("Construction city model", "[fzk-haus-citygml-3.0][construction]") {
    auto city_model = conformance::read(DATASET, CONSTRUCTION);
    require_city_model(*city_model, {458899.5, 5438784.5, 113.5}, {458912.5, 5438795.5, 120.017691});
    std::vector<FeatureType> expected{FeatureType::CityModel, FeatureType::Building, FeatureType::Storey};
    append(expected, FeatureType::BuildingConstructiveElement, 5);
    append(expected, FeatureType::Storey, 1);
    append(expected, FeatureType::BuildingConstructiveElement, 6);
    append(expected, FeatureType::Appearance, 1);
    append(expected, FeatureType::ParameterizedTexture, 5);
    append(expected, FeatureType::X3DMaterial, 5);
    REQUIRE(feature_types(*city_model) == expected);
    REQUIRE(count(city_model->iter_city_objects()) == 14);
}

TEST_CASE("Construction building", "[fzk-haus-citygml-3.0][construction]") {
    auto city_model = conformance::read(DATASET, CONSTRUCTION);
    const auto* b = building(*city_model);
    REQUIRE(b->feature_id().as_str() == CONSTRUCTION_ID);
    auto names = b->names();
    REQUIRE(names->next()->value() == "KIT FZK-Haus");
    REQUIRE(names->next() == nullptr);
    REQUIRE(b->class_() == nullptr);
    auto functions = b->functions();
    REQUIRE(functions->next()->value() == "31001_1000");
    REQUIRE(functions->next() == nullptr);
    REQUIRE(b->usages()->next() == nullptr);
    REQUIRE(b->roof_type()->value() == "3100");
    REQUIRE_FALSE(b->storeys_above_ground().has_value());
    REQUIRE_FALSE(b->storeys_below_ground().has_value());
    require_height_and_occupancy(*b);
    REQUIRE(b->boundaries()->next() == nullptr);
    REQUIRE(b->generic_attributes()->next() == nullptr);
    REQUIRE(b->lod2_solid() == nullptr);
    REQUIRE(b->lod2_multi_surface() == nullptr);
}

TEST_CASE("Construction storeys", "[fzk-haus-citygml-3.0][construction]") {
    auto city_model = conformance::read(DATASET, CONSTRUCTION);
    auto subdivisions = building(*city_model)->building_subdivisions();
    int n = 0;
    while (const auto* subdivision = subdivisions->next()) {
        REQUIRE(subdivision->href() == nullptr);
        REQUIRE(subdivision->object() != nullptr);
        REQUIRE(subdivision->object()->feature_type() == FeatureType::Storey);
        ++n;
    }
    REQUIRE(n == 2);
    require_storeys(*city_model, {"Entrance Floor", "non Entrance Floor"});
    for (const auto* storey : storeys(*city_model)) {
        REQUIRE(storey->functions()->next() == nullptr);
        REQUIRE(storey->usages()->next() == nullptr);
        REQUIRE(storey->boundaries()->next() == nullptr);
        REQUIRE(storey->lod2_solid() == nullptr);
    }
}

TEST_CASE("Construction round trip", "[fzk-haus-citygml-3.0][construction]") {
    auto city_model = conformance::read(DATASET, CONSTRUCTION);
    require_round_trip(*city_model, CONSTRUCTION_ID);
}

TEST_CASE("Interior city model", "[fzk-haus-citygml-3.0][interior]") {
    auto city_model = conformance::read(DATASET, INTERIOR);
    require_city_model(*city_model, {458900.0, 5438785.0, 113.5}, {458912.0, 5438795.0, 120.017691});
    REQUIRE(feature_types(*city_model).size() == 77);
    REQUIRE(feature_type_counts(*city_model) == std::map<FeatureType, int>{
                                                    {FeatureType::CityModel, 1},
                                                    {FeatureType::Building, 1},
                                                    {FeatureType::Storey, 2},
                                                    {FeatureType::GroundSurface, 1},
                                                    {FeatureType::WallSurface, 8},
                                                    {FeatureType::RoofSurface, 2},
                                                    {FeatureType::BuildingRoom, 7},
                                                    {FeatureType::InteriorWallSurface, 27},
                                                    {FeatureType::CeilingSurface, 8},
                                                    {FeatureType::FloorSurface, 7},
                                                    {FeatureType::ClosureSurface, 6},
                                                    {FeatureType::Appearance, 1},
                                                    {FeatureType::ParameterizedTexture, 5},
                                                    {FeatureType::X3DMaterial, 1},
                                                });
    REQUIRE(count(city_model->iter_city_objects()) == 69);
}

TEST_CASE("Interior building", "[fzk-haus-citygml-3.0][interior]") {
    auto city_model = conformance::read(DATASET, INTERIOR);
    const auto* b = building(*city_model);
    REQUIRE(b->feature_id().as_str() == TEST_BUILDING_ID);
    auto names = b->names();
    REQUIRE(names->next()->value() == "KIT Test Building FZK-Haus for CityGML 3.0");
    REQUIRE(names->next() == nullptr);
    REQUIRE(b->class_() == nullptr);
    REQUIRE(b->roof_type() == nullptr);
    REQUIRE(b->functions()->next() == nullptr);
    REQUIRE(b->usages()->next() == nullptr);
    require_height_and_occupancy(*b);
    auto attributes = b->generic_attributes();
    const auto* attribute = attributes->next();
    REQUIRE(attribute != nullptr);
    REQUIRE(attributes->next() == nullptr);
    REQUIRE(attribute->name() == "@cityeditor:layer");
    REQUIRE(attribute->as_string() != nullptr);
    REQUIRE(attribute->as_string()->value() == "LoD2-Ausgeblendet");
    REQUIRE(b->boundaries()->next() == nullptr);
}

TEST_CASE("Interior solid unresolved", "[fzk-haus-citygml-3.0][interior]") {
    auto city_model = conformance::read(DATASET, INTERIOR);
    const auto* property = building(*city_model)->lod2_solid();
    REQUIRE(property != nullptr);
    REQUIRE(property->href() == nullptr);
    const auto* solid = property->object();
    REQUIRE(solid != nullptr);
    auto members = solid->exterior()->members();
    int n = 0;
    while (const auto* member = members->next()) {
        REQUIRE(member->object() == nullptr);
        ++n;
    }
    REQUIRE(n == 11);
    REQUIRE(solid->volume_3d().is_err());
}

TEST_CASE("Interior storey boundaries", "[fzk-haus-citygml-3.0][interior]") {
    auto city_model = conformance::read(DATASET, INTERIOR);
    using Expected = std::vector<std::tuple<FeatureType, std::string, double>>;
    const std::vector<Expected> expected{
        {
            {FeatureType::GroundSurface, "Ground", 120.0},
            {FeatureType::WallSurface, "Ground Floor / Wall East", 29.0},
            {FeatureType::WallSurface, "Ground Floor / Wall South", 34.80000000447035},
            {FeatureType::WallSurface, "Ground Floor / Wall West", 29.0},
            {FeatureType::WallSurface, "Ground Floor / Wall North", 34.80000000447035},
        },
        {
            {FeatureType::RoofSurface, "Second Floor / Roof South", 69.28203022609509},
            {FeatureType::RoofSurface, "Second Floor / Roof North", 69.28203022609509},
            {FeatureType::WallSurface, "Second Floor / Wall South", 8.771279998123646},
            {FeatureType::WallSurface, "Second Floor / Wall West", 21.743155002593994},
            {FeatureType::WallSurface, "Second Floor / Wall East", 21.743155002593994},
            {FeatureType::WallSurface, "Second Floor / Wall North", 8.771279998123646},
        },
    };
    const auto found = storeys(*city_model);
    REQUIRE(found.size() == expected.size());
    for (size_t i = 0; i < found.size(); ++i) {
        const auto surfaces = boundary_surfaces(*found[i]);
        REQUIRE(surfaces.size() == expected[i].size());
        for (size_t j = 0; j < surfaces.size(); ++j) {
            const auto& [type, name, area] = expected[i][j];
            REQUIRE(surfaces[j].type == type);
            REQUIRE(surfaces[j].name == name);
            REQUIRE(surfaces[j].lod2_multi_surface != nullptr);
            REQUIRE_THAT(ok(surfaces[j].lod2_multi_surface->object()->area_3d()), close(area));
        }
    }
    require_storeys(*city_model, {std::nullopt, std::nullopt});
}

TEST_CASE("Interior round trip", "[fzk-haus-citygml-3.0][interior]") {
    auto city_model = conformance::read(DATASET, INTERIOR);
    require_round_trip(*city_model, TEST_BUILDING_ID);
}

TEST_CASE("Window city model", "[fzk-haus-citygml-3.0][window]") {
    auto city_model = conformance::read(DATASET, WINDOW);
    require_city_model(*city_model, {458899.5, 5438784.5, 113.5}, {458912.5, 5438795.5, 120.017691});
    REQUIRE(feature_types(*city_model).size() == 54);
    REQUIRE(feature_type_counts(*city_model) == std::map<FeatureType, int>{
                                                    {FeatureType::CityModel, 1},
                                                    {FeatureType::Building, 1},
                                                    {FeatureType::Storey, 2},
                                                    {FeatureType::BuildingConstructiveElement, 18},
                                                    {FeatureType::Door, 5},
                                                    {FeatureType::Window, 11},
                                                    {FeatureType::Appearance, 2},
                                                    {FeatureType::ParameterizedTexture, 5},
                                                    {FeatureType::X3DMaterial, 9},
                                                });
    REQUIRE(count(city_model->iter_city_objects()) == 37);
}

TEST_CASE("Window building", "[fzk-haus-citygml-3.0][window]") {
    auto city_model = conformance::read(DATASET, WINDOW);
    const auto* b = building(*city_model);
    REQUIRE(b->feature_id().as_str() == WINDOW_ID);
    auto names = b->names();
    REQUIRE(names->next()->value() == "KIT FZK-Haus");
    REQUIRE(names->next() == nullptr);
    auto functions = b->functions();
    REQUIRE(functions->next()->value() == "31001_1000");
    REQUIRE(functions->next() == nullptr);
    REQUIRE(b->roof_type()->value() == "3100");
    REQUIRE(b->boundaries()->next() == nullptr);
    require_storeys(*city_model, {"Entrance Floor", "non Entrance Floor"});
}

TEST_CASE("Window round trip", "[fzk-haus-citygml-3.0][window]") {
    auto city_model = conformance::read(DATASET, WINDOW);
    require_round_trip(*city_model, WINDOW_ID);
}

TEST_CASE("Point cloud city model", "[fzk-haus-citygml-3.0][point-cloud]") {
    auto city_model = conformance::read(DATASET, POINT_CLOUD);
    require_city_model(*city_model, {458900.0, 5438785.0, 113.5}, {458912.0, 5438795.0, 120.017691});
    std::vector<FeatureType> expected{FeatureType::CityModel, FeatureType::Building, FeatureType::Storey,
                                      FeatureType::GroundSurface};
    append(expected, FeatureType::WallSurface, 4);
    append(expected, FeatureType::Storey, 1);
    append(expected, FeatureType::RoofSurface, 2);
    append(expected, FeatureType::WallSurface, 4);
    REQUIRE(feature_types(*city_model) == expected);
}

TEST_CASE("Point cloud storey boundaries", "[fzk-haus-citygml-3.0][point-cloud]") {
    auto city_model = conformance::read(DATASET, POINT_CLOUD);
    const auto* b = building(*city_model);
    REQUIRE(b->feature_id().as_str() == TEST_BUILDING_ID);
    REQUIRE(b->boundaries()->next() == nullptr);
    using Expected = std::vector<std::pair<FeatureType, std::string>>;
    const std::vector<Expected> expected{
        {
            {FeatureType::GroundSurface, " Ground Floor / GroundSurface"},
            {FeatureType::WallSurface, "Ground Floor / Wall East"},
            {FeatureType::WallSurface, "Ground Floor / Wall South"},
            {FeatureType::WallSurface, "Ground Floor / Wall West"},
            {FeatureType::WallSurface, "Ground Floor / Wall North"},
        },
        {
            {FeatureType::RoofSurface, "Second Floor / Roof North"},
            {FeatureType::RoofSurface, "Second Floor / Roof South"},
            {FeatureType::WallSurface, "Second Floor / Wall South"},
            {FeatureType::WallSurface, "Second Floor / Wall West"},
            {FeatureType::WallSurface, "Second Floor / Wall East"},
            {FeatureType::WallSurface, "Second Floor / Wall North"},
        },
    };
    const auto found = storeys(*city_model);
    REQUIRE(found.size() == expected.size());
    for (size_t i = 0; i < found.size(); ++i) {
        Expected actual;
        for (const auto& surface : boundary_surfaces(*found[i])) {
            actual.emplace_back(surface.type, surface.name);
            REQUIRE(surface.lod2_multi_surface == nullptr);
        }
        REQUIRE(actual == expected[i]);
    }
}

TEST_CASE("Point cloud round trip", "[fzk-haus-citygml-3.0][point-cloud]") {
    auto city_model = conformance::read(DATASET, POINT_CLOUD);
    require_round_trip(*city_model, TEST_BUILDING_ID);
}
