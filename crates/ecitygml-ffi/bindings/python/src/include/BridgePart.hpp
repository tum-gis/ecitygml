#ifndef ECITYGML_BridgePart_HPP
#define ECITYGML_BridgePart_HPP

#include "BridgePart.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "AbstractFeatureKindRef.hpp"
#include "AbstractSpaceBoundaryPropertyIterator.hpp"
#include "BoundingShape.hpp"
#include "BridgeClassValue.hpp"
#include "BridgeFunctionValueIterator.hpp"
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
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_BridgePart_id(const ecitygml::capi::BridgePart* self);

    ecitygml::capi::CodeIterator* ecitygml_BridgePart_names(const ecitygml::capi::BridgePart* self);

    const ecitygml::capi::BoundingShape* ecitygml_BridgePart_bounded_by(const ecitygml::capi::BridgePart* self);

    const ecitygml::capi::Id* ecitygml_BridgePart_feature_id(const ecitygml::capi::BridgePart* self);

    const ecitygml::capi::DateTime* ecitygml_BridgePart_creation_date(const ecitygml::capi::BridgePart* self);

    const ecitygml::capi::DateTime* ecitygml_BridgePart_termination_date(const ecitygml::capi::BridgePart* self);

    const ecitygml::capi::DateTime* ecitygml_BridgePart_valid_from(const ecitygml::capi::BridgePart* self);

    const ecitygml::capi::DateTime* ecitygml_BridgePart_valid_to(const ecitygml::capi::BridgePart* self);

    typedef struct ecitygml_BridgePart_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_BridgePart_relative_to_terrain_result;
    ecitygml_BridgePart_relative_to_terrain_result ecitygml_BridgePart_relative_to_terrain(const ecitygml::capi::BridgePart* self);

    typedef struct ecitygml_BridgePart_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_BridgePart_relative_to_water_result;
    ecitygml_BridgePart_relative_to_water_result ecitygml_BridgePart_relative_to_water(const ecitygml::capi::BridgePart* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_BridgePart_external_references(const ecitygml::capi::BridgePart* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_BridgePart_generic_attributes(const ecitygml::capi::BridgePart* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_BridgePart_related_to(const ecitygml::capi::BridgePart* self);

    typedef struct ecitygml_BridgePart_space_type_result {union {ecitygml::capi::SpaceType ok; }; bool is_ok;} ecitygml_BridgePart_space_type_result;
    ecitygml_BridgePart_space_type_result ecitygml_BridgePart_space_type(const ecitygml::capi::BridgePart* self);

    const ecitygml::capi::SolidProperty* ecitygml_BridgePart_lod1_solid(const ecitygml::capi::BridgePart* self);

    const ecitygml::capi::SolidProperty* ecitygml_BridgePart_lod2_solid(const ecitygml::capi::BridgePart* self);

    const ecitygml::capi::SolidProperty* ecitygml_BridgePart_lod3_solid(const ecitygml::capi::BridgePart* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_BridgePart_lod0_multi_surface(const ecitygml::capi::BridgePart* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_BridgePart_lod2_multi_surface(const ecitygml::capi::BridgePart* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_BridgePart_lod3_multi_surface(const ecitygml::capi::BridgePart* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_BridgePart_lod0_multi_curve(const ecitygml::capi::BridgePart* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_BridgePart_lod2_multi_curve(const ecitygml::capi::BridgePart* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_BridgePart_lod3_multi_curve(const ecitygml::capi::BridgePart* self);

    const ecitygml::capi::PointProperty* ecitygml_BridgePart_lod0_point(const ecitygml::capi::BridgePart* self);

    ecitygml::capi::AbstractSpaceBoundaryPropertyIterator* ecitygml_BridgePart_boundaries(const ecitygml::capi::BridgePart* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_BridgePart_lod1_terrain_intersection_curve(const ecitygml::capi::BridgePart* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_BridgePart_lod2_terrain_intersection_curve(const ecitygml::capi::BridgePart* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_BridgePart_lod3_terrain_intersection_curve(const ecitygml::capi::BridgePart* self);

    const ecitygml::capi::ImplicitGeometryProperty* ecitygml_BridgePart_lod1_implicit_representation(const ecitygml::capi::BridgePart* self);

    const ecitygml::capi::ImplicitGeometryProperty* ecitygml_BridgePart_lod2_implicit_representation(const ecitygml::capi::BridgePart* self);

    const ecitygml::capi::ImplicitGeometryProperty* ecitygml_BridgePart_lod3_implicit_representation(const ecitygml::capi::BridgePart* self);

    const ecitygml::capi::Date* ecitygml_BridgePart_date_of_construction(const ecitygml::capi::BridgePart* self);

    const ecitygml::capi::Date* ecitygml_BridgePart_date_of_demolition(const ecitygml::capi::BridgePart* self);

    ecitygml::capi::HeightIterator* ecitygml_BridgePart_heights(const ecitygml::capi::BridgePart* self);

    ecitygml::capi::OccupancyIterator* ecitygml_BridgePart_occupancies(const ecitygml::capi::BridgePart* self);

    const ecitygml::capi::BridgeClassValue* ecitygml_BridgePart_class(const ecitygml::capi::BridgePart* self);

    ecitygml::capi::BridgeFunctionValueIterator* ecitygml_BridgePart_functions(const ecitygml::capi::BridgePart* self);

    ecitygml::capi::BridgeUsageValueIterator* ecitygml_BridgePart_usages(const ecitygml::capi::BridgePart* self);

    typedef struct ecitygml_BridgePart_is_movable_result {union {bool ok; }; bool is_ok;} ecitygml_BridgePart_is_movable_result;
    ecitygml_BridgePart_is_movable_result ecitygml_BridgePart_is_movable(const ecitygml::capi::BridgePart* self);

    const ecitygml::capi::BridgePart* ecitygml_BridgePart_try_from(const ecitygml::capi::AbstractFeatureKindRef* feature);

    void ecitygml_BridgePart_destroy(BridgePart* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::BridgePart::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::BridgePart::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::BridgePart::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::BridgePart::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::BridgePart::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::BridgePart::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::BridgePart::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::BridgePart::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::BridgePart::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_BridgePart_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::BridgePart::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_BridgePart_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::BridgePart::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::BridgePart::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::BridgePart::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline std::optional<ecitygml::SpaceType> ecitygml::BridgePart::space_type() const {
    auto result = ecitygml::capi::ecitygml_BridgePart_space_type(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::SpaceType>(ecitygml::SpaceType::FromFFI(result.ok)) : std::nullopt;
}

inline const ecitygml::SolidProperty* ecitygml::BridgePart::lod1_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_lod1_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::BridgePart::lod2_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_lod2_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::BridgePart::lod3_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_lod3_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::BridgePart::lod0_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_lod0_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::BridgePart::lod2_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_lod2_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::BridgePart::lod3_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_lod3_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::BridgePart::lod0_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_lod0_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::BridgePart::lod2_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_lod2_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::BridgePart::lod3_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_lod3_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::PointProperty* ecitygml::BridgePart::lod0_point() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_lod0_point(this->AsFFI());
    return ecitygml::PointProperty::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator> ecitygml::BridgePart::boundaries() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_boundaries(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator>(ecitygml::AbstractSpaceBoundaryPropertyIterator::FromFFI(result));
}

inline const ecitygml::MultiCurveProperty* ecitygml::BridgePart::lod1_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_lod1_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::BridgePart::lod2_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_lod2_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::BridgePart::lod3_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_lod3_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::ImplicitGeometryProperty* ecitygml::BridgePart::lod1_implicit_representation() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_lod1_implicit_representation(this->AsFFI());
    return ecitygml::ImplicitGeometryProperty::FromFFI(result);
}

inline const ecitygml::ImplicitGeometryProperty* ecitygml::BridgePart::lod2_implicit_representation() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_lod2_implicit_representation(this->AsFFI());
    return ecitygml::ImplicitGeometryProperty::FromFFI(result);
}

inline const ecitygml::ImplicitGeometryProperty* ecitygml::BridgePart::lod3_implicit_representation() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_lod3_implicit_representation(this->AsFFI());
    return ecitygml::ImplicitGeometryProperty::FromFFI(result);
}

inline const ecitygml::Date* ecitygml::BridgePart::date_of_construction() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_date_of_construction(this->AsFFI());
    return ecitygml::Date::FromFFI(result);
}

inline const ecitygml::Date* ecitygml::BridgePart::date_of_demolition() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_date_of_demolition(this->AsFFI());
    return ecitygml::Date::FromFFI(result);
}

inline std::unique_ptr<ecitygml::HeightIterator> ecitygml::BridgePart::heights() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_heights(this->AsFFI());
    return std::unique_ptr<ecitygml::HeightIterator>(ecitygml::HeightIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::OccupancyIterator> ecitygml::BridgePart::occupancies() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_occupancies(this->AsFFI());
    return std::unique_ptr<ecitygml::OccupancyIterator>(ecitygml::OccupancyIterator::FromFFI(result));
}

inline const ecitygml::BridgeClassValue* ecitygml::BridgePart::class_() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_class(this->AsFFI());
    return ecitygml::BridgeClassValue::FromFFI(result);
}

inline std::unique_ptr<ecitygml::BridgeFunctionValueIterator> ecitygml::BridgePart::functions() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_functions(this->AsFFI());
    return std::unique_ptr<ecitygml::BridgeFunctionValueIterator>(ecitygml::BridgeFunctionValueIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::BridgeUsageValueIterator> ecitygml::BridgePart::usages() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePart_usages(this->AsFFI());
    return std::unique_ptr<ecitygml::BridgeUsageValueIterator>(ecitygml::BridgeUsageValueIterator::FromFFI(result));
}

inline std::optional<bool> ecitygml::BridgePart::is_movable() const {
    auto result = ecitygml::capi::ecitygml_BridgePart_is_movable(this->AsFFI());
    return result.is_ok ? std::optional<bool>(result.ok) : std::nullopt;
}

inline const ecitygml::BridgePart* ecitygml::BridgePart::try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_BridgePart_try_from(feature.AsFFI());
    return ecitygml::BridgePart::FromFFI(result);
}

inline const ecitygml::capi::BridgePart* ecitygml::BridgePart::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::BridgePart*>(this);
}

inline ecitygml::capi::BridgePart* ecitygml::BridgePart::AsFFI() {
    return reinterpret_cast<ecitygml::capi::BridgePart*>(this);
}

inline const ecitygml::BridgePart* ecitygml::BridgePart::FromFFI(const ecitygml::capi::BridgePart* ptr) {
    return reinterpret_cast<const ecitygml::BridgePart*>(ptr);
}

inline ecitygml::BridgePart* ecitygml::BridgePart::FromFFI(ecitygml::capi::BridgePart* ptr) {
    return reinterpret_cast<ecitygml::BridgePart*>(ptr);
}

inline void ecitygml::BridgePart::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_BridgePart_destroy(reinterpret_cast<ecitygml::capi::BridgePart*>(ptr));
}


#endif // ECITYGML_BridgePart_HPP
