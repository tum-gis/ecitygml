#ifndef ecitygml_TunnelUsageValueIterator_HPP
#define ecitygml_TunnelUsageValueIterator_HPP

#include "TunnelUsageValueIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "TunnelUsageValue.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::TunnelUsageValue* ecitygml_TunnelUsageValueIterator_next(ecitygml::capi::TunnelUsageValueIterator* self);

    void ecitygml_TunnelUsageValueIterator_destroy(TunnelUsageValueIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::TunnelUsageValue* ecitygml::TunnelUsageValueIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelUsageValueIterator_next(this->AsFFI());
    return ecitygml::TunnelUsageValue::FromFFI(result);
}

inline const ecitygml::capi::TunnelUsageValueIterator* ecitygml::TunnelUsageValueIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::TunnelUsageValueIterator*>(this);
}

inline ecitygml::capi::TunnelUsageValueIterator* ecitygml::TunnelUsageValueIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::TunnelUsageValueIterator*>(this);
}

inline const ecitygml::TunnelUsageValueIterator* ecitygml::TunnelUsageValueIterator::FromFFI(const ecitygml::capi::TunnelUsageValueIterator* ptr) {
    return reinterpret_cast<const ecitygml::TunnelUsageValueIterator*>(ptr);
}

inline ecitygml::TunnelUsageValueIterator* ecitygml::TunnelUsageValueIterator::FromFFI(ecitygml::capi::TunnelUsageValueIterator* ptr) {
    return reinterpret_cast<ecitygml::TunnelUsageValueIterator*>(ptr);
}

inline void ecitygml::TunnelUsageValueIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_TunnelUsageValueIterator_destroy(reinterpret_cast<ecitygml::capi::TunnelUsageValueIterator*>(ptr));
}


#endif // ecitygml_TunnelUsageValueIterator_HPP
