#ifndef ECITYGML_AuxiliaryTrafficArea_HPP
#define ECITYGML_AuxiliaryTrafficArea_HPP

#include "AuxiliaryTrafficArea.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "AbstractFeatureKindRef.hpp"
#include "AuxiliaryTrafficAreaClassValue.hpp"
#include "AuxiliaryTrafficAreaFunctionValueIterator.hpp"
#include "AuxiliaryTrafficAreaUsageValueIterator.hpp"
#include "BoundingShape.hpp"
#include "CityObjectRelationPropertyIterator.hpp"
#include "CodeIterator.hpp"
#include "DateTime.hpp"
#include "ExternalReferenceIterator.hpp"
#include "GenericAttributeKindIterator.hpp"
#include "Id.hpp"
#include "MultiCurveProperty.hpp"
#include "MultiSurfaceProperty.hpp"
#include "RelativeToTerrain.hpp"
#include "RelativeToWater.hpp"
#include "SurfaceMaterialValue.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_AuxiliaryTrafficArea_id(const ecitygml::capi::AuxiliaryTrafficArea* self);

    ecitygml::capi::CodeIterator* ecitygml_AuxiliaryTrafficArea_names(const ecitygml::capi::AuxiliaryTrafficArea* self);

    const ecitygml::capi::BoundingShape* ecitygml_AuxiliaryTrafficArea_bounded_by(const ecitygml::capi::AuxiliaryTrafficArea* self);

    const ecitygml::capi::Id* ecitygml_AuxiliaryTrafficArea_feature_id(const ecitygml::capi::AuxiliaryTrafficArea* self);

    const ecitygml::capi::DateTime* ecitygml_AuxiliaryTrafficArea_creation_date(const ecitygml::capi::AuxiliaryTrafficArea* self);

    const ecitygml::capi::DateTime* ecitygml_AuxiliaryTrafficArea_termination_date(const ecitygml::capi::AuxiliaryTrafficArea* self);

    const ecitygml::capi::DateTime* ecitygml_AuxiliaryTrafficArea_valid_from(const ecitygml::capi::AuxiliaryTrafficArea* self);

    const ecitygml::capi::DateTime* ecitygml_AuxiliaryTrafficArea_valid_to(const ecitygml::capi::AuxiliaryTrafficArea* self);

    typedef struct ecitygml_AuxiliaryTrafficArea_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_AuxiliaryTrafficArea_relative_to_terrain_result;
    ecitygml_AuxiliaryTrafficArea_relative_to_terrain_result ecitygml_AuxiliaryTrafficArea_relative_to_terrain(const ecitygml::capi::AuxiliaryTrafficArea* self);

    typedef struct ecitygml_AuxiliaryTrafficArea_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_AuxiliaryTrafficArea_relative_to_water_result;
    ecitygml_AuxiliaryTrafficArea_relative_to_water_result ecitygml_AuxiliaryTrafficArea_relative_to_water(const ecitygml::capi::AuxiliaryTrafficArea* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_AuxiliaryTrafficArea_external_references(const ecitygml::capi::AuxiliaryTrafficArea* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_AuxiliaryTrafficArea_generic_attributes(const ecitygml::capi::AuxiliaryTrafficArea* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_AuxiliaryTrafficArea_related_to(const ecitygml::capi::AuxiliaryTrafficArea* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_AuxiliaryTrafficArea_lod0_multi_curve(const ecitygml::capi::AuxiliaryTrafficArea* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_AuxiliaryTrafficArea_lod0_multi_surface(const ecitygml::capi::AuxiliaryTrafficArea* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_AuxiliaryTrafficArea_lod1_multi_surface(const ecitygml::capi::AuxiliaryTrafficArea* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_AuxiliaryTrafficArea_lod2_multi_surface(const ecitygml::capi::AuxiliaryTrafficArea* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_AuxiliaryTrafficArea_lod3_multi_surface(const ecitygml::capi::AuxiliaryTrafficArea* self);

    const ecitygml::capi::AuxiliaryTrafficArea* ecitygml_AuxiliaryTrafficArea_try_from(const ecitygml::capi::AbstractFeatureKindRef* feature);

    const ecitygml::capi::AuxiliaryTrafficAreaClassValue* ecitygml_AuxiliaryTrafficArea_class(const ecitygml::capi::AuxiliaryTrafficArea* self);

    ecitygml::capi::AuxiliaryTrafficAreaFunctionValueIterator* ecitygml_AuxiliaryTrafficArea_functions(const ecitygml::capi::AuxiliaryTrafficArea* self);

    ecitygml::capi::AuxiliaryTrafficAreaUsageValueIterator* ecitygml_AuxiliaryTrafficArea_usages(const ecitygml::capi::AuxiliaryTrafficArea* self);

    const ecitygml::capi::SurfaceMaterialValue* ecitygml_AuxiliaryTrafficArea_surface_material(const ecitygml::capi::AuxiliaryTrafficArea* self);

    void ecitygml_AuxiliaryTrafficArea_destroy(AuxiliaryTrafficArea* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::AuxiliaryTrafficArea::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficArea_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::AuxiliaryTrafficArea::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficArea_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::AuxiliaryTrafficArea::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficArea_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::AuxiliaryTrafficArea::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficArea_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::AuxiliaryTrafficArea::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficArea_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::AuxiliaryTrafficArea::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficArea_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::AuxiliaryTrafficArea::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficArea_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::AuxiliaryTrafficArea::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficArea_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::AuxiliaryTrafficArea::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficArea_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::AuxiliaryTrafficArea::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficArea_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::AuxiliaryTrafficArea::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficArea_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::AuxiliaryTrafficArea::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficArea_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::AuxiliaryTrafficArea::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficArea_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline const ecitygml::MultiCurveProperty* ecitygml::AuxiliaryTrafficArea::lod0_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficArea_lod0_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::AuxiliaryTrafficArea::lod0_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficArea_lod0_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::AuxiliaryTrafficArea::lod1_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficArea_lod1_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::AuxiliaryTrafficArea::lod2_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficArea_lod2_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::AuxiliaryTrafficArea::lod3_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficArea_lod3_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::AuxiliaryTrafficArea* ecitygml::AuxiliaryTrafficArea::try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficArea_try_from(feature.AsFFI());
    return ecitygml::AuxiliaryTrafficArea::FromFFI(result);
}

inline const ecitygml::AuxiliaryTrafficAreaClassValue* ecitygml::AuxiliaryTrafficArea::class_() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficArea_class(this->AsFFI());
    return ecitygml::AuxiliaryTrafficAreaClassValue::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AuxiliaryTrafficAreaFunctionValueIterator> ecitygml::AuxiliaryTrafficArea::functions() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficArea_functions(this->AsFFI());
    return std::unique_ptr<ecitygml::AuxiliaryTrafficAreaFunctionValueIterator>(ecitygml::AuxiliaryTrafficAreaFunctionValueIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::AuxiliaryTrafficAreaUsageValueIterator> ecitygml::AuxiliaryTrafficArea::usages() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficArea_usages(this->AsFFI());
    return std::unique_ptr<ecitygml::AuxiliaryTrafficAreaUsageValueIterator>(ecitygml::AuxiliaryTrafficAreaUsageValueIterator::FromFFI(result));
}

inline const ecitygml::SurfaceMaterialValue* ecitygml::AuxiliaryTrafficArea::surface_material() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficArea_surface_material(this->AsFFI());
    return ecitygml::SurfaceMaterialValue::FromFFI(result);
}

inline const ecitygml::capi::AuxiliaryTrafficArea* ecitygml::AuxiliaryTrafficArea::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AuxiliaryTrafficArea*>(this);
}

inline ecitygml::capi::AuxiliaryTrafficArea* ecitygml::AuxiliaryTrafficArea::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AuxiliaryTrafficArea*>(this);
}

inline const ecitygml::AuxiliaryTrafficArea* ecitygml::AuxiliaryTrafficArea::FromFFI(const ecitygml::capi::AuxiliaryTrafficArea* ptr) {
    return reinterpret_cast<const ecitygml::AuxiliaryTrafficArea*>(ptr);
}

inline ecitygml::AuxiliaryTrafficArea* ecitygml::AuxiliaryTrafficArea::FromFFI(ecitygml::capi::AuxiliaryTrafficArea* ptr) {
    return reinterpret_cast<ecitygml::AuxiliaryTrafficArea*>(ptr);
}

inline void ecitygml::AuxiliaryTrafficArea::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AuxiliaryTrafficArea_destroy(reinterpret_cast<ecitygml::capi::AuxiliaryTrafficArea*>(ptr));
}


#endif // ECITYGML_AuxiliaryTrafficArea_HPP
