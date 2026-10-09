#ifndef ecitygml_AbstractRingKind_HPP
#define ecitygml_AbstractRingKind_HPP

#include "AbstractRingKind.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "AbstractCurveKind.hpp"
#include "CodeIterator.hpp"
#include "DirectPositionIterator.hpp"
#include "Envelope.hpp"
#include "GeometryType.hpp"
#include "Id.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_AbstractRingKind_id(const ecitygml::capi::AbstractRingKind* self);

    ecitygml::capi::CodeIterator* ecitygml_AbstractRingKind_names(const ecitygml::capi::AbstractRingKind* self);

    const ecitygml::capi::AbstractRingKind* ecitygml_AbstractRingKind_try_from(const ecitygml::capi::AbstractCurveKind* curve);

    ecitygml::capi::GeometryType ecitygml_AbstractRingKind_geometry_type(const ecitygml::capi::AbstractRingKind* self);

    ecitygml::capi::DirectPositionIterator* ecitygml_AbstractRingKind_points(const ecitygml::capi::AbstractRingKind* self);

    double ecitygml_AbstractRingKind_length_3d(const ecitygml::capi::AbstractRingKind* self);

    double ecitygml_AbstractRingKind_area_3d(const ecitygml::capi::AbstractRingKind* self);

    ecitygml::capi::Envelope* ecitygml_AbstractRingKind_compute_envelope(const ecitygml::capi::AbstractRingKind* self);

    void ecitygml_AbstractRingKind_destroy(AbstractRingKind* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::AbstractRingKind::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractRingKind_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::AbstractRingKind::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractRingKind_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::AbstractRingKind* ecitygml::AbstractRingKind::try_from(const ecitygml::AbstractCurveKind& curve DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_AbstractRingKind_try_from(curve.AsFFI());
    return ecitygml::AbstractRingKind::FromFFI(result);
}

inline ecitygml::GeometryType ecitygml::AbstractRingKind::geometry_type() const {
    auto result = ecitygml::capi::ecitygml_AbstractRingKind_geometry_type(this->AsFFI());
    return ecitygml::GeometryType::FromFFI(result);
}

inline std::unique_ptr<ecitygml::DirectPositionIterator> ecitygml::AbstractRingKind::points() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractRingKind_points(this->AsFFI());
    return std::unique_ptr<ecitygml::DirectPositionIterator>(ecitygml::DirectPositionIterator::FromFFI(result));
}

inline double ecitygml::AbstractRingKind::length_3d() const {
    auto result = ecitygml::capi::ecitygml_AbstractRingKind_length_3d(this->AsFFI());
    return result;
}

inline double ecitygml::AbstractRingKind::area_3d() const {
    auto result = ecitygml::capi::ecitygml_AbstractRingKind_area_3d(this->AsFFI());
    return result;
}

inline std::unique_ptr<ecitygml::Envelope> ecitygml::AbstractRingKind::compute_envelope() const {
    auto result = ecitygml::capi::ecitygml_AbstractRingKind_compute_envelope(this->AsFFI());
    return std::unique_ptr<ecitygml::Envelope>(ecitygml::Envelope::FromFFI(result));
}

inline const ecitygml::capi::AbstractRingKind* ecitygml::AbstractRingKind::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AbstractRingKind*>(this);
}

inline ecitygml::capi::AbstractRingKind* ecitygml::AbstractRingKind::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AbstractRingKind*>(this);
}

inline const ecitygml::AbstractRingKind* ecitygml::AbstractRingKind::FromFFI(const ecitygml::capi::AbstractRingKind* ptr) {
    return reinterpret_cast<const ecitygml::AbstractRingKind*>(ptr);
}

inline ecitygml::AbstractRingKind* ecitygml::AbstractRingKind::FromFFI(ecitygml::capi::AbstractRingKind* ptr) {
    return reinterpret_cast<ecitygml::AbstractRingKind*>(ptr);
}

inline void ecitygml::AbstractRingKind::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AbstractRingKind_destroy(reinterpret_cast<ecitygml::capi::AbstractRingKind*>(ptr));
}


#endif // ecitygml_AbstractRingKind_HPP
