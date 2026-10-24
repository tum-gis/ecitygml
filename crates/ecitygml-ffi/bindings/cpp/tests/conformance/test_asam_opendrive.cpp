// The cases of crates/ecitygml/tests/conformance/asam-opendrive.md.
#include "conformance/conformance.hpp"

#include <ecitygml/AbstractCityObjectKindRef.hpp>
#include <ecitygml/AbstractCityObjectKindRefIterator.hpp>
#include <ecitygml/AbstractCurveKind.hpp>
#include <ecitygml/AbstractCurveProperty.hpp>
#include <ecitygml/AbstractCurvePropertyIterator.hpp>
#include <ecitygml/AbstractSpaceBoundaryKind.hpp>
#include <ecitygml/AbstractSpaceBoundaryProperty.hpp>
#include <ecitygml/AbstractSpaceBoundaryPropertyIterator.hpp>
#include <ecitygml/AbstractSurfacePropertyIterator.hpp>
#include <ecitygml/AuxiliaryTrafficArea.hpp>
#include <ecitygml/AuxiliaryTrafficAreaFunctionValueIterator.hpp>
#include <ecitygml/AuxiliaryTrafficAreaUsageValueIterator.hpp>
#include <ecitygml/AuxiliaryTrafficSpace.hpp>
#include <ecitygml/AuxiliaryTrafficSpaceFunctionValueIterator.hpp>
#include <ecitygml/AuxiliaryTrafficSpaceProperty.hpp>
#include <ecitygml/AuxiliaryTrafficSpacePropertyIterator.hpp>
#include <ecitygml/AuxiliaryTrafficSpaceUsageValueIterator.hpp>
#include <ecitygml/BoundingShape.hpp>
#include <ecitygml/DirectPosition.hpp>
#include <ecitygml/DirectPositionIterator.hpp>
#include <ecitygml/DoubleAttribute.hpp>
#include <ecitygml/Envelope.hpp>
#include <ecitygml/FeatureType.hpp>
#include <ecitygml/GenericAttributeKind.hpp>
#include <ecitygml/GenericAttributeKindIterator.hpp>
#include <ecitygml/GranularityValue.hpp>
#include <ecitygml/HRef.hpp>
#include <ecitygml/HolePropertyIterator.hpp>
#include <ecitygml/Id.hpp>
#include <ecitygml/IntAttribute.hpp>
#include <ecitygml/Intersection.hpp>
#include <ecitygml/IntersectionProperty.hpp>
#include <ecitygml/IntersectionPropertyIterator.hpp>
#include <ecitygml/LineString.hpp>
#include <ecitygml/Marking.hpp>
#include <ecitygml/MarkingProperty.hpp>
#include <ecitygml/MarkingPropertyIterator.hpp>
#include <ecitygml/MultiCurve.hpp>
#include <ecitygml/MultiCurveProperty.hpp>
#include <ecitygml/MultiSurface.hpp>
#include <ecitygml/MultiSurfaceProperty.hpp>
#include <ecitygml/OccupancyIterator.hpp>
#include <ecitygml/Reference.hpp>
#include <ecitygml/Road.hpp>
#include <ecitygml/RoadFunctionValueIterator.hpp>
#include <ecitygml/RoadUsageValueIterator.hpp>
#include <ecitygml/Section.hpp>
#include <ecitygml/SectionProperty.hpp>
#include <ecitygml/SectionPropertyIterator.hpp>
#include <ecitygml/Solid.hpp>
#include <ecitygml/SolidProperty.hpp>
#include <ecitygml/SpaceType.hpp>
#include <ecitygml/StringAttribute.hpp>
#include <ecitygml/TrafficArea.hpp>
#include <ecitygml/TrafficAreaFunctionValue.hpp>
#include <ecitygml/TrafficAreaFunctionValueIterator.hpp>
#include <ecitygml/TrafficAreaUsageValue.hpp>
#include <ecitygml/TrafficAreaUsageValueIterator.hpp>
#include <ecitygml/TrafficDirectionValue.hpp>
#include <ecitygml/TrafficSpace.hpp>
#include <ecitygml/TrafficSpaceFunctionValue.hpp>
#include <ecitygml/TrafficSpaceFunctionValueIterator.hpp>
#include <ecitygml/TrafficSpaceProperty.hpp>
#include <ecitygml/TrafficSpacePropertyIterator.hpp>
#include <ecitygml/TrafficSpaceReference.hpp>
#include <ecitygml/TrafficSpaceReferenceIterator.hpp>
#include <ecitygml/TrafficSpaceUsageValue.hpp>
#include <ecitygml/TrafficSpaceUsageValueIterator.hpp>

#include <array>
#include <memory>
#include <string>
#include <utility>
#include <variant>
#include <vector>

using conformance::close;
using conformance::features;
using conformance::first_name;
using ecitygml::FeatureType;

namespace {
const std::string ROAD_SHAPE = "ASAM-UC_RoadShape.gml";
const std::string JUNCTION = "ASAM-Ex_Bidirectional_Junction.gml";

const std::vector<std::string> SPACES = {
    "UUID_ae81947d-a661-3678-a5ee-eed58b68694f", "UUID_6e4de408-1e54-3869-b7ce-1be3f2261421",
    "UUID_9582b02f-5cc7-38f8-b79c-a3a18b31856c", "UUID_c772e261-27f1-30b6-8a94-1ccf23e71a74",
    "UUID_656f23c9-92b6-3c98-a1bf-40b5f2625b13", "UUID_86f8df09-c972-332b-a279-636373ce4e0c",
    "UUID_144a6807-5844-32b2-bb34-8b2671b1afaa",
};

using Point = std::array<double, 3>;

/// The value of a successful result.
template <typename Result>
auto ok(Result result) {
    REQUIRE(result.is_ok());
    return std::move(result).ok().value();
}

/// The number of items of a Diplomat iterator.
template <typename Iterator>
int count(const std::unique_ptr<Iterator>& iterator) {
    int n = 0;
    while (iterator->next() != nullptr) {
        ++n;
    }
    return n;
}

/// The objects of inline properties; fails on a reference-only property.
template <typename Iterator>
auto objects(const std::unique_ptr<Iterator>& properties) {
    std::vector<decltype(properties->next()->object())> result;
    while (const auto* property = properties->next()) {
        REQUIRE(property->href() == nullptr);
        REQUIRE(property->object() != nullptr);
        result.push_back(property->object());
    }
    return result;
}

template <typename T>
std::vector<std::string> ids(const std::vector<const T*>& features) {
    std::vector<std::string> result;
    for (const auto* feature : features) {
        result.emplace_back(feature->feature_id().as_str());
    }
    return result;
}

/// The code values of a code list iterator.
template <typename Iterator>
std::vector<std::string> values(const std::unique_ptr<Iterator>& iterator) {
    std::vector<std::string> result;
    while (const auto* value = iterator->next()) {
        result.emplace_back(value->value());
    }
    return result;
}

const ecitygml::Road* road(const ecitygml::CityModel& city_model) {
    for (const auto& feature : features(city_model)) {
        if (const auto* road = ecitygml::Road::try_from(*feature)) {
            return road;
        }
    }
    FAIL("no road");
    return nullptr;
}

std::vector<FeatureType> feature_types(const ecitygml::CityModel& city_model) {
    std::vector<FeatureType> result;
    for (const auto& feature : features(city_model)) {
        result.push_back(feature->feature_type());
    }
    return result;
}

void require_point_close(const ecitygml::DirectPosition& position, const Point& expected) {
    REQUIRE_THAT(position.x(), close(expected[0]));
    REQUIRE_THAT(position.y(), close(expected[1]));
    REQUIRE_THAT(position.z(), close(expected[2]));
}

void require_envelope(const ecitygml::CityModel& city_model, const Point& lower, const Point& upper) {
    const auto* envelope = city_model.bounded_by()->envelope();
    REQUIRE(envelope != nullptr);
    require_point_close(envelope->lower_corner(), lower);
    require_point_close(envelope->upper_corner(), upper);
}

/// The single boundary of a space, inline, as a feature; the model must outlive it.
std::unique_ptr<ecitygml::AbstractFeatureKindRef> only_boundary(
    const std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator>& boundaries) {
    const auto all = objects(boundaries);
    REQUIRE(all.size() == 1);
    return ecitygml::AbstractFeatureKindRef::from_space_boundary(*all.front());
}

/// The single curve member of an inline multi curve, as a line string: (point count, length).
std::pair<int, double> line_string(const ecitygml::MultiCurve& multi_curve) {
    const auto members = objects(multi_curve.curve_member());
    REQUIRE(members.size() == 1);
    const auto* curve = ecitygml::LineString::try_from(*members.front());
    REQUIRE(curve != nullptr);
    return {count(curve->points()), curve->length_3d()};
}

std::vector<std::string> local_ids(const std::unique_ptr<ecitygml::TrafficSpaceReferenceIterator>& references) {
    std::vector<std::string> result;
    while (const auto* reference = references->next()) {
        // The reference owns the href: keep it alive while reading.
        const auto owned = ecitygml::Reference::from_traffic_space_reference(*reference);
        const auto* href = owned->href();
        REQUIRE(href != nullptr);
        REQUIRE(href->local_id().has_value());
        result.emplace_back(*href->local_id());
    }
    return result;
}

const ecitygml::Section* road_shape_section(const ecitygml::CityModel& city_model) {
    const auto sections = objects(road(city_model)->sections());
    REQUIRE(sections.size() == 1);
    return sections.front();
}

std::vector<const ecitygml::TrafficSpace*> road_shape_spaces(const ecitygml::CityModel& city_model) {
    return objects(road_shape_section(city_model)->traffic_spaces());
}

std::vector<const ecitygml::TrafficSpace*> traffic_spaces(
    const std::vector<std::unique_ptr<ecitygml::AbstractFeatureKindRef>>& all) {
    std::vector<const ecitygml::TrafficSpace*> result;
    for (const auto& feature : all) {
        if (const auto* space = ecitygml::TrafficSpace::try_from(*feature)) {
            result.push_back(space);
        }
    }
    return result;
}
}  // namespace

TEST_CASE("Road shape city model", "[asam-opendrive][road-shape]") {
    auto city_model = conformance::read("asam-opendrive", ROAD_SHAPE);
    REQUIRE(city_model->city_objects_len() == 1);
    const std::vector<FeatureType> types = {
        FeatureType::CityModel,     FeatureType::Road,          FeatureType::Section,
        FeatureType::TrafficSpace,  FeatureType::TrafficArea,   FeatureType::TrafficSpace,
        FeatureType::TrafficArea,   FeatureType::AuxiliaryTrafficSpace, FeatureType::AuxiliaryTrafficArea,
        FeatureType::AuxiliaryTrafficSpace, FeatureType::AuxiliaryTrafficArea,
    };
    REQUIRE(feature_types(*city_model) == types);
    std::vector<FeatureType> objects_types;
    auto iterator = city_model->iter_city_objects();
    while (auto object = iterator->next()) {
        objects_types.push_back(object->feature_type());
    }
    REQUIRE(objects_types == std::vector<FeatureType>(types.begin() + 1, types.end()));
    require_envelope(*city_model, {-50.21567184593757, -2.4442507170297514, 0.0},
                     {-13.007511850967884, 29.053746110395082, 4.95});
}

TEST_CASE("Road shape road", "[asam-opendrive][road-shape]") {
    auto city_model = conformance::read("asam-opendrive", ROAD_SHAPE);
    const auto* r = road(*city_model);
    REQUIRE(r->feature_id().as_str() == "UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f");
    REQUIRE(r->class_() == nullptr);
    REQUIRE_FALSE(r->traffic_direction().has_value());
    REQUIRE(count(r->functions()) == 0);
    REQUIRE(count(r->usages()) == 0);
    REQUIRE(count(r->intersections()) == 0);
    REQUIRE(count(r->occupancies()) == 0);
    REQUIRE(count(r->traffic_spaces()) == 0);
    REQUIRE(count(r->auxiliary_traffic_spaces()) == 0);
    REQUIRE(count(r->markings()) == 0);
    REQUIRE(count(r->holes()) == 0);
    REQUIRE(road_shape_section(*city_model)->feature_id().as_str() == "UUID_0950bfa5-204e-33e6-bdb7-c5c318d73a29");
}

TEST_CASE("Road shape section", "[asam-opendrive][road-shape]") {
    auto city_model = conformance::read("asam-opendrive", ROAD_SHAPE);
    const auto* section = road_shape_section(*city_model);
    REQUIRE(section->class_() == nullptr);
    REQUIRE_FALSE(section->traffic_direction().has_value());
    REQUIRE(section->lod0_multi_curve() == nullptr);
    REQUIRE(section->lod1_solid() == nullptr);
    REQUIRE(count(section->markings()) == 0);
    REQUIRE(count(section->holes()) == 0);
    REQUIRE(ids(objects(section->traffic_spaces())) ==
            std::vector<std::string>{"UUID_ae81947d-a661-3678-a5ee-eed58b68694f",
                                     "UUID_6e4de408-1e54-3869-b7ce-1be3f2261421"});
    REQUIRE(ids(objects(section->auxiliary_traffic_spaces())) ==
            std::vector<std::string>{"UUID_12298df9-4982-33a8-ab4a-9953410bbff7",
                                     "UUID_f8211bb5-0ce8-36e1-9b84-73d30114f578"});
}

TEST_CASE("Road shape traffic spaces", "[asam-opendrive][road-shape]") {
    auto city_model = conformance::read("asam-opendrive", ROAD_SHAPE);
    const auto spaces = road_shape_spaces(*city_model);
    REQUIRE(spaces.size() == 2);
    REQUIRE(spaces[0]->traffic_direction() == ecitygml::TrafficDirectionValue::Backwards);
    REQUIRE(spaces[1]->traffic_direction() == ecitygml::TrafficDirectionValue::Forwards);
    for (const auto* space : spaces) {
        REQUIRE(space->granularity() == ecitygml::GranularityValue::Lane);
        REQUIRE(space->class_() == nullptr);
        REQUIRE(values(space->functions()) == std::vector<std::string>{"1"});
        REQUIRE(values(space->usages()) == std::vector<std::string>{"2"});
        REQUIRE(count(space->occupancies()) == 0);
        REQUIRE(space->space_type() == ecitygml::SpaceType::Open);
        REQUIRE_FALSE(space->relative_to_terrain().has_value());
        REQUIRE(space->creation_date() == nullptr);
        REQUIRE(count(space->predecessors()) == 0);
        REQUIRE(count(space->successors()) == 0);
        REQUIRE(ecitygml::TrafficArea::try_from(*only_boundary(space->boundaries())) != nullptr);
    }
}

TEST_CASE("Road shape generic attributes", "[asam-opendrive][road-shape]") {
    auto city_model = conformance::read("asam-opendrive", ROAD_SHAPE);
    using Value = std::variant<int64_t, double, std::string>;
    std::vector<std::pair<std::string, Value>> attributes;
    auto iterator = road_shape_spaces(*city_model)[0]->generic_attributes();
    while (const auto* attribute = iterator->next()) {
        Value value;
        if (const auto* integer = attribute->as_int()) {
            value = integer->value();
        } else if (const auto* number = attribute->as_double()) {
            value = number->value();
        } else {
            REQUIRE(attribute->as_string() != nullptr);
            value = std::string(attribute->as_string()->value());
        }
        attributes.emplace_back(std::string(attribute->name()), value);
    }
    REQUIRE(attributes == std::vector<std::pair<std::string, Value>>{
                              {"identifier_laneId", int64_t{1}},
                              {"identifier_laneSectionId", int64_t{0}},
                              {"identifier_roadId", std::string("1")},
                              {"opendrive_road_length", 40.0},
                              {"opendrive_road_rule", std::string("RIGHT_HAND_TRAFFIC")},
                              {"opendrive_laneSection_curvePositionStart", 0.0},
                              {"opendrive_lane_type", std::string("DRIVING")},
                              {"opendrive_lane_level", std::string("false")},
                          });
}

TEST_CASE("Road shape traffic space geometry", "[asam-opendrive][road-shape]") {
    auto city_model = conformance::read("asam-opendrive", ROAD_SHAPE);
    const auto spaces = road_shape_spaces(*city_model);
    REQUIRE_THAT(ok(spaces[0]->lod2_solid()->object()->volume_3d()), close(720.0));
    REQUIRE_THAT(ok(spaces[1]->lod2_solid()->object()->volume_3d()), close(540.0));
    for (const auto* space : spaces) {
        const auto* property = space->lod2_multi_curve();
        REQUIRE(property != nullptr);
        REQUIRE(property->href() == nullptr);
        const auto* multi_curve = property->object();
        REQUIRE(multi_curve != nullptr);
        REQUIRE_THAT(ok(multi_curve->length_3d()), close(40.0));
        const auto [points, length] = line_string(*multi_curve);
        REQUIRE(points == 2);
        REQUIRE_THAT(length, close(40.0));
        REQUIRE(space->lod0_multi_curve() == nullptr);
        REQUIRE(space->lod3_multi_curve() == nullptr);
        REQUIRE(space->lod1_solid() == nullptr);
        REQUIRE(space->lod3_solid() == nullptr);
        REQUIRE(space->lod2_multi_surface() == nullptr);
    }
}

TEST_CASE("Road shape traffic areas", "[asam-opendrive][road-shape]") {
    auto city_model = conformance::read("asam-opendrive", ROAD_SHAPE);
    std::vector<std::unique_ptr<ecitygml::AbstractFeatureKindRef>> boundaries;
    std::vector<const ecitygml::TrafficArea*> areas;
    for (const auto* space : road_shape_spaces(*city_model)) {
        boundaries.push_back(only_boundary(space->boundaries()));
        areas.push_back(ecitygml::TrafficArea::try_from(*boundaries.back()));
        REQUIRE(areas.back() != nullptr);
    }
    REQUIRE(ids(areas) == std::vector<std::string>{"UUID_8625bf6f-57cb-3ddf-8fd1-6674b756a2e2",
                                                   "UUID_dc110e80-dadc-3c87-b864-2854cc0cb39a"});
    std::vector<double> area_3d;
    for (const auto* area : areas) {
        REQUIRE(first_name(*area) == "Lane");
        REQUIRE(area->class_() == nullptr);
        REQUIRE(values(area->functions()) == std::vector<std::string>{"1"});
        REQUIRE(values(area->usages()) == std::vector<std::string>{"2"});
        REQUIRE(area->surface_material() == nullptr);
        REQUIRE(area->lod0_multi_curve() == nullptr);
        REQUIRE(area->lod0_multi_surface() == nullptr);
        REQUIRE(area->lod1_multi_surface() == nullptr);
        REQUIRE(area->lod3_multi_surface() == nullptr);
        REQUIRE_FALSE(area->relative_to_terrain().has_value());
        const auto* multi_surface = area->lod2_multi_surface()->object();
        REQUIRE(count(multi_surface->surface_member()) == 1);
        area_3d.push_back(ok(multi_surface->area_3d()));
    }
    REQUIRE_THAT(area_3d[0], close(160.79800993793438));
    REQUIRE_THAT(area_3d[1], close(121.34249049694012));
}

TEST_CASE("Road shape auxiliary traffic", "[asam-opendrive][road-shape]") {
    auto city_model = conformance::read("asam-opendrive", ROAD_SHAPE);
    std::vector<std::unique_ptr<ecitygml::AbstractFeatureKindRef>> boundaries;
    std::vector<const ecitygml::AuxiliaryTrafficArea*> areas;
    for (const auto* space : objects(road_shape_section(*city_model)->auxiliary_traffic_spaces())) {
        REQUIRE(space->granularity() == ecitygml::GranularityValue::Lane);
        REQUIRE(space->class_() == nullptr);
        REQUIRE(count(space->functions()) == 0);
        REQUIRE(count(space->usages()) == 0);
        REQUIRE(space->space_type() == ecitygml::SpaceType::Open);
        REQUIRE_THAT(ok(space->lod2_solid()->object()->volume_3d()), close(100.0));
        REQUIRE_THAT(ok(space->lod2_multi_curve()->object()->length_3d()), close(40.0));
        boundaries.push_back(only_boundary(space->boundaries()));
        areas.push_back(ecitygml::AuxiliaryTrafficArea::try_from(*boundaries.back()));
        REQUIRE(areas.back() != nullptr);
    }
    REQUIRE(ids(areas) == std::vector<std::string>{"UUID_4890681a-e9fa-365e-a676-f89afb453f9b",
                                                   "UUID_d3c71d48-5222-355e-8037-9677aee30d7e"});
    for (const auto* area : areas) {
        REQUIRE(first_name(*area) == "Lane");
        REQUIRE(area->class_() == nullptr);
        REQUIRE(count(area->functions()) == 0);
        REQUIRE(count(area->usages()) == 0);
        REQUIRE(area->surface_material() == nullptr);
        REQUIRE_THAT(ok(area->lod2_multi_surface()->object()->area_3d()), close(40.0));
    }
}

TEST_CASE("Junction city model", "[asam-opendrive][junction]") {
    auto city_model = conformance::read("asam-opendrive", JUNCTION);
    REQUIRE(city_model->city_objects_len() == 1);
    REQUIRE(feature_types(*city_model) == std::vector<FeatureType>{
            FeatureType::CityModel, FeatureType::Road, FeatureType::Section, FeatureType::TrafficSpace,
            FeatureType::TrafficArea, FeatureType::TrafficSpace, FeatureType::TrafficArea, FeatureType::Marking,
            FeatureType::Marking, FeatureType::Marking, FeatureType::Marking, FeatureType::Section,
            FeatureType::TrafficSpace, FeatureType::TrafficArea, FeatureType::Section, FeatureType::TrafficSpace,
            FeatureType::TrafficArea, FeatureType::Intersection, FeatureType::TrafficSpace, FeatureType::TrafficArea,
            FeatureType::TrafficSpace, FeatureType::TrafficArea, FeatureType::TrafficSpace, FeatureType::TrafficArea,
        });
    REQUIRE(count(city_model->iter_city_objects()) == 23);
    require_envelope(*city_model, {-52.66282419815818, -37.4146115571896, 0.0},
                     {34.10760429351533, 6.338805461729647, 0.0});
}

TEST_CASE("Junction road", "[asam-opendrive][junction]") {
    auto city_model = conformance::read("asam-opendrive", JUNCTION);
    const auto* r = road(*city_model);
    REQUIRE(r->feature_id().as_str() == "UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f");
    const auto sections = objects(r->sections());
    REQUIRE(ids(sections) == std::vector<std::string>{"UUID_0950bfa5-204e-33e6-bdb7-c5c318d73a29",
                                                      "UUID_ef20f165-2564-373a-a5f8-98fd15f1ae69",
                                                      "UUID_4799566b-daf4-3135-aa9d-ec1b34a9167d"});
    std::vector<int> spaces;
    std::vector<int> markings;
    for (const auto* section : sections) {
        spaces.push_back(count(section->traffic_spaces()));
        markings.push_back(count(section->markings()));
        REQUIRE(count(section->auxiliary_traffic_spaces()) == 0);
    }
    REQUIRE(spaces == std::vector<int>{2, 1, 1});
    REQUIRE(markings == std::vector<int>{4, 0, 0});
    const auto intersections = objects(r->intersections());
    REQUIRE(intersections.size() == 1);
    REQUIRE(intersections[0]->feature_id().as_str() == "UUID_47b7678d-e8b1-36ca-90b6-5b86cc859571");
    REQUIRE(intersections[0]->class_() == nullptr);
    REQUIRE(ids(objects(intersections[0]->traffic_spaces())) ==
            std::vector<std::string>(SPACES.begin() + 4, SPACES.end()));
}

TEST_CASE("Junction traffic spaces", "[asam-opendrive][junction]") {
    auto city_model = conformance::read("asam-opendrive", JUNCTION);
    const auto all = features(*city_model);
    const auto spaces = traffic_spaces(all);
    REQUIRE(ids(spaces) == SPACES);
    std::vector<int> points;
    std::vector<double> lengths;
    for (std::size_t i = 0; i < spaces.size(); ++i) {
        REQUIRE(spaces[i]->traffic_direction() ==
                (i == 0 ? ecitygml::TrafficDirectionValue::Backwards : ecitygml::TrafficDirectionValue::Forwards));
        REQUIRE(spaces[i]->lod2_solid() == nullptr);
        const auto [n, length] = line_string(*spaces[i]->lod2_multi_curve()->object());
        points.push_back(n);
        lengths.push_back(length);
    }
    REQUIRE(points == std::vector<int>{9, 9, 5, 6, 7, 8, 7});
    const std::vector<double> expected = {36.74683751297985,  36.74683751297985,  20.0, 21.746217945006258,
                                          26.761532846607814, 30.210435770102656, 30.0};
    for (std::size_t i = 0; i < expected.size(); ++i) {
        REQUIRE_THAT(lengths[i], close(expected[i]));
    }
}

TEST_CASE("Junction traffic areas", "[asam-opendrive][junction]") {
    auto city_model = conformance::read("asam-opendrive", JUNCTION);
    std::vector<int> members;
    std::vector<double> areas;
    for (const auto& feature : features(*city_model)) {
        if (const auto* area = ecitygml::TrafficArea::try_from(*feature)) {
            const auto* multi_surface = area->lod2_multi_surface()->object();
            members.push_back(count(multi_surface->surface_member()));
            areas.push_back(ok(multi_surface->area_3d()));
        }
    }
    REQUIRE(members == std::vector<int>{8, 8, 4, 5, 6, 7, 6});
    const std::vector<double> expected = {112.81279116484816, 112.81279116484816, 61.4, 66.76088909116919,
                                          81.22157625123039,  92.69041581703632,  92.1};
    REQUIRE(areas.size() == expected.size());
    for (std::size_t i = 0; i < expected.size(); ++i) {
        REQUIRE_THAT(areas[i], close(expected[i]));
    }
}

TEST_CASE("Junction traffic space links", "[asam-opendrive][junction]") {
    auto city_model = conformance::read("asam-opendrive", JUNCTION);
    const auto all = features(*city_model);
    using Ids = std::vector<std::string>;
    std::vector<std::pair<Ids, Ids>> links;
    for (const auto* space : traffic_spaces(all)) {
        links.emplace_back(local_ids(space->predecessors()), local_ids(space->successors()));
    }
    const auto& s = SPACES;
    REQUIRE(links == std::vector<std::pair<Ids, Ids>>{
                         {{}, {}},
                         {{}, {s[6]}},
                         {{s[4], s[5]}, {}},
                         {{}, {s[4]}},
                         {{s[3]}, {s[2]}},
                         {{"UUID_d7d4aa5a-88c9-328d-9151-a6c043e57d7f"}, {s[0]}},
                         {{s[1]}, {s[2]}},
                     });
}

TEST_CASE("Junction markings", "[asam-opendrive][junction]") {
    auto city_model = conformance::read("asam-opendrive", JUNCTION);
    const auto* section = objects(road(*city_model)->sections()).front();
    std::vector<double> areas;
    for (const auto* marking : objects(section->markings())) {
        REQUIRE(first_name(*marking) == "RoadMarking");
        REQUIRE(marking->class_() == nullptr);
        REQUIRE(marking->lod0_multi_surface() == nullptr);
        REQUIRE(marking->lod3_multi_surface() == nullptr);
        const auto* multi_surface = marking->lod2_multi_surface()->object();
        REQUIRE(count(multi_surface->surface_member()) == 1);
        areas.push_back(ok(multi_surface->area_3d()));
    }
    const std::vector<double> expected = {0.48, 0.48, 0.48, 0.08962050155758661};
    REQUIRE(areas.size() == expected.size());
    for (std::size_t i = 0; i < expected.size(); ++i) {
        REQUIRE_THAT(areas[i], close(expected[i]));
    }
}
