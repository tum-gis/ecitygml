#ifndef ECITYGML_AbstractSpaceBoundaryKind_HPP
#define ECITYGML_AbstractSpaceBoundaryKind_HPP

#include "AbstractSpaceBoundaryKind.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
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
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_AbstractSpaceBoundaryKind_id(const ecitygml::capi::AbstractSpaceBoundaryKind* self);

    ecitygml::capi::CodeIterator* ecitygml_AbstractSpaceBoundaryKind_names(const ecitygml::capi::AbstractSpaceBoundaryKind* self);

    const ecitygml::capi::BoundingShape* ecitygml_AbstractSpaceBoundaryKind_bounded_by(const ecitygml::capi::AbstractSpaceBoundaryKind* self);

    const ecitygml::capi::Id* ecitygml_AbstractSpaceBoundaryKind_feature_id(const ecitygml::capi::AbstractSpaceBoundaryKind* self);

    const ecitygml::capi::DateTime* ecitygml_AbstractSpaceBoundaryKind_creation_date(const ecitygml::capi::AbstractSpaceBoundaryKind* self);

    const ecitygml::capi::DateTime* ecitygml_AbstractSpaceBoundaryKind_termination_date(const ecitygml::capi::AbstractSpaceBoundaryKind* self);

    const ecitygml::capi::DateTime* ecitygml_AbstractSpaceBoundaryKind_valid_from(const ecitygml::capi::AbstractSpaceBoundaryKind* self);

    const ecitygml::capi::DateTime* ecitygml_AbstractSpaceBoundaryKind_valid_to(const ecitygml::capi::AbstractSpaceBoundaryKind* self);

    typedef struct ecitygml_AbstractSpaceBoundaryKind_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_AbstractSpaceBoundaryKind_relative_to_terrain_result;
    ecitygml_AbstractSpaceBoundaryKind_relative_to_terrain_result ecitygml_AbstractSpaceBoundaryKind_relative_to_terrain(const ecitygml::capi::AbstractSpaceBoundaryKind* self);

    typedef struct ecitygml_AbstractSpaceBoundaryKind_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_AbstractSpaceBoundaryKind_relative_to_water_result;
    ecitygml_AbstractSpaceBoundaryKind_relative_to_water_result ecitygml_AbstractSpaceBoundaryKind_relative_to_water(const ecitygml::capi::AbstractSpaceBoundaryKind* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_AbstractSpaceBoundaryKind_external_references(const ecitygml::capi::AbstractSpaceBoundaryKind* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_AbstractSpaceBoundaryKind_generic_attributes(const ecitygml::capi::AbstractSpaceBoundaryKind* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_AbstractSpaceBoundaryKind_related_to(const ecitygml::capi::AbstractSpaceBoundaryKind* self);

    ecitygml::capi::FeatureType ecitygml_AbstractSpaceBoundaryKind_feature_type(const ecitygml::capi::AbstractSpaceBoundaryKind* self);

    void ecitygml_AbstractSpaceBoundaryKind_destroy(AbstractSpaceBoundaryKind* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::AbstractSpaceBoundaryKind::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractSpaceBoundaryKind_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::AbstractSpaceBoundaryKind::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractSpaceBoundaryKind_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::AbstractSpaceBoundaryKind::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractSpaceBoundaryKind_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::AbstractSpaceBoundaryKind::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractSpaceBoundaryKind_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::AbstractSpaceBoundaryKind::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractSpaceBoundaryKind_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::AbstractSpaceBoundaryKind::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractSpaceBoundaryKind_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::AbstractSpaceBoundaryKind::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractSpaceBoundaryKind_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::AbstractSpaceBoundaryKind::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractSpaceBoundaryKind_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::AbstractSpaceBoundaryKind::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_AbstractSpaceBoundaryKind_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::AbstractSpaceBoundaryKind::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_AbstractSpaceBoundaryKind_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::AbstractSpaceBoundaryKind::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractSpaceBoundaryKind_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::AbstractSpaceBoundaryKind::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractSpaceBoundaryKind_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::AbstractSpaceBoundaryKind::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractSpaceBoundaryKind_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline ecitygml::FeatureType ecitygml::AbstractSpaceBoundaryKind::feature_type() const {
    auto result = ecitygml::capi::ecitygml_AbstractSpaceBoundaryKind_feature_type(this->AsFFI());
    return ecitygml::FeatureType::FromFFI(result);
}

inline const ecitygml::capi::AbstractSpaceBoundaryKind* ecitygml::AbstractSpaceBoundaryKind::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AbstractSpaceBoundaryKind*>(this);
}

inline ecitygml::capi::AbstractSpaceBoundaryKind* ecitygml::AbstractSpaceBoundaryKind::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AbstractSpaceBoundaryKind*>(this);
}

inline const ecitygml::AbstractSpaceBoundaryKind* ecitygml::AbstractSpaceBoundaryKind::FromFFI(const ecitygml::capi::AbstractSpaceBoundaryKind* ptr) {
    return reinterpret_cast<const ecitygml::AbstractSpaceBoundaryKind*>(ptr);
}

inline ecitygml::AbstractSpaceBoundaryKind* ecitygml::AbstractSpaceBoundaryKind::FromFFI(ecitygml::capi::AbstractSpaceBoundaryKind* ptr) {
    return reinterpret_cast<ecitygml::AbstractSpaceBoundaryKind*>(ptr);
}

inline void ecitygml::AbstractSpaceBoundaryKind::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AbstractSpaceBoundaryKind_destroy(reinterpret_cast<ecitygml::capi::AbstractSpaceBoundaryKind*>(ptr));
}


#endif // ECITYGML_AbstractSpaceBoundaryKind_HPP
