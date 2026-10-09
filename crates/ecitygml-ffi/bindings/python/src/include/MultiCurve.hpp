#ifndef ECITYGML_MultiCurve_HPP
#define ECITYGML_MultiCurve_HPP

#include "MultiCurve.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "AbstractCurvePropertyIterator.hpp"
#include "AbstractGeometryKind.hpp"
#include "CodeIterator.hpp"
#include "Envelope.hpp"
#include "Error.hpp"
#include "Id.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_MultiCurve_id(const ecitygml::capi::MultiCurve* self);

    ecitygml::capi::CodeIterator* ecitygml_MultiCurve_names(const ecitygml::capi::MultiCurve* self);

    const ecitygml::capi::MultiCurve* ecitygml_MultiCurve_try_from(const ecitygml::capi::AbstractGeometryKind* geometry);

    ecitygml::capi::AbstractCurvePropertyIterator* ecitygml_MultiCurve_curve_member(const ecitygml::capi::MultiCurve* self);

    typedef struct ecitygml_MultiCurve_length_3d_result {union {double ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_MultiCurve_length_3d_result;
    ecitygml_MultiCurve_length_3d_result ecitygml_MultiCurve_length_3d(const ecitygml::capi::MultiCurve* self);

    ecitygml::capi::Envelope* ecitygml_MultiCurve_compute_envelope(const ecitygml::capi::MultiCurve* self);

    void ecitygml_MultiCurve_destroy(MultiCurve* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::MultiCurve::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_MultiCurve_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::MultiCurve::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_MultiCurve_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::MultiCurve* ecitygml::MultiCurve::try_from(const ecitygml::AbstractGeometryKind& geometry DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_MultiCurve_try_from(geometry.AsFFI());
    return ecitygml::MultiCurve::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AbstractCurvePropertyIterator> ecitygml::MultiCurve::curve_member() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_MultiCurve_curve_member(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractCurvePropertyIterator>(ecitygml::AbstractCurvePropertyIterator::FromFFI(result));
}

inline ecitygml::diplomat::result<double, std::unique_ptr<ecitygml::Error>> ecitygml::MultiCurve::length_3d() const {
    auto result = ecitygml::capi::ecitygml_MultiCurve_length_3d(this->AsFFI());
    return result.is_ok ? ecitygml::diplomat::result<double, std::unique_ptr<ecitygml::Error>>(ecitygml::diplomat::Ok<double>(result.ok)) : ecitygml::diplomat::result<double, std::unique_ptr<ecitygml::Error>>(ecitygml::diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline std::unique_ptr<ecitygml::Envelope> ecitygml::MultiCurve::compute_envelope() const {
    auto result = ecitygml::capi::ecitygml_MultiCurve_compute_envelope(this->AsFFI());
    return std::unique_ptr<ecitygml::Envelope>(ecitygml::Envelope::FromFFI(result));
}

inline const ecitygml::capi::MultiCurve* ecitygml::MultiCurve::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::MultiCurve*>(this);
}

inline ecitygml::capi::MultiCurve* ecitygml::MultiCurve::AsFFI() {
    return reinterpret_cast<ecitygml::capi::MultiCurve*>(this);
}

inline const ecitygml::MultiCurve* ecitygml::MultiCurve::FromFFI(const ecitygml::capi::MultiCurve* ptr) {
    return reinterpret_cast<const ecitygml::MultiCurve*>(ptr);
}

inline ecitygml::MultiCurve* ecitygml::MultiCurve::FromFFI(ecitygml::capi::MultiCurve* ptr) {
    return reinterpret_cast<ecitygml::MultiCurve*>(ptr);
}

inline void ecitygml::MultiCurve::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_MultiCurve_destroy(reinterpret_cast<ecitygml::capi::MultiCurve*>(ptr));
}


#endif // ECITYGML_MultiCurve_HPP
