#ifndef ECITYGML_AuxiliaryTrafficAreaUsageValueIterator_HPP
#define ECITYGML_AuxiliaryTrafficAreaUsageValueIterator_HPP

#include "AuxiliaryTrafficAreaUsageValueIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "AuxiliaryTrafficAreaUsageValue.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::AuxiliaryTrafficAreaUsageValue* ecitygml_AuxiliaryTrafficAreaUsageValueIterator_next(ecitygml::capi::AuxiliaryTrafficAreaUsageValueIterator* self);

    void ecitygml_AuxiliaryTrafficAreaUsageValueIterator_destroy(AuxiliaryTrafficAreaUsageValueIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::AuxiliaryTrafficAreaUsageValue* ecitygml::AuxiliaryTrafficAreaUsageValueIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficAreaUsageValueIterator_next(this->AsFFI());
    return ecitygml::AuxiliaryTrafficAreaUsageValue::FromFFI(result);
}

inline const ecitygml::capi::AuxiliaryTrafficAreaUsageValueIterator* ecitygml::AuxiliaryTrafficAreaUsageValueIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AuxiliaryTrafficAreaUsageValueIterator*>(this);
}

inline ecitygml::capi::AuxiliaryTrafficAreaUsageValueIterator* ecitygml::AuxiliaryTrafficAreaUsageValueIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AuxiliaryTrafficAreaUsageValueIterator*>(this);
}

inline const ecitygml::AuxiliaryTrafficAreaUsageValueIterator* ecitygml::AuxiliaryTrafficAreaUsageValueIterator::FromFFI(const ecitygml::capi::AuxiliaryTrafficAreaUsageValueIterator* ptr) {
    return reinterpret_cast<const ecitygml::AuxiliaryTrafficAreaUsageValueIterator*>(ptr);
}

inline ecitygml::AuxiliaryTrafficAreaUsageValueIterator* ecitygml::AuxiliaryTrafficAreaUsageValueIterator::FromFFI(ecitygml::capi::AuxiliaryTrafficAreaUsageValueIterator* ptr) {
    return reinterpret_cast<ecitygml::AuxiliaryTrafficAreaUsageValueIterator*>(ptr);
}

inline void ecitygml::AuxiliaryTrafficAreaUsageValueIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AuxiliaryTrafficAreaUsageValueIterator_destroy(reinterpret_cast<ecitygml::capi::AuxiliaryTrafficAreaUsageValueIterator*>(ptr));
}


#endif // ECITYGML_AuxiliaryTrafficAreaUsageValueIterator_HPP
