#ifndef ECITYGML_SolitaryVegetationObject_HPP
#define ECITYGML_SolitaryVegetationObject_HPP

#include "SolitaryVegetationObject.d.hpp"

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
#include "DateTime.hpp"
#include "ExternalReferenceIterator.hpp"
#include "GenericAttributeKindIterator.hpp"
#include "Id.hpp"
#include "ImplicitGeometryProperty.hpp"
#include "Measure.hpp"
#include "MultiCurveProperty.hpp"
#include "MultiSurfaceProperty.hpp"
#include "PointProperty.hpp"
#include "RelativeToTerrain.hpp"
#include "RelativeToWater.hpp"
#include "SolidProperty.hpp"
#include "SolitaryVegetationObjectClassValue.hpp"
#include "SolitaryVegetationObjectFunctionValueIterator.hpp"
#include "SolitaryVegetationObjectUsageValueIterator.hpp"
#include "SpaceType.hpp"
#include "SpeciesValue.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_SolitaryVegetationObject_id(const ecitygml::capi::SolitaryVegetationObject* self);

    ecitygml::capi::CodeIterator* ecitygml_SolitaryVegetationObject_names(const ecitygml::capi::SolitaryVegetationObject* self);

    const ecitygml::capi::BoundingShape* ecitygml_SolitaryVegetationObject_bounded_by(const ecitygml::capi::SolitaryVegetationObject* self);

    const ecitygml::capi::Id* ecitygml_SolitaryVegetationObject_feature_id(const ecitygml::capi::SolitaryVegetationObject* self);

    const ecitygml::capi::DateTime* ecitygml_SolitaryVegetationObject_creation_date(const ecitygml::capi::SolitaryVegetationObject* self);

    const ecitygml::capi::DateTime* ecitygml_SolitaryVegetationObject_termination_date(const ecitygml::capi::SolitaryVegetationObject* self);

    const ecitygml::capi::DateTime* ecitygml_SolitaryVegetationObject_valid_from(const ecitygml::capi::SolitaryVegetationObject* self);

    const ecitygml::capi::DateTime* ecitygml_SolitaryVegetationObject_valid_to(const ecitygml::capi::SolitaryVegetationObject* self);

    typedef struct ecitygml_SolitaryVegetationObject_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_SolitaryVegetationObject_relative_to_terrain_result;
    ecitygml_SolitaryVegetationObject_relative_to_terrain_result ecitygml_SolitaryVegetationObject_relative_to_terrain(const ecitygml::capi::SolitaryVegetationObject* self);

    typedef struct ecitygml_SolitaryVegetationObject_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_SolitaryVegetationObject_relative_to_water_result;
    ecitygml_SolitaryVegetationObject_relative_to_water_result ecitygml_SolitaryVegetationObject_relative_to_water(const ecitygml::capi::SolitaryVegetationObject* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_SolitaryVegetationObject_external_references(const ecitygml::capi::SolitaryVegetationObject* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_SolitaryVegetationObject_generic_attributes(const ecitygml::capi::SolitaryVegetationObject* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_SolitaryVegetationObject_related_to(const ecitygml::capi::SolitaryVegetationObject* self);

    typedef struct ecitygml_SolitaryVegetationObject_space_type_result {union {ecitygml::capi::SpaceType ok; }; bool is_ok;} ecitygml_SolitaryVegetationObject_space_type_result;
    ecitygml_SolitaryVegetationObject_space_type_result ecitygml_SolitaryVegetationObject_space_type(const ecitygml::capi::SolitaryVegetationObject* self);

    const ecitygml::capi::SolidProperty* ecitygml_SolitaryVegetationObject_lod1_solid(const ecitygml::capi::SolitaryVegetationObject* self);

    const ecitygml::capi::SolidProperty* ecitygml_SolitaryVegetationObject_lod2_solid(const ecitygml::capi::SolitaryVegetationObject* self);

    const ecitygml::capi::SolidProperty* ecitygml_SolitaryVegetationObject_lod3_solid(const ecitygml::capi::SolitaryVegetationObject* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_SolitaryVegetationObject_lod0_multi_surface(const ecitygml::capi::SolitaryVegetationObject* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_SolitaryVegetationObject_lod2_multi_surface(const ecitygml::capi::SolitaryVegetationObject* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_SolitaryVegetationObject_lod3_multi_surface(const ecitygml::capi::SolitaryVegetationObject* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_SolitaryVegetationObject_lod0_multi_curve(const ecitygml::capi::SolitaryVegetationObject* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_SolitaryVegetationObject_lod2_multi_curve(const ecitygml::capi::SolitaryVegetationObject* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_SolitaryVegetationObject_lod3_multi_curve(const ecitygml::capi::SolitaryVegetationObject* self);

    const ecitygml::capi::PointProperty* ecitygml_SolitaryVegetationObject_lod0_point(const ecitygml::capi::SolitaryVegetationObject* self);

    ecitygml::capi::AbstractSpaceBoundaryPropertyIterator* ecitygml_SolitaryVegetationObject_boundaries(const ecitygml::capi::SolitaryVegetationObject* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_SolitaryVegetationObject_lod1_terrain_intersection_curve(const ecitygml::capi::SolitaryVegetationObject* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_SolitaryVegetationObject_lod2_terrain_intersection_curve(const ecitygml::capi::SolitaryVegetationObject* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_SolitaryVegetationObject_lod3_terrain_intersection_curve(const ecitygml::capi::SolitaryVegetationObject* self);

    const ecitygml::capi::ImplicitGeometryProperty* ecitygml_SolitaryVegetationObject_lod1_implicit_representation(const ecitygml::capi::SolitaryVegetationObject* self);

    const ecitygml::capi::ImplicitGeometryProperty* ecitygml_SolitaryVegetationObject_lod2_implicit_representation(const ecitygml::capi::SolitaryVegetationObject* self);

    const ecitygml::capi::ImplicitGeometryProperty* ecitygml_SolitaryVegetationObject_lod3_implicit_representation(const ecitygml::capi::SolitaryVegetationObject* self);

    const ecitygml::capi::SolitaryVegetationObject* ecitygml_SolitaryVegetationObject_try_from(const ecitygml::capi::AbstractFeatureKindRef* feature);

    const ecitygml::capi::SolitaryVegetationObjectClassValue* ecitygml_SolitaryVegetationObject_class(const ecitygml::capi::SolitaryVegetationObject* self);

    ecitygml::capi::SolitaryVegetationObjectFunctionValueIterator* ecitygml_SolitaryVegetationObject_functions(const ecitygml::capi::SolitaryVegetationObject* self);

    ecitygml::capi::SolitaryVegetationObjectUsageValueIterator* ecitygml_SolitaryVegetationObject_usages(const ecitygml::capi::SolitaryVegetationObject* self);

    const ecitygml::capi::SpeciesValue* ecitygml_SolitaryVegetationObject_species(const ecitygml::capi::SolitaryVegetationObject* self);

    const ecitygml::capi::Measure* ecitygml_SolitaryVegetationObject_height(const ecitygml::capi::SolitaryVegetationObject* self);

    const ecitygml::capi::Measure* ecitygml_SolitaryVegetationObject_trunk_diameter(const ecitygml::capi::SolitaryVegetationObject* self);

    const ecitygml::capi::Measure* ecitygml_SolitaryVegetationObject_crown_diameter(const ecitygml::capi::SolitaryVegetationObject* self);

    const ecitygml::capi::Measure* ecitygml_SolitaryVegetationObject_root_ball_diameter(const ecitygml::capi::SolitaryVegetationObject* self);

    const ecitygml::capi::Measure* ecitygml_SolitaryVegetationObject_max_root_ball_depth(const ecitygml::capi::SolitaryVegetationObject* self);

    void ecitygml_SolitaryVegetationObject_destroy(SolitaryVegetationObject* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::SolitaryVegetationObject::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::SolitaryVegetationObject::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::SolitaryVegetationObject::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::SolitaryVegetationObject::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::SolitaryVegetationObject::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::SolitaryVegetationObject::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::SolitaryVegetationObject::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::SolitaryVegetationObject::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::SolitaryVegetationObject::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::SolitaryVegetationObject::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::SolitaryVegetationObject::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::SolitaryVegetationObject::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::SolitaryVegetationObject::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline std::optional<ecitygml::SpaceType> ecitygml::SolitaryVegetationObject::space_type() const {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_space_type(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::SpaceType>(ecitygml::SpaceType::FromFFI(result.ok)) : std::nullopt;
}

inline const ecitygml::SolidProperty* ecitygml::SolitaryVegetationObject::lod1_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_lod1_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::SolitaryVegetationObject::lod2_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_lod2_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::SolitaryVegetationObject::lod3_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_lod3_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::SolitaryVegetationObject::lod0_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_lod0_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::SolitaryVegetationObject::lod2_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_lod2_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::SolitaryVegetationObject::lod3_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_lod3_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::SolitaryVegetationObject::lod0_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_lod0_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::SolitaryVegetationObject::lod2_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_lod2_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::SolitaryVegetationObject::lod3_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_lod3_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::PointProperty* ecitygml::SolitaryVegetationObject::lod0_point() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_lod0_point(this->AsFFI());
    return ecitygml::PointProperty::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator> ecitygml::SolitaryVegetationObject::boundaries() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_boundaries(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator>(ecitygml::AbstractSpaceBoundaryPropertyIterator::FromFFI(result));
}

inline const ecitygml::MultiCurveProperty* ecitygml::SolitaryVegetationObject::lod1_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_lod1_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::SolitaryVegetationObject::lod2_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_lod2_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::SolitaryVegetationObject::lod3_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_lod3_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::ImplicitGeometryProperty* ecitygml::SolitaryVegetationObject::lod1_implicit_representation() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_lod1_implicit_representation(this->AsFFI());
    return ecitygml::ImplicitGeometryProperty::FromFFI(result);
}

inline const ecitygml::ImplicitGeometryProperty* ecitygml::SolitaryVegetationObject::lod2_implicit_representation() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_lod2_implicit_representation(this->AsFFI());
    return ecitygml::ImplicitGeometryProperty::FromFFI(result);
}

inline const ecitygml::ImplicitGeometryProperty* ecitygml::SolitaryVegetationObject::lod3_implicit_representation() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_lod3_implicit_representation(this->AsFFI());
    return ecitygml::ImplicitGeometryProperty::FromFFI(result);
}

inline const ecitygml::SolitaryVegetationObject* ecitygml::SolitaryVegetationObject::try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_try_from(feature.AsFFI());
    return ecitygml::SolitaryVegetationObject::FromFFI(result);
}

inline const ecitygml::SolitaryVegetationObjectClassValue* ecitygml::SolitaryVegetationObject::class_() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_class(this->AsFFI());
    return ecitygml::SolitaryVegetationObjectClassValue::FromFFI(result);
}

inline std::unique_ptr<ecitygml::SolitaryVegetationObjectFunctionValueIterator> ecitygml::SolitaryVegetationObject::functions() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_functions(this->AsFFI());
    return std::unique_ptr<ecitygml::SolitaryVegetationObjectFunctionValueIterator>(ecitygml::SolitaryVegetationObjectFunctionValueIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::SolitaryVegetationObjectUsageValueIterator> ecitygml::SolitaryVegetationObject::usages() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_usages(this->AsFFI());
    return std::unique_ptr<ecitygml::SolitaryVegetationObjectUsageValueIterator>(ecitygml::SolitaryVegetationObjectUsageValueIterator::FromFFI(result));
}

inline const ecitygml::SpeciesValue* ecitygml::SolitaryVegetationObject::species() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_species(this->AsFFI());
    return ecitygml::SpeciesValue::FromFFI(result);
}

inline const ecitygml::Measure* ecitygml::SolitaryVegetationObject::height() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_height(this->AsFFI());
    return ecitygml::Measure::FromFFI(result);
}

inline const ecitygml::Measure* ecitygml::SolitaryVegetationObject::trunk_diameter() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_trunk_diameter(this->AsFFI());
    return ecitygml::Measure::FromFFI(result);
}

inline const ecitygml::Measure* ecitygml::SolitaryVegetationObject::crown_diameter() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_crown_diameter(this->AsFFI());
    return ecitygml::Measure::FromFFI(result);
}

inline const ecitygml::Measure* ecitygml::SolitaryVegetationObject::root_ball_diameter() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_root_ball_diameter(this->AsFFI());
    return ecitygml::Measure::FromFFI(result);
}

inline const ecitygml::Measure* ecitygml::SolitaryVegetationObject::max_root_ball_depth() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObject_max_root_ball_depth(this->AsFFI());
    return ecitygml::Measure::FromFFI(result);
}

inline const ecitygml::capi::SolitaryVegetationObject* ecitygml::SolitaryVegetationObject::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::SolitaryVegetationObject*>(this);
}

inline ecitygml::capi::SolitaryVegetationObject* ecitygml::SolitaryVegetationObject::AsFFI() {
    return reinterpret_cast<ecitygml::capi::SolitaryVegetationObject*>(this);
}

inline const ecitygml::SolitaryVegetationObject* ecitygml::SolitaryVegetationObject::FromFFI(const ecitygml::capi::SolitaryVegetationObject* ptr) {
    return reinterpret_cast<const ecitygml::SolitaryVegetationObject*>(ptr);
}

inline ecitygml::SolitaryVegetationObject* ecitygml::SolitaryVegetationObject::FromFFI(ecitygml::capi::SolitaryVegetationObject* ptr) {
    return reinterpret_cast<ecitygml::SolitaryVegetationObject*>(ptr);
}

inline void ecitygml::SolitaryVegetationObject::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_SolitaryVegetationObject_destroy(reinterpret_cast<ecitygml::capi::SolitaryVegetationObject*>(ptr));
}


#endif // ECITYGML_SolitaryVegetationObject_HPP
