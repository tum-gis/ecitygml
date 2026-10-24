// The cases of crates/ecitygml/tests/api/types.md.
#include "api.hpp"

#include <ecitygml/AbstractCityObjectKindRef.hpp>
#include <ecitygml/AbstractCityObjectKindRefIterator.hpp>
#include <ecitygml/AbstractFeatureKindRef.hpp>
#include <ecitygml/AbstractFeatureKindRefIterator.hpp>
#include <ecitygml/AuxiliaryTrafficArea.hpp>
#include <ecitygml/AuxiliaryTrafficSpace.hpp>
#include <ecitygml/Building.hpp>
#include <ecitygml/BuildingClassValue.hpp>
#include <ecitygml/BuildingFunctionValue.hpp>
#include <ecitygml/BuildingFunctionValueIterator.hpp>
#include <ecitygml/BuildingUsageValue.hpp>
#include <ecitygml/BuildingUsageValueIterator.hpp>
#include <ecitygml/Code.hpp>
#include <ecitygml/CodeIterator.hpp>
#include <ecitygml/Date.hpp>
#include <ecitygml/DateTime.hpp>
#include <ecitygml/DirectPosition.hpp>
#include <ecitygml/DoorSurface.hpp>
#include <ecitygml/GroundSurface.hpp>
#include <ecitygml/Id.hpp>
#include <ecitygml/ImplicitGeometry.hpp>
#include <ecitygml/ImplicitGeometryProperty.hpp>
#include <ecitygml/LevelOfDetail.hpp>
#include <ecitygml/Road.hpp>
#include <ecitygml/RoofSurface.hpp>
#include <ecitygml/Section.hpp>
#include <ecitygml/SolitaryVegetationObject.hpp>
#include <ecitygml/TrafficArea.hpp>
#include <ecitygml/TrafficSpace.hpp>
#include <ecitygml/TransformationMatrix4x4.hpp>
#include <ecitygml/WallSurface.hpp>
#include <ecitygml/WindowSurface.hpp>

#include <cmath>
#include <functional>
#include <optional>
#include <string>
#include <utility>
#include <vector>

using ecitygml::ErrorKind;
using ecitygml::FeatureType;

namespace {
const std::string FZK_LOD1 = "fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml";
const std::string FZK_LOD2 = "fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml";
const std::string FZK_LOD3 = "fzk-haus/FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml";
const std::string TUM = "tum-main-entrance/TUM-Main-Entrance.gml";
const std::string ASAM_ROAD_SHAPE = "asam-opendrive/ASAM-UC_RoadShape.gml";
const std::string ASAM_JUNCTION = "asam-opendrive/ASAM-Ex_Bidirectional_Junction.gml";
const std::string RAILWAY = "railway-scene/Railway_Scene_LoD3__v3-thinned.gml";
const std::string SIG3D = "http://www.sig3d.org/codelists/citygml/2.0/building/2.0/_AbstractBuilding_";

/// The first feature that `T::try_from` accepts; the model must outlive it.
template <typename T>
const T& first_of(const ecitygml::CityModel& city_model) {
    auto features = city_model.iter_features();
    while (auto feature = features->next()) {
        if (const auto* typed = T::try_from(*feature)) {
            return *typed;
        }
    }
    FAIL("no feature of the type");
    throw;
}

using Accepts = std::function<bool(const ecitygml::AbstractFeatureKindRef&)>;

template <typename T>
std::pair<Accepts, FeatureType> accepts(FeatureType::Value feature_type) {
    return {[](const ecitygml::AbstractFeatureKindRef& feature) { return T::try_from(feature) != nullptr; },
            FeatureType(feature_type)};
}

/// `T::try_from` accepts exactly the features of its feature type.
void require_try_from_matches(const ecitygml::CityModel& city_model,
                              const std::vector<std::pair<Accepts, FeatureType>>& types) {
    auto features = city_model.iter_features();
    while (auto feature = features->next()) {
        for (const auto& [accepted, feature_type] : types) {
            CAPTURE(feature_type.to_string(), feature->feature_type().to_string());
            REQUIRE(accepted(*feature) == (feature->feature_type() == feature_type));
        }
    }
}

std::optional<std::string> code_space(const ecitygml::Code& code) {
    const auto value = code.code_space();
    return value ? std::optional<std::string>(*value) : std::nullopt;
}
}  // namespace

TEST_CASE("Direct position new", "[api][types]") {
    auto position = std::move(ecitygml::DirectPosition::create(1.0, 2.0, 3.0).ok().value());
    REQUIRE(position->x() == 1.0);
    REQUIRE(position->y() == 2.0);
    REQUIRE(position->z() == 3.0);
    require_error(*error_of(ecitygml::DirectPosition::create(std::nan(""), 0.0, 0.0)), ErrorKind::InvalidArgument,
                  "non-finite");
}

TEST_CASE("Level of detail index", "[api][types]") {
    const std::vector<ecitygml::LevelOfDetail> levels = {ecitygml::LevelOfDetail::Zero, ecitygml::LevelOfDetail::One,
                                                         ecitygml::LevelOfDetail::Two, ecitygml::LevelOfDetail::Three};
    for (size_t index = 0; index < levels.size(); ++index) {
        REQUIRE(levels[index].as_index() == index);
        REQUIRE(ecitygml::LevelOfDetail::try_from(static_cast<uint8_t>(index)).ok().value() == levels[index]);
    }
    require_error(*error_of(ecitygml::LevelOfDetail::try_from(4)), ErrorKind::InvalidArgument, "4");
}

TEST_CASE("Feature type name", "[api][types]") {
    REQUIRE(FeatureType(FeatureType::Building).to_string() == "Building");
    REQUIRE(FeatureType(FeatureType::TinRelief).to_string() == "TinRelief");
}

TEST_CASE("Date from parts", "[api][types]") {
    auto date = std::move(ecitygml::Date::from_parts(2020, 1, 2, 3600).ok().value());
    REQUIRE(date->year() == 2020);
    REQUIRE(date->month() == 1);
    REQUIRE(date->day() == 2);
    REQUIRE(date->offset_seconds() == 3600);
    auto start = date->start_of_day();
    REQUIRE(start->hour() == 0);
    REQUIRE(start->minute() == 0);
    REQUIRE(start->second() == 0);
    REQUIRE(start->to_rfc3339() == "2020-01-02T00:00:00+01:00");

    require_error(*error_of(ecitygml::Date::from_parts(2021, 2, 30, 0)), ErrorKind::InvalidArgument,
                  "do not form a valid date");
}

TEST_CASE("Date time from parts", "[api][types]") {
    auto date_time = std::move(ecitygml::DateTime::from_parts(2017, 1, 23, 13, 14, 15, 500000000, -7200).ok().value());
    REQUIRE(date_time->year() == 2017);
    REQUIRE(date_time->month() == 1);
    REQUIRE(date_time->day() == 23);
    REQUIRE(date_time->hour() == 13);
    REQUIRE(date_time->minute() == 14);
    REQUIRE(date_time->second() == 15);
    REQUIRE(date_time->nanosecond() == 500000000);
    REQUIRE(date_time->offset_seconds() == -7200);
    REQUIRE(date_time->timestamp() == 1485184455);
    REQUIRE(date_time->timestamp_subsec_nanos() == 500000000);
    REQUIRE(date_time->to_rfc3339() == "2017-01-23T13:14:15.500-02:00");

    require_error(*error_of(ecitygml::DateTime::from_parts(2020, 1, 1, 0, 0, 0, 0, 30)), ErrorKind::InvalidArgument,
                  "timezone offset of 30 s is invalid");
}

TEST_CASE("Date time read", "[api][types]") {
    auto city_model = read(fixture(FZK_LOD2));
    const auto* created = first_of<ecitygml::Building>(*city_model).creation_date();
    REQUIRE(created != nullptr);
    REQUIRE(created->to_rfc3339() == "2017-01-23T00:00:00+01:00");
}

TEST_CASE("Try from matches feature type", "[api][types]") {
    auto lod3 = read(fixture(FZK_LOD3));
    require_try_from_matches(*lod3, {
                                        accepts<ecitygml::Building>(FeatureType::Building),
                                        accepts<ecitygml::WallSurface>(FeatureType::WallSurface),
                                        accepts<ecitygml::RoofSurface>(FeatureType::RoofSurface),
                                        accepts<ecitygml::GroundSurface>(FeatureType::GroundSurface),
                                        accepts<ecitygml::DoorSurface>(FeatureType::DoorSurface),
                                        accepts<ecitygml::WindowSurface>(FeatureType::WindowSurface),
                                    });
    auto road_shape = read(fixture(ASAM_ROAD_SHAPE));
    require_try_from_matches(*road_shape, {
                                              accepts<ecitygml::Road>(FeatureType::Road),
                                              accepts<ecitygml::Section>(FeatureType::Section),
                                              accepts<ecitygml::TrafficSpace>(FeatureType::TrafficSpace),
                                              accepts<ecitygml::TrafficArea>(FeatureType::TrafficArea),
                                              accepts<ecitygml::AuxiliaryTrafficSpace>(FeatureType::AuxiliaryTrafficSpace),
                                              accepts<ecitygml::AuxiliaryTrafficArea>(FeatureType::AuxiliaryTrafficArea),
                                          });
}

TEST_CASE("Feature from city object", "[api][types]") {
    auto city_model = read(fixture(ASAM_JUNCTION));
    auto city_object = city_model->iter_city_objects()->next();
    REQUIRE(city_object != nullptr);
    REQUIRE(city_object->feature_type() == FeatureType::Road);
    auto feature = ecitygml::AbstractFeatureKindRef::from_city_object(*city_object);
    REQUIRE(feature->feature_type() == FeatureType::Road);
    const auto* road = ecitygml::Road::try_from(*feature);
    REQUIRE(road != nullptr);
    REQUIRE(road->feature_id().as_str() == "UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f");
    REQUIRE(ecitygml::Building::try_from(*feature) == nullptr);
}

TEST_CASE("Matrix index out of range", "[api][types]") {
    auto city_model = read(fixture(RAILWAY));
    const ecitygml::SolitaryVegetationObject* tree = nullptr;
    auto features = city_model->iter_features();
    while (auto feature = features->next()) {
        const auto* candidate = ecitygml::SolitaryVegetationObject::try_from(*feature);
        if (candidate != nullptr && candidate->feature_id().as_str() == "GMLID_SO092422_3593_9527") {
            tree = candidate;
        }
    }
    REQUIRE(tree != nullptr);
    const auto& matrix = tree->lod3_implicit_representation()->object()->transformation_matrix();
    REQUIRE(matrix.get(3, 3).ok().value() == 1.0);
    for (const auto& [row, column] : {std::pair<size_t, size_t>{4, 0}, std::pair<size_t, size_t>{0, 4}}) {
        require_error(*error_of(matrix.get(row, column)), ErrorKind::InvalidArgument, "out of range");
    }
}

TEST_CASE("Gml id", "[api][types]") {
    auto lod1 = read(fixture(FZK_LOD1));
    const std::string generated(lod1->feature_id().as_str());
    REQUIRE(generated.rfind("ecitygml-gen-feature-", 0) == 0);
    REQUIRE(lod1->id() != nullptr);
    REQUIRE(lod1->id()->as_str() == generated);

    auto lod2 = read(fixture(FZK_LOD2));
    const auto& wall = first_of<ecitygml::WallSurface>(*lod2);
    REQUIRE(wall.id() != nullptr);
    REQUIRE(wall.id()->as_str() == "GML_5856d7ad-5e34-498a-817b-9544bfbb1475");
    REQUIRE(wall.feature_id().as_str() == "GML_5856d7ad-5e34-498a-817b-9544bfbb1475");

    auto tum = read(fixture(TUM));
    const auto* id = first_of<ecitygml::Building>(*tum).id();
    REQUIRE(id != nullptr);
    REQUIRE(id->as_str() == "DEBY_LOD2_4959457");
}

TEST_CASE("Code space", "[api][types]") {
    auto lod2 = read(fixture(FZK_LOD2));
    const auto& building = first_of<ecitygml::Building>(*lod2);
    const auto& code = building.class_()->code();
    REQUIRE(code.value() == "1000");
    REQUIRE(code_space(code) == SIG3D + "class.xml");
    auto functions = building.functions();
    REQUIRE(code_space(functions->next()->code()) == SIG3D + "function.xml");
    REQUIRE(functions->next() == nullptr);
    auto usages = building.usages();
    REQUIRE(code_space(usages->next()->code()) == SIG3D + "usage.xml");
    REQUIRE(usages->next() == nullptr);

    auto tum = read(fixture(TUM));
    auto tum_functions = first_of<ecitygml::Building>(*tum).functions();
    const auto* function = tum_functions->next();
    REQUIRE(function->value() == "31001_3020");
    REQUIRE(code_space(function->code()) == std::nullopt);
    REQUIRE(tum_functions->next() == nullptr);

    auto lod1 = read(fixture(FZK_LOD1));
    auto names = lod1->names();
    const auto* name = names->next();
    REQUIRE(name->value() == "AC14-FZK-Haus");
    REQUIRE(code_space(*name) == std::nullopt);
    REQUIRE(names->next() == nullptr);
}
