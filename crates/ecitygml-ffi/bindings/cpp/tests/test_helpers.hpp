#pragma once

#include <catch2/catch_test_macros.hpp>

#include <ecitygml/CityModel.hpp>
#include <ecitygml/Error.hpp>
#include <ecitygml/AbstractFeatureKindRef.hpp>
#include <ecitygml/AbstractFeatureKindRefIterator.hpp>
#include <ecitygml/CitygmlFormat.hpp>
#include <ecitygml/GmlReader.hpp>

#include <filesystem>
#include <fstream>
#include <memory>
#include <sstream>
#include <cstdint>
#include <string>
#include <utility>

inline std::string fixture(const std::string& name) { return std::string(ECITYGML_FIXTURES) + "/" + name; }

/// `GmlReader::from_path(path)?.finish()`, as in Rust; fails the test on errors.
inline std::unique_ptr<ecitygml::CityModel> read(const std::string& path) {
    auto reader = ecitygml::GmlReader::from_path(path);
    REQUIRE(reader.is_ok());
    auto city_model = std::move(reader).ok().value()->finish();
    REQUIRE(city_model.is_ok());
    return std::move(std::move(city_model).ok().value());
}

/// Reads a temporary copy of the fixture with the first `from` replaced by `to`.
inline std::unique_ptr<ecitygml::CityModel> read_modified(const std::string& name, const std::string& from,
                                                          const std::string& to) {
    std::ifstream input(fixture(name));
    std::stringstream buffer;
    buffer << input.rdbuf();
    std::string content = buffer.str();
    content.replace(content.find(from), from.size(), to);

    const auto path = std::filesystem::temp_directory_path() / ("ecitygml-ffi-cpp-" + std::to_string(to.size()) + ".gml");
    std::ofstream(path) << content;
    auto city_model = read(path.string());
    std::filesystem::remove(path);
    return city_model;
}

/// A model with the FZK LoD2 header and `member` as its only city object (no fixture has one).
inline std::unique_ptr<ecitygml::CityModel> read_member(const std::string& member) {
    std::ifstream input(fixture("FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml"));
    std::stringstream buffer;
    buffer << input.rdbuf();
    const std::string text = buffer.str();
    const std::string content = text.substr(0, text.find("<cityObjectMember>")) + member;
    auto reader = ecitygml::GmlReader::create(
        diplomat::span<const uint8_t>(reinterpret_cast<const uint8_t*>(content.data()), content.size()),
        ecitygml::CitygmlFormat::Gml);
    auto city_model = reader->finish();
    REQUIRE(city_model.is_ok());
    return std::move(city_model).ok().value();
}

template <typename T>
const T* first(const ecitygml::CityModel& city_model) {
    auto features = city_model.iter_features();
    while (auto feature = features->next()) {
        if (const auto* typed = T::try_from(*feature)) {
            return typed;
        }
    }
    return nullptr;
}
