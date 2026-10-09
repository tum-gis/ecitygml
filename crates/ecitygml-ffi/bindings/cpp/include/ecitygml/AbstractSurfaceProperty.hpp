#ifndef ecitygml_AbstractSurfaceProperty_HPP
#define ecitygml_AbstractSurfaceProperty_HPP

#include "AbstractSurfaceProperty.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "AbstractSurfaceKind.hpp"
#include "HRef.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::AbstractSurfaceKind* ecitygml_AbstractSurfaceProperty_object(const ecitygml::capi::AbstractSurfaceProperty* self);

    const ecitygml::capi::HRef* ecitygml_AbstractSurfaceProperty_href(const ecitygml::capi::AbstractSurfaceProperty* self);

    void ecitygml_AbstractSurfaceProperty_destroy(AbstractSurfaceProperty* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::AbstractSurfaceKind* ecitygml::AbstractSurfaceProperty::object() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractSurfaceProperty_object(this->AsFFI());
    return ecitygml::AbstractSurfaceKind::FromFFI(result);
}

inline const ecitygml::HRef* ecitygml::AbstractSurfaceProperty::href() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractSurfaceProperty_href(this->AsFFI());
    return ecitygml::HRef::FromFFI(result);
}

inline const ecitygml::capi::AbstractSurfaceProperty* ecitygml::AbstractSurfaceProperty::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AbstractSurfaceProperty*>(this);
}

inline ecitygml::capi::AbstractSurfaceProperty* ecitygml::AbstractSurfaceProperty::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AbstractSurfaceProperty*>(this);
}

inline const ecitygml::AbstractSurfaceProperty* ecitygml::AbstractSurfaceProperty::FromFFI(const ecitygml::capi::AbstractSurfaceProperty* ptr) {
    return reinterpret_cast<const ecitygml::AbstractSurfaceProperty*>(ptr);
}

inline ecitygml::AbstractSurfaceProperty* ecitygml::AbstractSurfaceProperty::FromFFI(ecitygml::capi::AbstractSurfaceProperty* ptr) {
    return reinterpret_cast<ecitygml::AbstractSurfaceProperty*>(ptr);
}

inline void ecitygml::AbstractSurfaceProperty::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AbstractSurfaceProperty_destroy(reinterpret_cast<ecitygml::capi::AbstractSurfaceProperty*>(ptr));
}


#endif // ecitygml_AbstractSurfaceProperty_HPP
