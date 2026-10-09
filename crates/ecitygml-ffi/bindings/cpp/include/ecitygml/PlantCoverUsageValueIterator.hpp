#ifndef ecitygml_PlantCoverUsageValueIterator_HPP
#define ecitygml_PlantCoverUsageValueIterator_HPP

#include "PlantCoverUsageValueIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "PlantCoverUsageValue.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::PlantCoverUsageValue* ecitygml_PlantCoverUsageValueIterator_next(ecitygml::capi::PlantCoverUsageValueIterator* self);

    void ecitygml_PlantCoverUsageValueIterator_destroy(PlantCoverUsageValueIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::PlantCoverUsageValue* ecitygml::PlantCoverUsageValueIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCoverUsageValueIterator_next(this->AsFFI());
    return ecitygml::PlantCoverUsageValue::FromFFI(result);
}

inline const ecitygml::capi::PlantCoverUsageValueIterator* ecitygml::PlantCoverUsageValueIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::PlantCoverUsageValueIterator*>(this);
}

inline ecitygml::capi::PlantCoverUsageValueIterator* ecitygml::PlantCoverUsageValueIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::PlantCoverUsageValueIterator*>(this);
}

inline const ecitygml::PlantCoverUsageValueIterator* ecitygml::PlantCoverUsageValueIterator::FromFFI(const ecitygml::capi::PlantCoverUsageValueIterator* ptr) {
    return reinterpret_cast<const ecitygml::PlantCoverUsageValueIterator*>(ptr);
}

inline ecitygml::PlantCoverUsageValueIterator* ecitygml::PlantCoverUsageValueIterator::FromFFI(ecitygml::capi::PlantCoverUsageValueIterator* ptr) {
    return reinterpret_cast<ecitygml::PlantCoverUsageValueIterator*>(ptr);
}

inline void ecitygml::PlantCoverUsageValueIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_PlantCoverUsageValueIterator_destroy(reinterpret_cast<ecitygml::capi::PlantCoverUsageValueIterator*>(ptr));
}


#endif // ecitygml_PlantCoverUsageValueIterator_HPP
