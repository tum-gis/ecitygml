#ifndef ECITYGML_DoorSurface_HPP
#define ECITYGML_DoorSurface_HPP

#include "DoorSurface.d.hpp"

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
#include "MultiCurveProperty.hpp"
#include "MultiSurfaceProperty.hpp"
#include "RelativeToTerrain.hpp"
#include "RelativeToWater.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_DoorSurface_id(const ecitygml::capi::DoorSurface* self);

    ecitygml::capi::CodeIterator* ecitygml_DoorSurface_names(const ecitygml::capi::DoorSurface* self);

    const ecitygml::capi::BoundingShape* ecitygml_DoorSurface_bounded_by(const ecitygml::capi::DoorSurface* self);

    const ecitygml::capi::Id* ecitygml_DoorSurface_feature_id(const ecitygml::capi::DoorSurface* self);

    const ecitygml::capi::DateTime* ecitygml_DoorSurface_creation_date(const ecitygml::capi::DoorSurface* self);

    const ecitygml::capi::DateTime* ecitygml_DoorSurface_termination_date(const ecitygml::capi::DoorSurface* self);

    const ecitygml::capi::DateTime* ecitygml_DoorSurface_valid_from(const ecitygml::capi::DoorSurface* self);

    const ecitygml::capi::DateTime* ecitygml_DoorSurface_valid_to(const ecitygml::capi::DoorSurface* self);

    typedef struct ecitygml_DoorSurface_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_DoorSurface_relative_to_terrain_result;
    ecitygml_DoorSurface_relative_to_terrain_result ecitygml_DoorSurface_relative_to_terrain(const ecitygml::capi::DoorSurface* self);

    typedef struct ecitygml_DoorSurface_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_DoorSurface_relative_to_water_result;
    ecitygml_DoorSurface_relative_to_water_result ecitygml_DoorSurface_relative_to_water(const ecitygml::capi::DoorSurface* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_DoorSurface_external_references(const ecitygml::capi::DoorSurface* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_DoorSurface_generic_attributes(const ecitygml::capi::DoorSurface* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_DoorSurface_related_to(const ecitygml::capi::DoorSurface* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_DoorSurface_lod0_multi_curve(const ecitygml::capi::DoorSurface* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_DoorSurface_lod0_multi_surface(const ecitygml::capi::DoorSurface* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_DoorSurface_lod1_multi_surface(const ecitygml::capi::DoorSurface* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_DoorSurface_lod2_multi_surface(const ecitygml::capi::DoorSurface* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_DoorSurface_lod3_multi_surface(const ecitygml::capi::DoorSurface* self);

    const ecitygml::capi::DoorSurface* ecitygml_DoorSurface_try_from(const ecitygml::capi::AbstractFeatureKindRef* feature);

    void ecitygml_DoorSurface_destroy(DoorSurface* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::DoorSurface::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_DoorSurface_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::DoorSurface::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_DoorSurface_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::DoorSurface::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_DoorSurface_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::DoorSurface::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_DoorSurface_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::DoorSurface::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_DoorSurface_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::DoorSurface::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_DoorSurface_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::DoorSurface::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_DoorSurface_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::DoorSurface::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_DoorSurface_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::DoorSurface::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_DoorSurface_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::DoorSurface::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_DoorSurface_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::DoorSurface::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_DoorSurface_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::DoorSurface::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_DoorSurface_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::DoorSurface::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_DoorSurface_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline const ecitygml::MultiCurveProperty* ecitygml::DoorSurface::lod0_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_DoorSurface_lod0_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::DoorSurface::lod0_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_DoorSurface_lod0_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::DoorSurface::lod1_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_DoorSurface_lod1_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::DoorSurface::lod2_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_DoorSurface_lod2_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::DoorSurface::lod3_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_DoorSurface_lod3_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::DoorSurface* ecitygml::DoorSurface::try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_DoorSurface_try_from(feature.AsFFI());
    return ecitygml::DoorSurface::FromFFI(result);
}

inline const ecitygml::capi::DoorSurface* ecitygml::DoorSurface::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::DoorSurface*>(this);
}

inline ecitygml::capi::DoorSurface* ecitygml::DoorSurface::AsFFI() {
    return reinterpret_cast<ecitygml::capi::DoorSurface*>(this);
}

inline const ecitygml::DoorSurface* ecitygml::DoorSurface::FromFFI(const ecitygml::capi::DoorSurface* ptr) {
    return reinterpret_cast<const ecitygml::DoorSurface*>(ptr);
}

inline ecitygml::DoorSurface* ecitygml::DoorSurface::FromFFI(ecitygml::capi::DoorSurface* ptr) {
    return reinterpret_cast<ecitygml::DoorSurface*>(ptr);
}

inline void ecitygml::DoorSurface::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_DoorSurface_destroy(reinterpret_cast<ecitygml::capi::DoorSurface*>(ptr));
}


#endif // ECITYGML_DoorSurface_HPP
