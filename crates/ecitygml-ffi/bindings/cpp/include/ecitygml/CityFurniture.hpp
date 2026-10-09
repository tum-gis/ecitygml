#ifndef ecitygml_CityFurniture_HPP
#define ecitygml_CityFurniture_HPP

#include "CityFurniture.d.hpp"

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
#include "CityFurnitureClassValue.hpp"
#include "CityFurnitureFunctionValueIterator.hpp"
#include "CityFurnitureUsageValueIterator.hpp"
#include "CityObjectRelationPropertyIterator.hpp"
#include "CodeIterator.hpp"
#include "DateTime.hpp"
#include "ExternalReferenceIterator.hpp"
#include "GenericAttributeKindIterator.hpp"
#include "Id.hpp"
#include "ImplicitGeometryProperty.hpp"
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

    const ecitygml::capi::Id* ecitygml_CityFurniture_id(const ecitygml::capi::CityFurniture* self);

    ecitygml::capi::CodeIterator* ecitygml_CityFurniture_names(const ecitygml::capi::CityFurniture* self);

    const ecitygml::capi::BoundingShape* ecitygml_CityFurniture_bounded_by(const ecitygml::capi::CityFurniture* self);

    const ecitygml::capi::Id* ecitygml_CityFurniture_feature_id(const ecitygml::capi::CityFurniture* self);

    const ecitygml::capi::DateTime* ecitygml_CityFurniture_creation_date(const ecitygml::capi::CityFurniture* self);

    const ecitygml::capi::DateTime* ecitygml_CityFurniture_termination_date(const ecitygml::capi::CityFurniture* self);

    const ecitygml::capi::DateTime* ecitygml_CityFurniture_valid_from(const ecitygml::capi::CityFurniture* self);

    const ecitygml::capi::DateTime* ecitygml_CityFurniture_valid_to(const ecitygml::capi::CityFurniture* self);

    typedef struct ecitygml_CityFurniture_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_CityFurniture_relative_to_terrain_result;
    ecitygml_CityFurniture_relative_to_terrain_result ecitygml_CityFurniture_relative_to_terrain(const ecitygml::capi::CityFurniture* self);

    typedef struct ecitygml_CityFurniture_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_CityFurniture_relative_to_water_result;
    ecitygml_CityFurniture_relative_to_water_result ecitygml_CityFurniture_relative_to_water(const ecitygml::capi::CityFurniture* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_CityFurniture_external_references(const ecitygml::capi::CityFurniture* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_CityFurniture_generic_attributes(const ecitygml::capi::CityFurniture* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_CityFurniture_related_to(const ecitygml::capi::CityFurniture* self);

    typedef struct ecitygml_CityFurniture_space_type_result {union {ecitygml::capi::SpaceType ok; }; bool is_ok;} ecitygml_CityFurniture_space_type_result;
    ecitygml_CityFurniture_space_type_result ecitygml_CityFurniture_space_type(const ecitygml::capi::CityFurniture* self);

    const ecitygml::capi::SolidProperty* ecitygml_CityFurniture_lod1_solid(const ecitygml::capi::CityFurniture* self);

    const ecitygml::capi::SolidProperty* ecitygml_CityFurniture_lod2_solid(const ecitygml::capi::CityFurniture* self);

    const ecitygml::capi::SolidProperty* ecitygml_CityFurniture_lod3_solid(const ecitygml::capi::CityFurniture* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_CityFurniture_lod0_multi_surface(const ecitygml::capi::CityFurniture* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_CityFurniture_lod2_multi_surface(const ecitygml::capi::CityFurniture* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_CityFurniture_lod3_multi_surface(const ecitygml::capi::CityFurniture* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_CityFurniture_lod0_multi_curve(const ecitygml::capi::CityFurniture* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_CityFurniture_lod2_multi_curve(const ecitygml::capi::CityFurniture* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_CityFurniture_lod3_multi_curve(const ecitygml::capi::CityFurniture* self);

    const ecitygml::capi::PointProperty* ecitygml_CityFurniture_lod0_point(const ecitygml::capi::CityFurniture* self);

    ecitygml::capi::AbstractSpaceBoundaryPropertyIterator* ecitygml_CityFurniture_boundaries(const ecitygml::capi::CityFurniture* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_CityFurniture_lod1_terrain_intersection_curve(const ecitygml::capi::CityFurniture* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_CityFurniture_lod2_terrain_intersection_curve(const ecitygml::capi::CityFurniture* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_CityFurniture_lod3_terrain_intersection_curve(const ecitygml::capi::CityFurniture* self);

    const ecitygml::capi::ImplicitGeometryProperty* ecitygml_CityFurniture_lod1_implicit_representation(const ecitygml::capi::CityFurniture* self);

    const ecitygml::capi::ImplicitGeometryProperty* ecitygml_CityFurniture_lod2_implicit_representation(const ecitygml::capi::CityFurniture* self);

    const ecitygml::capi::ImplicitGeometryProperty* ecitygml_CityFurniture_lod3_implicit_representation(const ecitygml::capi::CityFurniture* self);

    const ecitygml::capi::CityFurniture* ecitygml_CityFurniture_try_from(const ecitygml::capi::AbstractFeatureKindRef* feature);

    const ecitygml::capi::CityFurnitureClassValue* ecitygml_CityFurniture_class(const ecitygml::capi::CityFurniture* self);

    ecitygml::capi::CityFurnitureFunctionValueIterator* ecitygml_CityFurniture_functions(const ecitygml::capi::CityFurniture* self);

    ecitygml::capi::CityFurnitureUsageValueIterator* ecitygml_CityFurniture_usages(const ecitygml::capi::CityFurniture* self);

    void ecitygml_CityFurniture_destroy(CityFurniture* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::CityFurniture::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurniture_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::CityFurniture::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurniture_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::CityFurniture::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurniture_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::CityFurniture::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurniture_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::CityFurniture::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurniture_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::CityFurniture::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurniture_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::CityFurniture::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurniture_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::CityFurniture::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurniture_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::CityFurniture::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_CityFurniture_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::CityFurniture::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_CityFurniture_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::CityFurniture::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurniture_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::CityFurniture::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurniture_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::CityFurniture::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurniture_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline std::optional<ecitygml::SpaceType> ecitygml::CityFurniture::space_type() const {
    auto result = ecitygml::capi::ecitygml_CityFurniture_space_type(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::SpaceType>(ecitygml::SpaceType::FromFFI(result.ok)) : std::nullopt;
}

inline const ecitygml::SolidProperty* ecitygml::CityFurniture::lod1_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurniture_lod1_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::CityFurniture::lod2_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurniture_lod2_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::CityFurniture::lod3_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurniture_lod3_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::CityFurniture::lod0_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurniture_lod0_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::CityFurniture::lod2_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurniture_lod2_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::CityFurniture::lod3_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurniture_lod3_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::CityFurniture::lod0_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurniture_lod0_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::CityFurniture::lod2_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurniture_lod2_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::CityFurniture::lod3_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurniture_lod3_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::PointProperty* ecitygml::CityFurniture::lod0_point() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurniture_lod0_point(this->AsFFI());
    return ecitygml::PointProperty::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator> ecitygml::CityFurniture::boundaries() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurniture_boundaries(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator>(ecitygml::AbstractSpaceBoundaryPropertyIterator::FromFFI(result));
}

inline const ecitygml::MultiCurveProperty* ecitygml::CityFurniture::lod1_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurniture_lod1_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::CityFurniture::lod2_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurniture_lod2_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::CityFurniture::lod3_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurniture_lod3_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::ImplicitGeometryProperty* ecitygml::CityFurniture::lod1_implicit_representation() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurniture_lod1_implicit_representation(this->AsFFI());
    return ecitygml::ImplicitGeometryProperty::FromFFI(result);
}

inline const ecitygml::ImplicitGeometryProperty* ecitygml::CityFurniture::lod2_implicit_representation() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurniture_lod2_implicit_representation(this->AsFFI());
    return ecitygml::ImplicitGeometryProperty::FromFFI(result);
}

inline const ecitygml::ImplicitGeometryProperty* ecitygml::CityFurniture::lod3_implicit_representation() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurniture_lod3_implicit_representation(this->AsFFI());
    return ecitygml::ImplicitGeometryProperty::FromFFI(result);
}

inline const ecitygml::CityFurniture* ecitygml::CityFurniture::try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_CityFurniture_try_from(feature.AsFFI());
    return ecitygml::CityFurniture::FromFFI(result);
}

inline const ecitygml::CityFurnitureClassValue* ecitygml::CityFurniture::class_() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurniture_class(this->AsFFI());
    return ecitygml::CityFurnitureClassValue::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CityFurnitureFunctionValueIterator> ecitygml::CityFurniture::functions() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurniture_functions(this->AsFFI());
    return std::unique_ptr<ecitygml::CityFurnitureFunctionValueIterator>(ecitygml::CityFurnitureFunctionValueIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityFurnitureUsageValueIterator> ecitygml::CityFurniture::usages() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurniture_usages(this->AsFFI());
    return std::unique_ptr<ecitygml::CityFurnitureUsageValueIterator>(ecitygml::CityFurnitureUsageValueIterator::FromFFI(result));
}

inline const ecitygml::capi::CityFurniture* ecitygml::CityFurniture::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::CityFurniture*>(this);
}

inline ecitygml::capi::CityFurniture* ecitygml::CityFurniture::AsFFI() {
    return reinterpret_cast<ecitygml::capi::CityFurniture*>(this);
}

inline const ecitygml::CityFurniture* ecitygml::CityFurniture::FromFFI(const ecitygml::capi::CityFurniture* ptr) {
    return reinterpret_cast<const ecitygml::CityFurniture*>(ptr);
}

inline ecitygml::CityFurniture* ecitygml::CityFurniture::FromFFI(ecitygml::capi::CityFurniture* ptr) {
    return reinterpret_cast<ecitygml::CityFurniture*>(ptr);
}

inline void ecitygml::CityFurniture::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_CityFurniture_destroy(reinterpret_cast<ecitygml::capi::CityFurniture*>(ptr));
}


#endif // ecitygml_CityFurniture_HPP
