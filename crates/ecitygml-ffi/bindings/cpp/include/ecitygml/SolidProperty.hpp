#ifndef ecitygml_SolidProperty_HPP
#define ecitygml_SolidProperty_HPP

#include "SolidProperty.d.hpp"

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
#include "Solid.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Solid* ecitygml_SolidProperty_object(const ecitygml::capi::SolidProperty* self);

    const ecitygml::capi::HRef* ecitygml_SolidProperty_href(const ecitygml::capi::SolidProperty* self);

    void ecitygml_SolidProperty_destroy(SolidProperty* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Solid* ecitygml::SolidProperty::object() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolidProperty_object(this->AsFFI());
    return ecitygml::Solid::FromFFI(result);
}

inline const ecitygml::HRef* ecitygml::SolidProperty::href() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolidProperty_href(this->AsFFI());
    return ecitygml::HRef::FromFFI(result);
}

inline const ecitygml::capi::SolidProperty* ecitygml::SolidProperty::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::SolidProperty*>(this);
}

inline ecitygml::capi::SolidProperty* ecitygml::SolidProperty::AsFFI() {
    return reinterpret_cast<ecitygml::capi::SolidProperty*>(this);
}

inline const ecitygml::SolidProperty* ecitygml::SolidProperty::FromFFI(const ecitygml::capi::SolidProperty* ptr) {
    return reinterpret_cast<const ecitygml::SolidProperty*>(ptr);
}

inline ecitygml::SolidProperty* ecitygml::SolidProperty::FromFFI(ecitygml::capi::SolidProperty* ptr) {
    return reinterpret_cast<ecitygml::SolidProperty*>(ptr);
}

inline void ecitygml::SolidProperty::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_SolidProperty_destroy(reinterpret_cast<ecitygml::capi::SolidProperty*>(ptr));
}


#endif // ecitygml_SolidProperty_HPP
