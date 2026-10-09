#ifndef ECITYGML_AbstractReliefComponentKind_HPP
#define ECITYGML_AbstractReliefComponentKind_HPP

#include "AbstractReliefComponentKind.d.hpp"

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
#include "LevelOfDetail.hpp"
#include "RelativeToTerrain.hpp"
#include "RelativeToWater.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_AbstractReliefComponentKind_id(const ecitygml::capi::AbstractReliefComponentKind* self);

    ecitygml::capi::CodeIterator* ecitygml_AbstractReliefComponentKind_names(const ecitygml::capi::AbstractReliefComponentKind* self);

    const ecitygml::capi::BoundingShape* ecitygml_AbstractReliefComponentKind_bounded_by(const ecitygml::capi::AbstractReliefComponentKind* self);

    const ecitygml::capi::Id* ecitygml_AbstractReliefComponentKind_feature_id(const ecitygml::capi::AbstractReliefComponentKind* self);

    const ecitygml::capi::DateTime* ecitygml_AbstractReliefComponentKind_creation_date(const ecitygml::capi::AbstractReliefComponentKind* self);

    const ecitygml::capi::DateTime* ecitygml_AbstractReliefComponentKind_termination_date(const ecitygml::capi::AbstractReliefComponentKind* self);

    const ecitygml::capi::DateTime* ecitygml_AbstractReliefComponentKind_valid_from(const ecitygml::capi::AbstractReliefComponentKind* self);

    const ecitygml::capi::DateTime* ecitygml_AbstractReliefComponentKind_valid_to(const ecitygml::capi::AbstractReliefComponentKind* self);

    typedef struct ecitygml_AbstractReliefComponentKind_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_AbstractReliefComponentKind_relative_to_terrain_result;
    ecitygml_AbstractReliefComponentKind_relative_to_terrain_result ecitygml_AbstractReliefComponentKind_relative_to_terrain(const ecitygml::capi::AbstractReliefComponentKind* self);

    typedef struct ecitygml_AbstractReliefComponentKind_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_AbstractReliefComponentKind_relative_to_water_result;
    ecitygml_AbstractReliefComponentKind_relative_to_water_result ecitygml_AbstractReliefComponentKind_relative_to_water(const ecitygml::capi::AbstractReliefComponentKind* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_AbstractReliefComponentKind_external_references(const ecitygml::capi::AbstractReliefComponentKind* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_AbstractReliefComponentKind_generic_attributes(const ecitygml::capi::AbstractReliefComponentKind* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_AbstractReliefComponentKind_related_to(const ecitygml::capi::AbstractReliefComponentKind* self);

    ecitygml::capi::LevelOfDetail ecitygml_AbstractReliefComponentKind_lod(const ecitygml::capi::AbstractReliefComponentKind* self);

    ecitygml::capi::FeatureType ecitygml_AbstractReliefComponentKind_feature_type(const ecitygml::capi::AbstractReliefComponentKind* self);

    void ecitygml_AbstractReliefComponentKind_destroy(AbstractReliefComponentKind* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::AbstractReliefComponentKind::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractReliefComponentKind_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::AbstractReliefComponentKind::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractReliefComponentKind_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::AbstractReliefComponentKind::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractReliefComponentKind_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::AbstractReliefComponentKind::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractReliefComponentKind_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::AbstractReliefComponentKind::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractReliefComponentKind_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::AbstractReliefComponentKind::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractReliefComponentKind_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::AbstractReliefComponentKind::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractReliefComponentKind_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::AbstractReliefComponentKind::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractReliefComponentKind_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::AbstractReliefComponentKind::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_AbstractReliefComponentKind_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::AbstractReliefComponentKind::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_AbstractReliefComponentKind_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::AbstractReliefComponentKind::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractReliefComponentKind_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::AbstractReliefComponentKind::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractReliefComponentKind_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::AbstractReliefComponentKind::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractReliefComponentKind_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline ecitygml::LevelOfDetail ecitygml::AbstractReliefComponentKind::lod() const {
    auto result = ecitygml::capi::ecitygml_AbstractReliefComponentKind_lod(this->AsFFI());
    return ecitygml::LevelOfDetail::FromFFI(result);
}

inline ecitygml::FeatureType ecitygml::AbstractReliefComponentKind::feature_type() const {
    auto result = ecitygml::capi::ecitygml_AbstractReliefComponentKind_feature_type(this->AsFFI());
    return ecitygml::FeatureType::FromFFI(result);
}

inline const ecitygml::capi::AbstractReliefComponentKind* ecitygml::AbstractReliefComponentKind::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AbstractReliefComponentKind*>(this);
}

inline ecitygml::capi::AbstractReliefComponentKind* ecitygml::AbstractReliefComponentKind::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AbstractReliefComponentKind*>(this);
}

inline const ecitygml::AbstractReliefComponentKind* ecitygml::AbstractReliefComponentKind::FromFFI(const ecitygml::capi::AbstractReliefComponentKind* ptr) {
    return reinterpret_cast<const ecitygml::AbstractReliefComponentKind*>(ptr);
}

inline ecitygml::AbstractReliefComponentKind* ecitygml::AbstractReliefComponentKind::FromFFI(ecitygml::capi::AbstractReliefComponentKind* ptr) {
    return reinterpret_cast<ecitygml::AbstractReliefComponentKind*>(ptr);
}

inline void ecitygml::AbstractReliefComponentKind::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AbstractReliefComponentKind_destroy(reinterpret_cast<ecitygml::capi::AbstractReliefComponentKind*>(ptr));
}


#endif // ECITYGML_AbstractReliefComponentKind_HPP
