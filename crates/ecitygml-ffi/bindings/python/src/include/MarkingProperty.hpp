#ifndef ECITYGML_MarkingProperty_HPP
#define ECITYGML_MarkingProperty_HPP

#include "MarkingProperty.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "HRef.hpp"
#include "Marking.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Marking* ecitygml_MarkingProperty_object(const ecitygml::capi::MarkingProperty* self);

    const ecitygml::capi::HRef* ecitygml_MarkingProperty_href(const ecitygml::capi::MarkingProperty* self);

    void ecitygml_MarkingProperty_destroy(MarkingProperty* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Marking* ecitygml::MarkingProperty::object() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_MarkingProperty_object(this->AsFFI());
    return ecitygml::Marking::FromFFI(result);
}

inline const ecitygml::HRef* ecitygml::MarkingProperty::href() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_MarkingProperty_href(this->AsFFI());
    return ecitygml::HRef::FromFFI(result);
}

inline const ecitygml::capi::MarkingProperty* ecitygml::MarkingProperty::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::MarkingProperty*>(this);
}

inline ecitygml::capi::MarkingProperty* ecitygml::MarkingProperty::AsFFI() {
    return reinterpret_cast<ecitygml::capi::MarkingProperty*>(this);
}

inline const ecitygml::MarkingProperty* ecitygml::MarkingProperty::FromFFI(const ecitygml::capi::MarkingProperty* ptr) {
    return reinterpret_cast<const ecitygml::MarkingProperty*>(ptr);
}

inline ecitygml::MarkingProperty* ecitygml::MarkingProperty::FromFFI(ecitygml::capi::MarkingProperty* ptr) {
    return reinterpret_cast<ecitygml::MarkingProperty*>(ptr);
}

inline void ecitygml::MarkingProperty::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_MarkingProperty_destroy(reinterpret_cast<ecitygml::capi::MarkingProperty*>(ptr));
}


#endif // ECITYGML_MarkingProperty_HPP
