#ifndef ecitygml_HoleProperty_HPP
#define ecitygml_HoleProperty_HPP

#include "HoleProperty.d.hpp"

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
#include "Hole.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Hole* ecitygml_HoleProperty_object(const ecitygml::capi::HoleProperty* self);

    const ecitygml::capi::HRef* ecitygml_HoleProperty_href(const ecitygml::capi::HoleProperty* self);

    void ecitygml_HoleProperty_destroy(HoleProperty* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Hole* ecitygml::HoleProperty::object() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_HoleProperty_object(this->AsFFI());
    return ecitygml::Hole::FromFFI(result);
}

inline const ecitygml::HRef* ecitygml::HoleProperty::href() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_HoleProperty_href(this->AsFFI());
    return ecitygml::HRef::FromFFI(result);
}

inline const ecitygml::capi::HoleProperty* ecitygml::HoleProperty::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::HoleProperty*>(this);
}

inline ecitygml::capi::HoleProperty* ecitygml::HoleProperty::AsFFI() {
    return reinterpret_cast<ecitygml::capi::HoleProperty*>(this);
}

inline const ecitygml::HoleProperty* ecitygml::HoleProperty::FromFFI(const ecitygml::capi::HoleProperty* ptr) {
    return reinterpret_cast<const ecitygml::HoleProperty*>(ptr);
}

inline ecitygml::HoleProperty* ecitygml::HoleProperty::FromFFI(ecitygml::capi::HoleProperty* ptr) {
    return reinterpret_cast<ecitygml::HoleProperty*>(ptr);
}

inline void ecitygml::HoleProperty::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_HoleProperty_destroy(reinterpret_cast<ecitygml::capi::HoleProperty*>(ptr));
}


#endif // ecitygml_HoleProperty_HPP
