#ifndef ECITYGML_Section_HPP
#define ECITYGML_Section_HPP

#include "Section.d.hpp"

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
#include "MarkingPropertyIterator.hpp"
#include "MultiCurveProperty.hpp"
#include "MultiSurfaceProperty.hpp"
#include "OccupancyIterator.hpp"
#include "PointProperty.hpp"
#include "RelativeToTerrain.hpp"
#include "RelativeToWater.hpp"
#include "SectionClassValue.hpp"
#include "SolidProperty.hpp"
#include "SpaceType.hpp"
#include "TrafficDirectionValue.hpp"
#include "TrafficSpacePropertyIterator.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_Section_id(const ecitygml::capi::Section* self);

    ecitygml::capi::CodeIterator* ecitygml_Section_names(const ecitygml::capi::Section* self);

    const ecitygml::capi::BoundingShape* ecitygml_Section_bounded_by(const ecitygml::capi::Section* self);

    const ecitygml::capi::Id* ecitygml_Section_feature_id(const ecitygml::capi::Section* self);

    const ecitygml::capi::DateTime* ecitygml_Section_creation_date(const ecitygml::capi::Section* self);

    const ecitygml::capi::DateTime* ecitygml_Section_termination_date(const ecitygml::capi::Section* self);

    const ecitygml::capi::DateTime* ecitygml_Section_valid_from(const ecitygml::capi::Section* self);

    const ecitygml::capi::DateTime* ecitygml_Section_valid_to(const ecitygml::capi::Section* self);

    typedef struct ecitygml_Section_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_Section_relative_to_terrain_result;
    ecitygml_Section_relative_to_terrain_result ecitygml_Section_relative_to_terrain(const ecitygml::capi::Section* self);

    typedef struct ecitygml_Section_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_Section_relative_to_water_result;
    ecitygml_Section_relative_to_water_result ecitygml_Section_relative_to_water(const ecitygml::capi::Section* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_Section_external_references(const ecitygml::capi::Section* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_Section_generic_attributes(const ecitygml::capi::Section* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_Section_related_to(const ecitygml::capi::Section* self);

    typedef struct ecitygml_Section_space_type_result {union {ecitygml::capi::SpaceType ok; }; bool is_ok;} ecitygml_Section_space_type_result;
    ecitygml_Section_space_type_result ecitygml_Section_space_type(const ecitygml::capi::Section* self);

    const ecitygml::capi::SolidProperty* ecitygml_Section_lod1_solid(const ecitygml::capi::Section* self);

    const ecitygml::capi::SolidProperty* ecitygml_Section_lod2_solid(const ecitygml::capi::Section* self);

    const ecitygml::capi::SolidProperty* ecitygml_Section_lod3_solid(const ecitygml::capi::Section* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_Section_lod0_multi_surface(const ecitygml::capi::Section* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_Section_lod2_multi_surface(const ecitygml::capi::Section* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_Section_lod3_multi_surface(const ecitygml::capi::Section* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Section_lod0_multi_curve(const ecitygml::capi::Section* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Section_lod2_multi_curve(const ecitygml::capi::Section* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Section_lod3_multi_curve(const ecitygml::capi::Section* self);

    const ecitygml::capi::PointProperty* ecitygml_Section_lod0_point(const ecitygml::capi::Section* self);

    ecitygml::capi::AbstractSpaceBoundaryPropertyIterator* ecitygml_Section_boundaries(const ecitygml::capi::Section* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Section_lod1_terrain_intersection_curve(const ecitygml::capi::Section* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Section_lod2_terrain_intersection_curve(const ecitygml::capi::Section* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Section_lod3_terrain_intersection_curve(const ecitygml::capi::Section* self);

    typedef struct ecitygml_Section_traffic_direction_result {union {ecitygml::capi::TrafficDirectionValue ok; }; bool is_ok;} ecitygml_Section_traffic_direction_result;
    ecitygml_Section_traffic_direction_result ecitygml_Section_traffic_direction(const ecitygml::capi::Section* self);

    ecitygml::capi::OccupancyIterator* ecitygml_Section_occupancies(const ecitygml::capi::Section* self);

    ecitygml::capi::TrafficSpacePropertyIterator* ecitygml_Section_traffic_spaces(const ecitygml::capi::Section* self);

    ecitygml::capi::AuxiliaryTrafficSpacePropertyIterator* ecitygml_Section_auxiliary_traffic_spaces(const ecitygml::capi::Section* self);

    ecitygml::capi::MarkingPropertyIterator* ecitygml_Section_markings(const ecitygml::capi::Section* self);

    ecitygml::capi::HolePropertyIterator* ecitygml_Section_holes(const ecitygml::capi::Section* self);

    const ecitygml::capi::Section* ecitygml_Section_try_from(const ecitygml::capi::AbstractFeatureKindRef* feature);

    const ecitygml::capi::SectionClassValue* ecitygml_Section_class(const ecitygml::capi::Section* self);

    void ecitygml_Section_destroy(Section* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::Section::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Section_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::Section::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Section_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::Section::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Section_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::Section::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Section_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Section::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Section_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Section::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Section_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Section::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Section_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Section::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Section_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::Section::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_Section_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::Section::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_Section_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::Section::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Section_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::Section::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Section_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::Section::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Section_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline std::optional<ecitygml::SpaceType> ecitygml::Section::space_type() const {
    auto result = ecitygml::capi::ecitygml_Section_space_type(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::SpaceType>(ecitygml::SpaceType::FromFFI(result.ok)) : std::nullopt;
}

inline const ecitygml::SolidProperty* ecitygml::Section::lod1_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Section_lod1_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::Section::lod2_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Section_lod2_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::Section::lod3_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Section_lod3_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::Section::lod0_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Section_lod0_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::Section::lod2_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Section_lod2_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::Section::lod3_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Section_lod3_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Section::lod0_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Section_lod0_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Section::lod2_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Section_lod2_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Section::lod3_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Section_lod3_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::PointProperty* ecitygml::Section::lod0_point() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Section_lod0_point(this->AsFFI());
    return ecitygml::PointProperty::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator> ecitygml::Section::boundaries() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Section_boundaries(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator>(ecitygml::AbstractSpaceBoundaryPropertyIterator::FromFFI(result));
}

inline const ecitygml::MultiCurveProperty* ecitygml::Section::lod1_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Section_lod1_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Section::lod2_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Section_lod2_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Section::lod3_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Section_lod3_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline std::optional<ecitygml::TrafficDirectionValue> ecitygml::Section::traffic_direction() const {
    auto result = ecitygml::capi::ecitygml_Section_traffic_direction(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::TrafficDirectionValue>(ecitygml::TrafficDirectionValue::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::OccupancyIterator> ecitygml::Section::occupancies() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Section_occupancies(this->AsFFI());
    return std::unique_ptr<ecitygml::OccupancyIterator>(ecitygml::OccupancyIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::TrafficSpacePropertyIterator> ecitygml::Section::traffic_spaces() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Section_traffic_spaces(this->AsFFI());
    return std::unique_ptr<ecitygml::TrafficSpacePropertyIterator>(ecitygml::TrafficSpacePropertyIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::AuxiliaryTrafficSpacePropertyIterator> ecitygml::Section::auxiliary_traffic_spaces() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Section_auxiliary_traffic_spaces(this->AsFFI());
    return std::unique_ptr<ecitygml::AuxiliaryTrafficSpacePropertyIterator>(ecitygml::AuxiliaryTrafficSpacePropertyIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::MarkingPropertyIterator> ecitygml::Section::markings() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Section_markings(this->AsFFI());
    return std::unique_ptr<ecitygml::MarkingPropertyIterator>(ecitygml::MarkingPropertyIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::HolePropertyIterator> ecitygml::Section::holes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Section_holes(this->AsFFI());
    return std::unique_ptr<ecitygml::HolePropertyIterator>(ecitygml::HolePropertyIterator::FromFFI(result));
}

inline const ecitygml::Section* ecitygml::Section::try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_Section_try_from(feature.AsFFI());
    return ecitygml::Section::FromFFI(result);
}

inline const ecitygml::SectionClassValue* ecitygml::Section::class_() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Section_class(this->AsFFI());
    return ecitygml::SectionClassValue::FromFFI(result);
}

inline const ecitygml::capi::Section* ecitygml::Section::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::Section*>(this);
}

inline ecitygml::capi::Section* ecitygml::Section::AsFFI() {
    return reinterpret_cast<ecitygml::capi::Section*>(this);
}

inline const ecitygml::Section* ecitygml::Section::FromFFI(const ecitygml::capi::Section* ptr) {
    return reinterpret_cast<const ecitygml::Section*>(ptr);
}

inline ecitygml::Section* ecitygml::Section::FromFFI(ecitygml::capi::Section* ptr) {
    return reinterpret_cast<ecitygml::Section*>(ptr);
}

inline void ecitygml::Section::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_Section_destroy(reinterpret_cast<ecitygml::capi::Section*>(ptr));
}


#endif // ECITYGML_Section_HPP
