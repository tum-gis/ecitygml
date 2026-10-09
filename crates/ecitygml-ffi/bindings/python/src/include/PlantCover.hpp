#ifndef ECITYGML_PlantCover_HPP
#define ECITYGML_PlantCover_HPP

#include "PlantCover.d.hpp"

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
#include "PlantCoverClassValue.hpp"
#include "PlantCoverFunctionValueIterator.hpp"
#include "PlantCoverUsageValueIterator.hpp"
#include "PointProperty.hpp"
#include "RelativeToTerrain.hpp"
#include "RelativeToWater.hpp"
#include "SolidProperty.hpp"
#include "SpaceType.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_PlantCover_id(const ecitygml::capi::PlantCover* self);

    ecitygml::capi::CodeIterator* ecitygml_PlantCover_names(const ecitygml::capi::PlantCover* self);

    const ecitygml::capi::BoundingShape* ecitygml_PlantCover_bounded_by(const ecitygml::capi::PlantCover* self);

    const ecitygml::capi::Id* ecitygml_PlantCover_feature_id(const ecitygml::capi::PlantCover* self);

    const ecitygml::capi::DateTime* ecitygml_PlantCover_creation_date(const ecitygml::capi::PlantCover* self);

    const ecitygml::capi::DateTime* ecitygml_PlantCover_termination_date(const ecitygml::capi::PlantCover* self);

    const ecitygml::capi::DateTime* ecitygml_PlantCover_valid_from(const ecitygml::capi::PlantCover* self);

    const ecitygml::capi::DateTime* ecitygml_PlantCover_valid_to(const ecitygml::capi::PlantCover* self);

    typedef struct ecitygml_PlantCover_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_PlantCover_relative_to_terrain_result;
    ecitygml_PlantCover_relative_to_terrain_result ecitygml_PlantCover_relative_to_terrain(const ecitygml::capi::PlantCover* self);

    typedef struct ecitygml_PlantCover_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_PlantCover_relative_to_water_result;
    ecitygml_PlantCover_relative_to_water_result ecitygml_PlantCover_relative_to_water(const ecitygml::capi::PlantCover* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_PlantCover_external_references(const ecitygml::capi::PlantCover* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_PlantCover_generic_attributes(const ecitygml::capi::PlantCover* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_PlantCover_related_to(const ecitygml::capi::PlantCover* self);

    typedef struct ecitygml_PlantCover_space_type_result {union {ecitygml::capi::SpaceType ok; }; bool is_ok;} ecitygml_PlantCover_space_type_result;
    ecitygml_PlantCover_space_type_result ecitygml_PlantCover_space_type(const ecitygml::capi::PlantCover* self);

    const ecitygml::capi::SolidProperty* ecitygml_PlantCover_lod1_solid(const ecitygml::capi::PlantCover* self);

    const ecitygml::capi::SolidProperty* ecitygml_PlantCover_lod2_solid(const ecitygml::capi::PlantCover* self);

    const ecitygml::capi::SolidProperty* ecitygml_PlantCover_lod3_solid(const ecitygml::capi::PlantCover* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_PlantCover_lod0_multi_surface(const ecitygml::capi::PlantCover* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_PlantCover_lod2_multi_surface(const ecitygml::capi::PlantCover* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_PlantCover_lod3_multi_surface(const ecitygml::capi::PlantCover* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_PlantCover_lod0_multi_curve(const ecitygml::capi::PlantCover* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_PlantCover_lod2_multi_curve(const ecitygml::capi::PlantCover* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_PlantCover_lod3_multi_curve(const ecitygml::capi::PlantCover* self);

    const ecitygml::capi::PointProperty* ecitygml_PlantCover_lod0_point(const ecitygml::capi::PlantCover* self);

    ecitygml::capi::AbstractSpaceBoundaryPropertyIterator* ecitygml_PlantCover_boundaries(const ecitygml::capi::PlantCover* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_PlantCover_lod1_terrain_intersection_curve(const ecitygml::capi::PlantCover* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_PlantCover_lod2_terrain_intersection_curve(const ecitygml::capi::PlantCover* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_PlantCover_lod3_terrain_intersection_curve(const ecitygml::capi::PlantCover* self);

    const ecitygml::capi::ImplicitGeometryProperty* ecitygml_PlantCover_lod1_implicit_representation(const ecitygml::capi::PlantCover* self);

    const ecitygml::capi::ImplicitGeometryProperty* ecitygml_PlantCover_lod2_implicit_representation(const ecitygml::capi::PlantCover* self);

    const ecitygml::capi::ImplicitGeometryProperty* ecitygml_PlantCover_lod3_implicit_representation(const ecitygml::capi::PlantCover* self);

    const ecitygml::capi::PlantCover* ecitygml_PlantCover_try_from(const ecitygml::capi::AbstractFeatureKindRef* feature);

    const ecitygml::capi::PlantCoverClassValue* ecitygml_PlantCover_class(const ecitygml::capi::PlantCover* self);

    ecitygml::capi::PlantCoverFunctionValueIterator* ecitygml_PlantCover_functions(const ecitygml::capi::PlantCover* self);

    ecitygml::capi::PlantCoverUsageValueIterator* ecitygml_PlantCover_usages(const ecitygml::capi::PlantCover* self);

    const ecitygml::capi::Measure* ecitygml_PlantCover_average_height(const ecitygml::capi::PlantCover* self);

    const ecitygml::capi::Measure* ecitygml_PlantCover_min_height(const ecitygml::capi::PlantCover* self);

    const ecitygml::capi::Measure* ecitygml_PlantCover_max_height(const ecitygml::capi::PlantCover* self);

    void ecitygml_PlantCover_destroy(PlantCover* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::PlantCover::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::PlantCover::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::PlantCover::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::PlantCover::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::PlantCover::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::PlantCover::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::PlantCover::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::PlantCover::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::PlantCover::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_PlantCover_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::PlantCover::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_PlantCover_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::PlantCover::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::PlantCover::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::PlantCover::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline std::optional<ecitygml::SpaceType> ecitygml::PlantCover::space_type() const {
    auto result = ecitygml::capi::ecitygml_PlantCover_space_type(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::SpaceType>(ecitygml::SpaceType::FromFFI(result.ok)) : std::nullopt;
}

inline const ecitygml::SolidProperty* ecitygml::PlantCover::lod1_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_lod1_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::PlantCover::lod2_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_lod2_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::SolidProperty* ecitygml::PlantCover::lod3_solid() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_lod3_solid(this->AsFFI());
    return ecitygml::SolidProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::PlantCover::lod0_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_lod0_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::PlantCover::lod2_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_lod2_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::PlantCover::lod3_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_lod3_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::PlantCover::lod0_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_lod0_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::PlantCover::lod2_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_lod2_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::PlantCover::lod3_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_lod3_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::PointProperty* ecitygml::PlantCover::lod0_point() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_lod0_point(this->AsFFI());
    return ecitygml::PointProperty::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator> ecitygml::PlantCover::boundaries() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_boundaries(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator>(ecitygml::AbstractSpaceBoundaryPropertyIterator::FromFFI(result));
}

inline const ecitygml::MultiCurveProperty* ecitygml::PlantCover::lod1_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_lod1_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::PlantCover::lod2_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_lod2_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiCurveProperty* ecitygml::PlantCover::lod3_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_lod3_terrain_intersection_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::ImplicitGeometryProperty* ecitygml::PlantCover::lod1_implicit_representation() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_lod1_implicit_representation(this->AsFFI());
    return ecitygml::ImplicitGeometryProperty::FromFFI(result);
}

inline const ecitygml::ImplicitGeometryProperty* ecitygml::PlantCover::lod2_implicit_representation() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_lod2_implicit_representation(this->AsFFI());
    return ecitygml::ImplicitGeometryProperty::FromFFI(result);
}

inline const ecitygml::ImplicitGeometryProperty* ecitygml::PlantCover::lod3_implicit_representation() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_lod3_implicit_representation(this->AsFFI());
    return ecitygml::ImplicitGeometryProperty::FromFFI(result);
}

inline const ecitygml::PlantCover* ecitygml::PlantCover::try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_PlantCover_try_from(feature.AsFFI());
    return ecitygml::PlantCover::FromFFI(result);
}

inline const ecitygml::PlantCoverClassValue* ecitygml::PlantCover::class_() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_class(this->AsFFI());
    return ecitygml::PlantCoverClassValue::FromFFI(result);
}

inline std::unique_ptr<ecitygml::PlantCoverFunctionValueIterator> ecitygml::PlantCover::functions() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_functions(this->AsFFI());
    return std::unique_ptr<ecitygml::PlantCoverFunctionValueIterator>(ecitygml::PlantCoverFunctionValueIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::PlantCoverUsageValueIterator> ecitygml::PlantCover::usages() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_usages(this->AsFFI());
    return std::unique_ptr<ecitygml::PlantCoverUsageValueIterator>(ecitygml::PlantCoverUsageValueIterator::FromFFI(result));
}

inline const ecitygml::Measure* ecitygml::PlantCover::average_height() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_average_height(this->AsFFI());
    return ecitygml::Measure::FromFFI(result);
}

inline const ecitygml::Measure* ecitygml::PlantCover::min_height() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_min_height(this->AsFFI());
    return ecitygml::Measure::FromFFI(result);
}

inline const ecitygml::Measure* ecitygml::PlantCover::max_height() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCover_max_height(this->AsFFI());
    return ecitygml::Measure::FromFFI(result);
}

inline const ecitygml::capi::PlantCover* ecitygml::PlantCover::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::PlantCover*>(this);
}

inline ecitygml::capi::PlantCover* ecitygml::PlantCover::AsFFI() {
    return reinterpret_cast<ecitygml::capi::PlantCover*>(this);
}

inline const ecitygml::PlantCover* ecitygml::PlantCover::FromFFI(const ecitygml::capi::PlantCover* ptr) {
    return reinterpret_cast<const ecitygml::PlantCover*>(ptr);
}

inline ecitygml::PlantCover* ecitygml::PlantCover::FromFFI(ecitygml::capi::PlantCover* ptr) {
    return reinterpret_cast<ecitygml::PlantCover*>(ptr);
}

inline void ecitygml::PlantCover::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_PlantCover_destroy(reinterpret_cast<ecitygml::capi::PlantCover*>(ptr));
}


#endif // ECITYGML_PlantCover_HPP
