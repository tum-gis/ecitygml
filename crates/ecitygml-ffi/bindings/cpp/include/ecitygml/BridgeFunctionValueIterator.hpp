#ifndef ecitygml_BridgeFunctionValueIterator_HPP
#define ecitygml_BridgeFunctionValueIterator_HPP

#include "BridgeFunctionValueIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "BridgeFunctionValue.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::BridgeFunctionValue* ecitygml_BridgeFunctionValueIterator_next(ecitygml::capi::BridgeFunctionValueIterator* self);

    void ecitygml_BridgeFunctionValueIterator_destroy(BridgeFunctionValueIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::BridgeFunctionValue* ecitygml::BridgeFunctionValueIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgeFunctionValueIterator_next(this->AsFFI());
    return ecitygml::BridgeFunctionValue::FromFFI(result);
}

inline const ecitygml::capi::BridgeFunctionValueIterator* ecitygml::BridgeFunctionValueIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::BridgeFunctionValueIterator*>(this);
}

inline ecitygml::capi::BridgeFunctionValueIterator* ecitygml::BridgeFunctionValueIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::BridgeFunctionValueIterator*>(this);
}

inline const ecitygml::BridgeFunctionValueIterator* ecitygml::BridgeFunctionValueIterator::FromFFI(const ecitygml::capi::BridgeFunctionValueIterator* ptr) {
    return reinterpret_cast<const ecitygml::BridgeFunctionValueIterator*>(ptr);
}

inline ecitygml::BridgeFunctionValueIterator* ecitygml::BridgeFunctionValueIterator::FromFFI(ecitygml::capi::BridgeFunctionValueIterator* ptr) {
    return reinterpret_cast<ecitygml::BridgeFunctionValueIterator*>(ptr);
}

inline void ecitygml::BridgeFunctionValueIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_BridgeFunctionValueIterator_destroy(reinterpret_cast<ecitygml::capi::BridgeFunctionValueIterator*>(ptr));
}


#endif // ecitygml_BridgeFunctionValueIterator_HPP
