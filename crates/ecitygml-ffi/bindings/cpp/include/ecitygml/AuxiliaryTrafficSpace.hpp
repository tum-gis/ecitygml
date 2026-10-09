#ifndef ecitygml_AuxiliaryTrafficSpace_HPP
#define ecitygml_AuxiliaryTrafficSpace_HPP

#include "AuxiliaryTrafficSpace.d.hpp"

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
#include "AuxiliaryTrafficSpaceClassValue.hpp"
#include "AuxiliaryTrafficSpaceFunctionValueIterator.hpp"
#include "AuxiliaryTrafficSpaceUsageValueIterator.hpp"
#include "BoundingShape.hpp"
#include "CityObjectRelationPropertyIterator.hpp"
#include "CodeIterator.hpp"
#include "DateTime.hpp"
#include "ExternalReferenceIterator.hpp"
#include "GenericAttributeKindIterator.hpp"
#include "GranularityValue.hpp"
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

    const ecitygml::capi::Id* ecitygml_AuxiliaryTrafficSpace_id(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    ecitygml::capi::CodeIterator* ecitygml_AuxiliaryTrafficSpace_names(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    const ecitygml::capi::BoundingShape* ecitygml_AuxiliaryTrafficSpace_bounded_by(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    const ecitygml::capi::Id* ecitygml_AuxiliaryTrafficSpace_feature_id(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    const ecitygml::capi::DateTime* ecitygml_AuxiliaryTrafficSpace_creation_date(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    const ecitygml::capi::DateTime* ecitygml_AuxiliaryTrafficSpace_termination_date(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    const ecitygml::capi::DateTime* ecitygml_AuxiliaryTrafficSpace_valid_from(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    const ecitygml::capi::DateTime* ecitygml_AuxiliaryTrafficSpace_valid_to(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    typedef struct ecitygml_AuxiliaryTrafficSpace_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_AuxiliaryTrafficSpace_relative_to_terrain_result;
    ecitygml_AuxiliaryTrafficSpace_relative_to_terrain_result ecitygml_AuxiliaryTrafficSpace_relative_to_terrain(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    typedef struct ecitygml_AuxiliaryTrafficSpace_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_AuxiliaryTrafficSpace_relative_to_water_result;
    ecitygml_AuxiliaryTrafficSpace_relative_to_water_result ecitygml_AuxiliaryTrafficSpace_relative_to_water(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_AuxiliaryTrafficSpace_external_references(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_AuxiliaryTrafficSpace_generic_attributes(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_AuxiliaryTrafficSpace_related_to(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    typedef struct ecitygml_AuxiliaryTrafficSpace_space_type_result {union {ecitygml::capi::SpaceType ok; }; bool is_ok;} ecitygml_AuxiliaryTrafficSpace_space_type_result;
    ecitygml_AuxiliaryTrafficSpace_space_type_result ecitygml_AuxiliaryTrafficSpace_space_type(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    const ecitygml::capi::SolidProperty* ecitygml_AuxiliaryTrafficSpace_lod1_solid(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    const ecitygml::capi::SolidProperty* ecitygml_AuxiliaryTrafficSpace_lod2_solid(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    const ecitygml::capi::SolidProperty* ecitygml_AuxiliaryTrafficSpace_lod3_solid(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_AuxiliaryTrafficSpace_lod0_multi_surface(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_AuxiliaryTrafficSpace_lod2_multi_surface(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_AuxiliaryTrafficSpace_lod3_multi_surface(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_AuxiliaryTrafficSpace_lod0_multi_curve(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_AuxiliaryTrafficSpace_lod2_multi_curve(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_AuxiliaryTrafficSpace_lod3_multi_curve(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    const ecitygml::capi::PointProperty* ecitygml_AuxiliaryTrafficSpace_lod0_point(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    ecitygml::capi::AbstractSpaceBoundaryPropertyIterator* ecitygml_AuxiliaryTrafficSpace_boundaries(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_AuxiliaryTrafficSpace_lod1_terrain_intersection_curve(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_AuxiliaryTrafficSpace_lod2_terrain_intersection_curve(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_AuxiliaryTrafficSpace_lod3_terrain_intersection_curve(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    const ecitygml::capi::AuxiliaryTrafficSpace* ecitygml_AuxiliaryTrafficSpace_try_from(const ecitygml::capi::AbstractFeatureKindRef* feature);

    const ecitygml::capi::AuxiliaryTrafficSpaceClassValue* ecitygml_AuxiliaryTrafficSpace_class(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    ecitygml::capi::AuxiliaryTrafficSpaceFunctionValueIterator* ecitygml_AuxiliaryTrafficSpace_functions(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    ecitygml::capi::AuxiliaryTrafficSpaceUsageValueIterator* ecitygml_AuxiliaryTrafficSpace_usages(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    ecitygml::capi::GranularityValue ecitygml_AuxiliaryTrafficSpace_granularity(const ecitygml::capi::AuxiliaryTrafficSpace* self);

    void ecitygml_AuxiliaryTrafficSpace_destroy(AuxiliaryTrafficSpace* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::AuxiliaryTrafficSpace::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::AuxiliaryTrafficSpace::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::AuxiliaryTrafficSpace::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::AuxiliaryTrafficSpace::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::AuxiliaryTrafficSpace::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::AuxiliaryTrafficSpace::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::AuxiliaryTrafficSpace::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::AuxiliaryTrafficSpace::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::AuxiliaryTrafficSpace::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::AuxiliaryTrafficSpace::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::AuxiliaryTrafficSpace::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::AuxiliaryTrafficSpace::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::AuxiliaryTrafficSpace::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline std::optional<ecitygml::SpaceType> ecitygml::AuxiliaryTrafficSpace::space_type() const {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_space_type(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::SpaceType>(ecitygml::SpaceType::FromFFI(result.ok)) : std::nullopt;
}

inline const ecitygml::SolidProperty* ecitygml::AuxiliaryTrafficSpace::lod1_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_lod1_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::AuxiliaryTrafficSpace::lod2_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_lod2_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::AuxiliaryTrafficSpace::lod3_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_lod3_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::AuxiliaryTrafficSpace::lod0_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_lod0_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::AuxiliaryTrafficSpace::lod2_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_lod2_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::AuxiliaryTrafficSpace::lod3_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_lod3_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::AuxiliaryTrafficSpace::lod0_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_lod0_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::AuxiliaryTrafficSpace::lod2_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_lod2_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::AuxiliaryTrafficSpace::lod3_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_lod3_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::PointProperty* ecitygml::AuxiliaryTrafficSpace::lod0_point() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_lod0_point(this->AsFFI());
    return ecitygml::PointProperty::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator> ecitygml::AuxiliaryTrafficSpace::boundaries() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_boundaries(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator>(ecitygml::AbstractSpaceBoundaryPropertyIterator::FromFFI(result));
}

inline const ecitygml::MultiCurveProperty* ecitygml::AuxiliaryTrafficSpace::lod1_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_lod1_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::AuxiliaryTrafficSpace::lod2_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_lod2_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::AuxiliaryTrafficSpace::lod3_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_lod3_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::AuxiliaryTrafficSpace* ecitygml::AuxiliaryTrafficSpace::try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_try_from(feature.AsFFI());
    return ecitygml::AuxiliaryTrafficSpace::FromFFI(result);
}

inline const ecitygml::AuxiliaryTrafficSpaceClassValue* ecitygml::AuxiliaryTrafficSpace::class_() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_class(this->AsFFI());
    return ecitygml::AuxiliaryTrafficSpaceClassValue::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AuxiliaryTrafficSpaceFunctionValueIterator> ecitygml::AuxiliaryTrafficSpace::functions() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_functions(this->AsFFI());
    return std::unique_ptr<ecitygml::AuxiliaryTrafficSpaceFunctionValueIterator>(ecitygml::AuxiliaryTrafficSpaceFunctionValueIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::AuxiliaryTrafficSpaceUsageValueIterator> ecitygml::AuxiliaryTrafficSpace::usages() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_usages(this->AsFFI());
    return std::unique_ptr<ecitygml::AuxiliaryTrafficSpaceUsageValueIterator>(ecitygml::AuxiliaryTrafficSpaceUsageValueIterator::FromFFI(result));
}

inline ecitygml::GranularityValue ecitygml::AuxiliaryTrafficSpace::granularity() const {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_granularity(this->AsFFI());
    return ecitygml::GranularityValue::FromFFI(result);
}

inline const ecitygml::capi::AuxiliaryTrafficSpace* ecitygml::AuxiliaryTrafficSpace::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AuxiliaryTrafficSpace*>(this);
}

inline ecitygml::capi::AuxiliaryTrafficSpace* ecitygml::AuxiliaryTrafficSpace::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AuxiliaryTrafficSpace*>(this);
}

inline const ecitygml::AuxiliaryTrafficSpace* ecitygml::AuxiliaryTrafficSpace::FromFFI(const ecitygml::capi::AuxiliaryTrafficSpace* ptr) {
    return reinterpret_cast<const ecitygml::AuxiliaryTrafficSpace*>(ptr);
}

inline ecitygml::AuxiliaryTrafficSpace* ecitygml::AuxiliaryTrafficSpace::FromFFI(ecitygml::capi::AuxiliaryTrafficSpace* ptr) {
    return reinterpret_cast<ecitygml::AuxiliaryTrafficSpace*>(ptr);
}

inline void ecitygml::AuxiliaryTrafficSpace::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AuxiliaryTrafficSpace_destroy(reinterpret_cast<ecitygml::capi::AuxiliaryTrafficSpace*>(ptr));
}


#endif // ecitygml_AuxiliaryTrafficSpace_HPP
