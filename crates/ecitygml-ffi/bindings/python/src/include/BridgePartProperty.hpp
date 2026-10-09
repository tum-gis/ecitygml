#ifndef ECITYGML_BridgePartProperty_HPP
#define ECITYGML_BridgePartProperty_HPP

#include "BridgePartProperty.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "BridgePart.hpp"
#include "HRef.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::BridgePart* ecitygml_BridgePartProperty_object(const ecitygml::capi::BridgePartProperty* self);

    const ecitygml::capi::HRef* ecitygml_BridgePartProperty_href(const ecitygml::capi::BridgePartProperty* self);

    void ecitygml_BridgePartProperty_destroy(BridgePartProperty* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::BridgePart* ecitygml::BridgePartProperty::object() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePartProperty_object(this->AsFFI());
    return ecitygml::BridgePart::FromFFI(result);
}

inline const ecitygml::HRef* ecitygml::BridgePartProperty::href() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePartProperty_href(this->AsFFI());
    return ecitygml::HRef::FromFFI(result);
}

inline const ecitygml::capi::BridgePartProperty* ecitygml::BridgePartProperty::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::BridgePartProperty*>(this);
}

inline ecitygml::capi::BridgePartProperty* ecitygml::BridgePartProperty::AsFFI() {
    return reinterpret_cast<ecitygml::capi::BridgePartProperty*>(this);
}

inline const ecitygml::BridgePartProperty* ecitygml::BridgePartProperty::FromFFI(const ecitygml::capi::BridgePartProperty* ptr) {
    return reinterpret_cast<const ecitygml::BridgePartProperty*>(ptr);
}

inline ecitygml::BridgePartProperty* ecitygml::BridgePartProperty::FromFFI(ecitygml::capi::BridgePartProperty* ptr) {
    return reinterpret_cast<ecitygml::BridgePartProperty*>(ptr);
}

inline void ecitygml::BridgePartProperty::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_BridgePartProperty_destroy(reinterpret_cast<ecitygml::capi::BridgePartProperty*>(ptr));
}


#endif // ECITYGML_BridgePartProperty_HPP
