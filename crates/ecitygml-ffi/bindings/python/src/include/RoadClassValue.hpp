#ifndef ECITYGML_RoadClassValue_HPP
#define ECITYGML_RoadClassValue_HPP

#include "RoadClassValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_RoadClassValue_code(const ecitygml::capi::RoadClassValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_RoadClassValue_value(const ecitygml::capi::RoadClassValue* self);

    void ecitygml_RoadClassValue_destroy(RoadClassValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::RoadClassValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_RoadClassValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::RoadClassValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_RoadClassValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::RoadClassValue* ecitygml::RoadClassValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::RoadClassValue*>(this);
}

inline ecitygml::capi::RoadClassValue* ecitygml::RoadClassValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::RoadClassValue*>(this);
}

inline const ecitygml::RoadClassValue* ecitygml::RoadClassValue::FromFFI(const ecitygml::capi::RoadClassValue* ptr) {
    return reinterpret_cast<const ecitygml::RoadClassValue*>(ptr);
}

inline ecitygml::RoadClassValue* ecitygml::RoadClassValue::FromFFI(ecitygml::capi::RoadClassValue* ptr) {
    return reinterpret_cast<ecitygml::RoadClassValue*>(ptr);
}

inline void ecitygml::RoadClassValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_RoadClassValue_destroy(reinterpret_cast<ecitygml::capi::RoadClassValue*>(ptr));
}


#endif // ECITYGML_RoadClassValue_HPP
