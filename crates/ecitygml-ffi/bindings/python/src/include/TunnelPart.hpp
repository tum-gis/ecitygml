#ifndef ECITYGML_TunnelPart_HPP
#define ECITYGML_TunnelPart_HPP

#include "TunnelPart.d.hpp"

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
#include "TunnelUsageValueIterator.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_TunnelPart_id(const ecitygml::capi::TunnelPart* self);

    ecitygml::capi::CodeIterator* ecitygml_TunnelPart_names(const ecitygml::capi::TunnelPart* self);

    const ecitygml::capi::BoundingShape* ecitygml_TunnelPart_bounded_by(const ecitygml::capi::TunnelPart* self);

    const ecitygml::capi::Id* ecitygml_TunnelPart_feature_id(const ecitygml::capi::TunnelPart* self);

    const ecitygml::capi::DateTime* ecitygml_TunnelPart_creation_date(const ecitygml::capi::TunnelPart* self);

    const ecitygml::capi::DateTime* ecitygml_TunnelPart_termination_date(const ecitygml::capi::TunnelPart* self);

    const ecitygml::capi::DateTime* ecitygml_TunnelPart_valid_from(const ecitygml::capi::TunnelPart* self);

    const ecitygml::capi::DateTime* ecitygml_TunnelPart_valid_to(const ecitygml::capi::TunnelPart* self);

    typedef struct ecitygml_TunnelPart_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_TunnelPart_relative_to_terrain_result;
    ecitygml_TunnelPart_relative_to_terrain_result ecitygml_TunnelPart_relative_to_terrain(const ecitygml::capi::TunnelPart* self);

    typedef struct ecitygml_TunnelPart_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_TunnelPart_relative_to_water_result;
    ecitygml_TunnelPart_relative_to_water_result ecitygml_TunnelPart_relative_to_water(const ecitygml::capi::TunnelPart* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_TunnelPart_external_references(const ecitygml::capi::TunnelPart* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_TunnelPart_generic_attributes(const ecitygml::capi::TunnelPart* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_TunnelPart_related_to(const ecitygml::capi::TunnelPart* self);

    typedef struct ecitygml_TunnelPart_space_type_result {union {ecitygml::capi::SpaceType ok; }; bool is_ok;} ecitygml_TunnelPart_space_type_result;
    ecitygml_TunnelPart_space_type_result ecitygml_TunnelPart_space_type(const ecitygml::capi::TunnelPart* self);

    const ecitygml::capi::SolidProperty* ecitygml_TunnelPart_lod1_solid(const ecitygml::capi::TunnelPart* self);

    const ecitygml::capi::SolidProperty* ecitygml_TunnelPart_lod2_solid(const ecitygml::capi::TunnelPart* self);

    const ecitygml::capi::SolidProperty* ecitygml_TunnelPart_lod3_solid(const ecitygml::capi::TunnelPart* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_TunnelPart_lod0_multi_surface(const ecitygml::capi::TunnelPart* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_TunnelPart_lod2_multi_surface(const ecitygml::capi::TunnelPart* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_TunnelPart_lod3_multi_surface(const ecitygml::capi::TunnelPart* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_TunnelPart_lod0_multi_curve(const ecitygml::capi::TunnelPart* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_TunnelPart_lod2_multi_curve(const ecitygml::capi::TunnelPart* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_TunnelPart_lod3_multi_curve(const ecitygml::capi::TunnelPart* self);

    const ecitygml::capi::PointProperty* ecitygml_TunnelPart_lod0_point(const ecitygml::capi::TunnelPart* self);

    ecitygml::capi::AbstractSpaceBoundaryPropertyIterator* ecitygml_TunnelPart_boundaries(const ecitygml::capi::TunnelPart* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_TunnelPart_lod1_terrain_intersection_curve(const ecitygml::capi::TunnelPart* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_TunnelPart_lod2_terrain_intersection_curve(const ecitygml::capi::TunnelPart* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_TunnelPart_lod3_terrain_intersection_curve(const ecitygml::capi::TunnelPart* self);

    const ecitygml::capi::ImplicitGeometryProperty* ecitygml_TunnelPart_lod1_implicit_representation(const ecitygml::capi::TunnelPart* self);

    const ecitygml::capi::ImplicitGeometryProperty* ecitygml_TunnelPart_lod2_implicit_representation(const ecitygml::capi::TunnelPart* self);

    const ecitygml::capi::ImplicitGeometryProperty* ecitygml_TunnelPart_lod3_implicit_representation(const ecitygml::capi::TunnelPart* self);

    const ecitygml::capi::Date* ecitygml_TunnelPart_date_of_construction(const ecitygml::capi::TunnelPart* self);

    const ecitygml::capi::Date* ecitygml_TunnelPart_date_of_demolition(const ecitygml::capi::TunnelPart* self);

    ecitygml::capi::HeightIterator* ecitygml_TunnelPart_heights(const ecitygml::capi::TunnelPart* self);

    ecitygml::capi::OccupancyIterator* ecitygml_TunnelPart_occupancies(const ecitygml::capi::TunnelPart* self);

    const ecitygml::capi::TunnelClassValue* ecitygml_TunnelPart_class(const ecitygml::capi::TunnelPart* self);

    ecitygml::capi::TunnelFunctionValueIterator* ecitygml_TunnelPart_functions(const ecitygml::capi::TunnelPart* self);

    ecitygml::capi::TunnelUsageValueIterator* ecitygml_TunnelPart_usages(const ecitygml::capi::TunnelPart* self);

    const ecitygml::capi::TunnelPart* ecitygml_TunnelPart_try_from(const ecitygml::capi::AbstractFeatureKindRef* feature);

    void ecitygml_TunnelPart_destroy(TunnelPart* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::TunnelPart::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::TunnelPart::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::TunnelPart::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::TunnelPart::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::TunnelPart::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::TunnelPart::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::TunnelPart::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::TunnelPart::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::TunnelPart::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_TunnelPart_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::TunnelPart::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_TunnelPart_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::TunnelPart::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::TunnelPart::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::TunnelPart::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline std::optional<ecitygml::SpaceType> ecitygml::TunnelPart::space_type() const {
    auto result = ecitygml::capi::ecitygml_TunnelPart_space_type(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::SpaceType>(ecitygml::SpaceType::FromFFI(result.ok)) : std::nullopt;
}

inline const ecitygml::SolidProperty* ecitygml::TunnelPart::lod1_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_lod1_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::TunnelPart::lod2_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_lod2_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::TunnelPart::lod3_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_lod3_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::TunnelPart::lod0_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_lod0_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::TunnelPart::lod2_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_lod2_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::TunnelPart::lod3_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_lod3_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::TunnelPart::lod0_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_lod0_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::TunnelPart::lod2_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_lod2_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::TunnelPart::lod3_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_lod3_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::PointProperty* ecitygml::TunnelPart::lod0_point() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_lod0_point(this->AsFFI());
    return ecitygml::PointProperty::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator> ecitygml::TunnelPart::boundaries() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_boundaries(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator>(ecitygml::AbstractSpaceBoundaryPropertyIterator::FromFFI(result));
}

inline const ecitygml::MultiCurveProperty* ecitygml::TunnelPart::lod1_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_lod1_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::TunnelPart::lod2_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_lod2_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::TunnelPart::lod3_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_lod3_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::ImplicitGeometryProperty* ecitygml::TunnelPart::lod1_implicit_representation() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_lod1_implicit_representation(this->AsFFI());
    return ecitygml::ImplicitGeometryProperty::FromFFI(result);
}

inline const ecitygml::ImplicitGeometryProperty* ecitygml::TunnelPart::lod2_implicit_representation() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_lod2_implicit_representation(this->AsFFI());
    return ecitygml::ImplicitGeometryProperty::FromFFI(result);
}

inline const ecitygml::ImplicitGeometryProperty* ecitygml::TunnelPart::lod3_implicit_representation() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_lod3_implicit_representation(this->AsFFI());
    return ecitygml::ImplicitGeometryProperty::FromFFI(result);
}

inline const ecitygml::Date* ecitygml::TunnelPart::date_of_construction() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_date_of_construction(this->AsFFI());
    return ecitygml::Date::FromFFI(result);
}

inline const ecitygml::Date* ecitygml::TunnelPart::date_of_demolition() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_date_of_demolition(this->AsFFI());
    return ecitygml::Date::FromFFI(result);
}

inline std::unique_ptr<ecitygml::HeightIterator> ecitygml::TunnelPart::heights() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_heights(this->AsFFI());
    return std::unique_ptr<ecitygml::HeightIterator>(ecitygml::HeightIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::OccupancyIterator> ecitygml::TunnelPart::occupancies() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_occupancies(this->AsFFI());
    return std::unique_ptr<ecitygml::OccupancyIterator>(ecitygml::OccupancyIterator::FromFFI(result));
}

inline const ecitygml::TunnelClassValue* ecitygml::TunnelPart::class_() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_class(this->AsFFI());
    return ecitygml::TunnelClassValue::FromFFI(result);
}

inline std::unique_ptr<ecitygml::TunnelFunctionValueIterator> ecitygml::TunnelPart::functions() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_functions(this->AsFFI());
    return std::unique_ptr<ecitygml::TunnelFunctionValueIterator>(ecitygml::TunnelFunctionValueIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::TunnelUsageValueIterator> ecitygml::TunnelPart::usages() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPart_usages(this->AsFFI());
    return std::unique_ptr<ecitygml::TunnelUsageValueIterator>(ecitygml::TunnelUsageValueIterator::FromFFI(result));
}

inline const ecitygml::TunnelPart* ecitygml::TunnelPart::try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_TunnelPart_try_from(feature.AsFFI());
    return ecitygml::TunnelPart::FromFFI(result);
}

inline const ecitygml::capi::TunnelPart* ecitygml::TunnelPart::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::TunnelPart*>(this);
}

inline ecitygml::capi::TunnelPart* ecitygml::TunnelPart::AsFFI() {
    return reinterpret_cast<ecitygml::capi::TunnelPart*>(this);
}

inline const ecitygml::TunnelPart* ecitygml::TunnelPart::FromFFI(const ecitygml::capi::TunnelPart* ptr) {
    return reinterpret_cast<const ecitygml::TunnelPart*>(ptr);
}

inline ecitygml::TunnelPart* ecitygml::TunnelPart::FromFFI(ecitygml::capi::TunnelPart* ptr) {
    return reinterpret_cast<ecitygml::TunnelPart*>(ptr);
}

inline void ecitygml::TunnelPart::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_TunnelPart_destroy(reinterpret_cast<ecitygml::capi::TunnelPart*>(ptr));
}


#endif // ECITYGML_TunnelPart_HPP
