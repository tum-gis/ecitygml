#ifndef ECITYGML_RoadUsageValueIterator_HPP
#define ECITYGML_RoadUsageValueIterator_HPP

#include "RoadUsageValueIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "RoadUsageValue.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::RoadUsageValue* ecitygml_RoadUsageValueIterator_next(ecitygml::capi::RoadUsageValueIterator* self);

    void ecitygml_RoadUsageValueIterator_destroy(RoadUsageValueIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::RoadUsageValue* ecitygml::RoadUsageValueIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_RoadUsageValueIterator_next(this->AsFFI());
    return ecitygml::RoadUsageValue::FromFFI(result);
}

inline const ecitygml::capi::RoadUsageValueIterator* ecitygml::RoadUsageValueIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::RoadUsageValueIterator*>(this);
}

inline ecitygml::capi::RoadUsageValueIterator* ecitygml::RoadUsageValueIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::RoadUsageValueIterator*>(this);
}

inline const ecitygml::RoadUsageValueIterator* ecitygml::RoadUsageValueIterator::FromFFI(const ecitygml::capi::RoadUsageValueIterator* ptr) {
    return reinterpret_cast<const ecitygml::RoadUsageValueIterator*>(ptr);
}

inline ecitygml::RoadUsageValueIterator* ecitygml::RoadUsageValueIterator::FromFFI(ecitygml::capi::RoadUsageValueIterator* ptr) {
    return reinterpret_cast<ecitygml::RoadUsageValueIterator*>(ptr);
}

inline void ecitygml::RoadUsageValueIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_RoadUsageValueIterator_destroy(reinterpret_cast<ecitygml::capi::RoadUsageValueIterator*>(ptr));
}


#endif // ECITYGML_RoadUsageValueIterator_HPP
