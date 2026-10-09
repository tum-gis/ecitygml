#ifndef ECITYGML_TrafficSpaceUsageValueIterator_HPP
#define ECITYGML_TrafficSpaceUsageValueIterator_HPP

#include "TrafficSpaceUsageValueIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "TrafficSpaceUsageValue.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::TrafficSpaceUsageValue* ecitygml_TrafficSpaceUsageValueIterator_next(ecitygml::capi::TrafficSpaceUsageValueIterator* self);

    void ecitygml_TrafficSpaceUsageValueIterator_destroy(TrafficSpaceUsageValueIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::TrafficSpaceUsageValue* ecitygml::TrafficSpaceUsageValueIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpaceUsageValueIterator_next(this->AsFFI());
    return ecitygml::TrafficSpaceUsageValue::FromFFI(result);
}

inline const ecitygml::capi::TrafficSpaceUsageValueIterator* ecitygml::TrafficSpaceUsageValueIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::TrafficSpaceUsageValueIterator*>(this);
}

inline ecitygml::capi::TrafficSpaceUsageValueIterator* ecitygml::TrafficSpaceUsageValueIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::TrafficSpaceUsageValueIterator*>(this);
}

inline const ecitygml::TrafficSpaceUsageValueIterator* ecitygml::TrafficSpaceUsageValueIterator::FromFFI(const ecitygml::capi::TrafficSpaceUsageValueIterator* ptr) {
    return reinterpret_cast<const ecitygml::TrafficSpaceUsageValueIterator*>(ptr);
}

inline ecitygml::TrafficSpaceUsageValueIterator* ecitygml::TrafficSpaceUsageValueIterator::FromFFI(ecitygml::capi::TrafficSpaceUsageValueIterator* ptr) {
    return reinterpret_cast<ecitygml::TrafficSpaceUsageValueIterator*>(ptr);
}

inline void ecitygml::TrafficSpaceUsageValueIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_TrafficSpaceUsageValueIterator_destroy(reinterpret_cast<ecitygml::capi::TrafficSpaceUsageValueIterator*>(ptr));
}


#endif // ECITYGML_TrafficSpaceUsageValueIterator_HPP
