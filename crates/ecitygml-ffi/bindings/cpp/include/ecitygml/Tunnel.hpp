#ifndef ecitygml_Tunnel_HPP
#define ecitygml_Tunnel_HPP

#include "Tunnel.d.hpp"

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
#include "TunnelClassValue.hpp"
#include "TunnelFunctionValueIterator.hpp"
#include "TunnelPartPropertyIterator.hpp"
#include "TunnelUsageValueIterator.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_Tunnel_id(const ecitygml::capi::Tunnel* self);

    ecitygml::capi::CodeIterator* ecitygml_Tunnel_names(const ecitygml::capi::Tunnel* self);

    const ecitygml::capi::BoundingShape* ecitygml_Tunnel_bounded_by(const ecitygml::capi::Tunnel* self);

    const ecitygml::capi::Id* ecitygml_Tunnel_feature_id(const ecitygml::capi::Tunnel* self);

    const ecitygml::capi::DateTime* ecitygml_Tunnel_creation_date(const ecitygml::capi::Tunnel* self);

    const ecitygml::capi::DateTime* ecitygml_Tunnel_termination_date(const ecitygml::capi::Tunnel* self);

    const ecitygml::capi::DateTime* ecitygml_Tunnel_valid_from(const ecitygml::capi::Tunnel* self);

    const ecitygml::capi::DateTime* ecitygml_Tunnel_valid_to(const ecitygml::capi::Tunnel* self);

    typedef struct ecitygml_Tunnel_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_Tunnel_relative_to_terrain_result;
    ecitygml_Tunnel_relative_to_terrain_result ecitygml_Tunnel_relative_to_terrain(const ecitygml::capi::Tunnel* self);

    typedef struct ecitygml_Tunnel_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_Tunnel_relative_to_water_result;
    ecitygml_Tunnel_relative_to_water_result ecitygml_Tunnel_relative_to_water(const ecitygml::capi::Tunnel* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_Tunnel_external_references(const ecitygml::capi::Tunnel* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_Tunnel_generic_attributes(const ecitygml::capi::Tunnel* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_Tunnel_related_to(const ecitygml::capi::Tunnel* self);

    typedef struct ecitygml_Tunnel_space_type_result {union {ecitygml::capi::SpaceType ok; }; bool is_ok;} ecitygml_Tunnel_space_type_result;
    ecitygml_Tunnel_space_type_result ecitygml_Tunnel_space_type(const ecitygml::capi::Tunnel* self);

    const ecitygml::capi::SolidProperty* ecitygml_Tunnel_lod1_solid(const ecitygml::capi::Tunnel* self);

    const ecitygml::capi::SolidProperty* ecitygml_Tunnel_lod2_solid(const ecitygml::capi::Tunnel* self);

    const ecitygml::capi::SolidProperty* ecitygml_Tunnel_lod3_solid(const ecitygml::capi::Tunnel* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_Tunnel_lod0_multi_surface(const ecitygml::capi::Tunnel* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_Tunnel_lod2_multi_surface(const ecitygml::capi::Tunnel* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_Tunnel_lod3_multi_surface(const ecitygml::capi::Tunnel* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Tunnel_lod0_multi_curve(const ecitygml::capi::Tunnel* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Tunnel_lod2_multi_curve(const ecitygml::capi::Tunnel* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Tunnel_lod3_multi_curve(const ecitygml::capi::Tunnel* self);

    const ecitygml::capi::PointProperty* ecitygml_Tunnel_lod0_point(const ecitygml::capi::Tunnel* self);

    ecitygml::capi::AbstractSpaceBoundaryPropertyIterator* ecitygml_Tunnel_boundaries(const ecitygml::capi::Tunnel* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Tunnel_lod1_terrain_intersection_curve(const ecitygml::capi::Tunnel* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Tunnel_lod2_terrain_intersection_curve(const ecitygml::capi::Tunnel* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Tunnel_lod3_terrain_intersection_curve(const ecitygml::capi::Tunnel* self);

    const ecitygml::capi::ImplicitGeometryProperty* ecitygml_Tunnel_lod1_implicit_representation(const ecitygml::capi::Tunnel* self);

    const ecitygml::capi::ImplicitGeometryProperty* ecitygml_Tunnel_lod2_implicit_representation(const ecitygml::capi::Tunnel* self);

    const ecitygml::capi::ImplicitGeometryProperty* ecitygml_Tunnel_lod3_implicit_representation(const ecitygml::capi::Tunnel* self);

    const ecitygml::capi::Date* ecitygml_Tunnel_date_of_construction(const ecitygml::capi::Tunnel* self);

    const ecitygml::capi::Date* ecitygml_Tunnel_date_of_demolition(const ecitygml::capi::Tunnel* self);

    ecitygml::capi::HeightIterator* ecitygml_Tunnel_heights(const ecitygml::capi::Tunnel* self);

    ecitygml::capi::OccupancyIterator* ecitygml_Tunnel_occupancies(const ecitygml::capi::Tunnel* self);

    const ecitygml::capi::TunnelClassValue* ecitygml_Tunnel_class(const ecitygml::capi::Tunnel* self);

    ecitygml::capi::TunnelFunctionValueIterator* ecitygml_Tunnel_functions(const ecitygml::capi::Tunnel* self);

    ecitygml::capi::TunnelUsageValueIterator* ecitygml_Tunnel_usages(const ecitygml::capi::Tunnel* self);

    const ecitygml::capi::Tunnel* ecitygml_Tunnel_try_from(const ecitygml::capi::AbstractFeatureKindRef* feature);

    ecitygml::capi::TunnelPartPropertyIterator* ecitygml_Tunnel_tunnel_parts(const ecitygml::capi::Tunnel* self);

    void ecitygml_Tunnel_destroy(Tunnel* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::Tunnel::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::Tunnel::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::Tunnel::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::Tunnel::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Tunnel::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Tunnel::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Tunnel::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Tunnel::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::Tunnel::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_Tunnel_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::Tunnel::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_Tunnel_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::Tunnel::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::Tunnel::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::Tunnel::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline std::optional<ecitygml::SpaceType> ecitygml::Tunnel::space_type() const {
    auto result = ecitygml::capi::ecitygml_Tunnel_space_type(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::SpaceType>(ecitygml::SpaceType::FromFFI(result.ok)) : std::nullopt;
}

inline const ecitygml::SolidProperty* ecitygml::Tunnel::lod1_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_lod1_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::Tunnel::lod2_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_lod2_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::Tunnel::lod3_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_lod3_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::Tunnel::lod0_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_lod0_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::Tunnel::lod2_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_lod2_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::Tunnel::lod3_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_lod3_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Tunnel::lod0_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_lod0_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Tunnel::lod2_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_lod2_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Tunnel::lod3_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_lod3_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::PointProperty* ecitygml::Tunnel::lod0_point() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_lod0_point(this->AsFFI());
    return ecitygml::PointProperty::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator> ecitygml::Tunnel::boundaries() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_boundaries(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator>(ecitygml::AbstractSpaceBoundaryPropertyIterator::FromFFI(result));
}

inline const ecitygml::MultiCurveProperty* ecitygml::Tunnel::lod1_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_lod1_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Tunnel::lod2_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_lod2_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Tunnel::lod3_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_lod3_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::ImplicitGeometryProperty* ecitygml::Tunnel::lod1_implicit_representation() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_lod1_implicit_representation(this->AsFFI());
    return ecitygml::ImplicitGeometryProperty::FromFFI(result);
}

inline const ecitygml::ImplicitGeometryProperty* ecitygml::Tunnel::lod2_implicit_representation() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_lod2_implicit_representation(this->AsFFI());
    return ecitygml::ImplicitGeometryProperty::FromFFI(result);
}

inline const ecitygml::ImplicitGeometryProperty* ecitygml::Tunnel::lod3_implicit_representation() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_lod3_implicit_representation(this->AsFFI());
    return ecitygml::ImplicitGeometryProperty::FromFFI(result);
}

inline const ecitygml::Date* ecitygml::Tunnel::date_of_construction() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_date_of_construction(this->AsFFI());
    return ecitygml::Date::FromFFI(result);
}

inline const ecitygml::Date* ecitygml::Tunnel::date_of_demolition() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_date_of_demolition(this->AsFFI());
    return ecitygml::Date::FromFFI(result);
}

inline std::unique_ptr<ecitygml::HeightIterator> ecitygml::Tunnel::heights() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_heights(this->AsFFI());
    return std::unique_ptr<ecitygml::HeightIterator>(ecitygml::HeightIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::OccupancyIterator> ecitygml::Tunnel::occupancies() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_occupancies(this->AsFFI());
    return std::unique_ptr<ecitygml::OccupancyIterator>(ecitygml::OccupancyIterator::FromFFI(result));
}

inline const ecitygml::TunnelClassValue* ecitygml::Tunnel::class_() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_class(this->AsFFI());
    return ecitygml::TunnelClassValue::FromFFI(result);
}

inline std::unique_ptr<ecitygml::TunnelFunctionValueIterator> ecitygml::Tunnel::functions() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_functions(this->AsFFI());
    return std::unique_ptr<ecitygml::TunnelFunctionValueIterator>(ecitygml::TunnelFunctionValueIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::TunnelUsageValueIterator> ecitygml::Tunnel::usages() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_usages(this->AsFFI());
    return std::unique_ptr<ecitygml::TunnelUsageValueIterator>(ecitygml::TunnelUsageValueIterator::FromFFI(result));
}

inline const ecitygml::Tunnel* ecitygml::Tunnel::try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_Tunnel_try_from(feature.AsFFI());
    return ecitygml::Tunnel::FromFFI(result);
}

inline std::unique_ptr<ecitygml::TunnelPartPropertyIterator> ecitygml::Tunnel::tunnel_parts() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Tunnel_tunnel_parts(this->AsFFI());
    return std::unique_ptr<ecitygml::TunnelPartPropertyIterator>(ecitygml::TunnelPartPropertyIterator::FromFFI(result));
}

inline const ecitygml::capi::Tunnel* ecitygml::Tunnel::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::Tunnel*>(this);
}

inline ecitygml::capi::Tunnel* ecitygml::Tunnel::AsFFI() {
    return reinterpret_cast<ecitygml::capi::Tunnel*>(this);
}

inline const ecitygml::Tunnel* ecitygml::Tunnel::FromFFI(const ecitygml::capi::Tunnel* ptr) {
    return reinterpret_cast<const ecitygml::Tunnel*>(ptr);
}

inline ecitygml::Tunnel* ecitygml::Tunnel::FromFFI(ecitygml::capi::Tunnel* ptr) {
    return reinterpret_cast<ecitygml::Tunnel*>(ptr);
}

inline void ecitygml::Tunnel::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_Tunnel_destroy(reinterpret_cast<ecitygml::capi::Tunnel*>(ptr));
}


#endif // ecitygml_Tunnel_HPP
