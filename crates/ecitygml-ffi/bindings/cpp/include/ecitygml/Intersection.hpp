#ifndef ecitygml_Intersection_HPP
#define ecitygml_Intersection_HPP

#include "Intersection.d.hpp"

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
#include "AuxiliaryTrafficSpacePropertyIterator.hpp"
#include "BoundingShape.hpp"
#include "CityObjectRelationPropertyIterator.hpp"
#include "CodeIterator.hpp"
#include "DateTime.hpp"
#include "ExternalReferenceIterator.hpp"
#include "GenericAttributeKindIterator.hpp"
#include "HolePropertyIterator.hpp"
#include "Id.hpp"
#include "IntersectionClassValue.hpp"
#include "MarkingPropertyIterator.hpp"
#include "MultiCurveProperty.hpp"
#include "MultiSurfaceProperty.hpp"
#include "OccupancyIterator.hpp"
#include "PointProperty.hpp"
#include "RelativeToTerrain.hpp"
#include "RelativeToWater.hpp"
#include "SolidProperty.hpp"
#include "SpaceType.hpp"
#include "TrafficDirectionValue.hpp"
#include "TrafficSpacePropertyIterator.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_Intersection_id(const ecitygml::capi::Intersection* self);

    ecitygml::capi::CodeIterator* ecitygml_Intersection_names(const ecitygml::capi::Intersection* self);

    const ecitygml::capi::BoundingShape* ecitygml_Intersection_bounded_by(const ecitygml::capi::Intersection* self);

    const ecitygml::capi::Id* ecitygml_Intersection_feature_id(const ecitygml::capi::Intersection* self);

    const ecitygml::capi::DateTime* ecitygml_Intersection_creation_date(const ecitygml::capi::Intersection* self);

    const ecitygml::capi::DateTime* ecitygml_Intersection_termination_date(const ecitygml::capi::Intersection* self);

    const ecitygml::capi::DateTime* ecitygml_Intersection_valid_from(const ecitygml::capi::Intersection* self);

    const ecitygml::capi::DateTime* ecitygml_Intersection_valid_to(const ecitygml::capi::Intersection* self);

    typedef struct ecitygml_Intersection_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_Intersection_relative_to_terrain_result;
    ecitygml_Intersection_relative_to_terrain_result ecitygml_Intersection_relative_to_terrain(const ecitygml::capi::Intersection* self);

    typedef struct ecitygml_Intersection_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_Intersection_relative_to_water_result;
    ecitygml_Intersection_relative_to_water_result ecitygml_Intersection_relative_to_water(const ecitygml::capi::Intersection* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_Intersection_external_references(const ecitygml::capi::Intersection* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_Intersection_generic_attributes(const ecitygml::capi::Intersection* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_Intersection_related_to(const ecitygml::capi::Intersection* self);

    typedef struct ecitygml_Intersection_space_type_result {union {ecitygml::capi::SpaceType ok; }; bool is_ok;} ecitygml_Intersection_space_type_result;
    ecitygml_Intersection_space_type_result ecitygml_Intersection_space_type(const ecitygml::capi::Intersection* self);

    const ecitygml::capi::SolidProperty* ecitygml_Intersection_lod1_solid(const ecitygml::capi::Intersection* self);

    const ecitygml::capi::SolidProperty* ecitygml_Intersection_lod2_solid(const ecitygml::capi::Intersection* self);

    const ecitygml::capi::SolidProperty* ecitygml_Intersection_lod3_solid(const ecitygml::capi::Intersection* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_Intersection_lod0_multi_surface(const ecitygml::capi::Intersection* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_Intersection_lod2_multi_surface(const ecitygml::capi::Intersection* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_Intersection_lod3_multi_surface(const ecitygml::capi::Intersection* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Intersection_lod0_multi_curve(const ecitygml::capi::Intersection* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Intersection_lod2_multi_curve(const ecitygml::capi::Intersection* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Intersection_lod3_multi_curve(const ecitygml::capi::Intersection* self);

    const ecitygml::capi::PointProperty* ecitygml_Intersection_lod0_point(const ecitygml::capi::Intersection* self);

    ecitygml::capi::AbstractSpaceBoundaryPropertyIterator* ecitygml_Intersection_boundaries(const ecitygml::capi::Intersection* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Intersection_lod1_terrain_intersection_curve(const ecitygml::capi::Intersection* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Intersection_lod2_terrain_intersection_curve(const ecitygml::capi::Intersection* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Intersection_lod3_terrain_intersection_curve(const ecitygml::capi::Intersection* self);

    typedef struct ecitygml_Intersection_traffic_direction_result {union {ecitygml::capi::TrafficDirectionValue ok; }; bool is_ok;} ecitygml_Intersection_traffic_direction_result;
    ecitygml_Intersection_traffic_direction_result ecitygml_Intersection_traffic_direction(const ecitygml::capi::Intersection* self);

    ecitygml::capi::OccupancyIterator* ecitygml_Intersection_occupancies(const ecitygml::capi::Intersection* self);

    ecitygml::capi::TrafficSpacePropertyIterator* ecitygml_Intersection_traffic_spaces(const ecitygml::capi::Intersection* self);

    ecitygml::capi::AuxiliaryTrafficSpacePropertyIterator* ecitygml_Intersection_auxiliary_traffic_spaces(const ecitygml::capi::Intersection* self);

    ecitygml::capi::MarkingPropertyIterator* ecitygml_Intersection_markings(const ecitygml::capi::Intersection* self);

    ecitygml::capi::HolePropertyIterator* ecitygml_Intersection_holes(const ecitygml::capi::Intersection* self);

    const ecitygml::capi::Intersection* ecitygml_Intersection_try_from(const ecitygml::capi::AbstractFeatureKindRef* feature);

    const ecitygml::capi::IntersectionClassValue* ecitygml_Intersection_class(const ecitygml::capi::Intersection* self);

    void ecitygml_Intersection_destroy(Intersection* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::Intersection::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Intersection_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::Intersection::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Intersection_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::Intersection::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Intersection_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::Intersection::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Intersection_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Intersection::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Intersection_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Intersection::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Intersection_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Intersection::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Intersection_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Intersection::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Intersection_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::Intersection::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_Intersection_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::Intersection::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_Intersection_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::Intersection::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Intersection_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::Intersection::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Intersection_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::Intersection::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Intersection_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline std::optional<ecitygml::SpaceType> ecitygml::Intersection::space_type() const {
    auto result = ecitygml::capi::ecitygml_Intersection_space_type(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::SpaceType>(ecitygml::SpaceType::FromFFI(result.ok)) : std::nullopt;
}

inline const ecitygml::SolidProperty* ecitygml::Intersection::lod1_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Intersection_lod1_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::Intersection::lod2_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Intersection_lod2_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::Intersection::lod3_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Intersection_lod3_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::Intersection::lod0_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Intersection_lod0_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::Intersection::lod2_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Intersection_lod2_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::Intersection::lod3_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Intersection_lod3_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Intersection::lod0_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Intersection_lod0_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Intersection::lod2_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Intersection_lod2_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Intersection::lod3_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Intersection_lod3_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::PointProperty* ecitygml::Intersection::lod0_point() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Intersection_lod0_point(this->AsFFI());
    return ecitygml::PointProperty::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator> ecitygml::Intersection::boundaries() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Intersection_boundaries(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator>(ecitygml::AbstractSpaceBoundaryPropertyIterator::FromFFI(result));
}

inline const ecitygml::MultiCurveProperty* ecitygml::Intersection::lod1_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Intersection_lod1_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Intersection::lod2_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Intersection_lod2_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Intersection::lod3_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Intersection_lod3_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline std::optional<ecitygml::TrafficDirectionValue> ecitygml::Intersection::traffic_direction() const {
    auto result = ecitygml::capi::ecitygml_Intersection_traffic_direction(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::TrafficDirectionValue>(ecitygml::TrafficDirectionValue::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::OccupancyIterator> ecitygml::Intersection::occupancies() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Intersection_occupancies(this->AsFFI());
    return std::unique_ptr<ecitygml::OccupancyIterator>(ecitygml::OccupancyIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::TrafficSpacePropertyIterator> ecitygml::Intersection::traffic_spaces() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Intersection_traffic_spaces(this->AsFFI());
    return std::unique_ptr<ecitygml::TrafficSpacePropertyIterator>(ecitygml::TrafficSpacePropertyIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::AuxiliaryTrafficSpacePropertyIterator> ecitygml::Intersection::auxiliary_traffic_spaces() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Intersection_auxiliary_traffic_spaces(this->AsFFI());
    return std::unique_ptr<ecitygml::AuxiliaryTrafficSpacePropertyIterator>(ecitygml::AuxiliaryTrafficSpacePropertyIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::MarkingPropertyIterator> ecitygml::Intersection::markings() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Intersection_markings(this->AsFFI());
    return std::unique_ptr<ecitygml::MarkingPropertyIterator>(ecitygml::MarkingPropertyIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::HolePropertyIterator> ecitygml::Intersection::holes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Intersection_holes(this->AsFFI());
    return std::unique_ptr<ecitygml::HolePropertyIterator>(ecitygml::HolePropertyIterator::FromFFI(result));
}

inline const ecitygml::Intersection* ecitygml::Intersection::try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_Intersection_try_from(feature.AsFFI());
    return ecitygml::Intersection::FromFFI(result);
}

inline const ecitygml::IntersectionClassValue* ecitygml::Intersection::class_() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Intersection_class(this->AsFFI());
    return ecitygml::IntersectionClassValue::FromFFI(result);
}

inline const ecitygml::capi::Intersection* ecitygml::Intersection::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::Intersection*>(this);
}

inline ecitygml::capi::Intersection* ecitygml::Intersection::AsFFI() {
    return reinterpret_cast<ecitygml::capi::Intersection*>(this);
}

inline const ecitygml::Intersection* ecitygml::Intersection::FromFFI(const ecitygml::capi::Intersection* ptr) {
    return reinterpret_cast<const ecitygml::Intersection*>(ptr);
}

inline ecitygml::Intersection* ecitygml::Intersection::FromFFI(ecitygml::capi::Intersection* ptr) {
    return reinterpret_cast<ecitygml::Intersection*>(ptr);
}

inline void ecitygml::Intersection::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_Intersection_destroy(reinterpret_cast<ecitygml::capi::Intersection*>(ptr));
}


#endif // ecitygml_Intersection_HPP
