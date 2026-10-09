#ifndef ECITYGML_BuildingSubdivisionUsageValueIterator_HPP
#define ECITYGML_BuildingSubdivisionUsageValueIterator_HPP

#include "BuildingSubdivisionUsageValueIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "BuildingSubdivisionUsageValue.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::BuildingSubdivisionUsageValue* ecitygml_BuildingSubdivisionUsageValueIterator_next(ecitygml::capi::BuildingSubdivisionUsageValueIterator* self);

    void ecitygml_BuildingSubdivisionUsageValueIterator_destroy(BuildingSubdivisionUsageValueIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::BuildingSubdivisionUsageValue* ecitygml::BuildingSubdivisionUsageValueIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingSubdivisionUsageValueIterator_next(this->AsFFI());
    return ecitygml::BuildingSubdivisionUsageValue::FromFFI(result);
}

inline const ecitygml::capi::BuildingSubdivisionUsageValueIterator* ecitygml::BuildingSubdivisionUsageValueIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::BuildingSubdivisionUsageValueIterator*>(this);
}

inline ecitygml::capi::BuildingSubdivisionUsageValueIterator* ecitygml::BuildingSubdivisionUsageValueIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::BuildingSubdivisionUsageValueIterator*>(this);
}

inline const ecitygml::BuildingSubdivisionUsageValueIterator* ecitygml::BuildingSubdivisionUsageValueIterator::FromFFI(const ecitygml::capi::BuildingSubdivisionUsageValueIterator* ptr) {
    return reinterpret_cast<const ecitygml::BuildingSubdivisionUsageValueIterator*>(ptr);
}

inline ecitygml::BuildingSubdivisionUsageValueIterator* ecitygml::BuildingSubdivisionUsageValueIterator::FromFFI(ecitygml::capi::BuildingSubdivisionUsageValueIterator* ptr) {
    return reinterpret_cast<ecitygml::BuildingSubdivisionUsageValueIterator*>(ptr);
}

inline void ecitygml::BuildingSubdivisionUsageValueIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_BuildingSubdivisionUsageValueIterator_destroy(reinterpret_cast<ecitygml::capi::BuildingSubdivisionUsageValueIterator*>(ptr));
}


#endif // ECITYGML_BuildingSubdivisionUsageValueIterator_HPP
