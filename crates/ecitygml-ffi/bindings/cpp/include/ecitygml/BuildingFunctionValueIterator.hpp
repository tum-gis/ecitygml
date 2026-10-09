#ifndef ecitygml_BuildingFunctionValueIterator_HPP
#define ecitygml_BuildingFunctionValueIterator_HPP

#include "BuildingFunctionValueIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "BuildingFunctionValue.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::BuildingFunctionValue* ecitygml_BuildingFunctionValueIterator_next(ecitygml::capi::BuildingFunctionValueIterator* self);

    void ecitygml_BuildingFunctionValueIterator_destroy(BuildingFunctionValueIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::BuildingFunctionValue* ecitygml::BuildingFunctionValueIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingFunctionValueIterator_next(this->AsFFI());
    return ecitygml::BuildingFunctionValue::FromFFI(result);
}

inline const ecitygml::capi::BuildingFunctionValueIterator* ecitygml::BuildingFunctionValueIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::BuildingFunctionValueIterator*>(this);
}

inline ecitygml::capi::BuildingFunctionValueIterator* ecitygml::BuildingFunctionValueIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::BuildingFunctionValueIterator*>(this);
}

inline const ecitygml::BuildingFunctionValueIterator* ecitygml::BuildingFunctionValueIterator::FromFFI(const ecitygml::capi::BuildingFunctionValueIterator* ptr) {
    return reinterpret_cast<const ecitygml::BuildingFunctionValueIterator*>(ptr);
}

inline ecitygml::BuildingFunctionValueIterator* ecitygml::BuildingFunctionValueIterator::FromFFI(ecitygml::capi::BuildingFunctionValueIterator* ptr) {
    return reinterpret_cast<ecitygml::BuildingFunctionValueIterator*>(ptr);
}

inline void ecitygml::BuildingFunctionValueIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_BuildingFunctionValueIterator_destroy(reinterpret_cast<ecitygml::capi::BuildingFunctionValueIterator*>(ptr));
}


#endif // ecitygml_BuildingFunctionValueIterator_HPP
