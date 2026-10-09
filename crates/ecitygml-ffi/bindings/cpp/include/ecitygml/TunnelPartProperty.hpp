#ifndef ecitygml_TunnelPartProperty_HPP
#define ecitygml_TunnelPartProperty_HPP

#include "TunnelPartProperty.d.hpp"

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
#include "TunnelPart.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::TunnelPart* ecitygml_TunnelPartProperty_object(const ecitygml::capi::TunnelPartProperty* self);

    const ecitygml::capi::HRef* ecitygml_TunnelPartProperty_href(const ecitygml::capi::TunnelPartProperty* self);

    void ecitygml_TunnelPartProperty_destroy(TunnelPartProperty* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::TunnelPart* ecitygml::TunnelPartProperty::object() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPartProperty_object(this->AsFFI());
    return ecitygml::TunnelPart::FromFFI(result);
}

inline const ecitygml::HRef* ecitygml::TunnelPartProperty::href() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPartProperty_href(this->AsFFI());
    return ecitygml::HRef::FromFFI(result);
}

inline const ecitygml::capi::TunnelPartProperty* ecitygml::TunnelPartProperty::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::TunnelPartProperty*>(this);
}

inline ecitygml::capi::TunnelPartProperty* ecitygml::TunnelPartProperty::AsFFI() {
    return reinterpret_cast<ecitygml::capi::TunnelPartProperty*>(this);
}

inline const ecitygml::TunnelPartProperty* ecitygml::TunnelPartProperty::FromFFI(const ecitygml::capi::TunnelPartProperty* ptr) {
    return reinterpret_cast<const ecitygml::TunnelPartProperty*>(ptr);
}

inline ecitygml::TunnelPartProperty* ecitygml::TunnelPartProperty::FromFFI(ecitygml::capi::TunnelPartProperty* ptr) {
    return reinterpret_cast<ecitygml::TunnelPartProperty*>(ptr);
}

inline void ecitygml::TunnelPartProperty::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_TunnelPartProperty_destroy(reinterpret_cast<ecitygml::capi::TunnelPartProperty*>(ptr));
}


#endif // ecitygml_TunnelPartProperty_HPP
