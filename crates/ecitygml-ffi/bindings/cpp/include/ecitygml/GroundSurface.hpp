#ifndef ecitygml_GroundSurface_HPP
#define ecitygml_GroundSurface_HPP

#include "GroundSurface.d.hpp"

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
#include "AbstractFillingSurfacePropertyIterator.hpp"
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


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_GroundSurface_id(const ecitygml::capi::GroundSurface* self);

    ecitygml::capi::CodeIterator* ecitygml_GroundSurface_names(const ecitygml::capi::GroundSurface* self);

    const ecitygml::capi::BoundingShape* ecitygml_GroundSurface_bounded_by(const ecitygml::capi::GroundSurface* self);

    const ecitygml::capi::Id* ecitygml_GroundSurface_feature_id(const ecitygml::capi::GroundSurface* self);

    const ecitygml::capi::DateTime* ecitygml_GroundSurface_creation_date(const ecitygml::capi::GroundSurface* self);

    const ecitygml::capi::DateTime* ecitygml_GroundSurface_termination_date(const ecitygml::capi::GroundSurface* self);

    const ecitygml::capi::DateTime* ecitygml_GroundSurface_valid_from(const ecitygml::capi::GroundSurface* self);

    const ecitygml::capi::DateTime* ecitygml_GroundSurface_valid_to(const ecitygml::capi::GroundSurface* self);

    typedef struct ecitygml_GroundSurface_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_GroundSurface_relative_to_terrain_result;
    ecitygml_GroundSurface_relative_to_terrain_result ecitygml_GroundSurface_relative_to_terrain(const ecitygml::capi::GroundSurface* self);

    typedef struct ecitygml_GroundSurface_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_GroundSurface_relative_to_water_result;
    ecitygml_GroundSurface_relative_to_water_result ecitygml_GroundSurface_relative_to_water(const ecitygml::capi::GroundSurface* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_GroundSurface_external_references(const ecitygml::capi::GroundSurface* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_GroundSurface_generic_attributes(const ecitygml::capi::GroundSurface* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_GroundSurface_related_to(const ecitygml::capi::GroundSurface* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_GroundSurface_lod0_multi_curve(const ecitygml::capi::GroundSurface* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_GroundSurface_lod0_multi_surface(const ecitygml::capi::GroundSurface* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_GroundSurface_lod1_multi_surface(const ecitygml::capi::GroundSurface* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_GroundSurface_lod2_multi_surface(const ecitygml::capi::GroundSurface* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_GroundSurface_lod3_multi_surface(const ecitygml::capi::GroundSurface* self);

    ecitygml::capi::AbstractFillingSurfacePropertyIterator* ecitygml_GroundSurface_filling_surfaces(const ecitygml::capi::GroundSurface* self);

    const ecitygml::capi::GroundSurface* ecitygml_GroundSurface_try_from(const ecitygml::capi::AbstractFeatureKindRef* feature);

    void ecitygml_GroundSurface_destroy(GroundSurface* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::GroundSurface::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_GroundSurface_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::GroundSurface::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_GroundSurface_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::GroundSurface::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_GroundSurface_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::GroundSurface::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_GroundSurface_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::GroundSurface::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_GroundSurface_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::GroundSurface::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_GroundSurface_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::GroundSurface::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_GroundSurface_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::GroundSurface::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_GroundSurface_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::GroundSurface::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_GroundSurface_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::GroundSurface::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_GroundSurface_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::GroundSurface::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_GroundSurface_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::GroundSurface::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_GroundSurface_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::GroundSurface::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_GroundSurface_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline const ecitygml::MultiCurveProperty* ecitygml::GroundSurface::lod0_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_GroundSurface_lod0_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::GroundSurface::lod0_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_GroundSurface_lod0_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::GroundSurface::lod1_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_GroundSurface_lod1_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::GroundSurface::lod2_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_GroundSurface_lod2_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::GroundSurface::lod3_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_GroundSurface_lod3_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AbstractFillingSurfacePropertyIterator> ecitygml::GroundSurface::filling_surfaces() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_GroundSurface_filling_surfaces(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractFillingSurfacePropertyIterator>(ecitygml::AbstractFillingSurfacePropertyIterator::FromFFI(result));
}

inline const ecitygml::GroundSurface* ecitygml::GroundSurface::try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_GroundSurface_try_from(feature.AsFFI());
    return ecitygml::GroundSurface::FromFFI(result);
}

inline const ecitygml::capi::GroundSurface* ecitygml::GroundSurface::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::GroundSurface*>(this);
}

inline ecitygml::capi::GroundSurface* ecitygml::GroundSurface::AsFFI() {
    return reinterpret_cast<ecitygml::capi::GroundSurface*>(this);
}

inline const ecitygml::GroundSurface* ecitygml::GroundSurface::FromFFI(const ecitygml::capi::GroundSurface* ptr) {
    return reinterpret_cast<const ecitygml::GroundSurface*>(ptr);
}

inline ecitygml::GroundSurface* ecitygml::GroundSurface::FromFFI(ecitygml::capi::GroundSurface* ptr) {
    return reinterpret_cast<ecitygml::GroundSurface*>(ptr);
}

inline void ecitygml::GroundSurface::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_GroundSurface_destroy(reinterpret_cast<ecitygml::capi::GroundSurface*>(ptr));
}


#endif // ecitygml_GroundSurface_HPP
