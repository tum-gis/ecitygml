#include "test_helpers.hpp"

#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <ecitygml/AbstractFeatureKindRef.hpp>
#include <ecitygml/AbstractFeatureKindRefIterator.hpp>
#include <ecitygml/AbstractFillingSurfaceKind.hpp>
#include <ecitygml/AbstractFillingSurfaceProperty.hpp>
#include <ecitygml/AbstractFillingSurfacePropertyIterator.hpp>
#include <ecitygml/Code.hpp>
#include <ecitygml/CodeIterator.hpp>
#include <ecitygml/DoorSurface.hpp>
#include <ecitygml/FeatureType.hpp>
#include <ecitygml/GroundSurface.hpp>
#include <ecitygml/MultiSurface.hpp>
#include <ecitygml/MultiSurfaceProperty.hpp>
#include <ecitygml/RoofSurface.hpp>
#include <ecitygml/WallSurface.hpp>
#include <ecitygml/WindowSurface.hpp>

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

using Catch::Matchers::WithinRel;

namespace {
/// The lod2 area of a thematic surface.
template <typename Surface>
double lod2_area(const Surface& surface) {
    auto area = surface.lod2_multi_surface()->object()->area_3d();
    REQUIRE(area.is_ok());
    return std::move(area).ok().value();
}
}  // namespace

TEST_CASE("Wall, roof and ground surfaces", "[construction]") {
    auto city_model = read(fixture("FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml"));
    std::vector<std::string> wall_names;
    double walls = 0.0;
    double roofs = 0.0;
    double grounds = 0.0;
    std::size_t roof_count = 0;
    auto features = city_model->iter_features();
    while (auto feature = features->next()) {
        if (const auto* wall = ecitygml::WallSurface::try_from(*feature)) {
            wall_names.emplace_back(wall->names()->next()->value());
            walls += lod2_area(*wall);
            REQUIRE(ecitygml::RoofSurface::try_from(*feature) == nullptr);
        } else if (const auto* roof = ecitygml::RoofSurface::try_from(*feature)) {
            ++roof_count;
            roofs += lod2_area(*roof);
        } else if (const auto* ground = ecitygml::GroundSurface::try_from(*feature)) {
            REQUIRE(ground->names()->next()->value() == "Base Surface");
            grounds += lod2_area(*ground);
        }
    }
    REQUIRE(wall_names == std::vector<std::string>{"Outer Wall 1 (West)", "Outer Wall 2 (South)",
                                                   "Outer Wall 3 (East)", "Outer Wall 4 (North)"});
    REQUIRE_THAT(walls, WithinRel(188.62887820601463, 1e-9));
    REQUIRE(roof_count == 2);
    REQUIRE_THAT(roofs, WithinRel(138.56406460961398, 1e-9));
    REQUIRE_THAT(grounds, WithinRel(120.0, 1e-9));
}

TEST_CASE("Door and window surfaces, also as filling surfaces", "[construction]") {
    auto city_model = read(fixture("FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml"));
    double doors = 0.0;
    std::size_t windows = 0;
    std::vector<std::string> west_fillings;
    auto features = city_model->iter_features();
    while (auto feature = features->next()) {
        if (const auto* door = ecitygml::DoorSurface::try_from(*feature)) {
            auto area = door->lod3_multi_surface()->object()->area_3d();
            REQUIRE(area.is_ok());
            doors += std::move(area).ok().value();
        } else if (ecitygml::WindowSurface::try_from(*feature) != nullptr) {
            ++windows;
        } else if (const auto* wall = ecitygml::WallSurface::try_from(*feature)) {
            if (wall->names()->next()->value() != "Outer Wall 1 (West)") {
                continue;
            }
            auto fillings = wall->filling_surfaces();
            while (const auto* property = fillings->next()) {
                const auto* filling = property->object();
                REQUIRE(filling != nullptr);
                const bool is_door = filling->feature_type() == ecitygml::FeatureType::DoorSurface;
                west_fillings.push_back(std::string(is_door ? "door:" : "window:") +
                                        std::string(filling->names()->next()->value()));
            }
        }
    }
    REQUIRE_THAT(doors, WithinRel(6.803850099444389, 1e-9));
    REQUIRE(windows == 11);
    REQUIRE(west_fillings == std::vector<std::string>{"window:Window Round", "window:Window North",
                                                      "door:Door West", "window:Window South"});
}
