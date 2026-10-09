#ifndef ecitygml_AuxiliaryTrafficSpaceUsageValueIterator_HPP
#define ecitygml_AuxiliaryTrafficSpaceUsageValueIterator_HPP

#include "AuxiliaryTrafficSpaceUsageValueIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "AuxiliaryTrafficSpaceUsageValue.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::AuxiliaryTrafficSpaceUsageValue* ecitygml_AuxiliaryTrafficSpaceUsageValueIterator_next(ecitygml::capi::AuxiliaryTrafficSpaceUsageValueIterator* self);

    void ecitygml_AuxiliaryTrafficSpaceUsageValueIterator_destroy(AuxiliaryTrafficSpaceUsageValueIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::AuxiliaryTrafficSpaceUsageValue* ecitygml::AuxiliaryTrafficSpaceUsageValueIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpaceUsageValueIterator_next(this->AsFFI());
    return ecitygml::AuxiliaryTrafficSpaceUsageValue::FromFFI(result);
}

inline const ecitygml::capi::AuxiliaryTrafficSpaceUsageValueIterator* ecitygml::AuxiliaryTrafficSpaceUsageValueIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AuxiliaryTrafficSpaceUsageValueIterator*>(this);
}

inline ecitygml::capi::AuxiliaryTrafficSpaceUsageValueIterator* ecitygml::AuxiliaryTrafficSpaceUsageValueIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AuxiliaryTrafficSpaceUsageValueIterator*>(this);
}

inline const ecitygml::AuxiliaryTrafficSpaceUsageValueIterator* ecitygml::AuxiliaryTrafficSpaceUsageValueIterator::FromFFI(const ecitygml::capi::AuxiliaryTrafficSpaceUsageValueIterator* ptr) {
    return reinterpret_cast<const ecitygml::AuxiliaryTrafficSpaceUsageValueIterator*>(ptr);
}

inline ecitygml::AuxiliaryTrafficSpaceUsageValueIterator* ecitygml::AuxiliaryTrafficSpaceUsageValueIterator::FromFFI(ecitygml::capi::AuxiliaryTrafficSpaceUsageValueIterator* ptr) {
    return reinterpret_cast<ecitygml::AuxiliaryTrafficSpaceUsageValueIterator*>(ptr);
}

inline void ecitygml::AuxiliaryTrafficSpaceUsageValueIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AuxiliaryTrafficSpaceUsageValueIterator_destroy(reinterpret_cast<ecitygml::capi::AuxiliaryTrafficSpaceUsageValueIterator*>(ptr));
}


#endif // ecitygml_AuxiliaryTrafficSpaceUsageValueIterator_HPP
