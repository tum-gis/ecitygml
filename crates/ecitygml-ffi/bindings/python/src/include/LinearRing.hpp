#ifndef ECITYGML_LinearRing_HPP
#define ECITYGML_LinearRing_HPP

#include "LinearRing.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "AbstractRingKind.hpp"
#include "CodeIterator.hpp"
#include "DirectPositionIterator.hpp"
#include "Envelope.hpp"
#include "Id.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_LinearRing_id(const ecitygml::capi::LinearRing* self);

    ecitygml::capi::CodeIterator* ecitygml_LinearRing_names(const ecitygml::capi::LinearRing* self);

    const ecitygml::capi::LinearRing* ecitygml_LinearRing_try_from(const ecitygml::capi::AbstractRingKind* ring);

    ecitygml::capi::DirectPositionIterator* ecitygml_LinearRing_points(const ecitygml::capi::LinearRing* self);

    double ecitygml_LinearRing_length_3d(const ecitygml::capi::LinearRing* self);

    double ecitygml_LinearRing_area_3d(const ecitygml::capi::LinearRing* self);

    ecitygml::capi::Envelope* ecitygml_LinearRing_compute_envelope(const ecitygml::capi::LinearRing* self);

    void ecitygml_LinearRing_destroy(LinearRing* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::LinearRing::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_LinearRing_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::LinearRing::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_LinearRing_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::LinearRing* ecitygml::LinearRing::try_from(const ecitygml::AbstractRingKind& ring DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_LinearRing_try_from(ring.AsFFI());
    return ecitygml::LinearRing::FromFFI(result);
}

inline std::unique_ptr<ecitygml::DirectPositionIterator> ecitygml::LinearRing::points() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_LinearRing_points(this->AsFFI());
    return std::unique_ptr<ecitygml::DirectPositionIterator>(ecitygml::DirectPositionIterator::FromFFI(result));
}

inline double ecitygml::LinearRing::length_3d() const {
    auto result = ecitygml::capi::ecitygml_LinearRing_length_3d(this->AsFFI());
    return result;
}

inline double ecitygml::LinearRing::area_3d() const {
    auto result = ecitygml::capi::ecitygml_LinearRing_area_3d(this->AsFFI());
    return result;
}

inline std::unique_ptr<ecitygml::Envelope> ecitygml::LinearRing::compute_envelope() const {
    auto result = ecitygml::capi::ecitygml_LinearRing_compute_envelope(this->AsFFI());
    return std::unique_ptr<ecitygml::Envelope>(ecitygml::Envelope::FromFFI(result));
}

inline const ecitygml::capi::LinearRing* ecitygml::LinearRing::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::LinearRing*>(this);
}

inline ecitygml::capi::LinearRing* ecitygml::LinearRing::AsFFI() {
    return reinterpret_cast<ecitygml::capi::LinearRing*>(this);
}

inline const ecitygml::LinearRing* ecitygml::LinearRing::FromFFI(const ecitygml::capi::LinearRing* ptr) {
    return reinterpret_cast<const ecitygml::LinearRing*>(ptr);
}

inline ecitygml::LinearRing* ecitygml::LinearRing::FromFFI(ecitygml::capi::LinearRing* ptr) {
    return reinterpret_cast<ecitygml::LinearRing*>(ptr);
}

inline void ecitygml::LinearRing::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_LinearRing_destroy(reinterpret_cast<ecitygml::capi::LinearRing*>(ptr));
}


#endif // ECITYGML_LinearRing_HPP
