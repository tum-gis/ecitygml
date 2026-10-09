#ifndef ECITYGML_AuxiliaryTrafficSpaceFunctionValue_HPP
#define ECITYGML_AuxiliaryTrafficSpaceFunctionValue_HPP

#include "AuxiliaryTrafficSpaceFunctionValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_AuxiliaryTrafficSpaceFunctionValue_code(const ecitygml::capi::AuxiliaryTrafficSpaceFunctionValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_AuxiliaryTrafficSpaceFunctionValue_value(const ecitygml::capi::AuxiliaryTrafficSpaceFunctionValue* self);

    void ecitygml_AuxiliaryTrafficSpaceFunctionValue_destroy(AuxiliaryTrafficSpaceFunctionValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::AuxiliaryTrafficSpaceFunctionValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpaceFunctionValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::AuxiliaryTrafficSpaceFunctionValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpaceFunctionValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::AuxiliaryTrafficSpaceFunctionValue* ecitygml::AuxiliaryTrafficSpaceFunctionValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AuxiliaryTrafficSpaceFunctionValue*>(this);
}

inline ecitygml::capi::AuxiliaryTrafficSpaceFunctionValue* ecitygml::AuxiliaryTrafficSpaceFunctionValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AuxiliaryTrafficSpaceFunctionValue*>(this);
}

inline const ecitygml::AuxiliaryTrafficSpaceFunctionValue* ecitygml::AuxiliaryTrafficSpaceFunctionValue::FromFFI(const ecitygml::capi::AuxiliaryTrafficSpaceFunctionValue* ptr) {
    return reinterpret_cast<const ecitygml::AuxiliaryTrafficSpaceFunctionValue*>(ptr);
}

inline ecitygml::AuxiliaryTrafficSpaceFunctionValue* ecitygml::AuxiliaryTrafficSpaceFunctionValue::FromFFI(ecitygml::capi::AuxiliaryTrafficSpaceFunctionValue* ptr) {
    return reinterpret_cast<ecitygml::AuxiliaryTrafficSpaceFunctionValue*>(ptr);
}

inline void ecitygml::AuxiliaryTrafficSpaceFunctionValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AuxiliaryTrafficSpaceFunctionValue_destroy(reinterpret_cast<ecitygml::capi::AuxiliaryTrafficSpaceFunctionValue*>(ptr));
}


#endif // ECITYGML_AuxiliaryTrafficSpaceFunctionValue_HPP
