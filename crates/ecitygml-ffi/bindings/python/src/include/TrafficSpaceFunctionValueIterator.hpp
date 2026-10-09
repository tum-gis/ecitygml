#ifndef ECITYGML_TrafficSpaceFunctionValueIterator_HPP
#define ECITYGML_TrafficSpaceFunctionValueIterator_HPP

#include "TrafficSpaceFunctionValueIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "TrafficSpaceFunctionValue.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::TrafficSpaceFunctionValue* ecitygml_TrafficSpaceFunctionValueIterator_next(ecitygml::capi::TrafficSpaceFunctionValueIterator* self);

    void ecitygml_TrafficSpaceFunctionValueIterator_destroy(TrafficSpaceFunctionValueIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::TrafficSpaceFunctionValue* ecitygml::TrafficSpaceFunctionValueIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpaceFunctionValueIterator_next(this->AsFFI());
    return ecitygml::TrafficSpaceFunctionValue::FromFFI(result);
}

inline const ecitygml::capi::TrafficSpaceFunctionValueIterator* ecitygml::TrafficSpaceFunctionValueIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::TrafficSpaceFunctionValueIterator*>(this);
}

inline ecitygml::capi::TrafficSpaceFunctionValueIterator* ecitygml::TrafficSpaceFunctionValueIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::TrafficSpaceFunctionValueIterator*>(this);
}

inline const ecitygml::TrafficSpaceFunctionValueIterator* ecitygml::TrafficSpaceFunctionValueIterator::FromFFI(const ecitygml::capi::TrafficSpaceFunctionValueIterator* ptr) {
    return reinterpret_cast<const ecitygml::TrafficSpaceFunctionValueIterator*>(ptr);
}

inline ecitygml::TrafficSpaceFunctionValueIterator* ecitygml::TrafficSpaceFunctionValueIterator::FromFFI(ecitygml::capi::TrafficSpaceFunctionValueIterator* ptr) {
    return reinterpret_cast<ecitygml::TrafficSpaceFunctionValueIterator*>(ptr);
}

inline void ecitygml::TrafficSpaceFunctionValueIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_TrafficSpaceFunctionValueIterator_destroy(reinterpret_cast<ecitygml::capi::TrafficSpaceFunctionValueIterator*>(ptr));
}


#endif // ECITYGML_TrafficSpaceFunctionValueIterator_HPP
