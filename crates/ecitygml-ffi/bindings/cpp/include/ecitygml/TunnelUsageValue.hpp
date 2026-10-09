#ifndef ecitygml_TunnelUsageValue_HPP
#define ecitygml_TunnelUsageValue_HPP

#include "TunnelUsageValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_TunnelUsageValue_code(const ecitygml::capi::TunnelUsageValue* self);

    diplomat::capi::DiplomatStringView ecitygml_TunnelUsageValue_value(const ecitygml::capi::TunnelUsageValue* self);

    void ecitygml_TunnelUsageValue_destroy(TunnelUsageValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::TunnelUsageValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelUsageValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::TunnelUsageValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelUsageValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::TunnelUsageValue* ecitygml::TunnelUsageValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::TunnelUsageValue*>(this);
}

inline ecitygml::capi::TunnelUsageValue* ecitygml::TunnelUsageValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::TunnelUsageValue*>(this);
}

inline const ecitygml::TunnelUsageValue* ecitygml::TunnelUsageValue::FromFFI(const ecitygml::capi::TunnelUsageValue* ptr) {
    return reinterpret_cast<const ecitygml::TunnelUsageValue*>(ptr);
}

inline ecitygml::TunnelUsageValue* ecitygml::TunnelUsageValue::FromFFI(ecitygml::capi::TunnelUsageValue* ptr) {
    return reinterpret_cast<ecitygml::TunnelUsageValue*>(ptr);
}

inline void ecitygml::TunnelUsageValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_TunnelUsageValue_destroy(reinterpret_cast<ecitygml::capi::TunnelUsageValue*>(ptr));
}


#endif // ecitygml_TunnelUsageValue_HPP
