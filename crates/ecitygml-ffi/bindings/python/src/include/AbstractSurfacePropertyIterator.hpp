#ifndef ECITYGML_AbstractSurfacePropertyIterator_HPP
#define ECITYGML_AbstractSurfacePropertyIterator_HPP

#include "AbstractSurfacePropertyIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "AbstractSurfaceProperty.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::AbstractSurfaceProperty* ecitygml_AbstractSurfacePropertyIterator_next(ecitygml::capi::AbstractSurfacePropertyIterator* self);

    void ecitygml_AbstractSurfacePropertyIterator_destroy(AbstractSurfacePropertyIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::AbstractSurfaceProperty* ecitygml::AbstractSurfacePropertyIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractSurfacePropertyIterator_next(this->AsFFI());
    return ecitygml::AbstractSurfaceProperty::FromFFI(result);
}

inline const ecitygml::capi::AbstractSurfacePropertyIterator* ecitygml::AbstractSurfacePropertyIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AbstractSurfacePropertyIterator*>(this);
}

inline ecitygml::capi::AbstractSurfacePropertyIterator* ecitygml::AbstractSurfacePropertyIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AbstractSurfacePropertyIterator*>(this);
}

inline const ecitygml::AbstractSurfacePropertyIterator* ecitygml::AbstractSurfacePropertyIterator::FromFFI(const ecitygml::capi::AbstractSurfacePropertyIterator* ptr) {
    return reinterpret_cast<const ecitygml::AbstractSurfacePropertyIterator*>(ptr);
}

inline ecitygml::AbstractSurfacePropertyIterator* ecitygml::AbstractSurfacePropertyIterator::FromFFI(ecitygml::capi::AbstractSurfacePropertyIterator* ptr) {
    return reinterpret_cast<ecitygml::AbstractSurfacePropertyIterator*>(ptr);
}

inline void ecitygml::AbstractSurfacePropertyIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AbstractSurfacePropertyIterator_destroy(reinterpret_cast<ecitygml::capi::AbstractSurfacePropertyIterator*>(ptr));
}


#endif // ECITYGML_AbstractSurfacePropertyIterator_HPP
