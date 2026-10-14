#ifndef ecitygml_AbstractCityObjectKind_HPP
#define ecitygml_AbstractCityObjectKind_HPP

#include "AbstractCityObjectKind.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "BoundingShape.hpp"
#include "CityObjectRelationPropertyIterator.hpp"
#include "CodeIterator.hpp"
#include "DateTime.hpp"
#include "ExternalReferenceIterator.hpp"
#include "FeatureType.hpp"
#include "GenericAttributeKindIterator.hpp"
#include "Id.hpp"
#include "RelativeToTerrain.hpp"
#include "RelativeToWater.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_AbstractCityObjectKind_id(const ecitygml::capi::AbstractCityObjectKind* self);

    ecitygml::capi::CodeIterator* ecitygml_AbstractCityObjectKind_names(const ecitygml::capi::AbstractCityObjectKind* self);

    const ecitygml::capi::BoundingShape* ecitygml_AbstractCityObjectKind_bounded_by(const ecitygml::capi::AbstractCityObjectKind* self);

    const ecitygml::capi::Id* ecitygml_AbstractCityObjectKind_feature_id(const ecitygml::capi::AbstractCityObjectKind* self);

    const ecitygml::capi::DateTime* ecitygml_AbstractCityObjectKind_creation_date(const ecitygml::capi::AbstractCityObjectKind* self);

    const ecitygml::capi::DateTime* ecitygml_AbstractCityObjectKind_termination_date(const ecitygml::capi::AbstractCityObjectKind* self);

    const ecitygml::capi::DateTime* ecitygml_AbstractCityObjectKind_valid_from(const ecitygml::capi::AbstractCityObjectKind* self);

    const ecitygml::capi::DateTime* ecitygml_AbstractCityObjectKind_valid_to(const ecitygml::capi::AbstractCityObjectKind* self);

    typedef struct ecitygml_AbstractCityObjectKind_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_AbstractCityObjectKind_relative_to_terrain_result;
    ecitygml_AbstractCityObjectKind_relative_to_terrain_result ecitygml_AbstractCityObjectKind_relative_to_terrain(const ecitygml::capi::AbstractCityObjectKind* self);

    typedef struct ecitygml_AbstractCityObjectKind_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_AbstractCityObjectKind_relative_to_water_result;
    ecitygml_AbstractCityObjectKind_relative_to_water_result ecitygml_AbstractCityObjectKind_relative_to_water(const ecitygml::capi::AbstractCityObjectKind* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_AbstractCityObjectKind_external_references(const ecitygml::capi::AbstractCityObjectKind* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_AbstractCityObjectKind_generic_attributes(const ecitygml::capi::AbstractCityObjectKind* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_AbstractCityObjectKind_related_to(const ecitygml::capi::AbstractCityObjectKind* self);

    ecitygml::capi::FeatureType ecitygml_AbstractCityObjectKind_feature_type(const ecitygml::capi::AbstractCityObjectKind* self);

    void ecitygml_AbstractCityObjectKind_destroy(AbstractCityObjectKind* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::AbstractCityObjectKind::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractCityObjectKind_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::AbstractCityObjectKind::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractCityObjectKind_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::AbstractCityObjectKind::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractCityObjectKind_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::AbstractCityObjectKind::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractCityObjectKind_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::AbstractCityObjectKind::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractCityObjectKind_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::AbstractCityObjectKind::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractCityObjectKind_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::AbstractCityObjectKind::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractCityObjectKind_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::AbstractCityObjectKind::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractCityObjectKind_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::AbstractCityObjectKind::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_AbstractCityObjectKind_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::AbstractCityObjectKind::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_AbstractCityObjectKind_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::AbstractCityObjectKind::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractCityObjectKind_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::AbstractCityObjectKind::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractCityObjectKind_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::AbstractCityObjectKind::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractCityObjectKind_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline ecitygml::FeatureType ecitygml::AbstractCityObjectKind::feature_type() const {
    auto result = ecitygml::capi::ecitygml_AbstractCityObjectKind_feature_type(this->AsFFI());
    return ecitygml::FeatureType::FromFFI(result);
}

inline const ecitygml::capi::AbstractCityObjectKind* ecitygml::AbstractCityObjectKind::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AbstractCityObjectKind*>(this);
}

inline ecitygml::capi::AbstractCityObjectKind* ecitygml::AbstractCityObjectKind::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AbstractCityObjectKind*>(this);
}

inline const ecitygml::AbstractCityObjectKind* ecitygml::AbstractCityObjectKind::FromFFI(const ecitygml::capi::AbstractCityObjectKind* ptr) {
    return reinterpret_cast<const ecitygml::AbstractCityObjectKind*>(ptr);
}

inline ecitygml::AbstractCityObjectKind* ecitygml::AbstractCityObjectKind::FromFFI(ecitygml::capi::AbstractCityObjectKind* ptr) {
    return reinterpret_cast<ecitygml::AbstractCityObjectKind*>(ptr);
}

inline void ecitygml::AbstractCityObjectKind::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AbstractCityObjectKind_destroy(reinterpret_cast<ecitygml::capi::AbstractCityObjectKind*>(ptr));
}


#endif // ecitygml_AbstractCityObjectKind_HPP
