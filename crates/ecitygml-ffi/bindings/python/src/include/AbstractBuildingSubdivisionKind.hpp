#ifndef ECITYGML_AbstractBuildingSubdivisionKind_HPP
#define ECITYGML_AbstractBuildingSubdivisionKind_HPP

#include "AbstractBuildingSubdivisionKind.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "AbstractSpaceBoundaryPropertyIterator.hpp"
#include "BoundingShape.hpp"
#include "BuildingSubdivisionClassValue.hpp"
#include "BuildingSubdivisionFunctionValueIterator.hpp"
#include "BuildingSubdivisionUsageValueIterator.hpp"
#include "CityObjectRelationPropertyIterator.hpp"
#include "CodeIterator.hpp"
#include "DateTime.hpp"
#include "ExternalReferenceIterator.hpp"
#include "FeatureType.hpp"
#include "GenericAttributeKindIterator.hpp"
#include "Id.hpp"
#include "MultiCurveProperty.hpp"
#include "MultiSurfaceProperty.hpp"
#include "PointProperty.hpp"
#include "RelativeToTerrain.hpp"
#include "RelativeToWater.hpp"
#include "SolidProperty.hpp"
#include "SpaceType.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_AbstractBuildingSubdivisionKind_id(const ecitygml::capi::AbstractBuildingSubdivisionKind* self);

    ecitygml::capi::CodeIterator* ecitygml_AbstractBuildingSubdivisionKind_names(const ecitygml::capi::AbstractBuildingSubdivisionKind* self);

    const ecitygml::capi::BoundingShape* ecitygml_AbstractBuildingSubdivisionKind_bounded_by(const ecitygml::capi::AbstractBuildingSubdivisionKind* self);

    const ecitygml::capi::Id* ecitygml_AbstractBuildingSubdivisionKind_feature_id(const ecitygml::capi::AbstractBuildingSubdivisionKind* self);

    const ecitygml::capi::DateTime* ecitygml_AbstractBuildingSubdivisionKind_creation_date(const ecitygml::capi::AbstractBuildingSubdivisionKind* self);

    const ecitygml::capi::DateTime* ecitygml_AbstractBuildingSubdivisionKind_termination_date(const ecitygml::capi::AbstractBuildingSubdivisionKind* self);

    const ecitygml::capi::DateTime* ecitygml_AbstractBuildingSubdivisionKind_valid_from(const ecitygml::capi::AbstractBuildingSubdivisionKind* self);

    const ecitygml::capi::DateTime* ecitygml_AbstractBuildingSubdivisionKind_valid_to(const ecitygml::capi::AbstractBuildingSubdivisionKind* self);

    typedef struct ecitygml_AbstractBuildingSubdivisionKind_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_AbstractBuildingSubdivisionKind_relative_to_terrain_result;
    ecitygml_AbstractBuildingSubdivisionKind_relative_to_terrain_result ecitygml_AbstractBuildingSubdivisionKind_relative_to_terrain(const ecitygml::capi::AbstractBuildingSubdivisionKind* self);

    typedef struct ecitygml_AbstractBuildingSubdivisionKind_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_AbstractBuildingSubdivisionKind_relative_to_water_result;
    ecitygml_AbstractBuildingSubdivisionKind_relative_to_water_result ecitygml_AbstractBuildingSubdivisionKind_relative_to_water(const ecitygml::capi::AbstractBuildingSubdivisionKind* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_AbstractBuildingSubdivisionKind_external_references(const ecitygml::capi::AbstractBuildingSubdivisionKind* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_AbstractBuildingSubdivisionKind_generic_attributes(const ecitygml::capi::AbstractBuildingSubdivisionKind* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_AbstractBuildingSubdivisionKind_related_to(const ecitygml::capi::AbstractBuildingSubdivisionKind* self);

    typedef struct ecitygml_AbstractBuildingSubdivisionKind_space_type_result {union {ecitygml::capi::SpaceType ok; }; bool is_ok;} ecitygml_AbstractBuildingSubdivisionKind_space_type_result;
    ecitygml_AbstractBuildingSubdivisionKind_space_type_result ecitygml_AbstractBuildingSubdivisionKind_space_type(const ecitygml::capi::AbstractBuildingSubdivisionKind* self);

    const ecitygml::capi::SolidProperty* ecitygml_AbstractBuildingSubdivisionKind_lod1_solid(const ecitygml::capi::AbstractBuildingSubdivisionKind* self);

    const ecitygml::capi::SolidProperty* ecitygml_AbstractBuildingSubdivisionKind_lod2_solid(const ecitygml::capi::AbstractBuildingSubdivisionKind* self);

    const ecitygml::capi::SolidProperty* ecitygml_AbstractBuildingSubdivisionKind_lod3_solid(const ecitygml::capi::AbstractBuildingSubdivisionKind* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_AbstractBuildingSubdivisionKind_lod0_multi_surface(const ecitygml::capi::AbstractBuildingSubdivisionKind* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_AbstractBuildingSubdivisionKind_lod2_multi_surface(const ecitygml::capi::AbstractBuildingSubdivisionKind* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_AbstractBuildingSubdivisionKind_lod3_multi_surface(const ecitygml::capi::AbstractBuildingSubdivisionKind* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_AbstractBuildingSubdivisionKind_lod0_multi_curve(const ecitygml::capi::AbstractBuildingSubdivisionKind* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_AbstractBuildingSubdivisionKind_lod2_multi_curve(const ecitygml::capi::AbstractBuildingSubdivisionKind* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_AbstractBuildingSubdivisionKind_lod3_multi_curve(const ecitygml::capi::AbstractBuildingSubdivisionKind* self);

    const ecitygml::capi::PointProperty* ecitygml_AbstractBuildingSubdivisionKind_lod0_point(const ecitygml::capi::AbstractBuildingSubdivisionKind* self);

    ecitygml::capi::AbstractSpaceBoundaryPropertyIterator* ecitygml_AbstractBuildingSubdivisionKind_boundaries(const ecitygml::capi::AbstractBuildingSubdivisionKind* self);

    const ecitygml::capi::BuildingSubdivisionClassValue* ecitygml_AbstractBuildingSubdivisionKind_class(const ecitygml::capi::AbstractBuildingSubdivisionKind* self);

    ecitygml::capi::BuildingSubdivisionFunctionValueIterator* ecitygml_AbstractBuildingSubdivisionKind_functions(const ecitygml::capi::AbstractBuildingSubdivisionKind* self);

    ecitygml::capi::BuildingSubdivisionUsageValueIterator* ecitygml_AbstractBuildingSubdivisionKind_usages(const ecitygml::capi::AbstractBuildingSubdivisionKind* self);

    ecitygml::capi::FeatureType ecitygml_AbstractBuildingSubdivisionKind_feature_type(const ecitygml::capi::AbstractBuildingSubdivisionKind* self);

    void ecitygml_AbstractBuildingSubdivisionKind_destroy(AbstractBuildingSubdivisionKind* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::AbstractBuildingSubdivisionKind::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionKind_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::AbstractBuildingSubdivisionKind::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionKind_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::AbstractBuildingSubdivisionKind::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionKind_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::AbstractBuildingSubdivisionKind::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionKind_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::AbstractBuildingSubdivisionKind::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionKind_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::AbstractBuildingSubdivisionKind::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionKind_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::AbstractBuildingSubdivisionKind::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionKind_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::AbstractBuildingSubdivisionKind::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionKind_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::AbstractBuildingSubdivisionKind::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionKind_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::AbstractBuildingSubdivisionKind::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionKind_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::AbstractBuildingSubdivisionKind::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionKind_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::AbstractBuildingSubdivisionKind::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionKind_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::AbstractBuildingSubdivisionKind::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionKind_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline std::optional<ecitygml::SpaceType> ecitygml::AbstractBuildingSubdivisionKind::space_type() const {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionKind_space_type(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::SpaceType>(ecitygml::SpaceType::FromFFI(result.ok)) : std::nullopt;
}

inline const ecitygml::SolidProperty* ecitygml::AbstractBuildingSubdivisionKind::lod1_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionKind_lod1_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::AbstractBuildingSubdivisionKind::lod2_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionKind_lod2_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::AbstractBuildingSubdivisionKind::lod3_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionKind_lod3_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::AbstractBuildingSubdivisionKind::lod0_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionKind_lod0_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::AbstractBuildingSubdivisionKind::lod2_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionKind_lod2_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::AbstractBuildingSubdivisionKind::lod3_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionKind_lod3_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::AbstractBuildingSubdivisionKind::lod0_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionKind_lod0_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::AbstractBuildingSubdivisionKind::lod2_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionKind_lod2_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::AbstractBuildingSubdivisionKind::lod3_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionKind_lod3_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::PointProperty* ecitygml::AbstractBuildingSubdivisionKind::lod0_point() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionKind_lod0_point(this->AsFFI());
    return ecitygml::PointProperty::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator> ecitygml::AbstractBuildingSubdivisionKind::boundaries() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionKind_boundaries(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator>(ecitygml::AbstractSpaceBoundaryPropertyIterator::FromFFI(result));
}

inline const ecitygml::BuildingSubdivisionClassValue* ecitygml::AbstractBuildingSubdivisionKind::class_() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionKind_class(this->AsFFI());
    return ecitygml::BuildingSubdivisionClassValue::FromFFI(result);
}

inline std::unique_ptr<ecitygml::BuildingSubdivisionFunctionValueIterator> ecitygml::AbstractBuildingSubdivisionKind::functions() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionKind_functions(this->AsFFI());
    return std::unique_ptr<ecitygml::BuildingSubdivisionFunctionValueIterator>(ecitygml::BuildingSubdivisionFunctionValueIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::BuildingSubdivisionUsageValueIterator> ecitygml::AbstractBuildingSubdivisionKind::usages() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionKind_usages(this->AsFFI());
    return std::unique_ptr<ecitygml::BuildingSubdivisionUsageValueIterator>(ecitygml::BuildingSubdivisionUsageValueIterator::FromFFI(result));
}

inline ecitygml::FeatureType ecitygml::AbstractBuildingSubdivisionKind::feature_type() const {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionKind_feature_type(this->AsFFI());
    return ecitygml::FeatureType::FromFFI(result);
}

inline const ecitygml::capi::AbstractBuildingSubdivisionKind* ecitygml::AbstractBuildingSubdivisionKind::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AbstractBuildingSubdivisionKind*>(this);
}

inline ecitygml::capi::AbstractBuildingSubdivisionKind* ecitygml::AbstractBuildingSubdivisionKind::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AbstractBuildingSubdivisionKind*>(this);
}

inline const ecitygml::AbstractBuildingSubdivisionKind* ecitygml::AbstractBuildingSubdivisionKind::FromFFI(const ecitygml::capi::AbstractBuildingSubdivisionKind* ptr) {
    return reinterpret_cast<const ecitygml::AbstractBuildingSubdivisionKind*>(ptr);
}

inline ecitygml::AbstractBuildingSubdivisionKind* ecitygml::AbstractBuildingSubdivisionKind::FromFFI(ecitygml::capi::AbstractBuildingSubdivisionKind* ptr) {
    return reinterpret_cast<ecitygml::AbstractBuildingSubdivisionKind*>(ptr);
}

inline void ecitygml::AbstractBuildingSubdivisionKind::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AbstractBuildingSubdivisionKind_destroy(reinterpret_cast<ecitygml::capi::AbstractBuildingSubdivisionKind*>(ptr));
}


#endif // ECITYGML_AbstractBuildingSubdivisionKind_HPP
