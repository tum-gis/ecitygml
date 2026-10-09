#ifndef ecitygml_TrafficArea_HPP
#define ecitygml_TrafficArea_HPP

#include "TrafficArea.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "AbstractFeatureKindRef.hpp"
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
#include "TrafficAreaClassValue.hpp"
#include "TrafficAreaFunctionValueIterator.hpp"
#include "TrafficAreaUsageValueIterator.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_TrafficArea_id(const ecitygml::capi::TrafficArea* self);

    ecitygml::capi::CodeIterator* ecitygml_TrafficArea_names(const ecitygml::capi::TrafficArea* self);

    const ecitygml::capi::BoundingShape* ecitygml_TrafficArea_bounded_by(const ecitygml::capi::TrafficArea* self);

    const ecitygml::capi::Id* ecitygml_TrafficArea_feature_id(const ecitygml::capi::TrafficArea* self);

    const ecitygml::capi::DateTime* ecitygml_TrafficArea_creation_date(const ecitygml::capi::TrafficArea* self);

    const ecitygml::capi::DateTime* ecitygml_TrafficArea_termination_date(const ecitygml::capi::TrafficArea* self);

    const ecitygml::capi::DateTime* ecitygml_TrafficArea_valid_from(const ecitygml::capi::TrafficArea* self);

    const ecitygml::capi::DateTime* ecitygml_TrafficArea_valid_to(const ecitygml::capi::TrafficArea* self);

    typedef struct ecitygml_TrafficArea_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_TrafficArea_relative_to_terrain_result;
    ecitygml_TrafficArea_relative_to_terrain_result ecitygml_TrafficArea_relative_to_terrain(const ecitygml::capi::TrafficArea* self);

    typedef struct ecitygml_TrafficArea_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_TrafficArea_relative_to_water_result;
    ecitygml_TrafficArea_relative_to_water_result ecitygml_TrafficArea_relative_to_water(const ecitygml::capi::TrafficArea* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_TrafficArea_external_references(const ecitygml::capi::TrafficArea* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_TrafficArea_generic_attributes(const ecitygml::capi::TrafficArea* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_TrafficArea_related_to(const ecitygml::capi::TrafficArea* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_TrafficArea_lod0_multi_curve(const ecitygml::capi::TrafficArea* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_TrafficArea_lod0_multi_surface(const ecitygml::capi::TrafficArea* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_TrafficArea_lod1_multi_surface(const ecitygml::capi::TrafficArea* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_TrafficArea_lod2_multi_surface(const ecitygml::capi::TrafficArea* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_TrafficArea_lod3_multi_surface(const ecitygml::capi::TrafficArea* self);

    const ecitygml::capi::TrafficArea* ecitygml_TrafficArea_try_from(const ecitygml::capi::AbstractFeatureKindRef* feature);

    const ecitygml::capi::TrafficAreaClassValue* ecitygml_TrafficArea_class(const ecitygml::capi::TrafficArea* self);

    ecitygml::capi::TrafficAreaFunctionValueIterator* ecitygml_TrafficArea_functions(const ecitygml::capi::TrafficArea* self);

    ecitygml::capi::TrafficAreaUsageValueIterator* ecitygml_TrafficArea_usages(const ecitygml::capi::TrafficArea* self);

    const ecitygml::capi::SurfaceMaterialValue* ecitygml_TrafficArea_surface_material(const ecitygml::capi::TrafficArea* self);

    void ecitygml_TrafficArea_destroy(TrafficArea* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::TrafficArea::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficArea_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::TrafficArea::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficArea_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::TrafficArea::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficArea_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::TrafficArea::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficArea_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::TrafficArea::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficArea_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::TrafficArea::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficArea_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::TrafficArea::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficArea_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::TrafficArea::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficArea_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::TrafficArea::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_TrafficArea_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::TrafficArea::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_TrafficArea_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::TrafficArea::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficArea_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::TrafficArea::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficArea_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::TrafficArea::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficArea_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline const ecitygml::MultiCurveProperty* ecitygml::TrafficArea::lod0_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficArea_lod0_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::TrafficArea::lod0_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficArea_lod0_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::TrafficArea::lod1_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficArea_lod1_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::TrafficArea::lod2_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficArea_lod2_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::TrafficArea::lod3_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficArea_lod3_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::TrafficArea* ecitygml::TrafficArea::try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_TrafficArea_try_from(feature.AsFFI());
    return ecitygml::TrafficArea::FromFFI(result);
}

inline const ecitygml::TrafficAreaClassValue* ecitygml::TrafficArea::class_() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficArea_class(this->AsFFI());
    return ecitygml::TrafficAreaClassValue::FromFFI(result);
}

inline std::unique_ptr<ecitygml::TrafficAreaFunctionValueIterator> ecitygml::TrafficArea::functions() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficArea_functions(this->AsFFI());
    return std::unique_ptr<ecitygml::TrafficAreaFunctionValueIterator>(ecitygml::TrafficAreaFunctionValueIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::TrafficAreaUsageValueIterator> ecitygml::TrafficArea::usages() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficArea_usages(this->AsFFI());
    return std::unique_ptr<ecitygml::TrafficAreaUsageValueIterator>(ecitygml::TrafficAreaUsageValueIterator::FromFFI(result));
}

inline const ecitygml::SurfaceMaterialValue* ecitygml::TrafficArea::surface_material() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficArea_surface_material(this->AsFFI());
    return ecitygml::SurfaceMaterialValue::FromFFI(result);
}

inline const ecitygml::capi::TrafficArea* ecitygml::TrafficArea::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::TrafficArea*>(this);
}

inline ecitygml::capi::TrafficArea* ecitygml::TrafficArea::AsFFI() {
    return reinterpret_cast<ecitygml::capi::TrafficArea*>(this);
}

inline const ecitygml::TrafficArea* ecitygml::TrafficArea::FromFFI(const ecitygml::capi::TrafficArea* ptr) {
    return reinterpret_cast<const ecitygml::TrafficArea*>(ptr);
}

inline ecitygml::TrafficArea* ecitygml::TrafficArea::FromFFI(ecitygml::capi::TrafficArea* ptr) {
    return reinterpret_cast<ecitygml::TrafficArea*>(ptr);
}

inline void ecitygml::TrafficArea::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_TrafficArea_destroy(reinterpret_cast<ecitygml::capi::TrafficArea*>(ptr));
}


#endif // ecitygml_TrafficArea_HPP
