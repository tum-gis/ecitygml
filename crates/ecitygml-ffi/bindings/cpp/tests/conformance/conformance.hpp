// Helpers of the conformance suite (crates/ecitygml/tests/conformance/README.md).
#pragma once

#include "test_helpers.hpp"

#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <ecitygml/AbstractSpaceBoundaryKind.hpp>
#include <ecitygml/AbstractSpaceBoundaryProperty.hpp>
#include <ecitygml/AbstractSpaceBoundaryPropertyIterator.hpp>
#include <ecitygml/Building.hpp>
#include <ecitygml/Code.hpp>
#include <ecitygml/CodeIterator.hpp>

#include <memory>
#include <string>
#include <vector>

namespace conformance {

/// The tolerance of floating point comparisons in the case lists.
inline constexpr double tolerance = 1e-6;

/// Reads `tests/fixtures/<dataset>/<file>`.
inline std::unique_ptr<ecitygml::CityModel> read(const std::string& dataset, const std::string& file) {
    return ::read(fixture(dataset + "/" + file));
}

inline Catch::Matchers::WithinAbsMatcher close(double expected) { return Catch::Matchers::WithinAbs(expected, tolerance); }

/// The city model's first building; the model must outlive it.
inline const ecitygml::Building* building(const ecitygml::CityModel& city_model) {
    auto features = city_model.iter_features();
    while (auto feature = features->next()) {
        if (const auto* building = ecitygml::Building::try_from(*feature)) {
            return building;
        }
    }
    FAIL("no building");
    return nullptr;
}

/// The building's boundaries, as features.
inline std::vector<std::unique_ptr<ecitygml::AbstractFeatureKindRef>> boundaries(const ecitygml::Building& building) {
    std::vector<std::unique_ptr<ecitygml::AbstractFeatureKindRef>> result;
    auto properties = building.boundaries();
    while (const auto* property = properties->next()) {
        result.push_back(ecitygml::AbstractFeatureKindRef::from_space_boundary(*property->object()));
    }
    return result;
}

/// All features of the city model; the model must outlive them.
inline std::vector<std::unique_ptr<ecitygml::AbstractFeatureKindRef>> features(const ecitygml::CityModel& city_model) {
    std::vector<std::unique_ptr<ecitygml::AbstractFeatureKindRef>> result;
    auto iterator = city_model.iter_features();
    while (auto feature = iterator->next()) {
        result.push_back(std::move(feature));
    }
    return result;
}

/// The first of a feature's names (`names()`).
template <typename T>
std::string first_name(const T& feature) {
    auto names = feature.names();
    const auto* name = names->next();
    REQUIRE(name != nullptr);
    return std::string(name->value());
}

}  // namespace conformance
