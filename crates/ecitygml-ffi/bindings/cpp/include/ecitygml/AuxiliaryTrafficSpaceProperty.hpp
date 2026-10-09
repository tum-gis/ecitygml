#ifndef ecitygml_AuxiliaryTrafficSpaceProperty_HPP
#define ecitygml_AuxiliaryTrafficSpaceProperty_HPP

#include "AuxiliaryTrafficSpaceProperty.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "AuxiliaryTrafficSpace.hpp"
#include "HRef.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::AuxiliaryTrafficSpace* ecitygml_AuxiliaryTrafficSpaceProperty_object(const ecitygml::capi::AuxiliaryTrafficSpaceProperty* self);

    const ecitygml::capi::HRef* ecitygml_AuxiliaryTrafficSpaceProperty_href(const ecitygml::capi::AuxiliaryTrafficSpaceProperty* self);

    void ecitygml_AuxiliaryTrafficSpaceProperty_destroy(AuxiliaryTrafficSpaceProperty* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::AuxiliaryTrafficSpace* ecitygml::AuxiliaryTrafficSpaceProperty::object() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpaceProperty_object(this->AsFFI());
    return ecitygml::AuxiliaryTrafficSpace::FromFFI(result);
}

inline const ecitygml::HRef* ecitygml::AuxiliaryTrafficSpaceProperty::href() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpaceProperty_href(this->AsFFI());
    return ecitygml::HRef::FromFFI(result);
}

inline const ecitygml::capi::AuxiliaryTrafficSpaceProperty* ecitygml::AuxiliaryTrafficSpaceProperty::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AuxiliaryTrafficSpaceProperty*>(this);
}

inline ecitygml::capi::AuxiliaryTrafficSpaceProperty* ecitygml::AuxiliaryTrafficSpaceProperty::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AuxiliaryTrafficSpaceProperty*>(this);
}

inline const ecitygml::AuxiliaryTrafficSpaceProperty* ecitygml::AuxiliaryTrafficSpaceProperty::FromFFI(const ecitygml::capi::AuxiliaryTrafficSpaceProperty* ptr) {
    return reinterpret_cast<const ecitygml::AuxiliaryTrafficSpaceProperty*>(ptr);
}

inline ecitygml::AuxiliaryTrafficSpaceProperty* ecitygml::AuxiliaryTrafficSpaceProperty::FromFFI(ecitygml::capi::AuxiliaryTrafficSpaceProperty* ptr) {
    return reinterpret_cast<ecitygml::AuxiliaryTrafficSpaceProperty*>(ptr);
}

inline void ecitygml::AuxiliaryTrafficSpaceProperty::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AuxiliaryTrafficSpaceProperty_destroy(reinterpret_cast<ecitygml::capi::AuxiliaryTrafficSpaceProperty*>(ptr));
}


#endif // ecitygml_AuxiliaryTrafficSpaceProperty_HPP
