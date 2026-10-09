#ifndef ECITYGML_Building_HPP
#define ECITYGML_Building_HPP

#include "Building.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "AbstractBuildingSubdivisionPropertyIterator.hpp"
#include "AbstractFeatureKindRef.hpp"
#include "AbstractSpaceBoundaryPropertyIterator.hpp"
#include "BoundingShape.hpp"
#include "BuildingClassValue.hpp"
#include "BuildingFunctionValueIterator.hpp"
#include "BuildingPartPropertyIterator.hpp"
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
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_Building_id(const ecitygml::capi::Building* self);

    ecitygml::capi::CodeIterator* ecitygml_Building_names(const ecitygml::capi::Building* self);

    const ecitygml::capi::BoundingShape* ecitygml_Building_bounded_by(const ecitygml::capi::Building* self);

    const ecitygml::capi::Id* ecitygml_Building_feature_id(const ecitygml::capi::Building* self);

    const ecitygml::capi::DateTime* ecitygml_Building_creation_date(const ecitygml::capi::Building* self);

    const ecitygml::capi::DateTime* ecitygml_Building_termination_date(const ecitygml::capi::Building* self);

    const ecitygml::capi::DateTime* ecitygml_Building_valid_from(const ecitygml::capi::Building* self);

    const ecitygml::capi::DateTime* ecitygml_Building_valid_to(const ecitygml::capi::Building* self);

    typedef struct ecitygml_Building_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_Building_relative_to_terrain_result;
    ecitygml_Building_relative_to_terrain_result ecitygml_Building_relative_to_terrain(const ecitygml::capi::Building* self);

    typedef struct ecitygml_Building_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_Building_relative_to_water_result;
    ecitygml_Building_relative_to_water_result ecitygml_Building_relative_to_water(const ecitygml::capi::Building* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_Building_external_references(const ecitygml::capi::Building* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_Building_generic_attributes(const ecitygml::capi::Building* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_Building_related_to(const ecitygml::capi::Building* self);

    typedef struct ecitygml_Building_space_type_result {union {ecitygml::capi::SpaceType ok; }; bool is_ok;} ecitygml_Building_space_type_result;
    ecitygml_Building_space_type_result ecitygml_Building_space_type(const ecitygml::capi::Building* self);

    const ecitygml::capi::SolidProperty* ecitygml_Building_lod1_solid(const ecitygml::capi::Building* self);

    const ecitygml::capi::SolidProperty* ecitygml_Building_lod2_solid(const ecitygml::capi::Building* self);

    const ecitygml::capi::SolidProperty* ecitygml_Building_lod3_solid(const ecitygml::capi::Building* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_Building_lod0_multi_surface(const ecitygml::capi::Building* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_Building_lod2_multi_surface(const ecitygml::capi::Building* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_Building_lod3_multi_surface(const ecitygml::capi::Building* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Building_lod0_multi_curve(const ecitygml::capi::Building* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Building_lod2_multi_curve(const ecitygml::capi::Building* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Building_lod3_multi_curve(const ecitygml::capi::Building* self);

    const ecitygml::capi::PointProperty* ecitygml_Building_lod0_point(const ecitygml::capi::Building* self);

    ecitygml::capi::AbstractSpaceBoundaryPropertyIterator* ecitygml_Building_boundaries(const ecitygml::capi::Building* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Building_lod1_terrain_intersection_curve(const ecitygml::capi::Building* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Building_lod2_terrain_intersection_curve(const ecitygml::capi::Building* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Building_lod3_terrain_intersection_curve(const ecitygml::capi::Building* self);

    const ecitygml::capi::ImplicitGeometryProperty* ecitygml_Building_lod1_implicit_representation(const ecitygml::capi::Building* self);

    const ecitygml::capi::ImplicitGeometryProperty* ecitygml_Building_lod2_implicit_representation(const ecitygml::capi::Building* self);

    const ecitygml::capi::ImplicitGeometryProperty* ecitygml_Building_lod3_implicit_representation(const ecitygml::capi::Building* self);

    const ecitygml::capi::Date* ecitygml_Building_date_of_construction(const ecitygml::capi::Building* self);

    const ecitygml::capi::Date* ecitygml_Building_date_of_demolition(const ecitygml::capi::Building* self);

    ecitygml::capi::HeightIterator* ecitygml_Building_heights(const ecitygml::capi::Building* self);

    ecitygml::capi::OccupancyIterator* ecitygml_Building_occupancies(const ecitygml::capi::Building* self);

    const ecitygml::capi::BuildingClassValue* ecitygml_Building_class(const ecitygml::capi::Building* self);

    ecitygml::capi::BuildingFunctionValueIterator* ecitygml_Building_functions(const ecitygml::capi::Building* self);

    ecitygml::capi::BuildingUsageValueIterator* ecitygml_Building_usages(const ecitygml::capi::Building* self);

    const ecitygml::capi::RoofTypeValue* ecitygml_Building_roof_type(const ecitygml::capi::Building* self);

    typedef struct ecitygml_Building_storeys_above_ground_result {union {int64_t ok; }; bool is_ok;} ecitygml_Building_storeys_above_ground_result;
    ecitygml_Building_storeys_above_ground_result ecitygml_Building_storeys_above_ground(const ecitygml::capi::Building* self);

    typedef struct ecitygml_Building_storeys_below_ground_result {union {int64_t ok; }; bool is_ok;} ecitygml_Building_storeys_below_ground_result;
    ecitygml_Building_storeys_below_ground_result ecitygml_Building_storeys_below_ground(const ecitygml::capi::Building* self);

    ecitygml::capi::AbstractBuildingSubdivisionPropertyIterator* ecitygml_Building_building_subdivisions(const ecitygml::capi::Building* self);

    const ecitygml::capi::Building* ecitygml_Building_try_from(const ecitygml::capi::AbstractFeatureKindRef* feature);

    ecitygml::capi::BuildingPartPropertyIterator* ecitygml_Building_building_parts(const ecitygml::capi::Building* self);

    void ecitygml_Building_destroy(Building* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::Building::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::Building::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::Building::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::Building::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Building::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Building::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Building::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Building::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::Building::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_Building_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::Building::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_Building_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::Building::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::Building::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::Building::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline std::optional<ecitygml::SpaceType> ecitygml::Building::space_type() const {
    auto result = ecitygml::capi::ecitygml_Building_space_type(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::SpaceType>(ecitygml::SpaceType::FromFFI(result.ok)) : std::nullopt;
}

inline const ecitygml::SolidProperty* ecitygml::Building::lod1_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_lod1_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::Building::lod2_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_lod2_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::Building::lod3_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_lod3_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::Building::lod0_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_lod0_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::Building::lod2_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_lod2_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::Building::lod3_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_lod3_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Building::lod0_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_lod0_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Building::lod2_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_lod2_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Building::lod3_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_lod3_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::PointProperty* ecitygml::Building::lod0_point() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_lod0_point(this->AsFFI());
    return ecitygml::PointProperty::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator> ecitygml::Building::boundaries() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_boundaries(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator>(ecitygml::AbstractSpaceBoundaryPropertyIterator::FromFFI(result));
}

inline const ecitygml::MultiCurveProperty* ecitygml::Building::lod1_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_lod1_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Building::lod2_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_lod2_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Building::lod3_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_lod3_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::ImplicitGeometryProperty* ecitygml::Building::lod1_implicit_representation() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_lod1_implicit_representation(this->AsFFI());
    return ecitygml::ImplicitGeometryProperty::FromFFI(result);
}

inline const ecitygml::ImplicitGeometryProperty* ecitygml::Building::lod2_implicit_representation() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_lod2_implicit_representation(this->AsFFI());
    return ecitygml::ImplicitGeometryProperty::FromFFI(result);
}

inline const ecitygml::ImplicitGeometryProperty* ecitygml::Building::lod3_implicit_representation() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_lod3_implicit_representation(this->AsFFI());
    return ecitygml::ImplicitGeometryProperty::FromFFI(result);
}

inline const ecitygml::Date* ecitygml::Building::date_of_construction() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_date_of_construction(this->AsFFI());
    return ecitygml::Date::FromFFI(result);
}

inline const ecitygml::Date* ecitygml::Building::date_of_demolition() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_date_of_demolition(this->AsFFI());
    return ecitygml::Date::FromFFI(result);
}

inline std::unique_ptr<ecitygml::HeightIterator> ecitygml::Building::heights() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_heights(this->AsFFI());
    return std::unique_ptr<ecitygml::HeightIterator>(ecitygml::HeightIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::OccupancyIterator> ecitygml::Building::occupancies() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_occupancies(this->AsFFI());
    return std::unique_ptr<ecitygml::OccupancyIterator>(ecitygml::OccupancyIterator::FromFFI(result));
}

inline const ecitygml::BuildingClassValue* ecitygml::Building::class_() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_class(this->AsFFI());
    return ecitygml::BuildingClassValue::FromFFI(result);
}

inline std::unique_ptr<ecitygml::BuildingFunctionValueIterator> ecitygml::Building::functions() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_functions(this->AsFFI());
    return std::unique_ptr<ecitygml::BuildingFunctionValueIterator>(ecitygml::BuildingFunctionValueIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::BuildingUsageValueIterator> ecitygml::Building::usages() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_usages(this->AsFFI());
    return std::unique_ptr<ecitygml::BuildingUsageValueIterator>(ecitygml::BuildingUsageValueIterator::FromFFI(result));
}

inline const ecitygml::RoofTypeValue* ecitygml::Building::roof_type() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_roof_type(this->AsFFI());
    return ecitygml::RoofTypeValue::FromFFI(result);
}

inline std::optional<int64_t> ecitygml::Building::storeys_above_ground() const {
    auto result = ecitygml::capi::ecitygml_Building_storeys_above_ground(this->AsFFI());
    return result.is_ok ? std::optional<int64_t>(result.ok) : std::nullopt;
}

inline std::optional<int64_t> ecitygml::Building::storeys_below_ground() const {
    auto result = ecitygml::capi::ecitygml_Building_storeys_below_ground(this->AsFFI());
    return result.is_ok ? std::optional<int64_t>(result.ok) : std::nullopt;
}

inline std::unique_ptr<ecitygml::AbstractBuildingSubdivisionPropertyIterator> ecitygml::Building::building_subdivisions() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_building_subdivisions(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractBuildingSubdivisionPropertyIterator>(ecitygml::AbstractBuildingSubdivisionPropertyIterator::FromFFI(result));
}

inline const ecitygml::Building* ecitygml::Building::try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_Building_try_from(feature.AsFFI());
    return ecitygml::Building::FromFFI(result);
}

inline std::unique_ptr<ecitygml::BuildingPartPropertyIterator> ecitygml::Building::building_parts() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Building_building_parts(this->AsFFI());
    return std::unique_ptr<ecitygml::BuildingPartPropertyIterator>(ecitygml::BuildingPartPropertyIterator::FromFFI(result));
}

inline const ecitygml::capi::Building* ecitygml::Building::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::Building*>(this);
}

inline ecitygml::capi::Building* ecitygml::Building::AsFFI() {
    return reinterpret_cast<ecitygml::capi::Building*>(this);
}

inline const ecitygml::Building* ecitygml::Building::FromFFI(const ecitygml::capi::Building* ptr) {
    return reinterpret_cast<const ecitygml::Building*>(ptr);
}

inline ecitygml::Building* ecitygml::Building::FromFFI(ecitygml::capi::Building* ptr) {
    return reinterpret_cast<ecitygml::Building*>(ptr);
}

inline void ecitygml::Building::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_Building_destroy(reinterpret_cast<ecitygml::capi::Building*>(ptr));
}


#endif // ECITYGML_Building_HPP
