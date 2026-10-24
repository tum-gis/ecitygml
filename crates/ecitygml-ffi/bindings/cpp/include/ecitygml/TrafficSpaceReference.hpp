#ifndef ecitygml_TrafficSpaceReference_HPP
#define ecitygml_TrafficSpaceReference_HPP

#include "TrafficSpaceReference.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    void ecitygml_TrafficSpaceReference_destroy(TrafficSpaceReference* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::capi::TrafficSpaceReference* ecitygml::TrafficSpaceReference::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::TrafficSpaceReference*>(this);
}

inline ecitygml::capi::TrafficSpaceReference* ecitygml::TrafficSpaceReference::AsFFI() {
    return reinterpret_cast<ecitygml::capi::TrafficSpaceReference*>(this);
}

inline const ecitygml::TrafficSpaceReference* ecitygml::TrafficSpaceReference::FromFFI(const ecitygml::capi::TrafficSpaceReference* ptr) {
    return reinterpret_cast<const ecitygml::TrafficSpaceReference*>(ptr);
}

inline ecitygml::TrafficSpaceReference* ecitygml::TrafficSpaceReference::FromFFI(ecitygml::capi::TrafficSpaceReference* ptr) {
    return reinterpret_cast<ecitygml::TrafficSpaceReference*>(ptr);
}

inline void ecitygml::TrafficSpaceReference::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_TrafficSpaceReference_destroy(reinterpret_cast<ecitygml::capi::TrafficSpaceReference*>(ptr));
}


#endif // ecitygml_TrafficSpaceReference_HPP
