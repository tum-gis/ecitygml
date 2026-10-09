#include "test_helpers.hpp"

#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <ecitygml/AbstractFeatureKindRef.hpp>
#include <ecitygml/AbstractFeatureKindRefIterator.hpp>
#include <ecitygml/AbstractSpaceBoundaryKind.hpp>
#include <ecitygml/AbstractSpaceBoundaryProperty.hpp>
#include <ecitygml/AbstractSpaceBoundaryPropertyIterator.hpp>
#include <ecitygml/Building.hpp>
#include <ecitygml/FeatureType.hpp>
#include <ecitygml/MultiSurface.hpp>
#include <ecitygml/MultiSurfaceProperty.hpp>
#include <ecitygml/WallSurface.hpp>

#include <cstddef>
#include <utility>

using Catch::Matchers::WithinRel;

TEST_CASE("Building boundaries", "[space_boundary]") {
    auto city_model = read(fixture("FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml"));
    const ecitygml::Building* building = nullptr;
    auto features = city_model->iter_features();
    while (auto feature = features->next()) {
        if ((building = ecitygml::Building::try_from(*feature)) != nullptr) {
            break;
        }
    }
    REQUIRE(building != nullptr);

    std::size_t count = 0;
    std::size_t walls = 0;
    double wall_area = 0.0;
    auto boundaries = building->boundaries();
    while (const auto* property = boundaries->next()) {
        ++count;
        const auto* boundary = property->object();
        REQUIRE(boundary != nullptr);
        auto feature = ecitygml::AbstractFeatureKindRef::from_space_boundary(*boundary);
        REQUIRE(feature->feature_type() == boundary->feature_type());
        if (const auto* wall = ecitygml::WallSurface::try_from(*feature)) {
            ++walls;
            auto area = wall->lod2_multi_surface()->object()->area_3d();
            REQUIRE(area.is_ok());
            wall_area += std::move(area).ok().value();
        }
    }
    REQUIRE(count == 7);
    REQUIRE(walls == 4);
    REQUIRE_THAT(wall_area, WithinRel(188.62887820601463, 1e-9));
}
