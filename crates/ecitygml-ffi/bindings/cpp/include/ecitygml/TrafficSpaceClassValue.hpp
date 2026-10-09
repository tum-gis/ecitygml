#ifndef ecitygml_TrafficSpaceClassValue_HPP
#define ecitygml_TrafficSpaceClassValue_HPP

#include "TrafficSpaceClassValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_TrafficSpaceClassValue_code(const ecitygml::capi::TrafficSpaceClassValue* self);

    diplomat::capi::DiplomatStringView ecitygml_TrafficSpaceClassValue_value(const ecitygml::capi::TrafficSpaceClassValue* self);

    void ecitygml_TrafficSpaceClassValue_destroy(TrafficSpaceClassValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::TrafficSpaceClassValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpaceClassValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::TrafficSpaceClassValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpaceClassValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::TrafficSpaceClassValue* ecitygml::TrafficSpaceClassValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::TrafficSpaceClassValue*>(this);
}

inline ecitygml::capi::TrafficSpaceClassValue* ecitygml::TrafficSpaceClassValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::TrafficSpaceClassValue*>(this);
}

inline const ecitygml::TrafficSpaceClassValue* ecitygml::TrafficSpaceClassValue::FromFFI(const ecitygml::capi::TrafficSpaceClassValue* ptr) {
    return reinterpret_cast<const ecitygml::TrafficSpaceClassValue*>(ptr);
}

inline ecitygml::TrafficSpaceClassValue* ecitygml::TrafficSpaceClassValue::FromFFI(ecitygml::capi::TrafficSpaceClassValue* ptr) {
    return reinterpret_cast<ecitygml::TrafficSpaceClassValue*>(ptr);
}

inline void ecitygml::TrafficSpaceClassValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_TrafficSpaceClassValue_destroy(reinterpret_cast<ecitygml::capi::TrafficSpaceClassValue*>(ptr));
}


#endif // ecitygml_TrafficSpaceClassValue_HPP
