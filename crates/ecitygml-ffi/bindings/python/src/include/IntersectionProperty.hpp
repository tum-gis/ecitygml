#ifndef ECITYGML_IntersectionProperty_HPP
#define ECITYGML_IntersectionProperty_HPP

#include "IntersectionProperty.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "HRef.hpp"
#include "Intersection.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Intersection* ecitygml_IntersectionProperty_object(const ecitygml::capi::IntersectionProperty* self);

    const ecitygml::capi::HRef* ecitygml_IntersectionProperty_href(const ecitygml::capi::IntersectionProperty* self);

    void ecitygml_IntersectionProperty_destroy(IntersectionProperty* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Intersection* ecitygml::IntersectionProperty::object() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_IntersectionProperty_object(this->AsFFI());
    return ecitygml::Intersection::FromFFI(result);
}

inline const ecitygml::HRef* ecitygml::IntersectionProperty::href() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_IntersectionProperty_href(this->AsFFI());
    return ecitygml::HRef::FromFFI(result);
}

inline const ecitygml::capi::IntersectionProperty* ecitygml::IntersectionProperty::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::IntersectionProperty*>(this);
}

inline ecitygml::capi::IntersectionProperty* ecitygml::IntersectionProperty::AsFFI() {
    return reinterpret_cast<ecitygml::capi::IntersectionProperty*>(this);
}

inline const ecitygml::IntersectionProperty* ecitygml::IntersectionProperty::FromFFI(const ecitygml::capi::IntersectionProperty* ptr) {
    return reinterpret_cast<const ecitygml::IntersectionProperty*>(ptr);
}

inline ecitygml::IntersectionProperty* ecitygml::IntersectionProperty::FromFFI(ecitygml::capi::IntersectionProperty* ptr) {
    return reinterpret_cast<ecitygml::IntersectionProperty*>(ptr);
}

inline void ecitygml::IntersectionProperty::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_IntersectionProperty_destroy(reinterpret_cast<ecitygml::capi::IntersectionProperty*>(ptr));
}


#endif // ECITYGML_IntersectionProperty_HPP
