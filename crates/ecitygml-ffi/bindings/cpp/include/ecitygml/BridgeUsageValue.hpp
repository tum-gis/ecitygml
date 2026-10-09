#ifndef ecitygml_BridgeUsageValue_HPP
#define ecitygml_BridgeUsageValue_HPP

#include "BridgeUsageValue.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "Code.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Code* ecitygml_BridgeUsageValue_code(const ecitygml::capi::BridgeUsageValue* self);

    diplomat::capi::DiplomatStringView ecitygml_BridgeUsageValue_value(const ecitygml::capi::BridgeUsageValue* self);

    void ecitygml_BridgeUsageValue_destroy(BridgeUsageValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::BridgeUsageValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgeUsageValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::BridgeUsageValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgeUsageValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::BridgeUsageValue* ecitygml::BridgeUsageValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::BridgeUsageValue*>(this);
}

inline ecitygml::capi::BridgeUsageValue* ecitygml::BridgeUsageValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::BridgeUsageValue*>(this);
}

inline const ecitygml::BridgeUsageValue* ecitygml::BridgeUsageValue::FromFFI(const ecitygml::capi::BridgeUsageValue* ptr) {
    return reinterpret_cast<const ecitygml::BridgeUsageValue*>(ptr);
}

inline ecitygml::BridgeUsageValue* ecitygml::BridgeUsageValue::FromFFI(ecitygml::capi::BridgeUsageValue* ptr) {
    return reinterpret_cast<ecitygml::BridgeUsageValue*>(ptr);
}

inline void ecitygml::BridgeUsageValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_BridgeUsageValue_destroy(reinterpret_cast<ecitygml::capi::BridgeUsageValue*>(ptr));
}


#endif // ecitygml_BridgeUsageValue_HPP
