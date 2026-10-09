#ifndef ecitygml_PlantCoverFunctionValueIterator_HPP
#define ecitygml_PlantCoverFunctionValueIterator_HPP

#include "PlantCoverFunctionValueIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "PlantCoverFunctionValue.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::PlantCoverFunctionValue* ecitygml_PlantCoverFunctionValueIterator_next(ecitygml::capi::PlantCoverFunctionValueIterator* self);

    void ecitygml_PlantCoverFunctionValueIterator_destroy(PlantCoverFunctionValueIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::PlantCoverFunctionValue* ecitygml::PlantCoverFunctionValueIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCoverFunctionValueIterator_next(this->AsFFI());
    return ecitygml::PlantCoverFunctionValue::FromFFI(result);
}

inline const ecitygml::capi::PlantCoverFunctionValueIterator* ecitygml::PlantCoverFunctionValueIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::PlantCoverFunctionValueIterator*>(this);
}

inline ecitygml::capi::PlantCoverFunctionValueIterator* ecitygml::PlantCoverFunctionValueIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::PlantCoverFunctionValueIterator*>(this);
}

inline const ecitygml::PlantCoverFunctionValueIterator* ecitygml::PlantCoverFunctionValueIterator::FromFFI(const ecitygml::capi::PlantCoverFunctionValueIterator* ptr) {
    return reinterpret_cast<const ecitygml::PlantCoverFunctionValueIterator*>(ptr);
}

inline ecitygml::PlantCoverFunctionValueIterator* ecitygml::PlantCoverFunctionValueIterator::FromFFI(ecitygml::capi::PlantCoverFunctionValueIterator* ptr) {
    return reinterpret_cast<ecitygml::PlantCoverFunctionValueIterator*>(ptr);
}

inline void ecitygml::PlantCoverFunctionValueIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_PlantCoverFunctionValueIterator_destroy(reinterpret_cast<ecitygml::capi::PlantCoverFunctionValueIterator*>(ptr));
}


#endif // ecitygml_PlantCoverFunctionValueIterator_HPP
