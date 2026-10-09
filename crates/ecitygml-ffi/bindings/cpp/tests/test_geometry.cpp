#include "test_helpers.hpp"

#include <catch2/matchers/catch_matchers_string.hpp>

#include <ecitygml/BoundingShape.hpp>
#include <ecitygml/Date.hpp>
#include <ecitygml/DateTime.hpp>
#include <ecitygml/DirectPosition.hpp>
#include <ecitygml/Envelope.hpp>
#include <ecitygml/ErrorKind.hpp>
#include <ecitygml/AbstractFeatureKindRef.hpp>
#include <ecitygml/AbstractFeatureKindRefIterator.hpp>
#include <ecitygml/AbstractRingKind.hpp>
#include <ecitygml/AbstractRingKindIterator.hpp>
#include <ecitygml/AbstractSurfaceKind.hpp>
#include <ecitygml/AbstractSurfaceProperty.hpp>
#include <ecitygml/AbstractSurfacePropertyIterator.hpp>
#include <ecitygml/Building.hpp>
#include <ecitygml/CompositeSurface.hpp>
#include <ecitygml/DirectPositionIterator.hpp>
#include <ecitygml/LevelOfDetail.hpp>
#include <ecitygml/LinearRing.hpp>
#include <ecitygml/Polygon.hpp>
#include <ecitygml/Shell.hpp>
#include <ecitygml/ShellIterator.hpp>
#include <ecitygml/Solid.hpp>
#include <ecitygml/SolidProperty.hpp>
#include <ecitygml/Triangle.hpp>
#include <ecitygml/TriangleIterator.hpp>
#include <ecitygml/TriangulatedSurface.hpp>
#include <ecitygml/Triangulation.hpp>
#include <ecitygml/TriangulationSkippedIterator.hpp>

#include <cmath>
#include <cstddef>
#include <utility>

using Catch::Matchers::ContainsSubstring;
using ecitygml::DirectPosition;

TEST_CASE("DirectPosition::create", "[geometry]") {
    auto position = std::move(DirectPosition::create(1.0, 2.0, 3.0).ok().value());
    REQUIRE(position->x() == 1.0);
    REQUIRE(position->y() == 2.0);
    REQUIRE(position->z() == 3.0);

    auto error = std::move(DirectPosition::create(std::nan(""), 0.0, 0.0).err().value());
    REQUIRE(error->kind() == ecitygml::ErrorKind::InvalidArgument);
    REQUIRE_THAT(error->message(), ContainsSubstring("non-finite"));
}

TEST_CASE("Envelope corners", "[geometry]") {
    auto city_model = read(fixture("FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml"));
    const auto& lower = city_model->bounded_by()->envelope()->lower_corner();
    REQUIRE(lower.x() == 457842.0);
    REQUIRE(lower.y() == 5439083.0);
    REQUIRE(lower.z() == 111.8);
    REQUIRE(city_model->bounded_by()->envelope()->upper_corner().z() == 118.317669);
}

TEST_CASE("Envelope volume and contains", "[geometry]") {
    auto city_model = read(fixture("FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml"));
    const auto* envelope = city_model->bounded_by()->envelope();
    REQUIRE(std::abs(envelope->volume() - 782.12028) < 1e-6);
    REQUIRE(envelope->contains(envelope->lower_corner()));
    REQUIRE(envelope->contains(envelope->upper_corner()));
    auto above = ecitygml::DirectPosition::create(457848.0, 5439088.0, 118.4);
    REQUIRE(above.is_ok());
    REQUIRE_FALSE(envelope->contains(*std::move(above).ok().value()));
}

TEST_CASE("LevelOfDetail as_index and try_from", "[common]") {
    REQUIRE(ecitygml::LevelOfDetail(ecitygml::LevelOfDetail::Two).as_index() == 2);
    auto three = ecitygml::LevelOfDetail::try_from(3);
    REQUIRE(three.is_ok());
    REQUIRE(std::move(three).ok().value() == ecitygml::LevelOfDetail::Three);
    auto invalid = ecitygml::LevelOfDetail::try_from(4);
    REQUIRE(invalid.is_err());
    REQUIRE(std::move(invalid).err().value()->kind() == ecitygml::ErrorKind::InvalidArgument);
}

TEST_CASE("Date and DateTime from_parts", "[xs]") {
    auto date_time = std::move(ecitygml::DateTime::from_parts(2017, 1, 23, 13, 14, 15, 0, -7200).ok().value());
    REQUIRE(date_time->year() == 2017);
    REQUIRE(date_time->hour() == 13);
    REQUIRE(date_time->offset_seconds() == -7200);
    REQUIRE(date_time->to_rfc3339() == "2017-01-23T13:14:15-02:00");

    auto date = std::move(ecitygml::Date::from_parts(2020, 1, 2, 3600).ok().value());
    REQUIRE(date->day() == 2);
    REQUIRE(date->start_of_day()->to_rfc3339() == "2020-01-02T00:00:00+01:00");

    auto invalid = ecitygml::Date::from_parts(2021, 2, 30, 0);
    REQUIRE(invalid.is_err());
    REQUIRE(std::move(invalid).err().value()->kind() == ecitygml::ErrorKind::InvalidArgument);
}

TEST_CASE("Solid shell, polygons and linear rings", "[geometry]") {
    auto city_model = read(fixture("FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml"));
    const ecitygml::Building* building = nullptr;
    auto features = city_model->iter_features();
    while (auto feature = features->next()) {
        if ((building = ecitygml::Building::try_from(*feature)) != nullptr) {
            break;
        }
    }
    REQUIRE(building != nullptr);
    const auto* solid = building->lod1_solid()->object();
    REQUIRE(solid->interior()->next() == nullptr);
    const auto* shell = solid->exterior();
    REQUIRE(shell != nullptr);

    std::size_t polygons = 0;
    auto members = shell->members();
    while (const auto* member = members->next()) {
        const auto* polygon = ecitygml::Polygon::try_from(*member->object());
        REQUIRE(polygon != nullptr);
        REQUIRE(polygon->interior()->next() == nullptr);
        const auto* ring = ecitygml::LinearRing::try_from(*polygon->exterior());
        REQUIRE(ring != nullptr);
        std::size_t points = 0;
        auto positions = ring->points();
        while (positions->next() != nullptr) {
            ++points;
        }
        REQUIRE(points == 4);  // without the repeated closing position
        ++polygons;
    }
    REQUIRE(polygons == 6);
    auto volume = shell->volume_3d();
    REQUIRE(volume.is_ok());
    REQUIRE(std::abs(std::move(volume).ok().value() - 782.1228) < 1e-6);
}

TEST_CASE("Solid triangulation", "[geometry]") {
    auto city_model = read(fixture("FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml"));
    const ecitygml::Building* building = nullptr;
    auto features = city_model->iter_features();
    while (auto feature = features->next()) {
        if ((building = ecitygml::Building::try_from(*feature)) != nullptr) {
            break;
        }
    }
    REQUIRE(building != nullptr);
    auto triangulation = building->lod1_solid()->object()->triangulate();
    REQUIRE(triangulation.is_ok());
    auto result = std::move(triangulation).ok().value();
    REQUIRE_FALSE(result->has_skipped());
    REQUIRE(result->skipped()->next() == nullptr);
    std::size_t triangles = 0;
    auto iterator = result->surface().triangles();
    while (const auto* triangle = iterator->next()) {
        REQUIRE(triangle->area() > 0.0);
        ++triangles;
    }
    REQUIRE(triangles == 12);
    auto area = result->surface().area_3d();
    REQUIRE(area.is_ok());
    REQUIRE(std::abs(std::move(area).ok().value() - 526.77836) < 1e-3);
}
