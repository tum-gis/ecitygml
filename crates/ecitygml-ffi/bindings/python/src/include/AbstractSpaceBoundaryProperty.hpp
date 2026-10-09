#ifndef ECITYGML_AbstractSpaceBoundaryProperty_HPP
#define ECITYGML_AbstractSpaceBoundaryProperty_HPP

#include "AbstractSpaceBoundaryProperty.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "AbstractSpaceBoundaryKind.hpp"
#include "HRef.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::AbstractSpaceBoundaryKind* ecitygml_AbstractSpaceBoundaryProperty_object(const ecitygml::capi::AbstractSpaceBoundaryProperty* self);

    const ecitygml::capi::HRef* ecitygml_AbstractSpaceBoundaryProperty_href(const ecitygml::capi::AbstractSpaceBoundaryProperty* self);

    void ecitygml_AbstractSpaceBoundaryProperty_destroy(AbstractSpaceBoundaryProperty* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::AbstractSpaceBoundaryKind* ecitygml::AbstractSpaceBoundaryProperty::object() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractSpaceBoundaryProperty_object(this->AsFFI());
    return ecitygml::AbstractSpaceBoundaryKind::FromFFI(result);
}

inline const ecitygml::HRef* ecitygml::AbstractSpaceBoundaryProperty::href() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractSpaceBoundaryProperty_href(this->AsFFI());
    return ecitygml::HRef::FromFFI(result);
}

inline const ecitygml::capi::AbstractSpaceBoundaryProperty* ecitygml::AbstractSpaceBoundaryProperty::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AbstractSpaceBoundaryProperty*>(this);
}

inline ecitygml::capi::AbstractSpaceBoundaryProperty* ecitygml::AbstractSpaceBoundaryProperty::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AbstractSpaceBoundaryProperty*>(this);
}

inline const ecitygml::AbstractSpaceBoundaryProperty* ecitygml::AbstractSpaceBoundaryProperty::FromFFI(const ecitygml::capi::AbstractSpaceBoundaryProperty* ptr) {
    return reinterpret_cast<const ecitygml::AbstractSpaceBoundaryProperty*>(ptr);
}

inline ecitygml::AbstractSpaceBoundaryProperty* ecitygml::AbstractSpaceBoundaryProperty::FromFFI(ecitygml::capi::AbstractSpaceBoundaryProperty* ptr) {
    return reinterpret_cast<ecitygml::AbstractSpaceBoundaryProperty*>(ptr);
}

inline void ecitygml::AbstractSpaceBoundaryProperty::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AbstractSpaceBoundaryProperty_destroy(reinterpret_cast<ecitygml::capi::AbstractSpaceBoundaryProperty*>(ptr));
}


#endif // ECITYGML_AbstractSpaceBoundaryProperty_HPP
