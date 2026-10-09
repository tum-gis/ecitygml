#ifndef ECITYGML_AbstractFillingSurfaceKind_HPP
#define ECITYGML_AbstractFillingSurfaceKind_HPP

#include "AbstractFillingSurfaceKind.d.hpp"

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
#include "MultiCurveProperty.hpp"
#include "MultiSurfaceProperty.hpp"
#include "RelativeToTerrain.hpp"
#include "RelativeToWater.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_AbstractFillingSurfaceKind_id(const ecitygml::capi::AbstractFillingSurfaceKind* self);

    ecitygml::capi::CodeIterator* ecitygml_AbstractFillingSurfaceKind_names(const ecitygml::capi::AbstractFillingSurfaceKind* self);

    const ecitygml::capi::BoundingShape* ecitygml_AbstractFillingSurfaceKind_bounded_by(const ecitygml::capi::AbstractFillingSurfaceKind* self);

    const ecitygml::capi::Id* ecitygml_AbstractFillingSurfaceKind_feature_id(const ecitygml::capi::AbstractFillingSurfaceKind* self);

    const ecitygml::capi::DateTime* ecitygml_AbstractFillingSurfaceKind_creation_date(const ecitygml::capi::AbstractFillingSurfaceKind* self);

    const ecitygml::capi::DateTime* ecitygml_AbstractFillingSurfaceKind_termination_date(const ecitygml::capi::AbstractFillingSurfaceKind* self);

    const ecitygml::capi::DateTime* ecitygml_AbstractFillingSurfaceKind_valid_from(const ecitygml::capi::AbstractFillingSurfaceKind* self);

    const ecitygml::capi::DateTime* ecitygml_AbstractFillingSurfaceKind_valid_to(const ecitygml::capi::AbstractFillingSurfaceKind* self);

    typedef struct ecitygml_AbstractFillingSurfaceKind_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_AbstractFillingSurfaceKind_relative_to_terrain_result;
    ecitygml_AbstractFillingSurfaceKind_relative_to_terrain_result ecitygml_AbstractFillingSurfaceKind_relative_to_terrain(const ecitygml::capi::AbstractFillingSurfaceKind* self);

    typedef struct ecitygml_AbstractFillingSurfaceKind_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_AbstractFillingSurfaceKind_relative_to_water_result;
    ecitygml_AbstractFillingSurfaceKind_relative_to_water_result ecitygml_AbstractFillingSurfaceKind_relative_to_water(const ecitygml::capi::AbstractFillingSurfaceKind* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_AbstractFillingSurfaceKind_external_references(const ecitygml::capi::AbstractFillingSurfaceKind* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_AbstractFillingSurfaceKind_generic_attributes(const ecitygml::capi::AbstractFillingSurfaceKind* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_AbstractFillingSurfaceKind_related_to(const ecitygml::capi::AbstractFillingSurfaceKind* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_AbstractFillingSurfaceKind_lod0_multi_curve(const ecitygml::capi::AbstractFillingSurfaceKind* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_AbstractFillingSurfaceKind_lod0_multi_surface(const ecitygml::capi::AbstractFillingSurfaceKind* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_AbstractFillingSurfaceKind_lod1_multi_surface(const ecitygml::capi::AbstractFillingSurfaceKind* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_AbstractFillingSurfaceKind_lod2_multi_surface(const ecitygml::capi::AbstractFillingSurfaceKind* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_AbstractFillingSurfaceKind_lod3_multi_surface(const ecitygml::capi::AbstractFillingSurfaceKind* self);

    ecitygml::capi::FeatureType ecitygml_AbstractFillingSurfaceKind_feature_type(const ecitygml::capi::AbstractFillingSurfaceKind* self);

    void ecitygml_AbstractFillingSurfaceKind_destroy(AbstractFillingSurfaceKind* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::AbstractFillingSurfaceKind::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractFillingSurfaceKind_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::AbstractFillingSurfaceKind::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractFillingSurfaceKind_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::AbstractFillingSurfaceKind::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractFillingSurfaceKind_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::AbstractFillingSurfaceKind::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractFillingSurfaceKind_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::AbstractFillingSurfaceKind::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractFillingSurfaceKind_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::AbstractFillingSurfaceKind::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractFillingSurfaceKind_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::AbstractFillingSurfaceKind::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractFillingSurfaceKind_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::AbstractFillingSurfaceKind::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractFillingSurfaceKind_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::AbstractFillingSurfaceKind::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_AbstractFillingSurfaceKind_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::AbstractFillingSurfaceKind::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_AbstractFillingSurfaceKind_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::AbstractFillingSurfaceKind::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractFillingSurfaceKind_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::AbstractFillingSurfaceKind::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractFillingSurfaceKind_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::AbstractFillingSurfaceKind::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractFillingSurfaceKind_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline const ecitygml::MultiCurveProperty* ecitygml::AbstractFillingSurfaceKind::lod0_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractFillingSurfaceKind_lod0_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::AbstractFillingSurfaceKind::lod0_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractFillingSurfaceKind_lod0_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::AbstractFillingSurfaceKind::lod1_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractFillingSurfaceKind_lod1_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::AbstractFillingSurfaceKind::lod2_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractFillingSurfaceKind_lod2_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::AbstractFillingSurfaceKind::lod3_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractFillingSurfaceKind_lod3_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline ecitygml::FeatureType ecitygml::AbstractFillingSurfaceKind::feature_type() const {
    auto result = ecitygml::capi::ecitygml_AbstractFillingSurfaceKind_feature_type(this->AsFFI());
    return ecitygml::FeatureType::FromFFI(result);
}

inline const ecitygml::capi::AbstractFillingSurfaceKind* ecitygml::AbstractFillingSurfaceKind::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AbstractFillingSurfaceKind*>(this);
}

inline ecitygml::capi::AbstractFillingSurfaceKind* ecitygml::AbstractFillingSurfaceKind::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AbstractFillingSurfaceKind*>(this);
}

inline const ecitygml::AbstractFillingSurfaceKind* ecitygml::AbstractFillingSurfaceKind::FromFFI(const ecitygml::capi::AbstractFillingSurfaceKind* ptr) {
    return reinterpret_cast<const ecitygml::AbstractFillingSurfaceKind*>(ptr);
}

inline ecitygml::AbstractFillingSurfaceKind* ecitygml::AbstractFillingSurfaceKind::FromFFI(ecitygml::capi::AbstractFillingSurfaceKind* ptr) {
    return reinterpret_cast<ecitygml::AbstractFillingSurfaceKind*>(ptr);
}

inline void ecitygml::AbstractFillingSurfaceKind::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AbstractFillingSurfaceKind_destroy(reinterpret_cast<ecitygml::capi::AbstractFillingSurfaceKind*>(ptr));
}


#endif // ECITYGML_AbstractFillingSurfaceKind_HPP
