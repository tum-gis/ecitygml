#ifndef ecitygml_BridgeUsageValueIterator_HPP
#define ecitygml_BridgeUsageValueIterator_HPP

#include "BridgeUsageValueIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "BridgeUsageValue.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::BridgeUsageValue* ecitygml_BridgeUsageValueIterator_next(ecitygml::capi::BridgeUsageValueIterator* self);

    void ecitygml_BridgeUsageValueIterator_destroy(BridgeUsageValueIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::BridgeUsageValue* ecitygml::BridgeUsageValueIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgeUsageValueIterator_next(this->AsFFI());
    return ecitygml::BridgeUsageValue::FromFFI(result);
}

inline const ecitygml::capi::BridgeUsageValueIterator* ecitygml::BridgeUsageValueIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::BridgeUsageValueIterator*>(this);
}

inline ecitygml::capi::BridgeUsageValueIterator* ecitygml::BridgeUsageValueIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::BridgeUsageValueIterator*>(this);
}

inline const ecitygml::BridgeUsageValueIterator* ecitygml::BridgeUsageValueIterator::FromFFI(const ecitygml::capi::BridgeUsageValueIterator* ptr) {
    return reinterpret_cast<const ecitygml::BridgeUsageValueIterator*>(ptr);
}

inline ecitygml::BridgeUsageValueIterator* ecitygml::BridgeUsageValueIterator::FromFFI(ecitygml::capi::BridgeUsageValueIterator* ptr) {
    return reinterpret_cast<ecitygml::BridgeUsageValueIterator*>(ptr);
}

inline void ecitygml::BridgeUsageValueIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_BridgeUsageValueIterator_destroy(reinterpret_cast<ecitygml::capi::BridgeUsageValueIterator*>(ptr));
}


#endif // ecitygml_BridgeUsageValueIterator_HPP
