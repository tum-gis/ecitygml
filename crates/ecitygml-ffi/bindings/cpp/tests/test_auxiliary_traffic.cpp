#include "test_helpers.hpp"

#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <ecitygml/AbstractFeatureKindRef.hpp>
#include <ecitygml/AbstractFeatureKindRefIterator.hpp>
#include <ecitygml/AuxiliaryTrafficArea.hpp>
#include <ecitygml/AuxiliaryTrafficAreaFunctionValueIterator.hpp>
#include <ecitygml/AuxiliaryTrafficSpace.hpp>
#include <ecitygml/AuxiliaryTrafficSpaceFunctionValueIterator.hpp>
#include <ecitygml/Code.hpp>
#include <ecitygml/CodeIterator.hpp>
#include <ecitygml/GranularityValue.hpp>
#include <ecitygml/MultiCurve.hpp>
#include <ecitygml/MultiCurveProperty.hpp>
#include <ecitygml/MultiSurface.hpp>
#include <ecitygml/MultiSurfaceProperty.hpp>
#include <ecitygml/Solid.hpp>
#include <ecitygml/SolidProperty.hpp>

#include <cstddef>
#include <utility>

using Catch::Matchers::WithinRel;

TEST_CASE("AuxiliaryTrafficSpace getters", "[auxiliary_traffic]") {
    auto city_model = read(fixture("ASAM-UC_RoadShape.gml"));
    std::size_t count = 0;
    auto features = city_model->iter_features();
    while (auto feature = features->next()) {
        const auto* space = ecitygml::AuxiliaryTrafficSpace::try_from(*feature);
        if (space == nullptr) {
            continue;
        }
        ++count;
        REQUIRE(space->class_() == nullptr);
        REQUIRE(space->functions()->next() == nullptr);
        REQUIRE(space->granularity() == ecitygml::GranularityValue::Lane);
        auto volume = space->lod2_solid()->object()->volume_3d();
        REQUIRE(volume.is_ok());
        REQUIRE_THAT(std::move(volume).ok().value(), WithinRel(100.0, 1e-9));
        auto length = space->lod2_multi_curve()->object()->length_3d();
        REQUIRE(length.is_ok());
        REQUIRE_THAT(std::move(length).ok().value(), WithinRel(40.0, 1e-9));
    }
    REQUIRE(count == 2);
}

TEST_CASE("AuxiliaryTrafficArea getters", "[auxiliary_traffic]") {
    auto city_model = read(fixture("ASAM-UC_RoadShape.gml"));
    std::size_t count = 0;
    auto features = city_model->iter_features();
    while (auto feature = features->next()) {
        const auto* area = ecitygml::AuxiliaryTrafficArea::try_from(*feature);
        if (area == nullptr) {
            continue;
        }
        ++count;
        REQUIRE(area->class_() == nullptr);
        REQUIRE(area->functions()->next() == nullptr);
        REQUIRE(area->surface_material() == nullptr);
        REQUIRE(area->names()->next()->value() == "Lane");
        auto area_3d = area->lod2_multi_surface()->object()->area_3d();
        REQUIRE(area_3d.is_ok());
        REQUIRE_THAT(std::move(area_3d).ok().value(), WithinRel(40.0, 1e-9));
    }
    REQUIRE(count == 2);
}
