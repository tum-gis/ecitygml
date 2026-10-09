#ifndef ecitygml_RoadFunctionValue_HPP
#define ecitygml_RoadFunctionValue_HPP

#include "RoadFunctionValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_RoadFunctionValue_code(const ecitygml::capi::RoadFunctionValue* self);

    diplomat::capi::DiplomatStringView ecitygml_RoadFunctionValue_value(const ecitygml::capi::RoadFunctionValue* self);

    void ecitygml_RoadFunctionValue_destroy(RoadFunctionValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::RoadFunctionValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_RoadFunctionValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::RoadFunctionValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_RoadFunctionValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::RoadFunctionValue* ecitygml::RoadFunctionValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::RoadFunctionValue*>(this);
}

inline ecitygml::capi::RoadFunctionValue* ecitygml::RoadFunctionValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::RoadFunctionValue*>(this);
}

inline const ecitygml::RoadFunctionValue* ecitygml::RoadFunctionValue::FromFFI(const ecitygml::capi::RoadFunctionValue* ptr) {
    return reinterpret_cast<const ecitygml::RoadFunctionValue*>(ptr);
}

inline ecitygml::RoadFunctionValue* ecitygml::RoadFunctionValue::FromFFI(ecitygml::capi::RoadFunctionValue* ptr) {
    return reinterpret_cast<ecitygml::RoadFunctionValue*>(ptr);
}

inline void ecitygml::RoadFunctionValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_RoadFunctionValue_destroy(reinterpret_cast<ecitygml::capi::RoadFunctionValue*>(ptr));
}


#endif // ecitygml_RoadFunctionValue_HPP
