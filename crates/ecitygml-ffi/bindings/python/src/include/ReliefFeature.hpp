#ifndef ECITYGML_ReliefFeature_HPP
#define ECITYGML_ReliefFeature_HPP

#include "ReliefFeature.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "AbstractFeatureKindRef.hpp"
#include "AbstractReliefComponentPropertyIterator.hpp"
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
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_ReliefFeature_id(const ecitygml::capi::ReliefFeature* self);

    ecitygml::capi::CodeIterator* ecitygml_ReliefFeature_names(const ecitygml::capi::ReliefFeature* self);

    const ecitygml::capi::BoundingShape* ecitygml_ReliefFeature_bounded_by(const ecitygml::capi::ReliefFeature* self);

    const ecitygml::capi::Id* ecitygml_ReliefFeature_feature_id(const ecitygml::capi::ReliefFeature* self);

    const ecitygml::capi::DateTime* ecitygml_ReliefFeature_creation_date(const ecitygml::capi::ReliefFeature* self);

    const ecitygml::capi::DateTime* ecitygml_ReliefFeature_termination_date(const ecitygml::capi::ReliefFeature* self);

    const ecitygml::capi::DateTime* ecitygml_ReliefFeature_valid_from(const ecitygml::capi::ReliefFeature* self);

    const ecitygml::capi::DateTime* ecitygml_ReliefFeature_valid_to(const ecitygml::capi::ReliefFeature* self);

    typedef struct ecitygml_ReliefFeature_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_ReliefFeature_relative_to_terrain_result;
    ecitygml_ReliefFeature_relative_to_terrain_result ecitygml_ReliefFeature_relative_to_terrain(const ecitygml::capi::ReliefFeature* self);

    typedef struct ecitygml_ReliefFeature_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_ReliefFeature_relative_to_water_result;
    ecitygml_ReliefFeature_relative_to_water_result ecitygml_ReliefFeature_relative_to_water(const ecitygml::capi::ReliefFeature* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_ReliefFeature_external_references(const ecitygml::capi::ReliefFeature* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_ReliefFeature_generic_attributes(const ecitygml::capi::ReliefFeature* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_ReliefFeature_related_to(const ecitygml::capi::ReliefFeature* self);

    const ecitygml::capi::ReliefFeature* ecitygml_ReliefFeature_try_from(const ecitygml::capi::AbstractFeatureKindRef* feature);

    ecitygml::capi::LevelOfDetail ecitygml_ReliefFeature_lod(const ecitygml::capi::ReliefFeature* self);

    ecitygml::capi::AbstractReliefComponentPropertyIterator* ecitygml_ReliefFeature_relief_components(const ecitygml::capi::ReliefFeature* self);

    void ecitygml_ReliefFeature_destroy(ReliefFeature* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::ReliefFeature::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_ReliefFeature_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::ReliefFeature::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_ReliefFeature_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::ReliefFeature::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_ReliefFeature_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::ReliefFeature::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_ReliefFeature_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::ReliefFeature::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_ReliefFeature_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::ReliefFeature::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_ReliefFeature_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::ReliefFeature::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_ReliefFeature_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::ReliefFeature::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_ReliefFeature_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::ReliefFeature::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_ReliefFeature_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::ReliefFeature::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_ReliefFeature_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::ReliefFeature::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_ReliefFeature_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::ReliefFeature::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_ReliefFeature_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::ReliefFeature::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_ReliefFeature_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline const ecitygml::ReliefFeature* ecitygml::ReliefFeature::try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_ReliefFeature_try_from(feature.AsFFI());
    return ecitygml::ReliefFeature::FromFFI(result);
}

inline ecitygml::LevelOfDetail ecitygml::ReliefFeature::lod() const {
    auto result = ecitygml::capi::ecitygml_ReliefFeature_lod(this->AsFFI());
    return ecitygml::LevelOfDetail::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AbstractReliefComponentPropertyIterator> ecitygml::ReliefFeature::relief_components() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_ReliefFeature_relief_components(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractReliefComponentPropertyIterator>(ecitygml::AbstractReliefComponentPropertyIterator::FromFFI(result));
}

inline const ecitygml::capi::ReliefFeature* ecitygml::ReliefFeature::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::ReliefFeature*>(this);
}

inline ecitygml::capi::ReliefFeature* ecitygml::ReliefFeature::AsFFI() {
    return reinterpret_cast<ecitygml::capi::ReliefFeature*>(this);
}

inline const ecitygml::ReliefFeature* ecitygml::ReliefFeature::FromFFI(const ecitygml::capi::ReliefFeature* ptr) {
    return reinterpret_cast<const ecitygml::ReliefFeature*>(ptr);
}

inline ecitygml::ReliefFeature* ecitygml::ReliefFeature::FromFFI(ecitygml::capi::ReliefFeature* ptr) {
    return reinterpret_cast<ecitygml::ReliefFeature*>(ptr);
}

inline void ecitygml::ReliefFeature::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_ReliefFeature_destroy(reinterpret_cast<ecitygml::capi::ReliefFeature*>(ptr));
}


#endif // ECITYGML_ReliefFeature_HPP
