#ifndef ecitygml_TrafficSpace_HPP
#define ecitygml_TrafficSpace_HPP

#include "TrafficSpace.d.hpp"

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
#include "CityObjectRelationPropertyIterator.hpp"
#include "CodeIterator.hpp"
#include "DateTime.hpp"
#include "ExternalReferenceIterator.hpp"
#include "GenericAttributeKindIterator.hpp"
#include "GranularityValue.hpp"
#include "Id.hpp"
#include "MultiCurveProperty.hpp"
#include "MultiSurfaceProperty.hpp"
#include "OccupancyIterator.hpp"
#include "PointProperty.hpp"
#include "RelativeToTerrain.hpp"
#include "RelativeToWater.hpp"
#include "SolidProperty.hpp"
#include "SpaceType.hpp"
#include "TrafficDirectionValue.hpp"
#include "TrafficSpaceClassValue.hpp"
#include "TrafficSpaceFunctionValueIterator.hpp"
#include "TrafficSpaceReferenceIterator.hpp"
#include "TrafficSpaceUsageValueIterator.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_TrafficSpace_id(const ecitygml::capi::TrafficSpace* self);

    ecitygml::capi::CodeIterator* ecitygml_TrafficSpace_names(const ecitygml::capi::TrafficSpace* self);

    const ecitygml::capi::BoundingShape* ecitygml_TrafficSpace_bounded_by(const ecitygml::capi::TrafficSpace* self);

    const ecitygml::capi::Id* ecitygml_TrafficSpace_feature_id(const ecitygml::capi::TrafficSpace* self);

    const ecitygml::capi::DateTime* ecitygml_TrafficSpace_creation_date(const ecitygml::capi::TrafficSpace* self);

    const ecitygml::capi::DateTime* ecitygml_TrafficSpace_termination_date(const ecitygml::capi::TrafficSpace* self);

    const ecitygml::capi::DateTime* ecitygml_TrafficSpace_valid_from(const ecitygml::capi::TrafficSpace* self);

    const ecitygml::capi::DateTime* ecitygml_TrafficSpace_valid_to(const ecitygml::capi::TrafficSpace* self);

    typedef struct ecitygml_TrafficSpace_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_TrafficSpace_relative_to_terrain_result;
    ecitygml_TrafficSpace_relative_to_terrain_result ecitygml_TrafficSpace_relative_to_terrain(const ecitygml::capi::TrafficSpace* self);

    typedef struct ecitygml_TrafficSpace_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_TrafficSpace_relative_to_water_result;
    ecitygml_TrafficSpace_relative_to_water_result ecitygml_TrafficSpace_relative_to_water(const ecitygml::capi::TrafficSpace* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_TrafficSpace_external_references(const ecitygml::capi::TrafficSpace* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_TrafficSpace_generic_attributes(const ecitygml::capi::TrafficSpace* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_TrafficSpace_related_to(const ecitygml::capi::TrafficSpace* self);

    typedef struct ecitygml_TrafficSpace_space_type_result {union {ecitygml::capi::SpaceType ok; }; bool is_ok;} ecitygml_TrafficSpace_space_type_result;
    ecitygml_TrafficSpace_space_type_result ecitygml_TrafficSpace_space_type(const ecitygml::capi::TrafficSpace* self);

    const ecitygml::capi::SolidProperty* ecitygml_TrafficSpace_lod1_solid(const ecitygml::capi::TrafficSpace* self);

    const ecitygml::capi::SolidProperty* ecitygml_TrafficSpace_lod2_solid(const ecitygml::capi::TrafficSpace* self);

    const ecitygml::capi::SolidProperty* ecitygml_TrafficSpace_lod3_solid(const ecitygml::capi::TrafficSpace* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_TrafficSpace_lod0_multi_surface(const ecitygml::capi::TrafficSpace* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_TrafficSpace_lod2_multi_surface(const ecitygml::capi::TrafficSpace* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_TrafficSpace_lod3_multi_surface(const ecitygml::capi::TrafficSpace* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_TrafficSpace_lod0_multi_curve(const ecitygml::capi::TrafficSpace* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_TrafficSpace_lod2_multi_curve(const ecitygml::capi::TrafficSpace* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_TrafficSpace_lod3_multi_curve(const ecitygml::capi::TrafficSpace* self);

    const ecitygml::capi::PointProperty* ecitygml_TrafficSpace_lod0_point(const ecitygml::capi::TrafficSpace* self);

    ecitygml::capi::AbstractSpaceBoundaryPropertyIterator* ecitygml_TrafficSpace_boundaries(const ecitygml::capi::TrafficSpace* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_TrafficSpace_lod1_terrain_intersection_curve(const ecitygml::capi::TrafficSpace* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_TrafficSpace_lod2_terrain_intersection_curve(const ecitygml::capi::TrafficSpace* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_TrafficSpace_lod3_terrain_intersection_curve(const ecitygml::capi::TrafficSpace* self);

    const ecitygml::capi::TrafficSpace* ecitygml_TrafficSpace_try_from(const ecitygml::capi::AbstractFeatureKindRef* feature);

    const ecitygml::capi::TrafficSpaceClassValue* ecitygml_TrafficSpace_class(const ecitygml::capi::TrafficSpace* self);

    ecitygml::capi::TrafficSpaceFunctionValueIterator* ecitygml_TrafficSpace_functions(const ecitygml::capi::TrafficSpace* self);

    ecitygml::capi::TrafficSpaceUsageValueIterator* ecitygml_TrafficSpace_usages(const ecitygml::capi::TrafficSpace* self);

    ecitygml::capi::GranularityValue ecitygml_TrafficSpace_granularity(const ecitygml::capi::TrafficSpace* self);

    typedef struct ecitygml_TrafficSpace_traffic_direction_result {union {ecitygml::capi::TrafficDirectionValue ok; }; bool is_ok;} ecitygml_TrafficSpace_traffic_direction_result;
    ecitygml_TrafficSpace_traffic_direction_result ecitygml_TrafficSpace_traffic_direction(const ecitygml::capi::TrafficSpace* self);

    ecitygml::capi::OccupancyIterator* ecitygml_TrafficSpace_occupancies(const ecitygml::capi::TrafficSpace* self);

    ecitygml::capi::TrafficSpaceReferenceIterator* ecitygml_TrafficSpace_predecessors(const ecitygml::capi::TrafficSpace* self);

    ecitygml::capi::TrafficSpaceReferenceIterator* ecitygml_TrafficSpace_successors(const ecitygml::capi::TrafficSpace* self);

    void ecitygml_TrafficSpace_destroy(TrafficSpace* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::TrafficSpace::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::TrafficSpace::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::TrafficSpace::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::TrafficSpace::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::TrafficSpace::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::TrafficSpace::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::TrafficSpace::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::TrafficSpace::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::TrafficSpace::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::TrafficSpace::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::TrafficSpace::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::TrafficSpace::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::TrafficSpace::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline std::optional<ecitygml::SpaceType> ecitygml::TrafficSpace::space_type() const {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_space_type(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::SpaceType>(ecitygml::SpaceType::FromFFI(result.ok)) : std::nullopt;
}

inline const ecitygml::SolidProperty* ecitygml::TrafficSpace::lod1_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_lod1_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::TrafficSpace::lod2_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_lod2_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::TrafficSpace::lod3_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_lod3_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::TrafficSpace::lod0_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_lod0_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::TrafficSpace::lod2_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_lod2_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::TrafficSpace::lod3_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_lod3_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::TrafficSpace::lod0_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_lod0_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::TrafficSpace::lod2_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_lod2_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::TrafficSpace::lod3_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_lod3_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::PointProperty* ecitygml::TrafficSpace::lod0_point() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_lod0_point(this->AsFFI());
    return ecitygml::PointProperty::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator> ecitygml::TrafficSpace::boundaries() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_boundaries(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator>(ecitygml::AbstractSpaceBoundaryPropertyIterator::FromFFI(result));
}

inline const ecitygml::MultiCurveProperty* ecitygml::TrafficSpace::lod1_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_lod1_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::TrafficSpace::lod2_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_lod2_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::TrafficSpace::lod3_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_lod3_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::TrafficSpace* ecitygml::TrafficSpace::try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_try_from(feature.AsFFI());
    return ecitygml::TrafficSpace::FromFFI(result);
}

inline const ecitygml::TrafficSpaceClassValue* ecitygml::TrafficSpace::class_() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_class(this->AsFFI());
    return ecitygml::TrafficSpaceClassValue::FromFFI(result);
}

inline std::unique_ptr<ecitygml::TrafficSpaceFunctionValueIterator> ecitygml::TrafficSpace::functions() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_functions(this->AsFFI());
    return std::unique_ptr<ecitygml::TrafficSpaceFunctionValueIterator>(ecitygml::TrafficSpaceFunctionValueIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::TrafficSpaceUsageValueIterator> ecitygml::TrafficSpace::usages() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_usages(this->AsFFI());
    return std::unique_ptr<ecitygml::TrafficSpaceUsageValueIterator>(ecitygml::TrafficSpaceUsageValueIterator::FromFFI(result));
}

inline ecitygml::GranularityValue ecitygml::TrafficSpace::granularity() const {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_granularity(this->AsFFI());
    return ecitygml::GranularityValue::FromFFI(result);
}

inline std::optional<ecitygml::TrafficDirectionValue> ecitygml::TrafficSpace::traffic_direction() const {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_traffic_direction(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::TrafficDirectionValue>(ecitygml::TrafficDirectionValue::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::OccupancyIterator> ecitygml::TrafficSpace::occupancies() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_occupancies(this->AsFFI());
    return std::unique_ptr<ecitygml::OccupancyIterator>(ecitygml::OccupancyIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::TrafficSpaceReferenceIterator> ecitygml::TrafficSpace::predecessors() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_predecessors(this->AsFFI());
    return std::unique_ptr<ecitygml::TrafficSpaceReferenceIterator>(ecitygml::TrafficSpaceReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::TrafficSpaceReferenceIterator> ecitygml::TrafficSpace::successors() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpace_successors(this->AsFFI());
    return std::unique_ptr<ecitygml::TrafficSpaceReferenceIterator>(ecitygml::TrafficSpaceReferenceIterator::FromFFI(result));
}

inline const ecitygml::capi::TrafficSpace* ecitygml::TrafficSpace::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::TrafficSpace*>(this);
}

inline ecitygml::capi::TrafficSpace* ecitygml::TrafficSpace::AsFFI() {
    return reinterpret_cast<ecitygml::capi::TrafficSpace*>(this);
}

inline const ecitygml::TrafficSpace* ecitygml::TrafficSpace::FromFFI(const ecitygml::capi::TrafficSpace* ptr) {
    return reinterpret_cast<const ecitygml::TrafficSpace*>(ptr);
}

inline ecitygml::TrafficSpace* ecitygml::TrafficSpace::FromFFI(ecitygml::capi::TrafficSpace* ptr) {
    return reinterpret_cast<ecitygml::TrafficSpace*>(ptr);
}

inline void ecitygml::TrafficSpace::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_TrafficSpace_destroy(reinterpret_cast<ecitygml::capi::TrafficSpace*>(ptr));
}


#endif // ecitygml_TrafficSpace_HPP
