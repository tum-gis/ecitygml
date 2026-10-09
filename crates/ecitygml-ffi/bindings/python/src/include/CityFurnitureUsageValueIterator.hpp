#ifndef ECITYGML_CityFurnitureUsageValueIterator_HPP
#define ECITYGML_CityFurnitureUsageValueIterator_HPP

#include "CityFurnitureUsageValueIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "CityFurnitureUsageValue.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::CityFurnitureUsageValue* ecitygml_CityFurnitureUsageValueIterator_next(ecitygml::capi::CityFurnitureUsageValueIterator* self);

    void ecitygml_CityFurnitureUsageValueIterator_destroy(CityFurnitureUsageValueIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::CityFurnitureUsageValue* ecitygml::CityFurnitureUsageValueIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurnitureUsageValueIterator_next(this->AsFFI());
    return ecitygml::CityFurnitureUsageValue::FromFFI(result);
}

inline const ecitygml::capi::CityFurnitureUsageValueIterator* ecitygml::CityFurnitureUsageValueIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::CityFurnitureUsageValueIterator*>(this);
}

inline ecitygml::capi::CityFurnitureUsageValueIterator* ecitygml::CityFurnitureUsageValueIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::CityFurnitureUsageValueIterator*>(this);
}

inline const ecitygml::CityFurnitureUsageValueIterator* ecitygml::CityFurnitureUsageValueIterator::FromFFI(const ecitygml::capi::CityFurnitureUsageValueIterator* ptr) {
    return reinterpret_cast<const ecitygml::CityFurnitureUsageValueIterator*>(ptr);
}

inline ecitygml::CityFurnitureUsageValueIterator* ecitygml::CityFurnitureUsageValueIterator::FromFFI(ecitygml::capi::CityFurnitureUsageValueIterator* ptr) {
    return reinterpret_cast<ecitygml::CityFurnitureUsageValueIterator*>(ptr);
}

inline void ecitygml::CityFurnitureUsageValueIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_CityFurnitureUsageValueIterator_destroy(reinterpret_cast<ecitygml::capi::CityFurnitureUsageValueIterator*>(ptr));
}


#endif // ECITYGML_CityFurnitureUsageValueIterator_HPP
