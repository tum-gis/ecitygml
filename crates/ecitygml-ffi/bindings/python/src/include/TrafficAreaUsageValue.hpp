#ifndef ECITYGML_TrafficAreaUsageValue_HPP
#define ECITYGML_TrafficAreaUsageValue_HPP

#include "TrafficAreaUsageValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_TrafficAreaUsageValue_code(const ecitygml::capi::TrafficAreaUsageValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_TrafficAreaUsageValue_value(const ecitygml::capi::TrafficAreaUsageValue* self);

    void ecitygml_TrafficAreaUsageValue_destroy(TrafficAreaUsageValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::TrafficAreaUsageValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficAreaUsageValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::TrafficAreaUsageValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficAreaUsageValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::TrafficAreaUsageValue* ecitygml::TrafficAreaUsageValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::TrafficAreaUsageValue*>(this);
}

inline ecitygml::capi::TrafficAreaUsageValue* ecitygml::TrafficAreaUsageValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::TrafficAreaUsageValue*>(this);
}

inline const ecitygml::TrafficAreaUsageValue* ecitygml::TrafficAreaUsageValue::FromFFI(const ecitygml::capi::TrafficAreaUsageValue* ptr) {
    return reinterpret_cast<const ecitygml::TrafficAreaUsageValue*>(ptr);
}

inline ecitygml::TrafficAreaUsageValue* ecitygml::TrafficAreaUsageValue::FromFFI(ecitygml::capi::TrafficAreaUsageValue* ptr) {
    return reinterpret_cast<ecitygml::TrafficAreaUsageValue*>(ptr);
}

inline void ecitygml::TrafficAreaUsageValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_TrafficAreaUsageValue_destroy(reinterpret_cast<ecitygml::capi::TrafficAreaUsageValue*>(ptr));
}


#endif // ECITYGML_TrafficAreaUsageValue_HPP
