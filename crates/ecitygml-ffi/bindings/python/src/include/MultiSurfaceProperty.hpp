#ifndef ECITYGML_MultiSurfaceProperty_HPP
#define ECITYGML_MultiSurfaceProperty_HPP

#include "MultiSurfaceProperty.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "HRef.hpp"
#include "MultiSurface.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::MultiSurface* ecitygml_MultiSurfaceProperty_object(const ecitygml::capi::MultiSurfaceProperty* self);

    const ecitygml::capi::HRef* ecitygml_MultiSurfaceProperty_href(const ecitygml::capi::MultiSurfaceProperty* self);

    void ecitygml_MultiSurfaceProperty_destroy(MultiSurfaceProperty* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::MultiSurface* ecitygml::MultiSurfaceProperty::object() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_MultiSurfaceProperty_object(this->AsFFI());
    return ecitygml::MultiSurface::FromFFI(result);
}

inline const ecitygml::HRef* ecitygml::MultiSurfaceProperty::href() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_MultiSurfaceProperty_href(this->AsFFI());
    return ecitygml::HRef::FromFFI(result);
}

inline const ecitygml::capi::MultiSurfaceProperty* ecitygml::MultiSurfaceProperty::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::MultiSurfaceProperty*>(this);
}

inline ecitygml::capi::MultiSurfaceProperty* ecitygml::MultiSurfaceProperty::AsFFI() {
    return reinterpret_cast<ecitygml::capi::MultiSurfaceProperty*>(this);
}

inline const ecitygml::MultiSurfaceProperty* ecitygml::MultiSurfaceProperty::FromFFI(const ecitygml::capi::MultiSurfaceProperty* ptr) {
    return reinterpret_cast<const ecitygml::MultiSurfaceProperty*>(ptr);
}

inline ecitygml::MultiSurfaceProperty* ecitygml::MultiSurfaceProperty::FromFFI(ecitygml::capi::MultiSurfaceProperty* ptr) {
    return reinterpret_cast<ecitygml::MultiSurfaceProperty*>(ptr);
}

inline void ecitygml::MultiSurfaceProperty::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_MultiSurfaceProperty_destroy(reinterpret_cast<ecitygml::capi::MultiSurfaceProperty*>(ptr));
}


#endif // ECITYGML_MultiSurfaceProperty_HPP
