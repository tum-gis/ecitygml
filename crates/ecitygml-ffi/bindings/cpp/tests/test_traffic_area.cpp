#include "test_helpers.hpp"

#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include <ecitygml/AbstractFeatureKindRef.hpp>
#include <ecitygml/AbstractFeatureKindRefIterator.hpp>
#include <ecitygml/Code.hpp>
#include <ecitygml/CodeIterator.hpp>
#include <ecitygml/Id.hpp>
#include <ecitygml/MultiSurface.hpp>
#include <ecitygml/MultiSurfaceProperty.hpp>
#include <ecitygml/TrafficArea.hpp>
#include <ecitygml/TrafficAreaFunctionValue.hpp>
#include <ecitygml/TrafficAreaFunctionValueIterator.hpp>
#include <ecitygml/TrafficAreaUsageValue.hpp>
#include <ecitygml/TrafficAreaUsageValueIterator.hpp>

#include <string>
#include <utility>
#include <vector>

using Catch::Matchers::StartsWith;
using Catch::Matchers::WithinRel;
using ecitygml::TrafficArea;

namespace {
/// The traffic areas of a model; the model must outlive the returned pointers.
std::vector<const TrafficArea*> traffic_areas(const ecitygml::CityModel& city_model) {
    std::vector<const TrafficArea*> areas;
    auto features = city_model.iter_features();
    while (auto feature = features->next()) {
        if (const auto* area = TrafficArea::try_from(*feature)) {
            areas.push_back(area);
        }
    }
    return areas;
}
}  // namespace

TEST_CASE("TrafficArea own and inherited getters", "[traffic_area]") {
    auto city_model = read(fixture("ASAM-UC_RoadShape.gml"));
    auto areas = traffic_areas(*city_model);
    REQUIRE(areas.size() == 2);

    const auto* area = areas.front();
    REQUIRE(area->class_() == nullptr);
    REQUIRE(area->functions()->next()->value() == "1");
    REQUIRE(area->usages()->next()->code().value() == "2");
    REQUIRE(area->surface_material() == nullptr);
    REQUIRE(area->lod0_multi_curve() == nullptr);
    REQUIRE(area->lod1_multi_surface() == nullptr);
    REQUIRE_THAT(std::string(area->feature_id().as_str()), StartsWith("UUID_8625bf6f"));
    REQUIRE(area->names()->next()->value() == "Lane");
}

TEST_CASE("Total LoD2 area of the traffic areas", "[traffic_area][geometry]") {
    auto city_model = read(fixture("ASAM-UC_RoadShape.gml"));

    double total_area = 0.0;
    for (const auto* area : traffic_areas(*city_model)) {
        const auto* property = area->lod2_multi_surface();
        REQUIRE(property != nullptr);
        auto area_3d = property->object()->area_3d();
        REQUIRE(area_3d.is_ok());
        total_area += std::move(area_3d).ok().value();
    }
    REQUIRE_THAT(total_area, WithinRel(282.1405004348745, 1e-9));
}
