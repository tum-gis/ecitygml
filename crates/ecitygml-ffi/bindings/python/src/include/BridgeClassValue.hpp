#ifndef ECITYGML_BridgeClassValue_HPP
#define ECITYGML_BridgeClassValue_HPP

#include "BridgeClassValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_BridgeClassValue_code(const ecitygml::capi::BridgeClassValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_BridgeClassValue_value(const ecitygml::capi::BridgeClassValue* self);

    void ecitygml_BridgeClassValue_destroy(BridgeClassValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::BridgeClassValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgeClassValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::BridgeClassValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgeClassValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::BridgeClassValue* ecitygml::BridgeClassValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::BridgeClassValue*>(this);
}

inline ecitygml::capi::BridgeClassValue* ecitygml::BridgeClassValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::BridgeClassValue*>(this);
}

inline const ecitygml::BridgeClassValue* ecitygml::BridgeClassValue::FromFFI(const ecitygml::capi::BridgeClassValue* ptr) {
    return reinterpret_cast<const ecitygml::BridgeClassValue*>(ptr);
}

inline ecitygml::BridgeClassValue* ecitygml::BridgeClassValue::FromFFI(ecitygml::capi::BridgeClassValue* ptr) {
    return reinterpret_cast<ecitygml::BridgeClassValue*>(ptr);
}

inline void ecitygml::BridgeClassValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_BridgeClassValue_destroy(reinterpret_cast<ecitygml::capi::BridgeClassValue*>(ptr));
}


#endif // ECITYGML_BridgeClassValue_HPP
