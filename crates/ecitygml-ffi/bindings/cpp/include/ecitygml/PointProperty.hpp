#ifndef ecitygml_PointProperty_HPP
#define ecitygml_PointProperty_HPP

#include "PointProperty.d.hpp"

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
#include "Point.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Point* ecitygml_PointProperty_object(const ecitygml::capi::PointProperty* self);

    const ecitygml::capi::HRef* ecitygml_PointProperty_href(const ecitygml::capi::PointProperty* self);

    void ecitygml_PointProperty_destroy(PointProperty* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Point* ecitygml::PointProperty::object() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PointProperty_object(this->AsFFI());
    return ecitygml::Point::FromFFI(result);
}

inline const ecitygml::HRef* ecitygml::PointProperty::href() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PointProperty_href(this->AsFFI());
    return ecitygml::HRef::FromFFI(result);
}

inline const ecitygml::capi::PointProperty* ecitygml::PointProperty::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::PointProperty*>(this);
}

inline ecitygml::capi::PointProperty* ecitygml::PointProperty::AsFFI() {
    return reinterpret_cast<ecitygml::capi::PointProperty*>(this);
}

inline const ecitygml::PointProperty* ecitygml::PointProperty::FromFFI(const ecitygml::capi::PointProperty* ptr) {
    return reinterpret_cast<const ecitygml::PointProperty*>(ptr);
}

inline ecitygml::PointProperty* ecitygml::PointProperty::FromFFI(ecitygml::capi::PointProperty* ptr) {
    return reinterpret_cast<ecitygml::PointProperty*>(ptr);
}

inline void ecitygml::PointProperty::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_PointProperty_destroy(reinterpret_cast<ecitygml::capi::PointProperty*>(ptr));
}


#endif // ecitygml_PointProperty_HPP
