#ifndef ecitygml_TrafficSpaceReferenceIterator_HPP
#define ecitygml_TrafficSpaceReferenceIterator_HPP

#include "TrafficSpaceReferenceIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "TrafficSpaceReference.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::TrafficSpaceReference* ecitygml_TrafficSpaceReferenceIterator_next(ecitygml::capi::TrafficSpaceReferenceIterator* self);

    void ecitygml_TrafficSpaceReferenceIterator_destroy(TrafficSpaceReferenceIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::TrafficSpaceReference* ecitygml::TrafficSpaceReferenceIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpaceReferenceIterator_next(this->AsFFI());
    return ecitygml::TrafficSpaceReference::FromFFI(result);
}

inline const ecitygml::capi::TrafficSpaceReferenceIterator* ecitygml::TrafficSpaceReferenceIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::TrafficSpaceReferenceIterator*>(this);
}

inline ecitygml::capi::TrafficSpaceReferenceIterator* ecitygml::TrafficSpaceReferenceIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::TrafficSpaceReferenceIterator*>(this);
}

inline const ecitygml::TrafficSpaceReferenceIterator* ecitygml::TrafficSpaceReferenceIterator::FromFFI(const ecitygml::capi::TrafficSpaceReferenceIterator* ptr) {
    return reinterpret_cast<const ecitygml::TrafficSpaceReferenceIterator*>(ptr);
}

inline ecitygml::TrafficSpaceReferenceIterator* ecitygml::TrafficSpaceReferenceIterator::FromFFI(ecitygml::capi::TrafficSpaceReferenceIterator* ptr) {
    return reinterpret_cast<ecitygml::TrafficSpaceReferenceIterator*>(ptr);
}

inline void ecitygml::TrafficSpaceReferenceIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_TrafficSpaceReferenceIterator_destroy(reinterpret_cast<ecitygml::capi::TrafficSpaceReferenceIterator*>(ptr));
}


#endif // ecitygml_TrafficSpaceReferenceIterator_HPP
