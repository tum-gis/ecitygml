#ifndef ECITYGML_AbstractFillingSurfaceProperty_HPP
#define ECITYGML_AbstractFillingSurfaceProperty_HPP

#include "AbstractFillingSurfaceProperty.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "AbstractFillingSurfaceKind.hpp"
#include "HRef.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::AbstractFillingSurfaceKind* ecitygml_AbstractFillingSurfaceProperty_object(const ecitygml::capi::AbstractFillingSurfaceProperty* self);

    const ecitygml::capi::HRef* ecitygml_AbstractFillingSurfaceProperty_href(const ecitygml::capi::AbstractFillingSurfaceProperty* self);

    void ecitygml_AbstractFillingSurfaceProperty_destroy(AbstractFillingSurfaceProperty* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::AbstractFillingSurfaceKind* ecitygml::AbstractFillingSurfaceProperty::object() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractFillingSurfaceProperty_object(this->AsFFI());
    return ecitygml::AbstractFillingSurfaceKind::FromFFI(result);
}

inline const ecitygml::HRef* ecitygml::AbstractFillingSurfaceProperty::href() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractFillingSurfaceProperty_href(this->AsFFI());
    return ecitygml::HRef::FromFFI(result);
}

inline const ecitygml::capi::AbstractFillingSurfaceProperty* ecitygml::AbstractFillingSurfaceProperty::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AbstractFillingSurfaceProperty*>(this);
}

inline ecitygml::capi::AbstractFillingSurfaceProperty* ecitygml::AbstractFillingSurfaceProperty::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AbstractFillingSurfaceProperty*>(this);
}

inline const ecitygml::AbstractFillingSurfaceProperty* ecitygml::AbstractFillingSurfaceProperty::FromFFI(const ecitygml::capi::AbstractFillingSurfaceProperty* ptr) {
    return reinterpret_cast<const ecitygml::AbstractFillingSurfaceProperty*>(ptr);
}

inline ecitygml::AbstractFillingSurfaceProperty* ecitygml::AbstractFillingSurfaceProperty::FromFFI(ecitygml::capi::AbstractFillingSurfaceProperty* ptr) {
    return reinterpret_cast<ecitygml::AbstractFillingSurfaceProperty*>(ptr);
}

inline void ecitygml::AbstractFillingSurfaceProperty::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AbstractFillingSurfaceProperty_destroy(reinterpret_cast<ecitygml::capi::AbstractFillingSurfaceProperty*>(ptr));
}


#endif // ECITYGML_AbstractFillingSurfaceProperty_HPP
