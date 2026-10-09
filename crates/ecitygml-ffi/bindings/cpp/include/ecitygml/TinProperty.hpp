#ifndef ecitygml_TinProperty_HPP
#define ecitygml_TinProperty_HPP

#include "TinProperty.d.hpp"

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
#include "TriangulatedSurface.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::TriangulatedSurface* ecitygml_TinProperty_object(const ecitygml::capi::TinProperty* self);

    const ecitygml::capi::HRef* ecitygml_TinProperty_href(const ecitygml::capi::TinProperty* self);

    void ecitygml_TinProperty_destroy(TinProperty* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::TriangulatedSurface* ecitygml::TinProperty::object() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TinProperty_object(this->AsFFI());
    return ecitygml::TriangulatedSurface::FromFFI(result);
}

inline const ecitygml::HRef* ecitygml::TinProperty::href() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TinProperty_href(this->AsFFI());
    return ecitygml::HRef::FromFFI(result);
}

inline const ecitygml::capi::TinProperty* ecitygml::TinProperty::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::TinProperty*>(this);
}

inline ecitygml::capi::TinProperty* ecitygml::TinProperty::AsFFI() {
    return reinterpret_cast<ecitygml::capi::TinProperty*>(this);
}

inline const ecitygml::TinProperty* ecitygml::TinProperty::FromFFI(const ecitygml::capi::TinProperty* ptr) {
    return reinterpret_cast<const ecitygml::TinProperty*>(ptr);
}

inline ecitygml::TinProperty* ecitygml::TinProperty::FromFFI(ecitygml::capi::TinProperty* ptr) {
    return reinterpret_cast<ecitygml::TinProperty*>(ptr);
}

inline void ecitygml::TinProperty::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_TinProperty_destroy(reinterpret_cast<ecitygml::capi::TinProperty*>(ptr));
}


#endif // ecitygml_TinProperty_HPP
