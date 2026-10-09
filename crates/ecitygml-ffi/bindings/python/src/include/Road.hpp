#ifndef ECITYGML_Road_HPP
#define ECITYGML_Road_HPP

#include "Road.d.hpp"

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
#include "AuxiliaryTrafficSpacePropertyIterator.hpp"
#include "BoundingShape.hpp"
#include "CityObjectRelationPropertyIterator.hpp"
#include "CodeIterator.hpp"
#include "DateTime.hpp"
#include "ExternalReferenceIterator.hpp"
#include "GenericAttributeKindIterator.hpp"
#include "HolePropertyIterator.hpp"
#include "Id.hpp"
#include "IntersectionPropertyIterator.hpp"
#include "MarkingPropertyIterator.hpp"
#include "MultiCurveProperty.hpp"
#include "MultiSurfaceProperty.hpp"
#include "OccupancyIterator.hpp"
#include "PointProperty.hpp"
#include "RelativeToTerrain.hpp"
#include "RelativeToWater.hpp"
#include "RoadClassValue.hpp"
#include "RoadFunctionValueIterator.hpp"
#include "RoadUsageValueIterator.hpp"
#include "SectionPropertyIterator.hpp"
#include "SolidProperty.hpp"
#include "SpaceType.hpp"
#include "TrafficDirectionValue.hpp"
#include "TrafficSpacePropertyIterator.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_Road_id(const ecitygml::capi::Road* self);

    ecitygml::capi::CodeIterator* ecitygml_Road_names(const ecitygml::capi::Road* self);

    const ecitygml::capi::BoundingShape* ecitygml_Road_bounded_by(const ecitygml::capi::Road* self);

    const ecitygml::capi::Id* ecitygml_Road_feature_id(const ecitygml::capi::Road* self);

    const ecitygml::capi::DateTime* ecitygml_Road_creation_date(const ecitygml::capi::Road* self);

    const ecitygml::capi::DateTime* ecitygml_Road_termination_date(const ecitygml::capi::Road* self);

    const ecitygml::capi::DateTime* ecitygml_Road_valid_from(const ecitygml::capi::Road* self);

    const ecitygml::capi::DateTime* ecitygml_Road_valid_to(const ecitygml::capi::Road* self);

    typedef struct ecitygml_Road_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_Road_relative_to_terrain_result;
    ecitygml_Road_relative_to_terrain_result ecitygml_Road_relative_to_terrain(const ecitygml::capi::Road* self);

    typedef struct ecitygml_Road_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_Road_relative_to_water_result;
    ecitygml_Road_relative_to_water_result ecitygml_Road_relative_to_water(const ecitygml::capi::Road* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_Road_external_references(const ecitygml::capi::Road* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_Road_generic_attributes(const ecitygml::capi::Road* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_Road_related_to(const ecitygml::capi::Road* self);

    typedef struct ecitygml_Road_space_type_result {union {ecitygml::capi::SpaceType ok; }; bool is_ok;} ecitygml_Road_space_type_result;
    ecitygml_Road_space_type_result ecitygml_Road_space_type(const ecitygml::capi::Road* self);

    const ecitygml::capi::SolidProperty* ecitygml_Road_lod1_solid(const ecitygml::capi::Road* self);

    const ecitygml::capi::SolidProperty* ecitygml_Road_lod2_solid(const ecitygml::capi::Road* self);

    const ecitygml::capi::SolidProperty* ecitygml_Road_lod3_solid(const ecitygml::capi::Road* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_Road_lod0_multi_surface(const ecitygml::capi::Road* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_Road_lod2_multi_surface(const ecitygml::capi::Road* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_Road_lod3_multi_surface(const ecitygml::capi::Road* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Road_lod0_multi_curve(const ecitygml::capi::Road* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Road_lod2_multi_curve(const ecitygml::capi::Road* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Road_lod3_multi_curve(const ecitygml::capi::Road* self);

    const ecitygml::capi::PointProperty* ecitygml_Road_lod0_point(const ecitygml::capi::Road* self);

    ecitygml::capi::AbstractSpaceBoundaryPropertyIterator* ecitygml_Road_boundaries(const ecitygml::capi::Road* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Road_lod1_terrain_intersection_curve(const ecitygml::capi::Road* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Road_lod2_terrain_intersection_curve(const ecitygml::capi::Road* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Road_lod3_terrain_intersection_curve(const ecitygml::capi::Road* self);

    typedef struct ecitygml_Road_traffic_direction_result {union {ecitygml::capi::TrafficDirectionValue ok; }; bool is_ok;} ecitygml_Road_traffic_direction_result;
    ecitygml_Road_traffic_direction_result ecitygml_Road_traffic_direction(const ecitygml::capi::Road* self);

    ecitygml::capi::OccupancyIterator* ecitygml_Road_occupancies(const ecitygml::capi::Road* self);

    ecitygml::capi::TrafficSpacePropertyIterator* ecitygml_Road_traffic_spaces(const ecitygml::capi::Road* self);

    ecitygml::capi::AuxiliaryTrafficSpacePropertyIterator* ecitygml_Road_auxiliary_traffic_spaces(const ecitygml::capi::Road* self);

    ecitygml::capi::MarkingPropertyIterator* ecitygml_Road_markings(const ecitygml::capi::Road* self);

    ecitygml::capi::HolePropertyIterator* ecitygml_Road_holes(const ecitygml::capi::Road* self);

    const ecitygml::capi::Road* ecitygml_Road_try_from(const ecitygml::capi::AbstractFeatureKindRef* feature);

    const ecitygml::capi::RoadClassValue* ecitygml_Road_class(const ecitygml::capi::Road* self);

    ecitygml::capi::RoadFunctionValueIterator* ecitygml_Road_functions(const ecitygml::capi::Road* self);

    ecitygml::capi::RoadUsageValueIterator* ecitygml_Road_usages(const ecitygml::capi::Road* self);

    ecitygml::capi::SectionPropertyIterator* ecitygml_Road_sections(const ecitygml::capi::Road* self);

    ecitygml::capi::IntersectionPropertyIterator* ecitygml_Road_intersections(const ecitygml::capi::Road* self);

    void ecitygml_Road_destroy(Road* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::Road::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::Road::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::Road::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::Road::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Road::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Road::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Road::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Road::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::Road::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_Road_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::Road::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_Road_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::Road::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::Road::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::Road::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline std::optional<ecitygml::SpaceType> ecitygml::Road::space_type() const {
    auto result = ecitygml::capi::ecitygml_Road_space_type(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::SpaceType>(ecitygml::SpaceType::FromFFI(result.ok)) : std::nullopt;
}

inline const ecitygml::SolidProperty* ecitygml::Road::lod1_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_lod1_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::Road::lod2_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_lod2_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::Road::lod3_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_lod3_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::Road::lod0_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_lod0_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::Road::lod2_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_lod2_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::Road::lod3_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_lod3_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Road::lod0_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_lod0_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Road::lod2_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_lod2_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Road::lod3_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_lod3_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::PointProperty* ecitygml::Road::lod0_point() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_lod0_point(this->AsFFI());
    return ecitygml::PointProperty::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator> ecitygml::Road::boundaries() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_boundaries(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator>(ecitygml::AbstractSpaceBoundaryPropertyIterator::FromFFI(result));
}

inline const ecitygml::MultiCurveProperty* ecitygml::Road::lod1_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_lod1_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Road::lod2_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_lod2_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Road::lod3_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_lod3_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline std::optional<ecitygml::TrafficDirectionValue> ecitygml::Road::traffic_direction() const {
    auto result = ecitygml::capi::ecitygml_Road_traffic_direction(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::TrafficDirectionValue>(ecitygml::TrafficDirectionValue::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::OccupancyIterator> ecitygml::Road::occupancies() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_occupancies(this->AsFFI());
    return std::unique_ptr<ecitygml::OccupancyIterator>(ecitygml::OccupancyIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::TrafficSpacePropertyIterator> ecitygml::Road::traffic_spaces() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_traffic_spaces(this->AsFFI());
    return std::unique_ptr<ecitygml::TrafficSpacePropertyIterator>(ecitygml::TrafficSpacePropertyIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::AuxiliaryTrafficSpacePropertyIterator> ecitygml::Road::auxiliary_traffic_spaces() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_auxiliary_traffic_spaces(this->AsFFI());
    return std::unique_ptr<ecitygml::AuxiliaryTrafficSpacePropertyIterator>(ecitygml::AuxiliaryTrafficSpacePropertyIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::MarkingPropertyIterator> ecitygml::Road::markings() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_markings(this->AsFFI());
    return std::unique_ptr<ecitygml::MarkingPropertyIterator>(ecitygml::MarkingPropertyIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::HolePropertyIterator> ecitygml::Road::holes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_holes(this->AsFFI());
    return std::unique_ptr<ecitygml::HolePropertyIterator>(ecitygml::HolePropertyIterator::FromFFI(result));
}

inline const ecitygml::Road* ecitygml::Road::try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_Road_try_from(feature.AsFFI());
    return ecitygml::Road::FromFFI(result);
}

inline const ecitygml::RoadClassValue* ecitygml::Road::class_() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_class(this->AsFFI());
    return ecitygml::RoadClassValue::FromFFI(result);
}

inline std::unique_ptr<ecitygml::RoadFunctionValueIterator> ecitygml::Road::functions() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_functions(this->AsFFI());
    return std::unique_ptr<ecitygml::RoadFunctionValueIterator>(ecitygml::RoadFunctionValueIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::RoadUsageValueIterator> ecitygml::Road::usages() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_usages(this->AsFFI());
    return std::unique_ptr<ecitygml::RoadUsageValueIterator>(ecitygml::RoadUsageValueIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::SectionPropertyIterator> ecitygml::Road::sections() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_sections(this->AsFFI());
    return std::unique_ptr<ecitygml::SectionPropertyIterator>(ecitygml::SectionPropertyIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::IntersectionPropertyIterator> ecitygml::Road::intersections() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Road_intersections(this->AsFFI());
    return std::unique_ptr<ecitygml::IntersectionPropertyIterator>(ecitygml::IntersectionPropertyIterator::FromFFI(result));
}

inline const ecitygml::capi::Road* ecitygml::Road::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::Road*>(this);
}

inline ecitygml::capi::Road* ecitygml::Road::AsFFI() {
    return reinterpret_cast<ecitygml::capi::Road*>(this);
}

inline const ecitygml::Road* ecitygml::Road::FromFFI(const ecitygml::capi::Road* ptr) {
    return reinterpret_cast<const ecitygml::Road*>(ptr);
}

inline ecitygml::Road* ecitygml::Road::FromFFI(ecitygml::capi::Road* ptr) {
    return reinterpret_cast<ecitygml::Road*>(ptr);
}

inline void ecitygml::Road::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_Road_destroy(reinterpret_cast<ecitygml::capi::Road*>(ptr));
}


#endif // ECITYGML_Road_HPP
