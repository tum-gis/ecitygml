#ifndef ECITYGML_BuildingPartProperty_HPP
#define ECITYGML_BuildingPartProperty_HPP

#include "BuildingPartProperty.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "BuildingPart.hpp"
#include "HRef.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::BuildingPart* ecitygml_BuildingPartProperty_object(const ecitygml::capi::BuildingPartProperty* self);

    const ecitygml::capi::HRef* ecitygml_BuildingPartProperty_href(const ecitygml::capi::BuildingPartProperty* self);

    void ecitygml_BuildingPartProperty_destroy(BuildingPartProperty* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::BuildingPart* ecitygml::BuildingPartProperty::object() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPartProperty_object(this->AsFFI());
    return ecitygml::BuildingPart::FromFFI(result);
}

inline const ecitygml::HRef* ecitygml::BuildingPartProperty::href() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPartProperty_href(this->AsFFI());
    return ecitygml::HRef::FromFFI(result);
}

inline const ecitygml::capi::BuildingPartProperty* ecitygml::BuildingPartProperty::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::BuildingPartProperty*>(this);
}

inline ecitygml::capi::BuildingPartProperty* ecitygml::BuildingPartProperty::AsFFI() {
    return reinterpret_cast<ecitygml::capi::BuildingPartProperty*>(this);
}

inline const ecitygml::BuildingPartProperty* ecitygml::BuildingPartProperty::FromFFI(const ecitygml::capi::BuildingPartProperty* ptr) {
    return reinterpret_cast<const ecitygml::BuildingPartProperty*>(ptr);
}

inline ecitygml::BuildingPartProperty* ecitygml::BuildingPartProperty::FromFFI(ecitygml::capi::BuildingPartProperty* ptr) {
    return reinterpret_cast<ecitygml::BuildingPartProperty*>(ptr);
}

inline void ecitygml::BuildingPartProperty::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_BuildingPartProperty_destroy(reinterpret_cast<ecitygml::capi::BuildingPartProperty*>(ptr));
}


#endif // ECITYGML_BuildingPartProperty_HPP
