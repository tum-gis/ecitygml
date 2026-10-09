#ifndef ecitygml_BuildingUnit_HPP
#define ecitygml_BuildingUnit_HPP

#include "BuildingUnit.d.hpp"

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
#include "AbstractSpaceBoundaryPropertyIterator.hpp"
#include "BoundingShape.hpp"
#include "BuildingSubdivisionClassValue.hpp"
#include "BuildingSubdivisionFunctionValueIterator.hpp"
#include "BuildingSubdivisionUsageValueIterator.hpp"
#include "CityObjectRelationPropertyIterator.hpp"
#include "CodeIterator.hpp"
#include "DateTime.hpp"
#include "ExternalReferenceIterator.hpp"
#include "GenericAttributeKindIterator.hpp"
#include "Id.hpp"
#include "MultiCurveProperty.hpp"
#include "MultiSurfaceProperty.hpp"
#include "PointProperty.hpp"
#include "RelativeToTerrain.hpp"
#include "RelativeToWater.hpp"
#include "SolidProperty.hpp"
#include "SpaceType.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_BuildingUnit_id(const ecitygml::capi::BuildingUnit* self);

    ecitygml::capi::CodeIterator* ecitygml_BuildingUnit_names(const ecitygml::capi::BuildingUnit* self);

    const ecitygml::capi::BoundingShape* ecitygml_BuildingUnit_bounded_by(const ecitygml::capi::BuildingUnit* self);

    const ecitygml::capi::Id* ecitygml_BuildingUnit_feature_id(const ecitygml::capi::BuildingUnit* self);

    const ecitygml::capi::DateTime* ecitygml_BuildingUnit_creation_date(const ecitygml::capi::BuildingUnit* self);

    const ecitygml::capi::DateTime* ecitygml_BuildingUnit_termination_date(const ecitygml::capi::BuildingUnit* self);

    const ecitygml::capi::DateTime* ecitygml_BuildingUnit_valid_from(const ecitygml::capi::BuildingUnit* self);

    const ecitygml::capi::DateTime* ecitygml_BuildingUnit_valid_to(const ecitygml::capi::BuildingUnit* self);

    typedef struct ecitygml_BuildingUnit_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_BuildingUnit_relative_to_terrain_result;
    ecitygml_BuildingUnit_relative_to_terrain_result ecitygml_BuildingUnit_relative_to_terrain(const ecitygml::capi::BuildingUnit* self);

    typedef struct ecitygml_BuildingUnit_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_BuildingUnit_relative_to_water_result;
    ecitygml_BuildingUnit_relative_to_water_result ecitygml_BuildingUnit_relative_to_water(const ecitygml::capi::BuildingUnit* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_BuildingUnit_external_references(const ecitygml::capi::BuildingUnit* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_BuildingUnit_generic_attributes(const ecitygml::capi::BuildingUnit* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_BuildingUnit_related_to(const ecitygml::capi::BuildingUnit* self);

    typedef struct ecitygml_BuildingUnit_space_type_result {union {ecitygml::capi::SpaceType ok; }; bool is_ok;} ecitygml_BuildingUnit_space_type_result;
    ecitygml_BuildingUnit_space_type_result ecitygml_BuildingUnit_space_type(const ecitygml::capi::BuildingUnit* self);

    const ecitygml::capi::SolidProperty* ecitygml_BuildingUnit_lod1_solid(const ecitygml::capi::BuildingUnit* self);

    const ecitygml::capi::SolidProperty* ecitygml_BuildingUnit_lod2_solid(const ecitygml::capi::BuildingUnit* self);

    const ecitygml::capi::SolidProperty* ecitygml_BuildingUnit_lod3_solid(const ecitygml::capi::BuildingUnit* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_BuildingUnit_lod0_multi_surface(const ecitygml::capi::BuildingUnit* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_BuildingUnit_lod2_multi_surface(const ecitygml::capi::BuildingUnit* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_BuildingUnit_lod3_multi_surface(const ecitygml::capi::BuildingUnit* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_BuildingUnit_lod0_multi_curve(const ecitygml::capi::BuildingUnit* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_BuildingUnit_lod2_multi_curve(const ecitygml::capi::BuildingUnit* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_BuildingUnit_lod3_multi_curve(const ecitygml::capi::BuildingUnit* self);

    const ecitygml::capi::PointProperty* ecitygml_BuildingUnit_lod0_point(const ecitygml::capi::BuildingUnit* self);

    ecitygml::capi::AbstractSpaceBoundaryPropertyIterator* ecitygml_BuildingUnit_boundaries(const ecitygml::capi::BuildingUnit* self);

    const ecitygml::capi::BuildingSubdivisionClassValue* ecitygml_BuildingUnit_class(const ecitygml::capi::BuildingUnit* self);

    ecitygml::capi::BuildingSubdivisionFunctionValueIterator* ecitygml_BuildingUnit_functions(const ecitygml::capi::BuildingUnit* self);

    ecitygml::capi::BuildingSubdivisionUsageValueIterator* ecitygml_BuildingUnit_usages(const ecitygml::capi::BuildingUnit* self);

    const ecitygml::capi::BuildingUnit* ecitygml_BuildingUnit_try_from(const ecitygml::capi::AbstractFeatureKindRef* feature);

    void ecitygml_BuildingUnit_destroy(BuildingUnit* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::BuildingUnit::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingUnit_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::BuildingUnit::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingUnit_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::BuildingUnit::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingUnit_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::BuildingUnit::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingUnit_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::BuildingUnit::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingUnit_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::BuildingUnit::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingUnit_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::BuildingUnit::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingUnit_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::BuildingUnit::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingUnit_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::BuildingUnit::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_BuildingUnit_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::BuildingUnit::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_BuildingUnit_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::BuildingUnit::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingUnit_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::BuildingUnit::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingUnit_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::BuildingUnit::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingUnit_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline std::optional<ecitygml::SpaceType> ecitygml::BuildingUnit::space_type() const {
    auto result = ecitygml::capi::ecitygml_BuildingUnit_space_type(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::SpaceType>(ecitygml::SpaceType::FromFFI(result.ok)) : std::nullopt;
}

inline const ecitygml::SolidProperty* ecitygml::BuildingUnit::lod1_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingUnit_lod1_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::BuildingUnit::lod2_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingUnit_lod2_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::BuildingUnit::lod3_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingUnit_lod3_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::BuildingUnit::lod0_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingUnit_lod0_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::BuildingUnit::lod2_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingUnit_lod2_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::BuildingUnit::lod3_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingUnit_lod3_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::BuildingUnit::lod0_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingUnit_lod0_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::BuildingUnit::lod2_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingUnit_lod2_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::BuildingUnit::lod3_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingUnit_lod3_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::PointProperty* ecitygml::BuildingUnit::lod0_point() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingUnit_lod0_point(this->AsFFI());
    return ecitygml::PointProperty::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator> ecitygml::BuildingUnit::boundaries() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingUnit_boundaries(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator>(ecitygml::AbstractSpaceBoundaryPropertyIterator::FromFFI(result));
}

inline const ecitygml::BuildingSubdivisionClassValue* ecitygml::BuildingUnit::class_() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingUnit_class(this->AsFFI());
    return ecitygml::BuildingSubdivisionClassValue::FromFFI(result);
}

inline std::unique_ptr<ecitygml::BuildingSubdivisionFunctionValueIterator> ecitygml::BuildingUnit::functions() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingUnit_functions(this->AsFFI());
    return std::unique_ptr<ecitygml::BuildingSubdivisionFunctionValueIterator>(ecitygml::BuildingSubdivisionFunctionValueIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::BuildingSubdivisionUsageValueIterator> ecitygml::BuildingUnit::usages() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingUnit_usages(this->AsFFI());
    return std::unique_ptr<ecitygml::BuildingSubdivisionUsageValueIterator>(ecitygml::BuildingSubdivisionUsageValueIterator::FromFFI(result));
}

inline const ecitygml::BuildingUnit* ecitygml::BuildingUnit::try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_BuildingUnit_try_from(feature.AsFFI());
    return ecitygml::BuildingUnit::FromFFI(result);
}

inline const ecitygml::capi::BuildingUnit* ecitygml::BuildingUnit::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::BuildingUnit*>(this);
}

inline ecitygml::capi::BuildingUnit* ecitygml::BuildingUnit::AsFFI() {
    return reinterpret_cast<ecitygml::capi::BuildingUnit*>(this);
}

inline const ecitygml::BuildingUnit* ecitygml::BuildingUnit::FromFFI(const ecitygml::capi::BuildingUnit* ptr) {
    return reinterpret_cast<const ecitygml::BuildingUnit*>(ptr);
}

inline ecitygml::BuildingUnit* ecitygml::BuildingUnit::FromFFI(ecitygml::capi::BuildingUnit* ptr) {
    return reinterpret_cast<ecitygml::BuildingUnit*>(ptr);
}

inline void ecitygml::BuildingUnit::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_BuildingUnit_destroy(reinterpret_cast<ecitygml::capi::BuildingUnit*>(ptr));
}


#endif // ecitygml_BuildingUnit_HPP
