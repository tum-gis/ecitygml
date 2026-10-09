#ifndef ecitygml_RoadFunctionValueIterator_HPP
#define ecitygml_RoadFunctionValueIterator_HPP

#include "RoadFunctionValueIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "RoadFunctionValue.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::RoadFunctionValue* ecitygml_RoadFunctionValueIterator_next(ecitygml::capi::RoadFunctionValueIterator* self);

    void ecitygml_RoadFunctionValueIterator_destroy(RoadFunctionValueIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::RoadFunctionValue* ecitygml::RoadFunctionValueIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_RoadFunctionValueIterator_next(this->AsFFI());
    return ecitygml::RoadFunctionValue::FromFFI(result);
}

inline const ecitygml::capi::RoadFunctionValueIterator* ecitygml::RoadFunctionValueIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::RoadFunctionValueIterator*>(this);
}

inline ecitygml::capi::RoadFunctionValueIterator* ecitygml::RoadFunctionValueIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::RoadFunctionValueIterator*>(this);
}

inline const ecitygml::RoadFunctionValueIterator* ecitygml::RoadFunctionValueIterator::FromFFI(const ecitygml::capi::RoadFunctionValueIterator* ptr) {
    return reinterpret_cast<const ecitygml::RoadFunctionValueIterator*>(ptr);
}

inline ecitygml::RoadFunctionValueIterator* ecitygml::RoadFunctionValueIterator::FromFFI(ecitygml::capi::RoadFunctionValueIterator* ptr) {
    return reinterpret_cast<ecitygml::RoadFunctionValueIterator*>(ptr);
}

inline void ecitygml::RoadFunctionValueIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_RoadFunctionValueIterator_destroy(reinterpret_cast<ecitygml::capi::RoadFunctionValueIterator*>(ptr));
}


#endif // ecitygml_RoadFunctionValueIterator_HPP
