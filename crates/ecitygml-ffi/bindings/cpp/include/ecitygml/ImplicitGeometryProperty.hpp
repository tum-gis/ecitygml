#ifndef ecitygml_ImplicitGeometryProperty_HPP
#define ecitygml_ImplicitGeometryProperty_HPP

#include "ImplicitGeometryProperty.d.hpp"

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
#include "ImplicitGeometry.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::ImplicitGeometry* ecitygml_ImplicitGeometryProperty_object(const ecitygml::capi::ImplicitGeometryProperty* self);

    const ecitygml::capi::HRef* ecitygml_ImplicitGeometryProperty_href(const ecitygml::capi::ImplicitGeometryProperty* self);

    void ecitygml_ImplicitGeometryProperty_destroy(ImplicitGeometryProperty* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::ImplicitGeometry* ecitygml::ImplicitGeometryProperty::object() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_ImplicitGeometryProperty_object(this->AsFFI());
    return ecitygml::ImplicitGeometry::FromFFI(result);
}

inline const ecitygml::HRef* ecitygml::ImplicitGeometryProperty::href() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_ImplicitGeometryProperty_href(this->AsFFI());
    return ecitygml::HRef::FromFFI(result);
}

inline const ecitygml::capi::ImplicitGeometryProperty* ecitygml::ImplicitGeometryProperty::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::ImplicitGeometryProperty*>(this);
}

inline ecitygml::capi::ImplicitGeometryProperty* ecitygml::ImplicitGeometryProperty::AsFFI() {
    return reinterpret_cast<ecitygml::capi::ImplicitGeometryProperty*>(this);
}

inline const ecitygml::ImplicitGeometryProperty* ecitygml::ImplicitGeometryProperty::FromFFI(const ecitygml::capi::ImplicitGeometryProperty* ptr) {
    return reinterpret_cast<const ecitygml::ImplicitGeometryProperty*>(ptr);
}

inline ecitygml::ImplicitGeometryProperty* ecitygml::ImplicitGeometryProperty::FromFFI(ecitygml::capi::ImplicitGeometryProperty* ptr) {
    return reinterpret_cast<ecitygml::ImplicitGeometryProperty*>(ptr);
}

inline void ecitygml::ImplicitGeometryProperty::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_ImplicitGeometryProperty_destroy(reinterpret_cast<ecitygml::capi::ImplicitGeometryProperty*>(ptr));
}


#endif // ecitygml_ImplicitGeometryProperty_HPP
