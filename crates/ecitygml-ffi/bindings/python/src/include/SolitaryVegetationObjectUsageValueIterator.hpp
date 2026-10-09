#ifndef ECITYGML_SolitaryVegetationObjectUsageValueIterator_HPP
#define ECITYGML_SolitaryVegetationObjectUsageValueIterator_HPP

#include "SolitaryVegetationObjectUsageValueIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "SolitaryVegetationObjectUsageValue.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::SolitaryVegetationObjectUsageValue* ecitygml_SolitaryVegetationObjectUsageValueIterator_next(ecitygml::capi::SolitaryVegetationObjectUsageValueIterator* self);

    void ecitygml_SolitaryVegetationObjectUsageValueIterator_destroy(SolitaryVegetationObjectUsageValueIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::SolitaryVegetationObjectUsageValue* ecitygml::SolitaryVegetationObjectUsageValueIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObjectUsageValueIterator_next(this->AsFFI());
    return ecitygml::SolitaryVegetationObjectUsageValue::FromFFI(result);
}

inline const ecitygml::capi::SolitaryVegetationObjectUsageValueIterator* ecitygml::SolitaryVegetationObjectUsageValueIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::SolitaryVegetationObjectUsageValueIterator*>(this);
}

inline ecitygml::capi::SolitaryVegetationObjectUsageValueIterator* ecitygml::SolitaryVegetationObjectUsageValueIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::SolitaryVegetationObjectUsageValueIterator*>(this);
}

inline const ecitygml::SolitaryVegetationObjectUsageValueIterator* ecitygml::SolitaryVegetationObjectUsageValueIterator::FromFFI(const ecitygml::capi::SolitaryVegetationObjectUsageValueIterator* ptr) {
    return reinterpret_cast<const ecitygml::SolitaryVegetationObjectUsageValueIterator*>(ptr);
}

inline ecitygml::SolitaryVegetationObjectUsageValueIterator* ecitygml::SolitaryVegetationObjectUsageValueIterator::FromFFI(ecitygml::capi::SolitaryVegetationObjectUsageValueIterator* ptr) {
    return reinterpret_cast<ecitygml::SolitaryVegetationObjectUsageValueIterator*>(ptr);
}

inline void ecitygml::SolitaryVegetationObjectUsageValueIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_SolitaryVegetationObjectUsageValueIterator_destroy(reinterpret_cast<ecitygml::capi::SolitaryVegetationObjectUsageValueIterator*>(ptr));
}


#endif // ECITYGML_SolitaryVegetationObjectUsageValueIterator_HPP
