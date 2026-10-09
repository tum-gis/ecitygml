#ifndef ecitygml_Storey_HPP
#define ecitygml_Storey_HPP

#include "Storey.d.hpp"

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

    const ecitygml::capi::Id* ecitygml_Storey_id(const ecitygml::capi::Storey* self);

    ecitygml::capi::CodeIterator* ecitygml_Storey_names(const ecitygml::capi::Storey* self);

    const ecitygml::capi::BoundingShape* ecitygml_Storey_bounded_by(const ecitygml::capi::Storey* self);

    const ecitygml::capi::Id* ecitygml_Storey_feature_id(const ecitygml::capi::Storey* self);

    const ecitygml::capi::DateTime* ecitygml_Storey_creation_date(const ecitygml::capi::Storey* self);

    const ecitygml::capi::DateTime* ecitygml_Storey_termination_date(const ecitygml::capi::Storey* self);

    const ecitygml::capi::DateTime* ecitygml_Storey_valid_from(const ecitygml::capi::Storey* self);

    const ecitygml::capi::DateTime* ecitygml_Storey_valid_to(const ecitygml::capi::Storey* self);

    typedef struct ecitygml_Storey_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_Storey_relative_to_terrain_result;
    ecitygml_Storey_relative_to_terrain_result ecitygml_Storey_relative_to_terrain(const ecitygml::capi::Storey* self);

    typedef struct ecitygml_Storey_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_Storey_relative_to_water_result;
    ecitygml_Storey_relative_to_water_result ecitygml_Storey_relative_to_water(const ecitygml::capi::Storey* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_Storey_external_references(const ecitygml::capi::Storey* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_Storey_generic_attributes(const ecitygml::capi::Storey* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_Storey_related_to(const ecitygml::capi::Storey* self);

    typedef struct ecitygml_Storey_space_type_result {union {ecitygml::capi::SpaceType ok; }; bool is_ok;} ecitygml_Storey_space_type_result;
    ecitygml_Storey_space_type_result ecitygml_Storey_space_type(const ecitygml::capi::Storey* self);

    const ecitygml::capi::SolidProperty* ecitygml_Storey_lod1_solid(const ecitygml::capi::Storey* self);

    const ecitygml::capi::SolidProperty* ecitygml_Storey_lod2_solid(const ecitygml::capi::Storey* self);

    const ecitygml::capi::SolidProperty* ecitygml_Storey_lod3_solid(const ecitygml::capi::Storey* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_Storey_lod0_multi_surface(const ecitygml::capi::Storey* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_Storey_lod2_multi_surface(const ecitygml::capi::Storey* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_Storey_lod3_multi_surface(const ecitygml::capi::Storey* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Storey_lod0_multi_curve(const ecitygml::capi::Storey* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Storey_lod2_multi_curve(const ecitygml::capi::Storey* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Storey_lod3_multi_curve(const ecitygml::capi::Storey* self);

    const ecitygml::capi::PointProperty* ecitygml_Storey_lod0_point(const ecitygml::capi::Storey* self);

    ecitygml::capi::AbstractSpaceBoundaryPropertyIterator* ecitygml_Storey_boundaries(const ecitygml::capi::Storey* self);

    const ecitygml::capi::BuildingSubdivisionClassValue* ecitygml_Storey_class(const ecitygml::capi::Storey* self);

    ecitygml::capi::BuildingSubdivisionFunctionValueIterator* ecitygml_Storey_functions(const ecitygml::capi::Storey* self);

    ecitygml::capi::BuildingSubdivisionUsageValueIterator* ecitygml_Storey_usages(const ecitygml::capi::Storey* self);

    const ecitygml::capi::Storey* ecitygml_Storey_try_from(const ecitygml::capi::AbstractFeatureKindRef* feature);

    void ecitygml_Storey_destroy(Storey* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::Storey::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Storey_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::Storey::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Storey_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::Storey::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Storey_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::Storey::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Storey_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Storey::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Storey_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Storey::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Storey_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Storey::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Storey_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Storey::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Storey_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::Storey::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_Storey_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::Storey::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_Storey_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::Storey::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Storey_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::Storey::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Storey_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::Storey::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Storey_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline std::optional<ecitygml::SpaceType> ecitygml::Storey::space_type() const {
    auto result = ecitygml::capi::ecitygml_Storey_space_type(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::SpaceType>(ecitygml::SpaceType::FromFFI(result.ok)) : std::nullopt;
}

inline const ecitygml::SolidProperty* ecitygml::Storey::lod1_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Storey_lod1_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::Storey::lod2_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Storey_lod2_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::Storey::lod3_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Storey_lod3_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::Storey::lod0_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Storey_lod0_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::Storey::lod2_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Storey_lod2_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::Storey::lod3_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Storey_lod3_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Storey::lod0_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Storey_lod0_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Storey::lod2_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Storey_lod2_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Storey::lod3_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Storey_lod3_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::PointProperty* ecitygml::Storey::lod0_point() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Storey_lod0_point(this->AsFFI());
    return ecitygml::PointProperty::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator> ecitygml::Storey::boundaries() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Storey_boundaries(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator>(ecitygml::AbstractSpaceBoundaryPropertyIterator::FromFFI(result));
}

inline const ecitygml::BuildingSubdivisionClassValue* ecitygml::Storey::class_() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Storey_class(this->AsFFI());
    return ecitygml::BuildingSubdivisionClassValue::FromFFI(result);
}

inline std::unique_ptr<ecitygml::BuildingSubdivisionFunctionValueIterator> ecitygml::Storey::functions() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Storey_functions(this->AsFFI());
    return std::unique_ptr<ecitygml::BuildingSubdivisionFunctionValueIterator>(ecitygml::BuildingSubdivisionFunctionValueIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::BuildingSubdivisionUsageValueIterator> ecitygml::Storey::usages() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Storey_usages(this->AsFFI());
    return std::unique_ptr<ecitygml::BuildingSubdivisionUsageValueIterator>(ecitygml::BuildingSubdivisionUsageValueIterator::FromFFI(result));
}

inline const ecitygml::Storey* ecitygml::Storey::try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_Storey_try_from(feature.AsFFI());
    return ecitygml::Storey::FromFFI(result);
}

inline const ecitygml::capi::Storey* ecitygml::Storey::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::Storey*>(this);
}

inline ecitygml::capi::Storey* ecitygml::Storey::AsFFI() {
    return reinterpret_cast<ecitygml::capi::Storey*>(this);
}

inline const ecitygml::Storey* ecitygml::Storey::FromFFI(const ecitygml::capi::Storey* ptr) {
    return reinterpret_cast<const ecitygml::Storey*>(ptr);
}

inline ecitygml::Storey* ecitygml::Storey::FromFFI(ecitygml::capi::Storey* ptr) {
    return reinterpret_cast<ecitygml::Storey*>(ptr);
}

inline void ecitygml::Storey::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_Storey_destroy(reinterpret_cast<ecitygml::capi::Storey*>(ptr));
}


#endif // ecitygml_Storey_HPP
