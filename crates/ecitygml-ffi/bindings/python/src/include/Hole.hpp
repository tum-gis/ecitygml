#ifndef ECITYGML_Hole_HPP
#define ECITYGML_Hole_HPP

#include "Hole.d.hpp"

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
#include "HoleClassValue.hpp"
#include "Id.hpp"
#include "MultiCurveProperty.hpp"
#include "MultiSurfaceProperty.hpp"
#include "PointProperty.hpp"
#include "RelativeToTerrain.hpp"
#include "RelativeToWater.hpp"
#include "SolidProperty.hpp"
#include "SpaceType.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_Hole_id(const ecitygml::capi::Hole* self);

    ecitygml::capi::CodeIterator* ecitygml_Hole_names(const ecitygml::capi::Hole* self);

    const ecitygml::capi::BoundingShape* ecitygml_Hole_bounded_by(const ecitygml::capi::Hole* self);

    const ecitygml::capi::Id* ecitygml_Hole_feature_id(const ecitygml::capi::Hole* self);

    const ecitygml::capi::DateTime* ecitygml_Hole_creation_date(const ecitygml::capi::Hole* self);

    const ecitygml::capi::DateTime* ecitygml_Hole_termination_date(const ecitygml::capi::Hole* self);

    const ecitygml::capi::DateTime* ecitygml_Hole_valid_from(const ecitygml::capi::Hole* self);

    const ecitygml::capi::DateTime* ecitygml_Hole_valid_to(const ecitygml::capi::Hole* self);

    typedef struct ecitygml_Hole_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_Hole_relative_to_terrain_result;
    ecitygml_Hole_relative_to_terrain_result ecitygml_Hole_relative_to_terrain(const ecitygml::capi::Hole* self);

    typedef struct ecitygml_Hole_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_Hole_relative_to_water_result;
    ecitygml_Hole_relative_to_water_result ecitygml_Hole_relative_to_water(const ecitygml::capi::Hole* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_Hole_external_references(const ecitygml::capi::Hole* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_Hole_generic_attributes(const ecitygml::capi::Hole* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_Hole_related_to(const ecitygml::capi::Hole* self);

    typedef struct ecitygml_Hole_space_type_result {union {ecitygml::capi::SpaceType ok; }; bool is_ok;} ecitygml_Hole_space_type_result;
    ecitygml_Hole_space_type_result ecitygml_Hole_space_type(const ecitygml::capi::Hole* self);

    const ecitygml::capi::SolidProperty* ecitygml_Hole_lod1_solid(const ecitygml::capi::Hole* self);

    const ecitygml::capi::SolidProperty* ecitygml_Hole_lod2_solid(const ecitygml::capi::Hole* self);

    const ecitygml::capi::SolidProperty* ecitygml_Hole_lod3_solid(const ecitygml::capi::Hole* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_Hole_lod0_multi_surface(const ecitygml::capi::Hole* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_Hole_lod2_multi_surface(const ecitygml::capi::Hole* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_Hole_lod3_multi_surface(const ecitygml::capi::Hole* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Hole_lod0_multi_curve(const ecitygml::capi::Hole* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Hole_lod2_multi_curve(const ecitygml::capi::Hole* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Hole_lod3_multi_curve(const ecitygml::capi::Hole* self);

    const ecitygml::capi::PointProperty* ecitygml_Hole_lod0_point(const ecitygml::capi::Hole* self);

    ecitygml::capi::AbstractSpaceBoundaryPropertyIterator* ecitygml_Hole_boundaries(const ecitygml::capi::Hole* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Hole_lod1_terrain_intersection_curve(const ecitygml::capi::Hole* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Hole_lod2_terrain_intersection_curve(const ecitygml::capi::Hole* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Hole_lod3_terrain_intersection_curve(const ecitygml::capi::Hole* self);

    const ecitygml::capi::Hole* ecitygml_Hole_try_from(const ecitygml::capi::AbstractFeatureKindRef* feature);

    const ecitygml::capi::HoleClassValue* ecitygml_Hole_class(const ecitygml::capi::Hole* self);

    void ecitygml_Hole_destroy(Hole* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::Hole::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Hole_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::Hole::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Hole_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::Hole::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Hole_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::Hole::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Hole_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Hole::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Hole_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Hole::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Hole_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Hole::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Hole_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Hole::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Hole_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::Hole::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_Hole_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::Hole::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_Hole_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::Hole::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Hole_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::Hole::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Hole_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::Hole::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Hole_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline std::optional<ecitygml::SpaceType> ecitygml::Hole::space_type() const {
    auto result = ecitygml::capi::ecitygml_Hole_space_type(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::SpaceType>(ecitygml::SpaceType::FromFFI(result.ok)) : std::nullopt;
}

inline const ecitygml::SolidProperty* ecitygml::Hole::lod1_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Hole_lod1_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::Hole::lod2_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Hole_lod2_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::Hole::lod3_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Hole_lod3_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::Hole::lod0_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Hole_lod0_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::Hole::lod2_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Hole_lod2_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::Hole::lod3_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Hole_lod3_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Hole::lod0_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Hole_lod0_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Hole::lod2_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Hole_lod2_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Hole::lod3_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Hole_lod3_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::PointProperty* ecitygml::Hole::lod0_point() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Hole_lod0_point(this->AsFFI());
    return ecitygml::PointProperty::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator> ecitygml::Hole::boundaries() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Hole_boundaries(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator>(ecitygml::AbstractSpaceBoundaryPropertyIterator::FromFFI(result));
}

inline const ecitygml::MultiCurveProperty* ecitygml::Hole::lod1_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Hole_lod1_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Hole::lod2_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Hole_lod2_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::Hole::lod3_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Hole_lod3_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::Hole* ecitygml::Hole::try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_Hole_try_from(feature.AsFFI());
    return ecitygml::Hole::FromFFI(result);
}

inline const ecitygml::HoleClassValue* ecitygml::Hole::class_() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Hole_class(this->AsFFI());
    return ecitygml::HoleClassValue::FromFFI(result);
}

inline const ecitygml::capi::Hole* ecitygml::Hole::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::Hole*>(this);
}

inline ecitygml::capi::Hole* ecitygml::Hole::AsFFI() {
    return reinterpret_cast<ecitygml::capi::Hole*>(this);
}

inline const ecitygml::Hole* ecitygml::Hole::FromFFI(const ecitygml::capi::Hole* ptr) {
    return reinterpret_cast<const ecitygml::Hole*>(ptr);
}

inline ecitygml::Hole* ecitygml::Hole::FromFFI(ecitygml::capi::Hole* ptr) {
    return reinterpret_cast<ecitygml::Hole*>(ptr);
}

inline void ecitygml::Hole::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_Hole_destroy(reinterpret_cast<ecitygml::capi::Hole*>(ptr));
}


#endif // ECITYGML_Hole_HPP
