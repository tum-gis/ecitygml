#ifndef ECITYGML_BuildingUsageValueIterator_HPP
#define ECITYGML_BuildingUsageValueIterator_HPP

#include "BuildingUsageValueIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "BuildingUsageValue.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::BuildingUsageValue* ecitygml_BuildingUsageValueIterator_next(ecitygml::capi::BuildingUsageValueIterator* self);

    void ecitygml_BuildingUsageValueIterator_destroy(BuildingUsageValueIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::BuildingUsageValue* ecitygml::BuildingUsageValueIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingUsageValueIterator_next(this->AsFFI());
    return ecitygml::BuildingUsageValue::FromFFI(result);
}

inline const ecitygml::capi::BuildingUsageValueIterator* ecitygml::BuildingUsageValueIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::BuildingUsageValueIterator*>(this);
}

inline ecitygml::capi::BuildingUsageValueIterator* ecitygml::BuildingUsageValueIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::BuildingUsageValueIterator*>(this);
}

inline const ecitygml::BuildingUsageValueIterator* ecitygml::BuildingUsageValueIterator::FromFFI(const ecitygml::capi::BuildingUsageValueIterator* ptr) {
    return reinterpret_cast<const ecitygml::BuildingUsageValueIterator*>(ptr);
}

inline ecitygml::BuildingUsageValueIterator* ecitygml::BuildingUsageValueIterator::FromFFI(ecitygml::capi::BuildingUsageValueIterator* ptr) {
    return reinterpret_cast<ecitygml::BuildingUsageValueIterator*>(ptr);
}

inline void ecitygml::BuildingUsageValueIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_BuildingUsageValueIterator_destroy(reinterpret_cast<ecitygml::capi::BuildingUsageValueIterator*>(ptr));
}


#endif // ECITYGML_BuildingUsageValueIterator_HPP
