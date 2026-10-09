#ifndef ECITYGML_OccupancyIterator_HPP
#define ECITYGML_OccupancyIterator_HPP

#include "OccupancyIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "Occupancy.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Occupancy* ecitygml_OccupancyIterator_next(ecitygml::capi::OccupancyIterator* self);

    void ecitygml_OccupancyIterator_destroy(OccupancyIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Occupancy* ecitygml::OccupancyIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_OccupancyIterator_next(this->AsFFI());
    return ecitygml::Occupancy::FromFFI(result);
}

inline const ecitygml::capi::OccupancyIterator* ecitygml::OccupancyIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::OccupancyIterator*>(this);
}

inline ecitygml::capi::OccupancyIterator* ecitygml::OccupancyIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::OccupancyIterator*>(this);
}

inline const ecitygml::OccupancyIterator* ecitygml::OccupancyIterator::FromFFI(const ecitygml::capi::OccupancyIterator* ptr) {
    return reinterpret_cast<const ecitygml::OccupancyIterator*>(ptr);
}

inline ecitygml::OccupancyIterator* ecitygml::OccupancyIterator::FromFFI(ecitygml::capi::OccupancyIterator* ptr) {
    return reinterpret_cast<ecitygml::OccupancyIterator*>(ptr);
}

inline void ecitygml::OccupancyIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_OccupancyIterator_destroy(reinterpret_cast<ecitygml::capi::OccupancyIterator*>(ptr));
}


#endif // ECITYGML_OccupancyIterator_HPP
