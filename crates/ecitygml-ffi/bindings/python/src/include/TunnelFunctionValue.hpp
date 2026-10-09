#ifndef ECITYGML_TunnelFunctionValue_HPP
#define ECITYGML_TunnelFunctionValue_HPP

#include "TunnelFunctionValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_TunnelFunctionValue_code(const ecitygml::capi::TunnelFunctionValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_TunnelFunctionValue_value(const ecitygml::capi::TunnelFunctionValue* self);

    void ecitygml_TunnelFunctionValue_destroy(TunnelFunctionValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::TunnelFunctionValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelFunctionValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::TunnelFunctionValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelFunctionValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::TunnelFunctionValue* ecitygml::TunnelFunctionValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::TunnelFunctionValue*>(this);
}

inline ecitygml::capi::TunnelFunctionValue* ecitygml::TunnelFunctionValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::TunnelFunctionValue*>(this);
}

inline const ecitygml::TunnelFunctionValue* ecitygml::TunnelFunctionValue::FromFFI(const ecitygml::capi::TunnelFunctionValue* ptr) {
    return reinterpret_cast<const ecitygml::TunnelFunctionValue*>(ptr);
}

inline ecitygml::TunnelFunctionValue* ecitygml::TunnelFunctionValue::FromFFI(ecitygml::capi::TunnelFunctionValue* ptr) {
    return reinterpret_cast<ecitygml::TunnelFunctionValue*>(ptr);
}

inline void ecitygml::TunnelFunctionValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_TunnelFunctionValue_destroy(reinterpret_cast<ecitygml::capi::TunnelFunctionValue*>(ptr));
}


#endif // ECITYGML_TunnelFunctionValue_HPP
