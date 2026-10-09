#ifndef ECITYGML_TrafficAreaClassValue_HPP
#define ECITYGML_TrafficAreaClassValue_HPP

#include "TrafficAreaClassValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_TrafficAreaClassValue_code(const ecitygml::capi::TrafficAreaClassValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_TrafficAreaClassValue_value(const ecitygml::capi::TrafficAreaClassValue* self);

    void ecitygml_TrafficAreaClassValue_destroy(TrafficAreaClassValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::TrafficAreaClassValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficAreaClassValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::TrafficAreaClassValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficAreaClassValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::TrafficAreaClassValue* ecitygml::TrafficAreaClassValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::TrafficAreaClassValue*>(this);
}

inline ecitygml::capi::TrafficAreaClassValue* ecitygml::TrafficAreaClassValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::TrafficAreaClassValue*>(this);
}

inline const ecitygml::TrafficAreaClassValue* ecitygml::TrafficAreaClassValue::FromFFI(const ecitygml::capi::TrafficAreaClassValue* ptr) {
    return reinterpret_cast<const ecitygml::TrafficAreaClassValue*>(ptr);
}

inline ecitygml::TrafficAreaClassValue* ecitygml::TrafficAreaClassValue::FromFFI(ecitygml::capi::TrafficAreaClassValue* ptr) {
    return reinterpret_cast<ecitygml::TrafficAreaClassValue*>(ptr);
}

inline void ecitygml::TrafficAreaClassValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_TrafficAreaClassValue_destroy(reinterpret_cast<ecitygml::capi::TrafficAreaClassValue*>(ptr));
}


#endif // ECITYGML_TrafficAreaClassValue_HPP
