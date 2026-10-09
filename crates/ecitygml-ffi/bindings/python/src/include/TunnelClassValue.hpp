#ifndef ECITYGML_TunnelClassValue_HPP
#define ECITYGML_TunnelClassValue_HPP

#include "TunnelClassValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_TunnelClassValue_code(const ecitygml::capi::TunnelClassValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_TunnelClassValue_value(const ecitygml::capi::TunnelClassValue* self);

    void ecitygml_TunnelClassValue_destroy(TunnelClassValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::TunnelClassValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelClassValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::TunnelClassValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelClassValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::TunnelClassValue* ecitygml::TunnelClassValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::TunnelClassValue*>(this);
}

inline ecitygml::capi::TunnelClassValue* ecitygml::TunnelClassValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::TunnelClassValue*>(this);
}

inline const ecitygml::TunnelClassValue* ecitygml::TunnelClassValue::FromFFI(const ecitygml::capi::TunnelClassValue* ptr) {
    return reinterpret_cast<const ecitygml::TunnelClassValue*>(ptr);
}

inline ecitygml::TunnelClassValue* ecitygml::TunnelClassValue::FromFFI(ecitygml::capi::TunnelClassValue* ptr) {
    return reinterpret_cast<ecitygml::TunnelClassValue*>(ptr);
}

inline void ecitygml::TunnelClassValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_TunnelClassValue_destroy(reinterpret_cast<ecitygml::capi::TunnelClassValue*>(ptr));
}


#endif // ECITYGML_TunnelClassValue_HPP
