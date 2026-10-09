#ifndef ECITYGML_AbstractReliefComponentProperty_HPP
#define ECITYGML_AbstractReliefComponentProperty_HPP

#include "AbstractReliefComponentProperty.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "AbstractReliefComponentKind.hpp"
#include "HRef.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::AbstractReliefComponentKind* ecitygml_AbstractReliefComponentProperty_object(const ecitygml::capi::AbstractReliefComponentProperty* self);

    const ecitygml::capi::HRef* ecitygml_AbstractReliefComponentProperty_href(const ecitygml::capi::AbstractReliefComponentProperty* self);

    void ecitygml_AbstractReliefComponentProperty_destroy(AbstractReliefComponentProperty* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::AbstractReliefComponentKind* ecitygml::AbstractReliefComponentProperty::object() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractReliefComponentProperty_object(this->AsFFI());
    return ecitygml::AbstractReliefComponentKind::FromFFI(result);
}

inline const ecitygml::HRef* ecitygml::AbstractReliefComponentProperty::href() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractReliefComponentProperty_href(this->AsFFI());
    return ecitygml::HRef::FromFFI(result);
}

inline const ecitygml::capi::AbstractReliefComponentProperty* ecitygml::AbstractReliefComponentProperty::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AbstractReliefComponentProperty*>(this);
}

inline ecitygml::capi::AbstractReliefComponentProperty* ecitygml::AbstractReliefComponentProperty::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AbstractReliefComponentProperty*>(this);
}

inline const ecitygml::AbstractReliefComponentProperty* ecitygml::AbstractReliefComponentProperty::FromFFI(const ecitygml::capi::AbstractReliefComponentProperty* ptr) {
    return reinterpret_cast<const ecitygml::AbstractReliefComponentProperty*>(ptr);
}

inline ecitygml::AbstractReliefComponentProperty* ecitygml::AbstractReliefComponentProperty::FromFFI(ecitygml::capi::AbstractReliefComponentProperty* ptr) {
    return reinterpret_cast<ecitygml::AbstractReliefComponentProperty*>(ptr);
}

inline void ecitygml::AbstractReliefComponentProperty::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AbstractReliefComponentProperty_destroy(reinterpret_cast<ecitygml::capi::AbstractReliefComponentProperty*>(ptr));
}


#endif // ECITYGML_AbstractReliefComponentProperty_HPP
