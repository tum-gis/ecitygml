#ifndef ECITYGML_TrafficAreaFunctionValue_HPP
#define ECITYGML_TrafficAreaFunctionValue_HPP

#include "TrafficAreaFunctionValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_TrafficAreaFunctionValue_code(const ecitygml::capi::TrafficAreaFunctionValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_TrafficAreaFunctionValue_value(const ecitygml::capi::TrafficAreaFunctionValue* self);

    void ecitygml_TrafficAreaFunctionValue_destroy(TrafficAreaFunctionValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::TrafficAreaFunctionValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficAreaFunctionValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::TrafficAreaFunctionValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficAreaFunctionValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::TrafficAreaFunctionValue* ecitygml::TrafficAreaFunctionValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::TrafficAreaFunctionValue*>(this);
}

inline ecitygml::capi::TrafficAreaFunctionValue* ecitygml::TrafficAreaFunctionValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::TrafficAreaFunctionValue*>(this);
}

inline const ecitygml::TrafficAreaFunctionValue* ecitygml::TrafficAreaFunctionValue::FromFFI(const ecitygml::capi::TrafficAreaFunctionValue* ptr) {
    return reinterpret_cast<const ecitygml::TrafficAreaFunctionValue*>(ptr);
}

inline ecitygml::TrafficAreaFunctionValue* ecitygml::TrafficAreaFunctionValue::FromFFI(ecitygml::capi::TrafficAreaFunctionValue* ptr) {
    return reinterpret_cast<ecitygml::TrafficAreaFunctionValue*>(ptr);
}

inline void ecitygml::TrafficAreaFunctionValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_TrafficAreaFunctionValue_destroy(reinterpret_cast<ecitygml::capi::TrafficAreaFunctionValue*>(ptr));
}


#endif // ECITYGML_TrafficAreaFunctionValue_HPP
