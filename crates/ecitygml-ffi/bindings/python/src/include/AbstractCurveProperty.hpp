#ifndef ECITYGML_AbstractCurveProperty_HPP
#define ECITYGML_AbstractCurveProperty_HPP

#include "AbstractCurveProperty.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "AbstractCurveKind.hpp"
#include "HRef.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::AbstractCurveKind* ecitygml_AbstractCurveProperty_object(const ecitygml::capi::AbstractCurveProperty* self);

    const ecitygml::capi::HRef* ecitygml_AbstractCurveProperty_href(const ecitygml::capi::AbstractCurveProperty* self);

    void ecitygml_AbstractCurveProperty_destroy(AbstractCurveProperty* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::AbstractCurveKind* ecitygml::AbstractCurveProperty::object() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractCurveProperty_object(this->AsFFI());
    return ecitygml::AbstractCurveKind::FromFFI(result);
}

inline const ecitygml::HRef* ecitygml::AbstractCurveProperty::href() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractCurveProperty_href(this->AsFFI());
    return ecitygml::HRef::FromFFI(result);
}

inline const ecitygml::capi::AbstractCurveProperty* ecitygml::AbstractCurveProperty::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AbstractCurveProperty*>(this);
}

inline ecitygml::capi::AbstractCurveProperty* ecitygml::AbstractCurveProperty::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AbstractCurveProperty*>(this);
}

inline const ecitygml::AbstractCurveProperty* ecitygml::AbstractCurveProperty::FromFFI(const ecitygml::capi::AbstractCurveProperty* ptr) {
    return reinterpret_cast<const ecitygml::AbstractCurveProperty*>(ptr);
}

inline ecitygml::AbstractCurveProperty* ecitygml::AbstractCurveProperty::FromFFI(ecitygml::capi::AbstractCurveProperty* ptr) {
    return reinterpret_cast<ecitygml::AbstractCurveProperty*>(ptr);
}

inline void ecitygml::AbstractCurveProperty::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AbstractCurveProperty_destroy(reinterpret_cast<ecitygml::capi::AbstractCurveProperty*>(ptr));
}


#endif // ECITYGML_AbstractCurveProperty_HPP
