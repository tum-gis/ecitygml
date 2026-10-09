#ifndef ecitygml_TrafficSpaceProperty_HPP
#define ecitygml_TrafficSpaceProperty_HPP

#include "TrafficSpaceProperty.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "HRef.hpp"
#include "TrafficSpace.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::TrafficSpace* ecitygml_TrafficSpaceProperty_object(const ecitygml::capi::TrafficSpaceProperty* self);

    const ecitygml::capi::HRef* ecitygml_TrafficSpaceProperty_href(const ecitygml::capi::TrafficSpaceProperty* self);

    void ecitygml_TrafficSpaceProperty_destroy(TrafficSpaceProperty* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::TrafficSpace* ecitygml::TrafficSpaceProperty::object() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpaceProperty_object(this->AsFFI());
    return ecitygml::TrafficSpace::FromFFI(result);
}

inline const ecitygml::HRef* ecitygml::TrafficSpaceProperty::href() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpaceProperty_href(this->AsFFI());
    return ecitygml::HRef::FromFFI(result);
}

inline const ecitygml::capi::TrafficSpaceProperty* ecitygml::TrafficSpaceProperty::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::TrafficSpaceProperty*>(this);
}

inline ecitygml::capi::TrafficSpaceProperty* ecitygml::TrafficSpaceProperty::AsFFI() {
    return reinterpret_cast<ecitygml::capi::TrafficSpaceProperty*>(this);
}

inline const ecitygml::TrafficSpaceProperty* ecitygml::TrafficSpaceProperty::FromFFI(const ecitygml::capi::TrafficSpaceProperty* ptr) {
    return reinterpret_cast<const ecitygml::TrafficSpaceProperty*>(ptr);
}

inline ecitygml::TrafficSpaceProperty* ecitygml::TrafficSpaceProperty::FromFFI(ecitygml::capi::TrafficSpaceProperty* ptr) {
    return reinterpret_cast<ecitygml::TrafficSpaceProperty*>(ptr);
}

inline void ecitygml::TrafficSpaceProperty::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_TrafficSpaceProperty_destroy(reinterpret_cast<ecitygml::capi::TrafficSpaceProperty*>(ptr));
}


#endif // ecitygml_TrafficSpaceProperty_HPP
