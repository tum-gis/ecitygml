#include "test_helpers.hpp"

#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <ecitygml/AbstractFeatureKindRef.hpp>
#include <ecitygml/AbstractFeatureKindRefIterator.hpp>
#include <ecitygml/AuxiliaryTrafficSpace.hpp>
#include <ecitygml/AuxiliaryTrafficSpaceProperty.hpp>
#include <ecitygml/AuxiliaryTrafficSpacePropertyIterator.hpp>
#include <ecitygml/HolePropertyIterator.hpp>
#include <ecitygml/Intersection.hpp>
#include <ecitygml/IntersectionProperty.hpp>
#include <ecitygml/IntersectionPropertyIterator.hpp>
#include <ecitygml/Marking.hpp>
#include <ecitygml/MarkingProperty.hpp>
#include <ecitygml/MarkingPropertyIterator.hpp>
#include <ecitygml/Road.hpp>
#include <ecitygml/Section.hpp>
#include <ecitygml/SectionProperty.hpp>
#include <ecitygml/SectionPropertyIterator.hpp>
#include <ecitygml/Solid.hpp>
#include <ecitygml/SolidProperty.hpp>
#include <ecitygml/TrafficSpacePropertyIterator.hpp>

#include <cstddef>
#include <utility>
#include <vector>

using Catch::Matchers::WithinRel;

namespace {
/// The first road of a model; the model must outlive the returned pointer.
const ecitygml::Road* first_road(const ecitygml::CityModel& city_model) {
    auto features = city_model.iter_features();
    while (auto feature = features->next()) {
        if (const auto* road = ecitygml::Road::try_from(*feature)) {
            return road;
        }
    }
    return nullptr;
}

template <typename Iterator>
std::size_t count(Iterator&& iterator) {
    std::size_t n = 0;
    while (iterator->next() != nullptr) {
        ++n;
    }
    return n;
}
}  // namespace

TEST_CASE("Road with a section of traffic and auxiliary traffic spaces", "[road]") {
    auto city_model = read(fixture("ASAM-UC_RoadShape.gml"));
    const auto* road = first_road(*city_model);
    REQUIRE(road != nullptr);
    REQUIRE(road->class_() == nullptr);
    REQUIRE(count(road->intersections()) == 0);
    REQUIRE(count(road->traffic_spaces()) == 0);
    REQUIRE(count(road->holes()) == 0);

    auto sections = road->sections();
    const auto* property = sections->next();
    REQUIRE(property != nullptr);
    REQUIRE(sections->next() == nullptr);
    const auto* section = property->object();
    REQUIRE(section != nullptr);
    REQUIRE(count(section->traffic_spaces()) == 2);

    double volume = 0.0;
    auto auxiliary = section->auxiliary_traffic_spaces();
    while (const auto* space = auxiliary->next()) {
        auto space_volume = space->object()->lod2_solid()->object()->volume_3d();
        REQUIRE(space_volume.is_ok());
        volume += std::move(space_volume).ok().value();
    }
    REQUIRE_THAT(volume, WithinRel(200.0, 1e-9));
}

TEST_CASE("Road with sections, an intersection and markings", "[road]") {
    auto city_model = read(fixture("ASAM-Ex_Bidirectional_Junction.gml"));
    const auto* road = first_road(*city_model);
    REQUIRE(road != nullptr);

    std::vector<std::size_t> per_section;
    auto sections = road->sections();
    while (const auto* property = sections->next()) {
        per_section.push_back(count(property->object()->traffic_spaces()));
    }
    REQUIRE(per_section == std::vector<std::size_t>{2, 1, 1});

    auto first_sections = road->sections();
    auto markings = first_sections->next()->object()->markings();
    std::size_t n = 0;
    while (const auto* marking = markings->next()) {
        REQUIRE(marking->object()->class_() == nullptr);
        ++n;
    }
    REQUIRE(n == 4);

    auto intersections = road->intersections();
    const auto* intersection = intersections->next();
    REQUIRE(intersection != nullptr);
    REQUIRE(intersections->next() == nullptr);
    REQUIRE(count(intersection->object()->traffic_spaces()) == 3);
}
