#ifndef ECITYGML_TinRelief_HPP
#define ECITYGML_TinRelief_HPP

#include "TinRelief.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "AbstractFeatureKindRef.hpp"
#include "BoundingShape.hpp"
#include "CityObjectRelationPropertyIterator.hpp"
#include "CodeIterator.hpp"
#include "DateTime.hpp"
#include "ExternalReferenceIterator.hpp"
#include "GenericAttributeKindIterator.hpp"
#include "Id.hpp"
#include "LevelOfDetail.hpp"
#include "RelativeToTerrain.hpp"
#include "RelativeToWater.hpp"
#include "TinProperty.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_TinRelief_id(const ecitygml::capi::TinRelief* self);

    ecitygml::capi::CodeIterator* ecitygml_TinRelief_names(const ecitygml::capi::TinRelief* self);

    const ecitygml::capi::BoundingShape* ecitygml_TinRelief_bounded_by(const ecitygml::capi::TinRelief* self);

    const ecitygml::capi::Id* ecitygml_TinRelief_feature_id(const ecitygml::capi::TinRelief* self);

    const ecitygml::capi::DateTime* ecitygml_TinRelief_creation_date(const ecitygml::capi::TinRelief* self);

    const ecitygml::capi::DateTime* ecitygml_TinRelief_termination_date(const ecitygml::capi::TinRelief* self);

    const ecitygml::capi::DateTime* ecitygml_TinRelief_valid_from(const ecitygml::capi::TinRelief* self);

    const ecitygml::capi::DateTime* ecitygml_TinRelief_valid_to(const ecitygml::capi::TinRelief* self);

    typedef struct ecitygml_TinRelief_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_TinRelief_relative_to_terrain_result;
    ecitygml_TinRelief_relative_to_terrain_result ecitygml_TinRelief_relative_to_terrain(const ecitygml::capi::TinRelief* self);

    typedef struct ecitygml_TinRelief_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_TinRelief_relative_to_water_result;
    ecitygml_TinRelief_relative_to_water_result ecitygml_TinRelief_relative_to_water(const ecitygml::capi::TinRelief* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_TinRelief_external_references(const ecitygml::capi::TinRelief* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_TinRelief_generic_attributes(const ecitygml::capi::TinRelief* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_TinRelief_related_to(const ecitygml::capi::TinRelief* self);

    ecitygml::capi::LevelOfDetail ecitygml_TinRelief_lod(const ecitygml::capi::TinRelief* self);

    const ecitygml::capi::TinRelief* ecitygml_TinRelief_try_from(const ecitygml::capi::AbstractFeatureKindRef* feature);

    const ecitygml::capi::TinProperty* ecitygml_TinRelief_tin(const ecitygml::capi::TinRelief* self);

    void ecitygml_TinRelief_destroy(TinRelief* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::TinRelief::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TinRelief_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::TinRelief::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TinRelief_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::TinRelief::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TinRelief_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::TinRelief::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TinRelief_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::TinRelief::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TinRelief_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::TinRelief::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TinRelief_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::TinRelief::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TinRelief_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::TinRelief::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TinRelief_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::TinRelief::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_TinRelief_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::TinRelief::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_TinRelief_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::TinRelief::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TinRelief_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::TinRelief::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TinRelief_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::TinRelief::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TinRelief_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline ecitygml::LevelOfDetail ecitygml::TinRelief::lod() const {
    auto result = ecitygml::capi::ecitygml_TinRelief_lod(this->AsFFI());
    return ecitygml::LevelOfDetail::FromFFI(result);
}

inline const ecitygml::TinRelief* ecitygml::TinRelief::try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_TinRelief_try_from(feature.AsFFI());
    return ecitygml::TinRelief::FromFFI(result);
}

inline const ecitygml::TinProperty* ecitygml::TinRelief::tin() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TinRelief_tin(this->AsFFI());
    return ecitygml::TinProperty::FromFFI(result);
}

inline const ecitygml::capi::TinRelief* ecitygml::TinRelief::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::TinRelief*>(this);
}

inline ecitygml::capi::TinRelief* ecitygml::TinRelief::AsFFI() {
    return reinterpret_cast<ecitygml::capi::TinRelief*>(this);
}

inline const ecitygml::TinRelief* ecitygml::TinRelief::FromFFI(const ecitygml::capi::TinRelief* ptr) {
    return reinterpret_cast<const ecitygml::TinRelief*>(ptr);
}

inline ecitygml::TinRelief* ecitygml::TinRelief::FromFFI(ecitygml::capi::TinRelief* ptr) {
    return reinterpret_cast<ecitygml::TinRelief*>(ptr);
}

inline void ecitygml::TinRelief::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_TinRelief_destroy(reinterpret_cast<ecitygml::capi::TinRelief*>(ptr));
}


#endif // ECITYGML_TinRelief_HPP
