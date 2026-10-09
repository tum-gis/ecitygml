#ifndef ECITYGML_GenericAttributeKind_HPP
#define ECITYGML_GenericAttributeKind_HPP

#include "GenericAttributeKind.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "DoubleAttribute.hpp"
#include "IntAttribute.hpp"
#include "StringAttribute.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_GenericAttributeKind_name(const ecitygml::capi::GenericAttributeKind* self);

    const ecitygml::capi::StringAttribute* ecitygml_GenericAttributeKind_as_string(const ecitygml::capi::GenericAttributeKind* self);

    const ecitygml::capi::IntAttribute* ecitygml_GenericAttributeKind_as_int(const ecitygml::capi::GenericAttributeKind* self);

    const ecitygml::capi::DoubleAttribute* ecitygml_GenericAttributeKind_as_double(const ecitygml::capi::GenericAttributeKind* self);

    void ecitygml_GenericAttributeKind_destroy(GenericAttributeKind* self);

    } // extern "C"
} // namespace capi
} // namespace

inline std::string_view ecitygml::GenericAttributeKind::name() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_GenericAttributeKind_name(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::StringAttribute* ecitygml::GenericAttributeKind::as_string() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_GenericAttributeKind_as_string(this->AsFFI());
    return ecitygml::StringAttribute::FromFFI(result);
}

inline const ecitygml::IntAttribute* ecitygml::GenericAttributeKind::as_int() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_GenericAttributeKind_as_int(this->AsFFI());
    return ecitygml::IntAttribute::FromFFI(result);
}

inline const ecitygml::DoubleAttribute* ecitygml::GenericAttributeKind::as_double() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_GenericAttributeKind_as_double(this->AsFFI());
    return ecitygml::DoubleAttribute::FromFFI(result);
}

inline const ecitygml::capi::GenericAttributeKind* ecitygml::GenericAttributeKind::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::GenericAttributeKind*>(this);
}

inline ecitygml::capi::GenericAttributeKind* ecitygml::GenericAttributeKind::AsFFI() {
    return reinterpret_cast<ecitygml::capi::GenericAttributeKind*>(this);
}

inline const ecitygml::GenericAttributeKind* ecitygml::GenericAttributeKind::FromFFI(const ecitygml::capi::GenericAttributeKind* ptr) {
    return reinterpret_cast<const ecitygml::GenericAttributeKind*>(ptr);
}

inline ecitygml::GenericAttributeKind* ecitygml::GenericAttributeKind::FromFFI(ecitygml::capi::GenericAttributeKind* ptr) {
    return reinterpret_cast<ecitygml::GenericAttributeKind*>(ptr);
}

inline void ecitygml::GenericAttributeKind::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_GenericAttributeKind_destroy(reinterpret_cast<ecitygml::capi::GenericAttributeKind*>(ptr));
}


#endif // ECITYGML_GenericAttributeKind_HPP
