#ifndef ECITYGML_AuxiliaryTrafficSpaceClassValue_HPP
#define ECITYGML_AuxiliaryTrafficSpaceClassValue_HPP

#include "AuxiliaryTrafficSpaceClassValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_AuxiliaryTrafficSpaceClassValue_code(const ecitygml::capi::AuxiliaryTrafficSpaceClassValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_AuxiliaryTrafficSpaceClassValue_value(const ecitygml::capi::AuxiliaryTrafficSpaceClassValue* self);

    void ecitygml_AuxiliaryTrafficSpaceClassValue_destroy(AuxiliaryTrafficSpaceClassValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::AuxiliaryTrafficSpaceClassValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpaceClassValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::AuxiliaryTrafficSpaceClassValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpaceClassValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::AuxiliaryTrafficSpaceClassValue* ecitygml::AuxiliaryTrafficSpaceClassValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AuxiliaryTrafficSpaceClassValue*>(this);
}

inline ecitygml::capi::AuxiliaryTrafficSpaceClassValue* ecitygml::AuxiliaryTrafficSpaceClassValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AuxiliaryTrafficSpaceClassValue*>(this);
}

inline const ecitygml::AuxiliaryTrafficSpaceClassValue* ecitygml::AuxiliaryTrafficSpaceClassValue::FromFFI(const ecitygml::capi::AuxiliaryTrafficSpaceClassValue* ptr) {
    return reinterpret_cast<const ecitygml::AuxiliaryTrafficSpaceClassValue*>(ptr);
}

inline ecitygml::AuxiliaryTrafficSpaceClassValue* ecitygml::AuxiliaryTrafficSpaceClassValue::FromFFI(ecitygml::capi::AuxiliaryTrafficSpaceClassValue* ptr) {
    return reinterpret_cast<ecitygml::AuxiliaryTrafficSpaceClassValue*>(ptr);
}

inline void ecitygml::AuxiliaryTrafficSpaceClassValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AuxiliaryTrafficSpaceClassValue_destroy(reinterpret_cast<ecitygml::capi::AuxiliaryTrafficSpaceClassValue*>(ptr));
}


#endif // ECITYGML_AuxiliaryTrafficSpaceClassValue_HPP
