#ifndef ecitygml_Bridge_HPP
#define ecitygml_Bridge_HPP

#include "Bridge.d.hpp"

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
#include "BridgeClassValue.hpp"
#include "BridgeFunctionValueIterator.hpp"
#include "BridgePartPropertyIterator.hpp"
#include "BridgeUsageValueIterator.hpp"
#include "CityObjectRelationPropertyIterator.hpp"
#include "CodeIterator.hpp"
#include "Date.hpp"
#include "DateTime.hpp"
#include "ExternalReferenceIterator.hpp"
#include "GenericAttributeKindIterator.hpp"
#include "HeightIterator.hpp"
#include "Id.hpp"
#include "ImplicitGeometryProperty.hpp"
#include "MultiCurveProperty.hpp"
#include "MultiSurfaceProperty.hpp"
#include "OccupancyIterator.hpp"
#include "PointProperty.hpp"
#include "RelativeToTerrain.hpp"
#include "RelativeToWater.hpp"
#include "SolidProperty.hpp"
#include "SpaceType.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_Bridge_id(const ecitygml::capi::Bridge* self);

    ecitygml::capi::CodeIterator* ecitygml_Bridge_names(const ecitygml::capi::Bridge* self);

    const ecitygml::capi::BoundingShape* ecitygml_Bridge_bounded_by(const ecitygml::capi::Bridge* self);

    const ecitygml::capi::Id* ecitygml_Bridge_feature_id(const ecitygml::capi::Bridge* self);

    const ecitygml::capi::DateTime* ecitygml_Bridge_creation_date(const ecitygml::capi::Bridge* self);

    const ecitygml::capi::DateTime* ecitygml_Bridge_termination_date(const ecitygml::capi::Bridge* self);

    const ecitygml::capi::DateTime* ecitygml_Bridge_valid_from(const ecitygml::capi::Bridge* self);

    const ecitygml::capi::DateTime* ecitygml_Bridge_valid_to(const ecitygml::capi::Bridge* self);

    typedef struct ecitygml_Bridge_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_Bridge_relative_to_terrain_result;
    ecitygml_Bridge_relative_to_terrain_result ecitygml_Bridge_relative_to_terrain(const ecitygml::capi::Bridge* self);

    typedef struct ecitygml_Bridge_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_Bridge_relative_to_water_result;
    ecitygml_Bridge_relative_to_water_result ecitygml_Bridge_relative_to_water(const ecitygml::capi::Bridge* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_Bridge_external_references(const ecitygml::capi::Bridge* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_Bridge_generic_attributes(const ecitygml::capi::Bridge* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_Bridge_related_to(const ecitygml::capi::Bridge* self);

    typedef struct ecitygml_Bridge_space_type_result {union {ecitygml::capi::SpaceType ok; }; bool is_ok;} ecitygml_Bridge_space_type_result;
    ecitygml_Bridge_space_type_result ecitygml_Bridge_space_type(const ecitygml::capi::Bridge* self);

    const ecitygml::capi::SolidProperty* ecitygml_Bridge_lod1_solid(const ecitygml::capi::Bridge* self);

    const ecitygml::capi::SolidProperty* ecitygml_Bridge_lod2_solid(const ecitygml::capi::Bridge* self);

    const ecitygml::capi::SolidProperty* ecitygml_Bridge_lod3_solid(const ecitygml::capi::Bridge* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_Bridge_lod0_multi_surface(const ecitygml::capi::Bridge* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_Bridge_lod2_multi_surface(const ecitygml::capi::Bridge* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_Bridge_lod3_multi_surface(const ecitygml::capi::Bridge* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Bridge_lod0_multi_curve(const ecitygml::capi::Bridge* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Bridge_lod2_multi_curve(const ecitygml::capi::Bridge* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Bridge_lod3_multi_curve(const ecitygml::capi::Bridge* self);

    const ecitygml::capi::PointProperty* ecitygml_Bridge_lod0_point(const ecitygml::capi::Bridge* self);

    ecitygml::capi::AbstractSpaceBoundaryPropertyIterator* ecitygml_Bridge_boundaries(const ecitygml::capi::Bridge* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Bridge_lod1_terrain_intersection_curve(const ecitygml::capi::Bridge* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Bridge_lod2_terrain_intersection_curve(const ecitygml::capi::Bridge* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Bridge_lod3_terrain_intersection_curve(const ecitygml::capi::Bridge* self);

    const ecitygml::capi::ImplicitGeometryProperty* ecitygml_Bridge_lod1_implicit_representation(const ecitygml::capi::Bridge* self);

    const ecitygml::capi::ImplicitGeometryProperty* ecitygml_Bridge_lod2_implicit_representation(const ecitygml::capi::Bridge* self);

    const ecitygml::capi::ImplicitGeometryProperty* ecitygml_Bridge_lod3_implicit_representation(const ecitygml::capi::Bridge* self);

    const ecitygml::capi::Date* ecitygml_Bridge_date_of_construction(const ecitygml::capi::Bridge* self);

    const ecitygml::capi::Date* ecitygml_Bridge_date_of_demolition(const ecitygml::capi::Bridge* self);

    ecitygml::capi::HeightIterator* ecitygml_Bridge_heights(const ecitygml::capi::Bridge* self);

    ecitygml::capi::OccupancyIterator* ecitygml_Bridge_occupancies(const ecitygml::capi::Bridge* self);

    const ecitygml::capi::BridgeClassValue* ecitygml_Bridge_class(const ecitygml::capi::Bridge* self);

    ecitygml::capi::BridgeFunctionValueIterator* ecitygml_Bridge_functions(const ecitygml::capi::Bridge* self);

    ecitygml::capi::BridgeUsageValueIterator* ecitygml_Bridge_usages(const ecitygml::capi::Bridge* self);

    typedef struct ecitygml_Bridge_is_movable_result {union {bool ok; }; bool is_ok;} ecitygml_Bridge_is_movable_result;
    ecitygml_Bridge_is_movable_result ecitygml_Bridge_is_movable(const ecitygml::capi::Bridge* self);

    const ecitygml::capi::Bridge* ecitygml_Bridge_try_from(const ecitygml::capi::AbstractFeatureKindRef* feature);

    ecitygml::capi::BridgePartPropertyIterator* ecitygml_Bridge_bridge_parts(const ecitygml::capi::Bridge* self);

    void ecitygml_Bridge_destroy(Bridge* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::Bridge::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::Bridge::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::Bridge::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::Bridge::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Bridge::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Bridge::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Bridge::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Bridge::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::Bridge::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_Bridge_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::Bridge::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_Bridge_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::Bridge::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::Bridge::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::Bridge::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline std::optional<ecitygml::SpaceType> ecitygml::Bridge::space_type() const {
    auto result = ecitygml::capi::ecitygml_Bridge_space_type(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::SpaceType>(ecitygml::SpaceType::FromFFI(result.ok)) : std::nullopt;
}

inline const ecitygml::SolidProperty* ecitygml::Bridge::lod1_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_lod1_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::Bridge::lod2_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_lod2_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::Bridge::lod3_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_lod3_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::Bridge::lod0_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_lod0_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::Bridge::lod2_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_lod2_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::Bridge::lod3_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_lod3_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Bridge::lod0_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_lod0_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Bridge::lod2_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_lod2_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Bridge::lod3_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_lod3_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::PointProperty* ecitygml::Bridge::lod0_point() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_lod0_point(this->AsFFI());
    return ecitygml::PointProperty::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator> ecitygml::Bridge::boundaries() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_boundaries(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator>(ecitygml::AbstractSpaceBoundaryPropertyIterator::FromFFI(result));
}

inline const ecitygml::MultiCurveProperty* ecitygml::Bridge::lod1_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_lod1_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Bridge::lod2_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_lod2_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Bridge::lod3_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_lod3_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::ImplicitGeometryProperty* ecitygml::Bridge::lod1_implicit_representation() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_lod1_implicit_representation(this->AsFFI());
    return ecitygml::ImplicitGeometryProperty::FromFFI(result);
}

inline const ecitygml::ImplicitGeometryProperty* ecitygml::Bridge::lod2_implicit_representation() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_lod2_implicit_representation(this->AsFFI());
    return ecitygml::ImplicitGeometryProperty::FromFFI(result);
}

inline const ecitygml::ImplicitGeometryProperty* ecitygml::Bridge::lod3_implicit_representation() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_lod3_implicit_representation(this->AsFFI());
    return ecitygml::ImplicitGeometryProperty::FromFFI(result);
}

inline const ecitygml::Date* ecitygml::Bridge::date_of_construction() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_date_of_construction(this->AsFFI());
    return ecitygml::Date::FromFFI(result);
}

inline const ecitygml::Date* ecitygml::Bridge::date_of_demolition() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_date_of_demolition(this->AsFFI());
    return ecitygml::Date::FromFFI(result);
}

inline std::unique_ptr<ecitygml::HeightIterator> ecitygml::Bridge::heights() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_heights(this->AsFFI());
    return std::unique_ptr<ecitygml::HeightIterator>(ecitygml::HeightIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::OccupancyIterator> ecitygml::Bridge::occupancies() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_occupancies(this->AsFFI());
    return std::unique_ptr<ecitygml::OccupancyIterator>(ecitygml::OccupancyIterator::FromFFI(result));
}

inline const ecitygml::BridgeClassValue* ecitygml::Bridge::class_() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_class(this->AsFFI());
    return ecitygml::BridgeClassValue::FromFFI(result);
}

inline std::unique_ptr<ecitygml::BridgeFunctionValueIterator> ecitygml::Bridge::functions() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_functions(this->AsFFI());
    return std::unique_ptr<ecitygml::BridgeFunctionValueIterator>(ecitygml::BridgeFunctionValueIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::BridgeUsageValueIterator> ecitygml::Bridge::usages() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_usages(this->AsFFI());
    return std::unique_ptr<ecitygml::BridgeUsageValueIterator>(ecitygml::BridgeUsageValueIterator::FromFFI(result));
}

inline std::optional<bool> ecitygml::Bridge::is_movable() const {
    auto result = ecitygml::capi::ecitygml_Bridge_is_movable(this->AsFFI());
    return result.is_ok ? std::optional<bool>(result.ok) : std::nullopt;
}

inline const ecitygml::Bridge* ecitygml::Bridge::try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_Bridge_try_from(feature.AsFFI());
    return ecitygml::Bridge::FromFFI(result);
}

inline std::unique_ptr<ecitygml::BridgePartPropertyIterator> ecitygml::Bridge::bridge_parts() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Bridge_bridge_parts(this->AsFFI());
    return std::unique_ptr<ecitygml::BridgePartPropertyIterator>(ecitygml::BridgePartPropertyIterator::FromFFI(result));
}

inline const ecitygml::capi::Bridge* ecitygml::Bridge::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::Bridge*>(this);
}

inline ecitygml::capi::Bridge* ecitygml::Bridge::AsFFI() {
    return reinterpret_cast<ecitygml::capi::Bridge*>(this);
}

inline const ecitygml::Bridge* ecitygml::Bridge::FromFFI(const ecitygml::capi::Bridge* ptr) {
    return reinterpret_cast<const ecitygml::Bridge*>(ptr);
}

inline ecitygml::Bridge* ecitygml::Bridge::FromFFI(ecitygml::capi::Bridge* ptr) {
    return reinterpret_cast<ecitygml::Bridge*>(ptr);
}

inline void ecitygml::Bridge::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_Bridge_destroy(reinterpret_cast<ecitygml::capi::Bridge*>(ptr));
}


#endif // ecitygml_Bridge_HPP
