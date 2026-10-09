#ifndef ecitygml_SolitaryVegetationObjectFunctionValueIterator_HPP
#define ecitygml_SolitaryVegetationObjectFunctionValueIterator_HPP

#include "SolitaryVegetationObjectFunctionValueIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "SolitaryVegetationObjectFunctionValue.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::SolitaryVegetationObjectFunctionValue* ecitygml_SolitaryVegetationObjectFunctionValueIterator_next(ecitygml::capi::SolitaryVegetationObjectFunctionValueIterator* self);

    void ecitygml_SolitaryVegetationObjectFunctionValueIterator_destroy(SolitaryVegetationObjectFunctionValueIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::SolitaryVegetationObjectFunctionValue* ecitygml::SolitaryVegetationObjectFunctionValueIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObjectFunctionValueIterator_next(this->AsFFI());
    return ecitygml::SolitaryVegetationObjectFunctionValue::FromFFI(result);
}

inline const ecitygml::capi::SolitaryVegetationObjectFunctionValueIterator* ecitygml::SolitaryVegetationObjectFunctionValueIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::SolitaryVegetationObjectFunctionValueIterator*>(this);
}

inline ecitygml::capi::SolitaryVegetationObjectFunctionValueIterator* ecitygml::SolitaryVegetationObjectFunctionValueIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::SolitaryVegetationObjectFunctionValueIterator*>(this);
}

inline const ecitygml::SolitaryVegetationObjectFunctionValueIterator* ecitygml::SolitaryVegetationObjectFunctionValueIterator::FromFFI(const ecitygml::capi::SolitaryVegetationObjectFunctionValueIterator* ptr) {
    return reinterpret_cast<const ecitygml::SolitaryVegetationObjectFunctionValueIterator*>(ptr);
}

inline ecitygml::SolitaryVegetationObjectFunctionValueIterator* ecitygml::SolitaryVegetationObjectFunctionValueIterator::FromFFI(ecitygml::capi::SolitaryVegetationObjectFunctionValueIterator* ptr) {
    return reinterpret_cast<ecitygml::SolitaryVegetationObjectFunctionValueIterator*>(ptr);
}

inline void ecitygml::SolitaryVegetationObjectFunctionValueIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_SolitaryVegetationObjectFunctionValueIterator_destroy(reinterpret_cast<ecitygml::capi::SolitaryVegetationObjectFunctionValueIterator*>(ptr));
}


#endif // ecitygml_SolitaryVegetationObjectFunctionValueIterator_HPP
