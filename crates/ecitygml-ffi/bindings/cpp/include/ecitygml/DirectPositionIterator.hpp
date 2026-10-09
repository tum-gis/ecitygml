#ifndef ecitygml_DirectPositionIterator_HPP
#define ecitygml_DirectPositionIterator_HPP

#include "DirectPositionIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "DirectPosition.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::DirectPosition* ecitygml_DirectPositionIterator_next(ecitygml::capi::DirectPositionIterator* self);

    void ecitygml_DirectPositionIterator_destroy(DirectPositionIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::DirectPosition* ecitygml::DirectPositionIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_DirectPositionIterator_next(this->AsFFI());
    return ecitygml::DirectPosition::FromFFI(result);
}

inline const ecitygml::capi::DirectPositionIterator* ecitygml::DirectPositionIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::DirectPositionIterator*>(this);
}

inline ecitygml::capi::DirectPositionIterator* ecitygml::DirectPositionIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::DirectPositionIterator*>(this);
}

inline const ecitygml::DirectPositionIterator* ecitygml::DirectPositionIterator::FromFFI(const ecitygml::capi::DirectPositionIterator* ptr) {
    return reinterpret_cast<const ecitygml::DirectPositionIterator*>(ptr);
}

inline ecitygml::DirectPositionIterator* ecitygml::DirectPositionIterator::FromFFI(ecitygml::capi::DirectPositionIterator* ptr) {
    return reinterpret_cast<ecitygml::DirectPositionIterator*>(ptr);
}

inline void ecitygml::DirectPositionIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_DirectPositionIterator_destroy(reinterpret_cast<ecitygml::capi::DirectPositionIterator*>(ptr));
}


#endif // ecitygml_DirectPositionIterator_HPP
