#ifndef ecitygml_WallSurface_HPP
#define ecitygml_WallSurface_HPP

#include "WallSurface.d.hpp"

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

    const ecitygml::capi::Id* ecitygml_WallSurface_id(const ecitygml::capi::WallSurface* self);

    ecitygml::capi::CodeIterator* ecitygml_WallSurface_names(const ecitygml::capi::WallSurface* self);

    const ecitygml::capi::BoundingShape* ecitygml_WallSurface_bounded_by(const ecitygml::capi::WallSurface* self);

    const ecitygml::capi::Id* ecitygml_WallSurface_feature_id(const ecitygml::capi::WallSurface* self);

    const ecitygml::capi::DateTime* ecitygml_WallSurface_creation_date(const ecitygml::capi::WallSurface* self);

    const ecitygml::capi::DateTime* ecitygml_WallSurface_termination_date(const ecitygml::capi::WallSurface* self);

    const ecitygml::capi::DateTime* ecitygml_WallSurface_valid_from(const ecitygml::capi::WallSurface* self);

    const ecitygml::capi::DateTime* ecitygml_WallSurface_valid_to(const ecitygml::capi::WallSurface* self);

    typedef struct ecitygml_WallSurface_relative_to_terrain_result {union {ecitygml::capi::RelativeToTerrain ok; }; bool is_ok;} ecitygml_WallSurface_relative_to_terrain_result;
    ecitygml_WallSurface_relative_to_terrain_result ecitygml_WallSurface_relative_to_terrain(const ecitygml::capi::WallSurface* self);

    typedef struct ecitygml_WallSurface_relative_to_water_result {union {ecitygml::capi::RelativeToWater ok; }; bool is_ok;} ecitygml_WallSurface_relative_to_water_result;
    ecitygml_WallSurface_relative_to_water_result ecitygml_WallSurface_relative_to_water(const ecitygml::capi::WallSurface* self);

    ecitygml::capi::ExternalReferenceIterator* ecitygml_WallSurface_external_references(const ecitygml::capi::WallSurface* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_WallSurface_generic_attributes(const ecitygml::capi::WallSurface* self);

    ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml_WallSurface_related_to(const ecitygml::capi::WallSurface* self);

    const ecitygml::capi::MultiCurveProperty* ecitygml_WallSurface_lod0_multi_curve(const ecitygml::capi::WallSurface* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_WallSurface_lod0_multi_surface(const ecitygml::capi::WallSurface* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_WallSurface_lod1_multi_surface(const ecitygml::capi::WallSurface* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_WallSurface_lod2_multi_surface(const ecitygml::capi::WallSurface* self);

    const ecitygml::capi::MultiSurfaceProperty* ecitygml_WallSurface_lod3_multi_surface(const ecitygml::capi::WallSurface* self);

    ecitygml::capi::AbstractFillingSurfacePropertyIterator* ecitygml_WallSurface_filling_surfaces(const ecitygml::capi::WallSurface* self);

    const ecitygml::capi::WallSurface* ecitygml_WallSurface_try_from(const ecitygml::capi::AbstractFeatureKindRef* feature);

    void ecitygml_WallSurface_destroy(WallSurface* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::WallSurface::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WallSurface_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::WallSurface::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WallSurface_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::BoundingShape* ecitygml::WallSurface::bounded_by() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WallSurface_bounded_by(this->AsFFI());
    return ecitygml::BoundingShape::FromFFI(result);
}

inline const ecitygml::Id& ecitygml::WallSurface::feature_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WallSurface_feature_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::WallSurface::creation_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WallSurface_creation_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::WallSurface::termination_date() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WallSurface_termination_date(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::WallSurface::valid_from() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WallSurface_valid_from(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline const ecitygml::DateTime* ecitygml::WallSurface::valid_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WallSurface_valid_to(this->AsFFI());
    return ecitygml::DateTime::FromFFI(result);
}

inline std::optional<ecitygml::RelativeToTerrain> ecitygml::WallSurface::relative_to_terrain() const {
    auto result = ecitygml::capi::ecitygml_WallSurface_relative_to_terrain(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToTerrain>(ecitygml::RelativeToTerrain::FromFFI(result.ok)) : std::nullopt;
}

inline std::optional<ecitygml::RelativeToWater> ecitygml::WallSurface::relative_to_water() const {
    auto result = ecitygml::capi::ecitygml_WallSurface_relative_to_water(this->AsFFI());
    return result.is_ok ? std::optional<ecitygml::RelativeToWater>(ecitygml::RelativeToWater::FromFFI(result.ok)) : std::nullopt;
}

inline std::unique_ptr<ecitygml::ExternalReferenceIterator> ecitygml::WallSurface::external_references() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WallSurface_external_references(this->AsFFI());
    return std::unique_ptr<ecitygml::ExternalReferenceIterator>(ecitygml::ExternalReferenceIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::WallSurface::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WallSurface_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> ecitygml::WallSurface::related_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WallSurface_related_to(this->AsFFI());
    return std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>(ecitygml::CityObjectRelationPropertyIterator::FromFFI(result));
}

inline const ecitygml::MultiCurveProperty* ecitygml::WallSurface::lod0_multi_curve() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WallSurface_lod0_multi_curve(this->AsFFI());
    return ecitygml::MultiCurveProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::WallSurface::lod0_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WallSurface_lod0_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::WallSurface::lod1_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WallSurface_lod1_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::WallSurface::lod2_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WallSurface_lod2_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::WallSurface::lod3_multi_surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WallSurface_lod3_multi_surface(this->AsFFI());
    return ecitygml::MultiSurfaceProperty::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AbstractFillingSurfacePropertyIterator> ecitygml::WallSurface::filling_surfaces() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_WallSurface_filling_surfaces(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractFillingSurfacePropertyIterator>(ecitygml::AbstractFillingSurfacePropertyIterator::FromFFI(result));
}

inline const ecitygml::WallSurface* ecitygml::WallSurface::try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_WallSurface_try_from(feature.AsFFI());
    return ecitygml::WallSurface::FromFFI(result);
}

inline const ecitygml::capi::WallSurface* ecitygml::WallSurface::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::WallSurface*>(this);
}

inline ecitygml::capi::WallSurface* ecitygml::WallSurface::AsFFI() {
    return reinterpret_cast<ecitygml::capi::WallSurface*>(this);
}

inline const ecitygml::WallSurface* ecitygml::WallSurface::FromFFI(const ecitygml::capi::WallSurface* ptr) {
    return reinterpret_cast<const ecitygml::WallSurface*>(ptr);
}

inline ecitygml::WallSurface* ecitygml::WallSurface::FromFFI(ecitygml::capi::WallSurface* ptr) {
    return reinterpret_cast<ecitygml::WallSurface*>(ptr);
}

inline void ecitygml::WallSurface::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_WallSurface_destroy(reinterpret_cast<ecitygml::capi::WallSurface*>(ptr));
}


#endif // ecitygml_WallSurface_HPP
