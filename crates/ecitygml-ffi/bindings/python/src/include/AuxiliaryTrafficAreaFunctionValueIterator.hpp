#ifndef ECITYGML_AuxiliaryTrafficAreaFunctionValueIterator_HPP
#define ECITYGML_AuxiliaryTrafficAreaFunctionValueIterator_HPP

#include "AuxiliaryTrafficAreaFunctionValueIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "AuxiliaryTrafficAreaFunctionValue.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::AuxiliaryTrafficAreaFunctionValue* ecitygml_AuxiliaryTrafficAreaFunctionValueIterator_next(ecitygml::capi::AuxiliaryTrafficAreaFunctionValueIterator* self);

    void ecitygml_AuxiliaryTrafficAreaFunctionValueIterator_destroy(AuxiliaryTrafficAreaFunctionValueIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::AuxiliaryTrafficAreaFunctionValue* ecitygml::AuxiliaryTrafficAreaFunctionValueIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficAreaFunctionValueIterator_next(this->AsFFI());
    return ecitygml::AuxiliaryTrafficAreaFunctionValue::FromFFI(result);
}

inline const ecitygml::capi::AuxiliaryTrafficAreaFunctionValueIterator* ecitygml::AuxiliaryTrafficAreaFunctionValueIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AuxiliaryTrafficAreaFunctionValueIterator*>(this);
}

inline ecitygml::capi::AuxiliaryTrafficAreaFunctionValueIterator* ecitygml::AuxiliaryTrafficAreaFunctionValueIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AuxiliaryTrafficAreaFunctionValueIterator*>(this);
}

inline const ecitygml::AuxiliaryTrafficAreaFunctionValueIterator* ecitygml::AuxiliaryTrafficAreaFunctionValueIterator::FromFFI(const ecitygml::capi::AuxiliaryTrafficAreaFunctionValueIterator* ptr) {
    return reinterpret_cast<const ecitygml::AuxiliaryTrafficAreaFunctionValueIterator*>(ptr);
}

inline ecitygml::AuxiliaryTrafficAreaFunctionValueIterator* ecitygml::AuxiliaryTrafficAreaFunctionValueIterator::FromFFI(ecitygml::capi::AuxiliaryTrafficAreaFunctionValueIterator* ptr) {
    return reinterpret_cast<ecitygml::AuxiliaryTrafficAreaFunctionValueIterator*>(ptr);
}

inline void ecitygml::AuxiliaryTrafficAreaFunctionValueIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AuxiliaryTrafficAreaFunctionValueIterator_destroy(reinterpret_cast<ecitygml::capi::AuxiliaryTrafficAreaFunctionValueIterator*>(ptr));
}


#endif // ECITYGML_AuxiliaryTrafficAreaFunctionValueIterator_HPP
