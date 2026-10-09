#ifndef ecitygml_TrafficAreaUsageValueIterator_HPP
#define ecitygml_TrafficAreaUsageValueIterator_HPP

#include "TrafficAreaUsageValueIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "TrafficAreaUsageValue.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::TrafficAreaUsageValue* ecitygml_TrafficAreaUsageValueIterator_next(ecitygml::capi::TrafficAreaUsageValueIterator* self);

    void ecitygml_TrafficAreaUsageValueIterator_destroy(TrafficAreaUsageValueIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::TrafficAreaUsageValue* ecitygml::TrafficAreaUsageValueIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficAreaUsageValueIterator_next(this->AsFFI());
    return ecitygml::TrafficAreaUsageValue::FromFFI(result);
}

inline const ecitygml::capi::TrafficAreaUsageValueIterator* ecitygml::TrafficAreaUsageValueIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::TrafficAreaUsageValueIterator*>(this);
}

inline ecitygml::capi::TrafficAreaUsageValueIterator* ecitygml::TrafficAreaUsageValueIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::TrafficAreaUsageValueIterator*>(this);
}

inline const ecitygml::TrafficAreaUsageValueIterator* ecitygml::TrafficAreaUsageValueIterator::FromFFI(const ecitygml::capi::TrafficAreaUsageValueIterator* ptr) {
    return reinterpret_cast<const ecitygml::TrafficAreaUsageValueIterator*>(ptr);
}

inline ecitygml::TrafficAreaUsageValueIterator* ecitygml::TrafficAreaUsageValueIterator::FromFFI(ecitygml::capi::TrafficAreaUsageValueIterator* ptr) {
    return reinterpret_cast<ecitygml::TrafficAreaUsageValueIterator*>(ptr);
}

inline void ecitygml::TrafficAreaUsageValueIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_TrafficAreaUsageValueIterator_destroy(reinterpret_cast<ecitygml::capi::TrafficAreaUsageValueIterator*>(ptr));
}


#endif // ecitygml_TrafficAreaUsageValueIterator_HPP
