#ifndef ECITYGML_AbstractCurveKind_HPP
#define ECITYGML_AbstractCurveKind_HPP

#include "AbstractCurveKind.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "AbstractGeometryKind.hpp"
#include "CodeIterator.hpp"
#include "Envelope.hpp"
#include "GeometryType.hpp"
#include "Id.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_AbstractCurveKind_id(const ecitygml::capi::AbstractCurveKind* self);

    ecitygml::capi::CodeIterator* ecitygml_AbstractCurveKind_names(const ecitygml::capi::AbstractCurveKind* self);

    const ecitygml::capi::AbstractCurveKind* ecitygml_AbstractCurveKind_try_from(const ecitygml::capi::AbstractGeometryKind* geometry);

    ecitygml::capi::GeometryType ecitygml_AbstractCurveKind_geometry_type(const ecitygml::capi::AbstractCurveKind* self);

    double ecitygml_AbstractCurveKind_length_3d(const ecitygml::capi::AbstractCurveKind* self);

    ecitygml::capi::Envelope* ecitygml_AbstractCurveKind_compute_envelope(const ecitygml::capi::AbstractCurveKind* self);

    void ecitygml_AbstractCurveKind_destroy(AbstractCurveKind* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::AbstractCurveKind::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractCurveKind_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::AbstractCurveKind::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractCurveKind_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::AbstractCurveKind* ecitygml::AbstractCurveKind::try_from(const ecitygml::AbstractGeometryKind& geometry DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_AbstractCurveKind_try_from(geometry.AsFFI());
    return ecitygml::AbstractCurveKind::FromFFI(result);
}

inline ecitygml::GeometryType ecitygml::AbstractCurveKind::geometry_type() const {
    auto result = ecitygml::capi::ecitygml_AbstractCurveKind_geometry_type(this->AsFFI());
    return ecitygml::GeometryType::FromFFI(result);
}

inline double ecitygml::AbstractCurveKind::length_3d() const {
    auto result = ecitygml::capi::ecitygml_AbstractCurveKind_length_3d(this->AsFFI());
    return result;
}

inline std::unique_ptr<ecitygml::Envelope> ecitygml::AbstractCurveKind::compute_envelope() const {
    auto result = ecitygml::capi::ecitygml_AbstractCurveKind_compute_envelope(this->AsFFI());
    return std::unique_ptr<ecitygml::Envelope>(ecitygml::Envelope::FromFFI(result));
}

inline const ecitygml::capi::AbstractCurveKind* ecitygml::AbstractCurveKind::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AbstractCurveKind*>(this);
}

inline ecitygml::capi::AbstractCurveKind* ecitygml::AbstractCurveKind::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AbstractCurveKind*>(this);
}

inline const ecitygml::AbstractCurveKind* ecitygml::AbstractCurveKind::FromFFI(const ecitygml::capi::AbstractCurveKind* ptr) {
    return reinterpret_cast<const ecitygml::AbstractCurveKind*>(ptr);
}

inline ecitygml::AbstractCurveKind* ecitygml::AbstractCurveKind::FromFFI(ecitygml::capi::AbstractCurveKind* ptr) {
    return reinterpret_cast<ecitygml::AbstractCurveKind*>(ptr);
}

inline void ecitygml::AbstractCurveKind::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AbstractCurveKind_destroy(reinterpret_cast<ecitygml::capi::AbstractCurveKind*>(ptr));
}


#endif // ECITYGML_AbstractCurveKind_HPP
