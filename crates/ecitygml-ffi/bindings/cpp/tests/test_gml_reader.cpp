#include "test_helpers.hpp"

#include <catch2/matchers/catch_matchers_string.hpp>

#include <ecitygml/AbstractFeatureKindRef.hpp>
#include <ecitygml/AbstractFeatureKindRefIterator.hpp>
#include <ecitygml/CitygmlFormat.hpp>
#include <ecitygml/ErrorKind.hpp>
#include <ecitygml/Formatting.hpp>
#include <ecitygml/GmlWriter.hpp>

#include <cstddef>
#include <filesystem>
#include <string>
#include <utility>

using Catch::Matchers::ContainsSubstring;
using ecitygml::ErrorKind;
using ecitygml::GmlReader;

TEST_CASE("GmlReader reads a city model", "[io]") {
    REQUIRE(read(fixture("FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml"))->city_objects_len() == 1);
}

TEST_CASE("GmlReader options and single finish", "[io]") {
    auto reader = std::move(GmlReader::from_path(fixture("FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml")).ok().value());
    reader->with_rebuild_object_bounds(false);
    REQUIRE(reader->finish().is_ok());

    auto again = reader->finish();
    REQUIRE(again.is_err());
    auto error = std::move(std::move(again).err().value());
    REQUIRE(error->kind() == ErrorKind::InvalidArgument);
    REQUIRE_THAT(error->message(), ContainsSubstring("already finished"));
}

TEST_CASE("GmlReader errors", "[io]") {
    SECTION("missing file") {
        auto error = std::move(GmlReader::from_path(fixture("does-not-exist.gml")).err().value());
        REQUIRE(error->kind() == ErrorKind::Io);
        REQUIRE_THAT(error->message(), ContainsSubstring("No such file"));
    }
    SECTION("unsupported extension") {
        auto error = std::move(GmlReader::from_path(fixture("../../README.md")).err().value());
        REQUIRE(error->kind() == ErrorKind::InvalidArgument);
    }
    SECTION("invalid content") {
        const auto path = std::filesystem::temp_directory_path() / "ecitygml-ffi-cpp-invalid.gml";
        std::ofstream(path) << "<no-citygml";
        auto reader = std::move(GmlReader::from_path(path.string()).ok().value());
        auto error = std::move(reader->finish().err().value());
        std::filesystem::remove(path);
        REQUIRE(error->kind() == ErrorKind::Parse);
    }
}

namespace {
std::size_t feature_count(const ecitygml::CityModel& city_model) {
    std::size_t n = 0;
    auto features = city_model.iter_features();
    while (features->next() != nullptr) {
        ++n;
    }
    return n;
}
}  // namespace

TEST_CASE("GmlWriter round trips in memory and through files", "[io]") {
    auto model = read(fixture("FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml"));
    const auto features = feature_count(*model);

    SECTION("in memory, indented") {
        auto writer = ecitygml::GmlWriter::create(ecitygml::CitygmlFormat::GmlZst);
        writer->with_formatting(*ecitygml::Formatting::indent(' ', 2));
        REQUIRE(writer->finish(*model).is_ok());
        auto reader = GmlReader::create(writer->data(), ecitygml::CitygmlFormat::GmlZst);
        auto written = reader->finish();
        REQUIRE(written.is_ok());
        REQUIRE(feature_count(*std::move(written).ok().value()) == features);
        REQUIRE(writer->finish(*model).is_err());
    }

    SECTION("file") {
        const auto path = std::filesystem::temp_directory_path() / "ecitygml-ffi-cpp-writer.gml.gz";
        auto writer = ecitygml::GmlWriter::from_path(path.string());
        REQUIRE(writer.is_ok());
        REQUIRE(std::move(writer).ok().value()->finish(*model).is_ok());
        REQUIRE(feature_count(*read(path.string())) == features);
        std::filesystem::remove(path);
    }

    SECTION("unknown extension") {
        auto error = std::move(ecitygml::GmlWriter::from_path("out.txt").err().value());
        REQUIRE(error->kind() == ErrorKind::InvalidArgument);
        REQUIRE_THAT(error->message(), ContainsSubstring("txt"));
    }
}
