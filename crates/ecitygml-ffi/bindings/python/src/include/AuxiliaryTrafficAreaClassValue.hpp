#ifndef ECITYGML_AuxiliaryTrafficAreaClassValue_HPP
#define ECITYGML_AuxiliaryTrafficAreaClassValue_HPP

#include "AuxiliaryTrafficAreaClassValue.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "Code.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Code* ecitygml_AuxiliaryTrafficAreaClassValue_code(const ecitygml::capi::AuxiliaryTrafficAreaClassValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_AuxiliaryTrafficAreaClassValue_value(const ecitygml::capi::AuxiliaryTrafficAreaClassValue* self);

    void ecitygml_AuxiliaryTrafficAreaClassValue_destroy(AuxiliaryTrafficAreaClassValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::AuxiliaryTrafficAreaClassValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficAreaClassValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::AuxiliaryTrafficAreaClassValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficAreaClassValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::AuxiliaryTrafficAreaClassValue* ecitygml::AuxiliaryTrafficAreaClassValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AuxiliaryTrafficAreaClassValue*>(this);
}

inline ecitygml::capi::AuxiliaryTrafficAreaClassValue* ecitygml::AuxiliaryTrafficAreaClassValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AuxiliaryTrafficAreaClassValue*>(this);
}

inline const ecitygml::AuxiliaryTrafficAreaClassValue* ecitygml::AuxiliaryTrafficAreaClassValue::FromFFI(const ecitygml::capi::AuxiliaryTrafficAreaClassValue* ptr) {
    return reinterpret_cast<const ecitygml::AuxiliaryTrafficAreaClassValue*>(ptr);
}

inline ecitygml::AuxiliaryTrafficAreaClassValue* ecitygml::AuxiliaryTrafficAreaClassValue::FromFFI(ecitygml::capi::AuxiliaryTrafficAreaClassValue* ptr) {
    return reinterpret_cast<ecitygml::AuxiliaryTrafficAreaClassValue*>(ptr);
}

inline void ecitygml::AuxiliaryTrafficAreaClassValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AuxiliaryTrafficAreaClassValue_destroy(reinterpret_cast<ecitygml::capi::AuxiliaryTrafficAreaClassValue*>(ptr));
}


#endif // ECITYGML_AuxiliaryTrafficAreaClassValue_HPP
