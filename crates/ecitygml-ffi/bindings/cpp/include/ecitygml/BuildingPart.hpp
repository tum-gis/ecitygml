#ifndef ecitygml_BuildingPart_HPP
#define ecitygml_BuildingPart_HPP

#include "BuildingPart.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "AbstractBuildingSubdivisionPropertyIterator.hpp"
#include "AbstractFeatureKindRef.hpp"
#include "AbstractSpaceBoundaryPropertyIterator.hpp"
#include "BoundingShape.hpp"
#include "BuildingClassValue.hpp"
#include "BuildingFunctionValueIterator.hpp"
#include "BuildingUsageValueIterator.hpp"
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
#include "RoofTypeValue.hpp"
#include "SolidProperty.hpp"
#include "SpaceType.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_BuildingPart_id(const ecitygml::capi::BuildingPart* self);

    ecitygml::capi::CodeIterator* ecitygml_BuildingPart_names(const ecitygml::capi::BuildingPart* self);

    const ecitygml::capi::BoundingShape* ecitygml_BuildingPart_bounded_by(const ecitygml::capi::BuildingPart* self);

    const ecitygml::capi::Id* ecitygml_BuildingPart_feature_id(const ecitygml::capi::BuildingPart* self);

    const ecitygml::capi::DateTime* ecitygml_BuildingPart_creation_date(const ecitygml::capi::BuildingPart* self);

    const ecitygml::capi::DateTime* ecitygml_BuildingPart_termination_date(const ecitygml::capi::BuildingPart* self);

    const ecitygml::capi::DateTime* ecitygml_BuildingPart_valid_from(const ecitygml::capi::BuildingPart* self);

    const ecitygml::capi::DateTime* ecitygml_BuildingPart_valid_to(const ecitygml::capi::BuildingPart* self);

    typedef struct ecitygml_BuildingPart_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_BuildingPart_relative_to_terrain_result;
    ecitygml_BuildingPart_relative_to_terrain_result ecitygml_BuildingPart_relative_to_terrain(const ecitygml::capi::BuildingPart* self);

    typedef struct ecitygml_BuildingPart_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_BuildingPart_relative_to_water_result;
    ecitygml_BuildingPart_relative_to_water_result ecitygml_BuildingPart_relative_to_water(const ecitygml::capi::BuildingPart* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_BuildingPart_external_references(const ecitygml::capi::BuildingPart* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_BuildingPart_generic_attributes(const ecitygml::capi::BuildingPart* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_BuildingPart_related_to(const ecitygml::capi::BuildingPart* self);

    typedef struct ecitygml_BuildingPart_space_type_result {union {ecitygml::capi::SpaceType ok; }; bool is_ok;} ecitygml_BuildingPart_space_type_result;
    ecitygml_BuildingPart_space_type_result ecitygml_BuildingPart_space_type(const ecitygml::capi::BuildingPart* self);

    const ecitygml::capi::SolidProperty* ecitygml_BuildingPart_lod1_solid(const ecitygml::capi::BuildingPart* self);

    const ecitygml::capi::SolidProperty* ecitygml_BuildingPart_lod2_solid(const ecitygml::capi::BuildingPart* self);

    const ecitygml::capi::SolidProperty* ecitygml_BuildingPart_lod3_solid(const ecitygml::capi::BuildingPart* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_BuildingPart_lod0_multi_surface(const ecitygml::capi::BuildingPart* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_BuildingPart_lod2_multi_surface(const ecitygml::capi::BuildingPart* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_BuildingPart_lod3_multi_surface(const ecitygml::capi::BuildingPart* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_BuildingPart_lod0_multi_curve(const ecitygml::capi::BuildingPart* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_BuildingPart_lod2_multi_curve(const ecitygml::capi::BuildingPart* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_BuildingPart_lod3_multi_curve(const ecitygml::capi::BuildingPart* self);

    const ecitygml::capi::PointProperty* ecitygml_BuildingPart_lod0_point(const ecitygml::capi::BuildingPart* self);

    ecitygml::capi::AbstractSpaceBoundaryPropertyIterator* ecitygml_BuildingPart_boundaries(const ecitygml::capi::BuildingPart* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_BuildingPart_lod1_terrain_intersection_curve(const ecitygml::capi::BuildingPart* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_BuildingPart_lod2_terrain_intersection_curve(const ecitygml::capi::BuildingPart* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_BuildingPart_lod3_terrain_intersection_curve(const ecitygml::capi::BuildingPart* self);

    const ecitygml::capi::ImplicitGeometryProperty* ecitygml_BuildingPart_lod1_implicit_representation(const ecitygml::capi::BuildingPart* self);

    const ecitygml::capi::ImplicitGeometryProperty* ecitygml_BuildingPart_lod2_implicit_representation(const ecitygml::capi::BuildingPart* self);

    const ecitygml::capi::ImplicitGeometryProperty* ecitygml_BuildingPart_lod3_implicit_representation(const ecitygml::capi::BuildingPart* self);

    const ecitygml::capi::Date* ecitygml_BuildingPart_date_of_construction(const ecitygml::capi::BuildingPart* self);

    const ecitygml::capi::Date* ecitygml_BuildingPart_date_of_demolition(const ecitygml::capi::BuildingPart* self);

    ecitygml::capi::HeightIterator* ecitygml_BuildingPart_heights(const ecitygml::capi::BuildingPart* self);

    ecitygml::capi::OccupancyIterator* ecitygml_BuildingPart_occupancies(const ecitygml::capi::BuildingPart* self);

    const ecitygml::capi::BuildingClassValue* ecitygml_BuildingPart_class(const ecitygml::capi::BuildingPart* self);

    ecitygml::capi::BuildingFunctionValueIterator* ecitygml_BuildingPart_functions(const ecitygml::capi::BuildingPart* self);

    ecitygml::capi::BuildingUsageValueIterator* ecitygml_BuildingPart_usages(const ecitygml::capi::BuildingPart* self);

    const ecitygml::capi::RoofTypeValue* ecitygml_BuildingPart_roof_type(const ecitygml::capi::BuildingPart* self);

    typedef struct ecitygml_BuildingPart_storeys_above_ground_result {union {int64_t ok; }; bool is_ok;} ecitygml_BuildingPart_storeys_above_ground_result;
    ecitygml_BuildingPart_storeys_above_ground_result ecitygml_BuildingPart_storeys_above_ground(const ecitygml::capi::BuildingPart* self);

    typedef struct ecitygml_BuildingPart_storeys_below_ground_result {union {int64_t ok; }; bool is_ok;} ecitygml_BuildingPart_storeys_below_ground_result;
    ecitygml_BuildingPart_storeys_below_ground_result ecitygml_BuildingPart_storeys_below_ground(const ecitygml::capi::BuildingPart* self);

    ecitygml::capi::AbstractBuildingSubdivisionPropertyIterator* ecitygml_BuildingPart_building_subdivisions(const ecitygml::capi::BuildingPart* self);

    const ecitygml::capi::BuildingPart* ecitygml_BuildingPart_try_from(const ecitygml::capi::AbstractFeatureKindRef* feature);

    void ecitygml_BuildingPart_destroy(BuildingPart* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::BuildingPart::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::BuildingPart::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::BuildingPart::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::BuildingPart::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::BuildingPart::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::BuildingPart::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::BuildingPart::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::BuildingPart::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::BuildingPart::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_BuildingPart_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::BuildingPart::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_BuildingPart_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::BuildingPart::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::BuildingPart::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::BuildingPart::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline std::optional<ecitygml::SpaceType> ecitygml::BuildingPart::space_type() const {
    auto result = ecitygml::capi::ecitygml_BuildingPart_space_type(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::SpaceType>(ecitygml::SpaceType::FromFFI(result.ok)) : std::nullopt;
}

inline const ecitygml::SolidProperty* ecitygml::BuildingPart::lod1_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_lod1_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::BuildingPart::lod2_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_lod2_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::BuildingPart::lod3_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_lod3_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::BuildingPart::lod0_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_lod0_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::BuildingPart::lod2_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_lod2_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::BuildingPart::lod3_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_lod3_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::BuildingPart::lod0_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_lod0_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::BuildingPart::lod2_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_lod2_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::BuildingPart::lod3_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_lod3_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::PointProperty* ecitygml::BuildingPart::lod0_point() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_lod0_point(this->AsFFI());
    return ecitygml::PointProperty::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator> ecitygml::BuildingPart::boundaries() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_boundaries(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator>(ecitygml::AbstractSpaceBoundaryPropertyIterator::FromFFI(result));
}

inline const ecitygml::MultiCurveProperty* ecitygml::BuildingPart::lod1_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_lod1_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::BuildingPart::lod2_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_lod2_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::BuildingPart::lod3_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_lod3_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::ImplicitGeometryProperty* ecitygml::BuildingPart::lod1_implicit_representation() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_lod1_implicit_representation(this->AsFFI());
    return ecitygml::ImplicitGeometryProperty::FromFFI(result);
}

inline const ecitygml::ImplicitGeometryProperty* ecitygml::BuildingPart::lod2_implicit_representation() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_lod2_implicit_representation(this->AsFFI());
    return ecitygml::ImplicitGeometryProperty::FromFFI(result);
}

inline const ecitygml::ImplicitGeometryProperty* ecitygml::BuildingPart::lod3_implicit_representation() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_lod3_implicit_representation(this->AsFFI());
    return ecitygml::ImplicitGeometryProperty::FromFFI(result);
}

inline const ecitygml::Date* ecitygml::BuildingPart::date_of_construction() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_date_of_construction(this->AsFFI());
    return ecitygml::Date::FromFFI(result);
}

inline const ecitygml::Date* ecitygml::BuildingPart::date_of_demolition() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_date_of_demolition(this->AsFFI());
    return ecitygml::Date::FromFFI(result);
}

inline std::unique_ptr<ecitygml::HeightIterator> ecitygml::BuildingPart::heights() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_heights(this->AsFFI());
    return std::unique_ptr<ecitygml::HeightIterator>(ecitygml::HeightIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::OccupancyIterator> ecitygml::BuildingPart::occupancies() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_occupancies(this->AsFFI());
    return std::unique_ptr<ecitygml::OccupancyIterator>(ecitygml::OccupancyIterator::FromFFI(result));
}

inline const ecitygml::BuildingClassValue* ecitygml::BuildingPart::class_() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_class(this->AsFFI());
    return ecitygml::BuildingClassValue::FromFFI(result);
}

inline std::unique_ptr<ecitygml::BuildingFunctionValueIterator> ecitygml::BuildingPart::functions() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_functions(this->AsFFI());
    return std::unique_ptr<ecitygml::BuildingFunctionValueIterator>(ecitygml::BuildingFunctionValueIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::BuildingUsageValueIterator> ecitygml::BuildingPart::usages() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_usages(this->AsFFI());
    return std::unique_ptr<ecitygml::BuildingUsageValueIterator>(ecitygml::BuildingUsageValueIterator::FromFFI(result));
}

inline const ecitygml::RoofTypeValue* ecitygml::BuildingPart::roof_type() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_roof_type(this->AsFFI());
    return ecitygml::RoofTypeValue::FromFFI(result);
}

inline std::optional<int64_t> ecitygml::BuildingPart::storeys_above_ground() const {
    auto result = ecitygml::capi::ecitygml_BuildingPart_storeys_above_ground(this->AsFFI());
    return result.is_ok ? std::optional<int64_t>(result.ok) : std::nullopt;
}

inline std::optional<int64_t> ecitygml::BuildingPart::storeys_below_ground() const {
    auto result = ecitygml::capi::ecitygml_BuildingPart_storeys_below_ground(this->AsFFI());
    return result.is_ok ? std::optional<int64_t>(result.ok) : std::nullopt;
}

inline std::unique_ptr<ecitygml::AbstractBuildingSubdivisionPropertyIterator> ecitygml::BuildingPart::building_subdivisions() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPart_building_subdivisions(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractBuildingSubdivisionPropertyIterator>(ecitygml::AbstractBuildingSubdivisionPropertyIterator::FromFFI(result));
}

inline const ecitygml::BuildingPart* ecitygml::BuildingPart::try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_BuildingPart_try_from(feature.AsFFI());
    return ecitygml::BuildingPart::FromFFI(result);
}

inline const ecitygml::capi::BuildingPart* ecitygml::BuildingPart::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::BuildingPart*>(this);
}

inline ecitygml::capi::BuildingPart* ecitygml::BuildingPart::AsFFI() {
    return reinterpret_cast<ecitygml::capi::BuildingPart*>(this);
}

inline const ecitygml::BuildingPart* ecitygml::BuildingPart::FromFFI(const ecitygml::capi::BuildingPart* ptr) {
    return reinterpret_cast<const ecitygml::BuildingPart*>(ptr);
}

inline ecitygml::BuildingPart* ecitygml::BuildingPart::FromFFI(ecitygml::capi::BuildingPart* ptr) {
    return reinterpret_cast<ecitygml::BuildingPart*>(ptr);
}

inline void ecitygml::BuildingPart::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_BuildingPart_destroy(reinterpret_cast<ecitygml::capi::BuildingPart*>(ptr));
}


#endif // ecitygml_BuildingPart_HPP
