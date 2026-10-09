#ifndef ECITYGML_AuxiliaryTrafficAreaFunctionValue_HPP
#define ECITYGML_AuxiliaryTrafficAreaFunctionValue_HPP

#include "AuxiliaryTrafficAreaFunctionValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_AuxiliaryTrafficAreaFunctionValue_code(const ecitygml::capi::AuxiliaryTrafficAreaFunctionValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_AuxiliaryTrafficAreaFunctionValue_value(const ecitygml::capi::AuxiliaryTrafficAreaFunctionValue* self);

    void ecitygml_AuxiliaryTrafficAreaFunctionValue_destroy(AuxiliaryTrafficAreaFunctionValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::AuxiliaryTrafficAreaFunctionValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficAreaFunctionValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::AuxiliaryTrafficAreaFunctionValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficAreaFunctionValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::AuxiliaryTrafficAreaFunctionValue* ecitygml::AuxiliaryTrafficAreaFunctionValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AuxiliaryTrafficAreaFunctionValue*>(this);
}

inline ecitygml::capi::AuxiliaryTrafficAreaFunctionValue* ecitygml::AuxiliaryTrafficAreaFunctionValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AuxiliaryTrafficAreaFunctionValue*>(this);
}

inline const ecitygml::AuxiliaryTrafficAreaFunctionValue* ecitygml::AuxiliaryTrafficAreaFunctionValue::FromFFI(const ecitygml::capi::AuxiliaryTrafficAreaFunctionValue* ptr) {
    return reinterpret_cast<const ecitygml::AuxiliaryTrafficAreaFunctionValue*>(ptr);
}

inline ecitygml::AuxiliaryTrafficAreaFunctionValue* ecitygml::AuxiliaryTrafficAreaFunctionValue::FromFFI(ecitygml::capi::AuxiliaryTrafficAreaFunctionValue* ptr) {
    return reinterpret_cast<ecitygml::AuxiliaryTrafficAreaFunctionValue*>(ptr);
}

inline void ecitygml::AuxiliaryTrafficAreaFunctionValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AuxiliaryTrafficAreaFunctionValue_destroy(reinterpret_cast<ecitygml::capi::AuxiliaryTrafficAreaFunctionValue*>(ptr));
}


#endif // ECITYGML_AuxiliaryTrafficAreaFunctionValue_HPP
