#ifndef ECITYGML_AbstractCurvePropertyIterator_HPP
#define ECITYGML_AbstractCurvePropertyIterator_HPP

#include "AbstractCurvePropertyIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "AbstractCurveProperty.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::AbstractCurveProperty* ecitygml_AbstractCurvePropertyIterator_next(ecitygml::capi::AbstractCurvePropertyIterator* self);

    void ecitygml_AbstractCurvePropertyIterator_destroy(AbstractCurvePropertyIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::AbstractCurveProperty* ecitygml::AbstractCurvePropertyIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractCurvePropertyIterator_next(this->AsFFI());
    return ecitygml::AbstractCurveProperty::FromFFI(result);
}

inline const ecitygml::capi::AbstractCurvePropertyIterator* ecitygml::AbstractCurvePropertyIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AbstractCurvePropertyIterator*>(this);
}

inline ecitygml::capi::AbstractCurvePropertyIterator* ecitygml::AbstractCurvePropertyIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AbstractCurvePropertyIterator*>(this);
}

inline const ecitygml::AbstractCurvePropertyIterator* ecitygml::AbstractCurvePropertyIterator::FromFFI(const ecitygml::capi::AbstractCurvePropertyIterator* ptr) {
    return reinterpret_cast<const ecitygml::AbstractCurvePropertyIterator*>(ptr);
}

inline ecitygml::AbstractCurvePropertyIterator* ecitygml::AbstractCurvePropertyIterator::FromFFI(ecitygml::capi::AbstractCurvePropertyIterator* ptr) {
    return reinterpret_cast<ecitygml::AbstractCurvePropertyIterator*>(ptr);
}

inline void ecitygml::AbstractCurvePropertyIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AbstractCurvePropertyIterator_destroy(reinterpret_cast<ecitygml::capi::AbstractCurvePropertyIterator*>(ptr));
}


#endif // ECITYGML_AbstractCurvePropertyIterator_HPP
