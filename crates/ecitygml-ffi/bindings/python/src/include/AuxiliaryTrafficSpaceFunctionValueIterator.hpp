#ifndef ECITYGML_AuxiliaryTrafficSpaceFunctionValueIterator_HPP
#define ECITYGML_AuxiliaryTrafficSpaceFunctionValueIterator_HPP

#include "AuxiliaryTrafficSpaceFunctionValueIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "AuxiliaryTrafficSpaceFunctionValue.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::AuxiliaryTrafficSpaceFunctionValue* ecitygml_AuxiliaryTrafficSpaceFunctionValueIterator_next(ecitygml::capi::AuxiliaryTrafficSpaceFunctionValueIterator* self);

    void ecitygml_AuxiliaryTrafficSpaceFunctionValueIterator_destroy(AuxiliaryTrafficSpaceFunctionValueIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::AuxiliaryTrafficSpaceFunctionValue* ecitygml::AuxiliaryTrafficSpaceFunctionValueIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpaceFunctionValueIterator_next(this->AsFFI());
    return ecitygml::AuxiliaryTrafficSpaceFunctionValue::FromFFI(result);
}

inline const ecitygml::capi::AuxiliaryTrafficSpaceFunctionValueIterator* ecitygml::AuxiliaryTrafficSpaceFunctionValueIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AuxiliaryTrafficSpaceFunctionValueIterator*>(this);
}

inline ecitygml::capi::AuxiliaryTrafficSpaceFunctionValueIterator* ecitygml::AuxiliaryTrafficSpaceFunctionValueIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AuxiliaryTrafficSpaceFunctionValueIterator*>(this);
}

inline const ecitygml::AuxiliaryTrafficSpaceFunctionValueIterator* ecitygml::AuxiliaryTrafficSpaceFunctionValueIterator::FromFFI(const ecitygml::capi::AuxiliaryTrafficSpaceFunctionValueIterator* ptr) {
    return reinterpret_cast<const ecitygml::AuxiliaryTrafficSpaceFunctionValueIterator*>(ptr);
}

inline ecitygml::AuxiliaryTrafficSpaceFunctionValueIterator* ecitygml::AuxiliaryTrafficSpaceFunctionValueIterator::FromFFI(ecitygml::capi::AuxiliaryTrafficSpaceFunctionValueIterator* ptr) {
    return reinterpret_cast<ecitygml::AuxiliaryTrafficSpaceFunctionValueIterator*>(ptr);
}

inline void ecitygml::AuxiliaryTrafficSpaceFunctionValueIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AuxiliaryTrafficSpaceFunctionValueIterator_destroy(reinterpret_cast<ecitygml::capi::AuxiliaryTrafficSpaceFunctionValueIterator*>(ptr));
}


#endif // ECITYGML_AuxiliaryTrafficSpaceFunctionValueIterator_HPP
