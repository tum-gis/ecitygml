#ifndef ECITYGML_AbstractCityObjectProperty_HPP
#define ECITYGML_AbstractCityObjectProperty_HPP

#include "AbstractCityObjectProperty.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "AbstractCityObjectKind.hpp"
#include "HRef.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::AbstractCityObjectKind* ecitygml_AbstractCityObjectProperty_object(const ecitygml::capi::AbstractCityObjectProperty* self);

    const ecitygml::capi::HRef* ecitygml_AbstractCityObjectProperty_href(const ecitygml::capi::AbstractCityObjectProperty* self);

    void ecitygml_AbstractCityObjectProperty_destroy(AbstractCityObjectProperty* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::AbstractCityObjectKind* ecitygml::AbstractCityObjectProperty::object() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractCityObjectProperty_object(this->AsFFI());
    return ecitygml::AbstractCityObjectKind::FromFFI(result);
}

inline const ecitygml::HRef* ecitygml::AbstractCityObjectProperty::href() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractCityObjectProperty_href(this->AsFFI());
    return ecitygml::HRef::FromFFI(result);
}

inline const ecitygml::capi::AbstractCityObjectProperty* ecitygml::AbstractCityObjectProperty::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AbstractCityObjectProperty*>(this);
}

inline ecitygml::capi::AbstractCityObjectProperty* ecitygml::AbstractCityObjectProperty::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AbstractCityObjectProperty*>(this);
}

inline const ecitygml::AbstractCityObjectProperty* ecitygml::AbstractCityObjectProperty::FromFFI(const ecitygml::capi::AbstractCityObjectProperty* ptr) {
    return reinterpret_cast<const ecitygml::AbstractCityObjectProperty*>(ptr);
}

inline ecitygml::AbstractCityObjectProperty* ecitygml::AbstractCityObjectProperty::FromFFI(ecitygml::capi::AbstractCityObjectProperty* ptr) {
    return reinterpret_cast<ecitygml::AbstractCityObjectProperty*>(ptr);
}

inline void ecitygml::AbstractCityObjectProperty::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AbstractCityObjectProperty_destroy(reinterpret_cast<ecitygml::capi::AbstractCityObjectProperty*>(ptr));
}


#endif // ECITYGML_AbstractCityObjectProperty_HPP
