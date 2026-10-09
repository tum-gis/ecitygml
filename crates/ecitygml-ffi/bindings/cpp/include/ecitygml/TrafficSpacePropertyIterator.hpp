#ifndef ecitygml_TrafficSpacePropertyIterator_HPP
#define ecitygml_TrafficSpacePropertyIterator_HPP

#include "TrafficSpacePropertyIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "TrafficSpaceProperty.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::TrafficSpaceProperty* ecitygml_TrafficSpacePropertyIterator_next(ecitygml::capi::TrafficSpacePropertyIterator* self);

    void ecitygml_TrafficSpacePropertyIterator_destroy(TrafficSpacePropertyIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::TrafficSpaceProperty* ecitygml::TrafficSpacePropertyIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpacePropertyIterator_next(this->AsFFI());
    return ecitygml::TrafficSpaceProperty::FromFFI(result);
}

inline const ecitygml::capi::TrafficSpacePropertyIterator* ecitygml::TrafficSpacePropertyIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::TrafficSpacePropertyIterator*>(this);
}

inline ecitygml::capi::TrafficSpacePropertyIterator* ecitygml::TrafficSpacePropertyIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::TrafficSpacePropertyIterator*>(this);
}

inline const ecitygml::TrafficSpacePropertyIterator* ecitygml::TrafficSpacePropertyIterator::FromFFI(const ecitygml::capi::TrafficSpacePropertyIterator* ptr) {
    return reinterpret_cast<const ecitygml::TrafficSpacePropertyIterator*>(ptr);
}

inline ecitygml::TrafficSpacePropertyIterator* ecitygml::TrafficSpacePropertyIterator::FromFFI(ecitygml::capi::TrafficSpacePropertyIterator* ptr) {
    return reinterpret_cast<ecitygml::TrafficSpacePropertyIterator*>(ptr);
}

inline void ecitygml::TrafficSpacePropertyIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_TrafficSpacePropertyIterator_destroy(reinterpret_cast<ecitygml::capi::TrafficSpacePropertyIterator*>(ptr));
}


#endif // ecitygml_TrafficSpacePropertyIterator_HPP
