#ifndef ECITYGML_RoofSurface_HPP
#define ECITYGML_RoofSurface_HPP

#include "RoofSurface.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
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
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_RoofSurface_id(const ecitygml::capi::RoofSurface* self);

    ecitygml::capi::CodeIterator* ecitygml_RoofSurface_names(const ecitygml::capi::RoofSurface* self);

    const ecitygml::capi::BoundingShape* ecitygml_RoofSurface_bounded_by(const ecitygml::capi::RoofSurface* self);

    const ecitygml::capi::Id* ecitygml_RoofSurface_feature_id(const ecitygml::capi::RoofSurface* self);

    const ecitygml::capi::DateTime* ecitygml_RoofSurface_creation_date(const ecitygml::capi::RoofSurface* self);

    const ecitygml::capi::DateTime* ecitygml_RoofSurface_termination_date(const ecitygml::capi::RoofSurface* self);

    const ecitygml::capi::DateTime* ecitygml_RoofSurface_valid_from(const ecitygml::capi::RoofSurface* self);

    const ecitygml::capi::DateTime* ecitygml_RoofSurface_valid_to(const ecitygml::capi::RoofSurface* self);

    typedef struct ecitygml_RoofSurface_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_RoofSurface_relative_to_terrain_result;
    ecitygml_RoofSurface_relative_to_terrain_result ecitygml_RoofSurface_relative_to_terrain(const ecitygml::capi::RoofSurface* self);

    typedef struct ecitygml_RoofSurface_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_RoofSurface_relative_to_water_result;
    ecitygml_RoofSurface_relative_to_water_result ecitygml_RoofSurface_relative_to_water(const ecitygml::capi::RoofSurface* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_RoofSurface_external_references(const ecitygml::capi::RoofSurface* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_RoofSurface_generic_attributes(const ecitygml::capi::RoofSurface* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_RoofSurface_related_to(const ecitygml::capi::RoofSurface* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_RoofSurface_lod0_multi_curve(const ecitygml::capi::RoofSurface* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_RoofSurface_lod0_multi_surface(const ecitygml::capi::RoofSurface* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_RoofSurface_lod1_multi_surface(const ecitygml::capi::RoofSurface* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_RoofSurface_lod2_multi_surface(const ecitygml::capi::RoofSurface* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_RoofSurface_lod3_multi_surface(const ecitygml::capi::RoofSurface* self);

    ecitygml::capi::AbstractFillingSurfacePropertyIterator* ecitygml_RoofSurface_filling_surfaces(const ecitygml::capi::RoofSurface* self);

    const ecitygml::capi::RoofSurface* ecitygml_RoofSurface_try_from(const ecitygml::capi::AbstractFeatureKindRef* feature);

    void ecitygml_RoofSurface_destroy(RoofSurface* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::RoofSurface::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_RoofSurface_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::RoofSurface::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_RoofSurface_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::RoofSurface::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_RoofSurface_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::RoofSurface::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_RoofSurface_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::RoofSurface::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_RoofSurface_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::RoofSurface::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_RoofSurface_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::RoofSurface::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_RoofSurface_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::RoofSurface::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_RoofSurface_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::RoofSurface::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_RoofSurface_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::RoofSurface::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_RoofSurface_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::RoofSurface::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_RoofSurface_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::RoofSurface::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_RoofSurface_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::RoofSurface::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_RoofSurface_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline const ecitygml::MultiCurveProperty* ecitygml::RoofSurface::lod0_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_RoofSurface_lod0_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::RoofSurface::lod0_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_RoofSurface_lod0_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::RoofSurface::lod1_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_RoofSurface_lod1_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::RoofSurface::lod2_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_RoofSurface_lod2_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::RoofSurface::lod3_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_RoofSurface_lod3_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AbstractFillingSurfacePropertyIterator> ecitygml::RoofSurface::filling_surfaces() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_RoofSurface_filling_surfaces(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractFillingSurfacePropertyIterator>(ecitygml::AbstractFillingSurfacePropertyIterator::FromFFI(result));
}

inline const ecitygml::RoofSurface* ecitygml::RoofSurface::try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_RoofSurface_try_from(feature.AsFFI());
    return ecitygml::RoofSurface::FromFFI(result);
}

inline const ecitygml::capi::RoofSurface* ecitygml::RoofSurface::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::RoofSurface*>(this);
}

inline ecitygml::capi::RoofSurface* ecitygml::RoofSurface::AsFFI() {
    return reinterpret_cast<ecitygml::capi::RoofSurface*>(this);
}

inline const ecitygml::RoofSurface* ecitygml::RoofSurface::FromFFI(const ecitygml::capi::RoofSurface* ptr) {
    return reinterpret_cast<const ecitygml::RoofSurface*>(ptr);
}

inline ecitygml::RoofSurface* ecitygml::RoofSurface::FromFFI(ecitygml::capi::RoofSurface* ptr) {
    return reinterpret_cast<ecitygml::RoofSurface*>(ptr);
}

inline void ecitygml::RoofSurface::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_RoofSurface_destroy(reinterpret_cast<ecitygml::capi::RoofSurface*>(ptr));
}


#endif // ECITYGML_RoofSurface_HPP
