#ifndef ECITYGML_Marking_HPP
#define ECITYGML_Marking_HPP

#include "Marking.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "AbstractFeatureKindRef.hpp"
#include "BoundingShape.hpp"
#include "CityObjectRelationPropertyIterator.hpp"
#include "CodeIterator.hpp"
#include "DateTime.hpp"
#include "ExternalReferenceIterator.hpp"
#include "GenericAttributeKindIterator.hpp"
#include "Id.hpp"
#include "MarkingClassValue.hpp"
#include "MultiCurveProperty.hpp"
#include "MultiSurfaceProperty.hpp"
#include "RelativeToTerrain.hpp"
#include "RelativeToWater.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_Marking_id(const ecitygml::capi::Marking* self);

    ecitygml::capi::CodeIterator* ecitygml_Marking_names(const ecitygml::capi::Marking* self);

    const ecitygml::capi::BoundingShape* ecitygml_Marking_bounded_by(const ecitygml::capi::Marking* self);

    const ecitygml::capi::Id* ecitygml_Marking_feature_id(const ecitygml::capi::Marking* self);

    const ecitygml::capi::DateTime* ecitygml_Marking_creation_date(const ecitygml::capi::Marking* self);

    const ecitygml::capi::DateTime* ecitygml_Marking_termination_date(const ecitygml::capi::Marking* self);

    const ecitygml::capi::DateTime* ecitygml_Marking_valid_from(const ecitygml::capi::Marking* self);

    const ecitygml::capi::DateTime* ecitygml_Marking_valid_to(const ecitygml::capi::Marking* self);

    typedef struct ecitygml_Marking_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_Marking_relative_to_terrain_result;
    ecitygml_Marking_relative_to_terrain_result ecitygml_Marking_relative_to_terrain(const ecitygml::capi::Marking* self);

    typedef struct ecitygml_Marking_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_Marking_relative_to_water_result;
    ecitygml_Marking_relative_to_water_result ecitygml_Marking_relative_to_water(const ecitygml::capi::Marking* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_Marking_external_references(const ecitygml::capi::Marking* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_Marking_generic_attributes(const ecitygml::capi::Marking* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_Marking_related_to(const ecitygml::capi::Marking* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_Marking_lod0_multi_curve(const ecitygml::capi::Marking* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_Marking_lod0_multi_surface(const ecitygml::capi::Marking* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_Marking_lod1_multi_surface(const ecitygml::capi::Marking* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_Marking_lod2_multi_surface(const ecitygml::capi::Marking* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_Marking_lod3_multi_surface(const ecitygml::capi::Marking* self);

    const ecitygml::capi::Marking* ecitygml_Marking_try_from(const ecitygml::capi::AbstractFeatureKindRef* feature);

    const ecitygml::capi::MarkingClassValue* ecitygml_Marking_class(const ecitygml::capi::Marking* self);

    void ecitygml_Marking_destroy(Marking* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::Marking::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Marking_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::Marking::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Marking_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::Marking::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Marking_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::Marking::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Marking_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Marking::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Marking_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Marking::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Marking_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Marking::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Marking_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::Marking::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Marking_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::Marking::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_Marking_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::Marking::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_Marking_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::Marking::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Marking_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::Marking::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Marking_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::Marking::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Marking_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline const ecitygml::MultiCurveProperty* ecitygml::Marking::lod0_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Marking_lod0_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::Marking::lod0_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Marking_lod0_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::Marking::lod1_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Marking_lod1_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::Marking::lod2_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Marking_lod2_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::Marking::lod3_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Marking_lod3_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::Marking* ecitygml::Marking::try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_Marking_try_from(feature.AsFFI());
    return ecitygml::Marking::FromFFI(result);
}

inline const ecitygml::MarkingClassValue* ecitygml::Marking::class_() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Marking_class(this->AsFFI());
    return ecitygml::MarkingClassValue::FromFFI(result);
}

inline const ecitygml::capi::Marking* ecitygml::Marking::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::Marking*>(this);
}

inline ecitygml::capi::Marking* ecitygml::Marking::AsFFI() {
    return reinterpret_cast<ecitygml::capi::Marking*>(this);
}

inline const ecitygml::Marking* ecitygml::Marking::FromFFI(const ecitygml::capi::Marking* ptr) {
    return reinterpret_cast<const ecitygml::Marking*>(ptr);
}

inline ecitygml::Marking* ecitygml::Marking::FromFFI(ecitygml::capi::Marking* ptr) {
    return reinterpret_cast<ecitygml::Marking*>(ptr);
}

inline void ecitygml::Marking::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_Marking_destroy(reinterpret_cast<ecitygml::capi::Marking*>(ptr));
}


#endif // ECITYGML_Marking_HPP
