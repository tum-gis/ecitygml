#ifndef ECITYGML_MultiCurveProperty_HPP
#define ECITYGML_MultiCurveProperty_HPP

#include "MultiCurveProperty.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "HRef.hpp"
#include "MultiCurve.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::MultiCurve* ecitygml_MultiCurveProperty_object(const ecitygml::capi::MultiCurveProperty* self);

    const ecitygml::capi::HRef* ecitygml_MultiCurveProperty_href(const ecitygml::capi::MultiCurveProperty* self);

    void ecitygml_MultiCurveProperty_destroy(MultiCurveProperty* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::MultiCurve* ecitygml::MultiCurveProperty::object() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_MultiCurveProperty_object(this->AsFFI());
    return ecitygml::MultiCurve::FromFFI(result);
}

inline const ecitygml::HRef* ecitygml::MultiCurveProperty::href() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_MultiCurveProperty_href(this->AsFFI());
    return ecitygml::HRef::FromFFI(result);
}

inline const ecitygml::capi::MultiCurveProperty* ecitygml::MultiCurveProperty::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::MultiCurveProperty*>(this);
}

inline ecitygml::capi::MultiCurveProperty* ecitygml::MultiCurveProperty::AsFFI() {
    return reinterpret_cast<ecitygml::capi::MultiCurveProperty*>(this);
}

inline const ecitygml::MultiCurveProperty* ecitygml::MultiCurveProperty::FromFFI(const ecitygml::capi::MultiCurveProperty* ptr) {
    return reinterpret_cast<const ecitygml::MultiCurveProperty*>(ptr);
}

inline ecitygml::MultiCurveProperty* ecitygml::MultiCurveProperty::FromFFI(ecitygml::capi::MultiCurveProperty* ptr) {
    return reinterpret_cast<ecitygml::MultiCurveProperty*>(ptr);
}

inline void ecitygml::MultiCurveProperty::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_MultiCurveProperty_destroy(reinterpret_cast<ecitygml::capi::MultiCurveProperty*>(ptr));
}


#endif // ECITYGML_MultiCurveProperty_HPP
