#ifndef ECITYGML_CityFurnitureFunctionValueIterator_HPP
#define ECITYGML_CityFurnitureFunctionValueIterator_HPP

#include "CityFurnitureFunctionValueIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "CityFurnitureFunctionValue.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::CityFurnitureFunctionValue* ecitygml_CityFurnitureFunctionValueIterator_next(ecitygml::capi::CityFurnitureFunctionValueIterator* self);

    void ecitygml_CityFurnitureFunctionValueIterator_destroy(CityFurnitureFunctionValueIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::CityFurnitureFunctionValue* ecitygml::CityFurnitureFunctionValueIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurnitureFunctionValueIterator_next(this->AsFFI());
    return ecitygml::CityFurnitureFunctionValue::FromFFI(result);
}

inline const ecitygml::capi::CityFurnitureFunctionValueIterator* ecitygml::CityFurnitureFunctionValueIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::CityFurnitureFunctionValueIterator*>(this);
}

inline ecitygml::capi::CityFurnitureFunctionValueIterator* ecitygml::CityFurnitureFunctionValueIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::CityFurnitureFunctionValueIterator*>(this);
}

inline const ecitygml::CityFurnitureFunctionValueIterator* ecitygml::CityFurnitureFunctionValueIterator::FromFFI(const ecitygml::capi::CityFurnitureFunctionValueIterator* ptr) {
    return reinterpret_cast<const ecitygml::CityFurnitureFunctionValueIterator*>(ptr);
}

inline ecitygml::CityFurnitureFunctionValueIterator* ecitygml::CityFurnitureFunctionValueIterator::FromFFI(ecitygml::capi::CityFurnitureFunctionValueIterator* ptr) {
    return reinterpret_cast<ecitygml::CityFurnitureFunctionValueIterator*>(ptr);
}

inline void ecitygml::CityFurnitureFunctionValueIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_CityFurnitureFunctionValueIterator_destroy(reinterpret_cast<ecitygml::capi::CityFurnitureFunctionValueIterator*>(ptr));
}


#endif // ECITYGML_CityFurnitureFunctionValueIterator_HPP
