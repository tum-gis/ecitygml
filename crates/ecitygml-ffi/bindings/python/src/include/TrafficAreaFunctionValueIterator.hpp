#ifndef ECITYGML_TrafficAreaFunctionValueIterator_HPP
#define ECITYGML_TrafficAreaFunctionValueIterator_HPP

#include "TrafficAreaFunctionValueIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "TrafficAreaFunctionValue.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::TrafficAreaFunctionValue* ecitygml_TrafficAreaFunctionValueIterator_next(ecitygml::capi::TrafficAreaFunctionValueIterator* self);

    void ecitygml_TrafficAreaFunctionValueIterator_destroy(TrafficAreaFunctionValueIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::TrafficAreaFunctionValue* ecitygml::TrafficAreaFunctionValueIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficAreaFunctionValueIterator_next(this->AsFFI());
    return ecitygml::TrafficAreaFunctionValue::FromFFI(result);
}

inline const ecitygml::capi::TrafficAreaFunctionValueIterator* ecitygml::TrafficAreaFunctionValueIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::TrafficAreaFunctionValueIterator*>(this);
}

inline ecitygml::capi::TrafficAreaFunctionValueIterator* ecitygml::TrafficAreaFunctionValueIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::TrafficAreaFunctionValueIterator*>(this);
}

inline const ecitygml::TrafficAreaFunctionValueIterator* ecitygml::TrafficAreaFunctionValueIterator::FromFFI(const ecitygml::capi::TrafficAreaFunctionValueIterator* ptr) {
    return reinterpret_cast<const ecitygml::TrafficAreaFunctionValueIterator*>(ptr);
}

inline ecitygml::TrafficAreaFunctionValueIterator* ecitygml::TrafficAreaFunctionValueIterator::FromFFI(ecitygml::capi::TrafficAreaFunctionValueIterator* ptr) {
    return reinterpret_cast<ecitygml::TrafficAreaFunctionValueIterator*>(ptr);
}

inline void ecitygml::TrafficAreaFunctionValueIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_TrafficAreaFunctionValueIterator_destroy(reinterpret_cast<ecitygml::capi::TrafficAreaFunctionValueIterator*>(ptr));
}


#endif // ECITYGML_TrafficAreaFunctionValueIterator_HPP
