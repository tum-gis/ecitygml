#ifndef ECITYGML_LineString_HPP
#define ECITYGML_LineString_HPP

#include "LineString.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "AbstractCurveKind.hpp"
#include "CodeIterator.hpp"
#include "DirectPositionIterator.hpp"
#include "Envelope.hpp"
#include "Id.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_LineString_id(const ecitygml::capi::LineString* self);

    ecitygml::capi::CodeIterator* ecitygml_LineString_names(const ecitygml::capi::LineString* self);

    const ecitygml::capi::LineString* ecitygml_LineString_try_from(const ecitygml::capi::AbstractCurveKind* curve);

    ecitygml::capi::DirectPositionIterator* ecitygml_LineString_points(const ecitygml::capi::LineString* self);

    double ecitygml_LineString_length_3d(const ecitygml::capi::LineString* self);

    ecitygml::capi::Envelope* ecitygml_LineString_compute_envelope(const ecitygml::capi::LineString* self);

    void ecitygml_LineString_destroy(LineString* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::LineString::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_LineString_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::LineString::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_LineString_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::LineString* ecitygml::LineString::try_from(const ecitygml::AbstractCurveKind& curve DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_LineString_try_from(curve.AsFFI());
    return ecitygml::LineString::FromFFI(result);
}

inline std::unique_ptr<ecitygml::DirectPositionIterator> ecitygml::LineString::points() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_LineString_points(this->AsFFI());
    return std::unique_ptr<ecitygml::DirectPositionIterator>(ecitygml::DirectPositionIterator::FromFFI(result));
}

inline double ecitygml::LineString::length_3d() const {
    auto result = ecitygml::capi::ecitygml_LineString_length_3d(this->AsFFI());
    return result;
}

inline std::unique_ptr<ecitygml::Envelope> ecitygml::LineString::compute_envelope() const {
    auto result = ecitygml::capi::ecitygml_LineString_compute_envelope(this->AsFFI());
    return std::unique_ptr<ecitygml::Envelope>(ecitygml::Envelope::FromFFI(result));
}

inline const ecitygml::capi::LineString* ecitygml::LineString::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::LineString*>(this);
}

inline ecitygml::capi::LineString* ecitygml::LineString::AsFFI() {
    return reinterpret_cast<ecitygml::capi::LineString*>(this);
}

inline const ecitygml::LineString* ecitygml::LineString::FromFFI(const ecitygml::capi::LineString* ptr) {
    return reinterpret_cast<const ecitygml::LineString*>(ptr);
}

inline ecitygml::LineString* ecitygml::LineString::FromFFI(ecitygml::capi::LineString* ptr) {
    return reinterpret_cast<ecitygml::LineString*>(ptr);
}

inline void ecitygml::LineString::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_LineString_destroy(reinterpret_cast<ecitygml::capi::LineString*>(ptr));
}


#endif // ECITYGML_LineString_HPP
