#ifndef ecitygml_AbstractGeometryProperty_HPP
#define ecitygml_AbstractGeometryProperty_HPP

#include "AbstractGeometryProperty.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "AbstractGeometryKind.hpp"
#include "HRef.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::AbstractGeometryKind* ecitygml_AbstractGeometryProperty_object(const ecitygml::capi::AbstractGeometryProperty* self);

    const ecitygml::capi::HRef* ecitygml_AbstractGeometryProperty_href(const ecitygml::capi::AbstractGeometryProperty* self);

    void ecitygml_AbstractGeometryProperty_destroy(AbstractGeometryProperty* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::AbstractGeometryKind* ecitygml::AbstractGeometryProperty::object() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractGeometryProperty_object(this->AsFFI());
    return ecitygml::AbstractGeometryKind::FromFFI(result);
}

inline const ecitygml::HRef* ecitygml::AbstractGeometryProperty::href() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractGeometryProperty_href(this->AsFFI());
    return ecitygml::HRef::FromFFI(result);
}

inline const ecitygml::capi::AbstractGeometryProperty* ecitygml::AbstractGeometryProperty::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AbstractGeometryProperty*>(this);
}

inline ecitygml::capi::AbstractGeometryProperty* ecitygml::AbstractGeometryProperty::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AbstractGeometryProperty*>(this);
}

inline const ecitygml::AbstractGeometryProperty* ecitygml::AbstractGeometryProperty::FromFFI(const ecitygml::capi::AbstractGeometryProperty* ptr) {
    return reinterpret_cast<const ecitygml::AbstractGeometryProperty*>(ptr);
}

inline ecitygml::AbstractGeometryProperty* ecitygml::AbstractGeometryProperty::FromFFI(ecitygml::capi::AbstractGeometryProperty* ptr) {
    return reinterpret_cast<ecitygml::AbstractGeometryProperty*>(ptr);
}

inline void ecitygml::AbstractGeometryProperty::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AbstractGeometryProperty_destroy(reinterpret_cast<ecitygml::capi::AbstractGeometryProperty*>(ptr));
}


#endif // ecitygml_AbstractGeometryProperty_HPP
