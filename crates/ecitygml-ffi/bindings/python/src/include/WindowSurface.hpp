#ifndef ECITYGML_WindowSurface_HPP
#define ECITYGML_WindowSurface_HPP

#include "WindowSurface.d.hpp"

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

    const ecitygml::capi::Id* ecitygml_WindowSurface_id(const ecitygml::capi::WindowSurface* self);

    ecitygml::capi::CodeIterator* ecitygml_WindowSurface_names(const ecitygml::capi::WindowSurface* self);

    const ecitygml::capi::BoundingShape* ecitygml_WindowSurface_bounded_by(const ecitygml::capi::WindowSurface* self);

    const ecitygml::capi::Id* ecitygml_WindowSurface_feature_id(const ecitygml::capi::WindowSurface* self);

    const ecitygml::capi::DateTime* ecitygml_WindowSurface_creation_date(const ecitygml::capi::WindowSurface* self);

    const ecitygml::capi::DateTime* ecitygml_WindowSurface_termination_date(const ecitygml::capi::WindowSurface* self);

    const ecitygml::capi::DateTime* ecitygml_WindowSurface_valid_from(const ecitygml::capi::WindowSurface* self);

    const ecitygml::capi::DateTime* ecitygml_WindowSurface_valid_to(const ecitygml::capi::WindowSurface* self);

    typedef struct ecitygml_WindowSurface_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_WindowSurface_relative_to_terrain_result;
    ecitygml_WindowSurface_relative_to_terrain_result ecitygml_WindowSurface_relative_to_terrain(const ecitygml::capi::WindowSurface* self);

    typedef struct ecitygml_WindowSurface_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_WindowSurface_relative_to_water_result;
    ecitygml_WindowSurface_relative_to_water_result ecitygml_WindowSurface_relative_to_water(const ecitygml::capi::WindowSurface* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_WindowSurface_external_references(const ecitygml::capi::WindowSurface* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_WindowSurface_generic_attributes(const ecitygml::capi::WindowSurface* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_WindowSurface_related_to(const ecitygml::capi::WindowSurface* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_WindowSurface_lod0_multi_curve(const ecitygml::capi::WindowSurface* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_WindowSurface_lod0_multi_surface(const ecitygml::capi::WindowSurface* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_WindowSurface_lod1_multi_surface(const ecitygml::capi::WindowSurface* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_WindowSurface_lod2_multi_surface(const ecitygml::capi::WindowSurface* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_WindowSurface_lod3_multi_surface(const ecitygml::capi::WindowSurface* self);

    const ecitygml::capi::WindowSurface* ecitygml_WindowSurface_try_from(const ecitygml::capi::AbstractFeatureKindRef* feature);

    void ecitygml_WindowSurface_destroy(WindowSurface* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::WindowSurface::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WindowSurface_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::WindowSurface::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WindowSurface_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::WindowSurface::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WindowSurface_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::WindowSurface::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WindowSurface_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::WindowSurface::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WindowSurface_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::WindowSurface::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WindowSurface_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::WindowSurface::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WindowSurface_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::WindowSurface::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WindowSurface_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::WindowSurface::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_WindowSurface_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::WindowSurface::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_WindowSurface_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::WindowSurface::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WindowSurface_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::WindowSurface::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WindowSurface_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::WindowSurface::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WindowSurface_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline const ecitygml::MultiCurveProperty* ecitygml::WindowSurface::lod0_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WindowSurface_lod0_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::WindowSurface::lod0_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WindowSurface_lod0_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::WindowSurface::lod1_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WindowSurface_lod1_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::WindowSurface::lod2_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WindowSurface_lod2_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::WindowSurface::lod3_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WindowSurface_lod3_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::WindowSurface* ecitygml::WindowSurface::try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_WindowSurface_try_from(feature.AsFFI());
    return ecitygml::WindowSurface::FromFFI(result);
}

inline const ecitygml::capi::WindowSurface* ecitygml::WindowSurface::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::WindowSurface*>(this);
}

inline ecitygml::capi::WindowSurface* ecitygml::WindowSurface::AsFFI() {
    return reinterpret_cast<ecitygml::capi::WindowSurface*>(this);
}

inline const ecitygml::WindowSurface* ecitygml::WindowSurface::FromFFI(const ecitygml::capi::WindowSurface* ptr) {
    return reinterpret_cast<const ecitygml::WindowSurface*>(ptr);
}

inline ecitygml::WindowSurface* ecitygml::WindowSurface::FromFFI(ecitygml::capi::WindowSurface* ptr) {
    return reinterpret_cast<ecitygml::WindowSurface*>(ptr);
}

inline void ecitygml::WindowSurface::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_WindowSurface_destroy(reinterpret_cast<ecitygml::capi::WindowSurface*>(ptr));
}


#endif // ECITYGML_WindowSurface_HPP
