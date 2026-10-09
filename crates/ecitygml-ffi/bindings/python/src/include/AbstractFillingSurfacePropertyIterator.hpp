#ifndef ECITYGML_AbstractFillingSurfacePropertyIterator_HPP
#define ECITYGML_AbstractFillingSurfacePropertyIterator_HPP

#include "AbstractFillingSurfacePropertyIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "AbstractFillingSurfaceProperty.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::AbstractFillingSurfaceProperty* ecitygml_AbstractFillingSurfacePropertyIterator_next(ecitygml::capi::AbstractFillingSurfacePropertyIterator* self);

    void ecitygml_AbstractFillingSurfacePropertyIterator_destroy(AbstractFillingSurfacePropertyIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::AbstractFillingSurfaceProperty* ecitygml::AbstractFillingSurfacePropertyIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractFillingSurfacePropertyIterator_next(this->AsFFI());
    return ecitygml::AbstractFillingSurfaceProperty::FromFFI(result);
}

inline const ecitygml::capi::AbstractFillingSurfacePropertyIterator* ecitygml::AbstractFillingSurfacePropertyIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AbstractFillingSurfacePropertyIterator*>(this);
}

inline ecitygml::capi::AbstractFillingSurfacePropertyIterator* ecitygml::AbstractFillingSurfacePropertyIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AbstractFillingSurfacePropertyIterator*>(this);
}

inline const ecitygml::AbstractFillingSurfacePropertyIterator* ecitygml::AbstractFillingSurfacePropertyIterator::FromFFI(const ecitygml::capi::AbstractFillingSurfacePropertyIterator* ptr) {
    return reinterpret_cast<const ecitygml::AbstractFillingSurfacePropertyIterator*>(ptr);
}

inline ecitygml::AbstractFillingSurfacePropertyIterator* ecitygml::AbstractFillingSurfacePropertyIterator::FromFFI(ecitygml::capi::AbstractFillingSurfacePropertyIterator* ptr) {
    return reinterpret_cast<ecitygml::AbstractFillingSurfacePropertyIterator*>(ptr);
}

inline void ecitygml::AbstractFillingSurfacePropertyIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AbstractFillingSurfacePropertyIterator_destroy(reinterpret_cast<ecitygml::capi::AbstractFillingSurfacePropertyIterator*>(ptr));
}


#endif // ECITYGML_AbstractFillingSurfacePropertyIterator_HPP
