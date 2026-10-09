#ifndef ECITYGML_BridgeFunctionValue_HPP
#define ECITYGML_BridgeFunctionValue_HPP

#include "BridgeFunctionValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_BridgeFunctionValue_code(const ecitygml::capi::BridgeFunctionValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_BridgeFunctionValue_value(const ecitygml::capi::BridgeFunctionValue* self);

    void ecitygml_BridgeFunctionValue_destroy(BridgeFunctionValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::BridgeFunctionValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgeFunctionValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::BridgeFunctionValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgeFunctionValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::BridgeFunctionValue* ecitygml::BridgeFunctionValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::BridgeFunctionValue*>(this);
}

inline ecitygml::capi::BridgeFunctionValue* ecitygml::BridgeFunctionValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::BridgeFunctionValue*>(this);
}

inline const ecitygml::BridgeFunctionValue* ecitygml::BridgeFunctionValue::FromFFI(const ecitygml::capi::BridgeFunctionValue* ptr) {
    return reinterpret_cast<const ecitygml::BridgeFunctionValue*>(ptr);
}

inline ecitygml::BridgeFunctionValue* ecitygml::BridgeFunctionValue::FromFFI(ecitygml::capi::BridgeFunctionValue* ptr) {
    return reinterpret_cast<ecitygml::BridgeFunctionValue*>(ptr);
}

inline void ecitygml::BridgeFunctionValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_BridgeFunctionValue_destroy(reinterpret_cast<ecitygml::capi::BridgeFunctionValue*>(ptr));
}


#endif // ECITYGML_BridgeFunctionValue_HPP
