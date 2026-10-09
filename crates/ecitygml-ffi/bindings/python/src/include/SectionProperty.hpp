#ifndef ECITYGML_SectionProperty_HPP
#define ECITYGML_SectionProperty_HPP

#include "SectionProperty.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "HRef.hpp"
#include "Section.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Section* ecitygml_SectionProperty_object(const ecitygml::capi::SectionProperty* self);

    const ecitygml::capi::HRef* ecitygml_SectionProperty_href(const ecitygml::capi::SectionProperty* self);

    void ecitygml_SectionProperty_destroy(SectionProperty* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Section* ecitygml::SectionProperty::object() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SectionProperty_object(this->AsFFI());
    return ecitygml::Section::FromFFI(result);
}

inline const ecitygml::HRef* ecitygml::SectionProperty::href() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SectionProperty_href(this->AsFFI());
    return ecitygml::HRef::FromFFI(result);
}

inline const ecitygml::capi::SectionProperty* ecitygml::SectionProperty::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::SectionProperty*>(this);
}

inline ecitygml::capi::SectionProperty* ecitygml::SectionProperty::AsFFI() {
    return reinterpret_cast<ecitygml::capi::SectionProperty*>(this);
}

inline const ecitygml::SectionProperty* ecitygml::SectionProperty::FromFFI(const ecitygml::capi::SectionProperty* ptr) {
    return reinterpret_cast<const ecitygml::SectionProperty*>(ptr);
}

inline ecitygml::SectionProperty* ecitygml::SectionProperty::FromFFI(ecitygml::capi::SectionProperty* ptr) {
    return reinterpret_cast<ecitygml::SectionProperty*>(ptr);
}

inline void ecitygml::SectionProperty::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_SectionProperty_destroy(reinterpret_cast<ecitygml::capi::SectionProperty*>(ptr));
}


#endif // ECITYGML_SectionProperty_HPP
