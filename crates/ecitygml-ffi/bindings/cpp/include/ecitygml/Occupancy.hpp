#ifndef ecitygml_Occupancy_HPP
#define ecitygml_Occupancy_HPP

#include "Occupancy.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "IntervalValue.hpp"
#include "OccupantTypeValue.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    int64_t ecitygml_Occupancy_number_of_occupants(const ecitygml::capi::Occupancy* self);

    const ecitygml::capi::IntervalValue* ecitygml_Occupancy_interval(const ecitygml::capi::Occupancy* self);

    const ecitygml::capi::OccupantTypeValue* ecitygml_Occupancy_occupant_type(const ecitygml::capi::Occupancy* self);

    void ecitygml_Occupancy_destroy(Occupancy* self);

    } // extern "C"
} // namespace capi
} // namespace

inline int64_t ecitygml::Occupancy::number_of_occupants() const {
    auto result = ecitygml::capi::ecitygml_Occupancy_number_of_occupants(this->AsFFI());
    return result;
}

inline const ecitygml::IntervalValue* ecitygml::Occupancy::interval() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Occupancy_interval(this->AsFFI());
    return ecitygml::IntervalValue::FromFFI(result);
}

inline const ecitygml::OccupantTypeValue* ecitygml::Occupancy::occupant_type() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Occupancy_occupant_type(this->AsFFI());
    return ecitygml::OccupantTypeValue::FromFFI(result);
}

inline const ecitygml::capi::Occupancy* ecitygml::Occupancy::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::Occupancy*>(this);
}

inline ecitygml::capi::Occupancy* ecitygml::Occupancy::AsFFI() {
    return reinterpret_cast<ecitygml::capi::Occupancy*>(this);
}

inline const ecitygml::Occupancy* ecitygml::Occupancy::FromFFI(const ecitygml::capi::Occupancy* ptr) {
    return reinterpret_cast<const ecitygml::Occupancy*>(ptr);
}

inline ecitygml::Occupancy* ecitygml::Occupancy::FromFFI(ecitygml::capi::Occupancy* ptr) {
    return reinterpret_cast<ecitygml::Occupancy*>(ptr);
}

inline void ecitygml::Occupancy::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_Occupancy_destroy(reinterpret_cast<ecitygml::capi::Occupancy*>(ptr));
}


#endif // ecitygml_Occupancy_HPP
