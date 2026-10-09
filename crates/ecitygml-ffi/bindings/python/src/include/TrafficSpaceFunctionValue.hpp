#ifndef ECITYGML_TrafficSpaceFunctionValue_HPP
#define ECITYGML_TrafficSpaceFunctionValue_HPP

#include "TrafficSpaceFunctionValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_TrafficSpaceFunctionValue_code(const ecitygml::capi::TrafficSpaceFunctionValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_TrafficSpaceFunctionValue_value(const ecitygml::capi::TrafficSpaceFunctionValue* self);

    void ecitygml_TrafficSpaceFunctionValue_destroy(TrafficSpaceFunctionValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::TrafficSpaceFunctionValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpaceFunctionValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::TrafficSpaceFunctionValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TrafficSpaceFunctionValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::TrafficSpaceFunctionValue* ecitygml::TrafficSpaceFunctionValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::TrafficSpaceFunctionValue*>(this);
}

inline ecitygml::capi::TrafficSpaceFunctionValue* ecitygml::TrafficSpaceFunctionValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::TrafficSpaceFunctionValue*>(this);
}

inline const ecitygml::TrafficSpaceFunctionValue* ecitygml::TrafficSpaceFunctionValue::FromFFI(const ecitygml::capi::TrafficSpaceFunctionValue* ptr) {
    return reinterpret_cast<const ecitygml::TrafficSpaceFunctionValue*>(ptr);
}

inline ecitygml::TrafficSpaceFunctionValue* ecitygml::TrafficSpaceFunctionValue::FromFFI(ecitygml::capi::TrafficSpaceFunctionValue* ptr) {
    return reinterpret_cast<ecitygml::TrafficSpaceFunctionValue*>(ptr);
}

inline void ecitygml::TrafficSpaceFunctionValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_TrafficSpaceFunctionValue_destroy(reinterpret_cast<ecitygml::capi::TrafficSpaceFunctionValue*>(ptr));
}


#endif // ECITYGML_TrafficSpaceFunctionValue_HPP
