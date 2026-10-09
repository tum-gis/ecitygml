#include "test_helpers.hpp"

#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <ecitygml/AbstractCurveKind.hpp>
#include <ecitygml/AbstractCurveProperty.hpp>
#include <ecitygml/AbstractCurvePropertyIterator.hpp>
#include <ecitygml/AbstractFeatureKindRef.hpp>
#include <ecitygml/AbstractFeatureKindRefIterator.hpp>
#include <ecitygml/AbstractSurfaceKind.hpp>
#include <ecitygml/AbstractSurfaceProperty.hpp>
#include <ecitygml/AbstractSurfacePropertyIterator.hpp>
#include <ecitygml/Code.hpp>
#include <ecitygml/DirectPositionIterator.hpp>
#include <ecitygml/Envelope.hpp>
#include <ecitygml/GeometryType.hpp>
#include <ecitygml/GranularityValue.hpp>
#include <ecitygml/Id.hpp>
#include <ecitygml/LineString.hpp>
#include <ecitygml/MultiCurve.hpp>
#include <ecitygml/MultiCurveProperty.hpp>
#include <ecitygml/MultiSurface.hpp>
#include <ecitygml/MultiSurfaceProperty.hpp>
#include <ecitygml/OccupancyIterator.hpp>
#include <ecitygml/Point.hpp>
#include <ecitygml/PointProperty.hpp>
#include <ecitygml/Polygon.hpp>
#include <ecitygml/Solid.hpp>
#include <ecitygml/SolidProperty.hpp>
#include <ecitygml/SpaceType.hpp>
#include <ecitygml/TrafficDirectionValue.hpp>
#include <ecitygml/TrafficSpace.hpp>
#include <ecitygml/TrafficSpaceFunctionValue.hpp>
#include <ecitygml/TrafficSpaceFunctionValueIterator.hpp>
#include <ecitygml/TrafficSpaceUsageValue.hpp>
#include <ecitygml/TrafficSpaceUsageValueIterator.hpp>

#include <algorithm>
#include <cstddef>
#include <vector>

using Catch::Matchers::WithinRel;
using ecitygml::TrafficSpace;

namespace {
/// The traffic spaces of a model; the model must outlive the returned pointers.
std::vector<const TrafficSpace*> traffic_spaces(const ecitygml::CityModel& city_model) {
    std::vector<const TrafficSpace*> spaces;
    auto features = city_model.iter_features();
    while (auto feature = features->next()) {
        if (const auto* space = TrafficSpace::try_from(*feature)) {
            spaces.push_back(space);
        }
    }
    return spaces;
}
}  // namespace

TEST_CASE("TrafficSpace via iter_features and try_from", "[traffic_space]") {
    auto city_model = read(fixture("ASAM-UC_RoadShape.gml"));
    auto spaces = traffic_spaces(*city_model);
    REQUIRE(spaces.size() == 2);

    std::vector<ecitygml::TrafficDirectionValue> directions;
    for (const auto* space : spaces) {
        directions.push_back(space->traffic_direction().value());
    }
    REQUIRE(std::count(directions.begin(), directions.end(), ecitygml::TrafficDirectionValue::Forwards) == 1);
    REQUIRE(std::count(directions.begin(), directions.end(), ecitygml::TrafficDirectionValue::Backwards) == 1);
}

TEST_CASE("TrafficSpace own and inherited getters", "[traffic_space]") {
    auto city_model = read(fixture("ASAM-UC_RoadShape.gml"));
    const auto* space = traffic_spaces(*city_model).at(0);

    // TrafficSpace
    REQUIRE(space->granularity() == ecitygml::GranularityValue::Lane);
    REQUIRE(space->class_() == nullptr);
    auto functions = space->functions();
    REQUIRE(functions->next()->value() == "1");
    REQUIRE(functions->next() == nullptr);
    REQUIRE(space->usages()->next()->code().value() == "2");
    REQUIRE(space->occupancies()->next() == nullptr);

    // AbstractSpace, AbstractCityObject, AbstractFeature (ecitygml and egml)
    REQUIRE(space->space_type() == ecitygml::SpaceType::Open);
    REQUIRE_FALSE(space->relative_to_terrain().has_value());
    REQUIRE_FALSE(space->feature_id().as_str().empty());
    REQUIRE(space->creation_date() == nullptr);
}

TEST_CASE("Total LoD2 volume of the traffic spaces", "[traffic_space][geometry]") {
    auto city_model = read(fixture("ASAM-UC_RoadShape.gml"));

    double total_volume = 0.0;
    for (const auto* space : traffic_spaces(*city_model)) {
        const auto* lod2_solid = space->lod2_solid();
        if (lod2_solid && lod2_solid->object()) {
            REQUIRE(lod2_solid->href() == nullptr);
            const auto* solid = lod2_solid->object();
            REQUIRE(solid->compute_envelope() != nullptr);
            REQUIRE(solid->points()->next() != nullptr);
            auto volume = solid->volume_3d();
            REQUIRE(volume.is_ok());
            total_volume += std::move(volume).ok().value();
        }
    }
    REQUIRE_THAT(total_volume, WithinRel(1260.0, 1e-9));
}

TEST_CASE("LoD2 multi curves of the traffic spaces", "[traffic_space][geometry]") {
    auto city_model = read(fixture("ASAM-UC_RoadShape.gml"));
    auto spaces = traffic_spaces(*city_model);
    REQUIRE(spaces.size() == 2);

    for (const auto* space : spaces) {
        REQUIRE(space->lod0_multi_curve() == nullptr);
        REQUIRE(space->lod3_multi_curve() == nullptr);
        const auto* property = space->lod2_multi_curve();
        REQUIRE(property != nullptr);
        REQUIRE(property->href() == nullptr);
        const auto* multi_curve = property->object();
        REQUIRE(multi_curve != nullptr);
        auto length = multi_curve->length_3d();
        REQUIRE(length.is_ok());
        REQUIRE_THAT(std::move(length).ok().value(), WithinRel(40.0, 1e-9));
        REQUIRE(multi_curve->compute_envelope() != nullptr);

        auto members = multi_curve->curve_member();
        const auto* member = members->next();
        REQUIRE(member != nullptr);
        REQUIRE(members->next() == nullptr);
        const auto* curve = member->object();
        REQUIRE(curve != nullptr);
        REQUIRE(curve->geometry_type() == ecitygml::GeometryType::LineString);
        REQUIRE_THAT(curve->length_3d(), WithinRel(40.0, 1e-9));

        const auto* line_string = ecitygml::LineString::try_from(*curve);
        REQUIRE(line_string != nullptr);
        REQUIRE_THAT(line_string->length_3d(), WithinRel(40.0, 1e-9));
        auto points = line_string->points();
        REQUIRE(points->next() != nullptr);
        REQUIRE(points->next() != nullptr);
        REQUIRE(points->next() == nullptr);
    }
}

namespace {
/// A 10 m x 4 m rectangle with a 1 m x 1 m hole (39 m^2), inserted after the first lod2Solid.
constexpr const char* lod2_multi_surface = "</lod2Solid><lod2MultiSurface><gml:MultiSurface><gml:surfaceMember><gml:Polygon gml:id=\"PolyID_space\"><gml:exterior><gml:LinearRing><gml:posList srsDimension=\"3\">0 0 0 10 0 0 10 4 0 0 4 0 0 0 0</gml:posList></gml:LinearRing></gml:exterior><gml:interior><gml:LinearRing><gml:posList srsDimension=\"3\">1 1 0 1 2 0 2 2 0 2 1 0 1 1 0</gml:posList></gml:LinearRing></gml:interior></gml:Polygon></gml:surfaceMember></gml:MultiSurface></lod2MultiSurface>";

std::size_t count(ecitygml::DirectPositionIterator& points) {
    std::size_t n = 0;
    while (points.next() != nullptr) {
        ++n;
    }
    return n;
}
}  // namespace

TEST_CASE("LoD2 multi surface of a traffic space", "[traffic_space][geometry]") {
    auto city_model = read_modified("ASAM-UC_RoadShape.gml", "</lod2Solid>", lod2_multi_surface);
    auto spaces = traffic_spaces(*city_model);
    REQUIRE(spaces.size() == 2);
    REQUIRE(spaces[1]->lod2_multi_surface() == nullptr);

    const auto* space = spaces[0];
    REQUIRE(space->lod0_multi_surface() == nullptr);
    REQUIRE(space->lod3_multi_surface() == nullptr);
    const auto* property = space->lod2_multi_surface();
    REQUIRE(property != nullptr);
    REQUIRE(property->href() == nullptr);
    const auto* multi_surface = property->object();
    REQUIRE(multi_surface != nullptr);
    auto area = multi_surface->area_3d();
    REQUIRE(area.is_ok());
    REQUIRE_THAT(std::move(area).ok().value(), WithinRel(39.0, 1e-9));
    REQUIRE(multi_surface->compute_envelope() != nullptr);
    // 4 positions per ring: egml drops the repeated closing position.
    REQUIRE(count(*multi_surface->points()) == 8);

    auto members = multi_surface->surface_member();
    const auto* member = members->next();
    REQUIRE(member != nullptr);
    REQUIRE(members->next() == nullptr);
    const auto* surface = member->object();
    REQUIRE(surface != nullptr);
    REQUIRE(surface->geometry_type() == ecitygml::GeometryType::Polygon);
    REQUIRE(surface->id()->as_str() == "PolyID_space");

    const auto* polygon = ecitygml::Polygon::try_from(*surface);
    REQUIRE(polygon != nullptr);
    auto polygon_area = polygon->area_3d();
    REQUIRE(polygon_area.is_ok());
    REQUIRE_THAT(std::move(polygon_area).ok().value(), WithinRel(39.0, 1e-9));
    REQUIRE(count(*polygon->points()) == 8);
}

TEST_CASE("LoD0 point of a traffic space", "[traffic_space][geometry]") {
    auto city_model = read_modified("ASAM-UC_RoadShape.gml", "</lod2Solid>", "</lod2Solid><lod0Point><gml:Point gml:id=\"PointID_space\"><gml:pos srsDimension=\"3\">1.5 -2.5 3.25</gml:pos></gml:Point></lod0Point>");
    auto spaces = traffic_spaces(*city_model);
    REQUIRE(spaces.size() == 2);
    REQUIRE(spaces[1]->lod0_point() == nullptr);

    const auto* property = spaces[0]->lod0_point();
    REQUIRE(property != nullptr);
    REQUIRE(property->href() == nullptr);
    const auto* point = property->object();
    REQUIRE(point != nullptr);
    REQUIRE(point->id()->as_str() == "PointID_space");
    const auto& pos = point->pos();
    REQUIRE(pos.x() == 1.5);
    REQUIRE(pos.y() == -2.5);
    REQUIRE(pos.z() == 3.25);
    auto envelope = point->compute_envelope();
    REQUIRE(envelope != nullptr);
    REQUIRE(envelope->lower_corner().x() == 1.5);
}
