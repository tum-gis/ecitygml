#ifndef ecitygml_TunnelFunctionValueIterator_HPP
#define ecitygml_TunnelFunctionValueIterator_HPP

#include "TunnelFunctionValueIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "TunnelFunctionValue.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::TunnelFunctionValue* ecitygml_TunnelFunctionValueIterator_next(ecitygml::capi::TunnelFunctionValueIterator* self);

    void ecitygml_TunnelFunctionValueIterator_destroy(TunnelFunctionValueIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::TunnelFunctionValue* ecitygml::TunnelFunctionValueIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelFunctionValueIterator_next(this->AsFFI());
    return ecitygml::TunnelFunctionValue::FromFFI(result);
}

inline const ecitygml::capi::TunnelFunctionValueIterator* ecitygml::TunnelFunctionValueIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::TunnelFunctionValueIterator*>(this);
}

inline ecitygml::capi::TunnelFunctionValueIterator* ecitygml::TunnelFunctionValueIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::TunnelFunctionValueIterator*>(this);
}

inline const ecitygml::TunnelFunctionValueIterator* ecitygml::TunnelFunctionValueIterator::FromFFI(const ecitygml::capi::TunnelFunctionValueIterator* ptr) {
    return reinterpret_cast<const ecitygml::TunnelFunctionValueIterator*>(ptr);
}

inline ecitygml::TunnelFunctionValueIterator* ecitygml::TunnelFunctionValueIterator::FromFFI(ecitygml::capi::TunnelFunctionValueIterator* ptr) {
    return reinterpret_cast<ecitygml::TunnelFunctionValueIterator*>(ptr);
}

inline void ecitygml::TunnelFunctionValueIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_TunnelFunctionValueIterator_destroy(reinterpret_cast<ecitygml::capi::TunnelFunctionValueIterator*>(ptr));
}


#endif // ecitygml_TunnelFunctionValueIterator_HPP
