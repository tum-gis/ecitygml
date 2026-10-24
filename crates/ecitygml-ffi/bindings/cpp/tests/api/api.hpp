// Helpers of the API suite (crates/ecitygml/tests/api/README.md).
#pragma once

#include "test_helpers.hpp"

#include <catch2/matchers/catch_matchers_string.hpp>

#include <ecitygml/ErrorKind.hpp>
#include <ecitygml/FeatureType.hpp>

#include <atomic>
#include <chrono>
#include <cstddef>
#include <vector>

/// The content of the file at `path`.
inline std::vector<uint8_t> read_bytes(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    REQUIRE(file.good());
    return {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
}

/// `GmlReader::new(data, format).finish()`; fails the test on errors.
inline std::unique_ptr<ecitygml::CityModel> read_data(diplomat::span<const uint8_t> data,
                                                      ecitygml::CitygmlFormat format) {
    auto city_model = ecitygml::GmlReader::create(data, format)->finish();
    REQUIRE(city_model.is_ok());
    return std::move(city_model).ok().value();
}

inline std::unique_ptr<ecitygml::CityModel> read_data(const std::vector<uint8_t>& data, ecitygml::CitygmlFormat format) {
    return read_data(diplomat::span<const uint8_t>(data.data(), data.size()), format);
}

inline std::vector<ecitygml::FeatureType> feature_types(const ecitygml::CityModel& city_model) {
    std::vector<ecitygml::FeatureType> types;
    auto features = city_model.iter_features();
    while (auto feature = features->next()) {
        types.push_back(feature->feature_type());
    }
    return types;
}

/// Asserts the error's kind and that its message contains `part`.
inline void require_error(const ecitygml::Error& error, ecitygml::ErrorKind kind, const std::string& part) {
    REQUIRE(error.kind() == kind);
    REQUIRE_THAT(error.message(), Catch::Matchers::ContainsSubstring(part));
}

/// The error of a failed result.
template <typename T>
std::unique_ptr<ecitygml::Error> error_of(diplomat::result<T, std::unique_ptr<ecitygml::Error>> result) {
    REQUIRE(result.is_err());
    return std::move(std::move(result).err().value());
}

/// A fresh temporary directory, removed when it goes out of scope.
class TempDir {
public:
    TempDir() {
        static std::atomic<int> next{0};
        path_ = std::filesystem::temp_directory_path() /
                ("ecitygml-cpp-api-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()) +
                 "-" + std::to_string(next++));
        std::filesystem::create_directories(path_);
    }
    ~TempDir() { std::filesystem::remove_all(path_); }
    TempDir(const TempDir&) = delete;
    TempDir& operator=(const TempDir&) = delete;

    /// The path of `name` in the directory.
    std::string path(const std::string& name) const { return (path_ / name).string(); }

private:
    std::filesystem::path path_;
};
