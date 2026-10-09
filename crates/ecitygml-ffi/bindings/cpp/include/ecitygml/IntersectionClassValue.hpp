#ifndef ecitygml_IntersectionClassValue_HPP
#define ecitygml_IntersectionClassValue_HPP

#include "IntersectionClassValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_IntersectionClassValue_code(const ecitygml::capi::IntersectionClassValue* self);

    diplomat::capi::DiplomatStringView ecitygml_IntersectionClassValue_value(const ecitygml::capi::IntersectionClassValue* self);

    void ecitygml_IntersectionClassValue_destroy(IntersectionClassValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::IntersectionClassValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_IntersectionClassValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::IntersectionClassValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_IntersectionClassValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::IntersectionClassValue* ecitygml::IntersectionClassValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::IntersectionClassValue*>(this);
}

inline ecitygml::capi::IntersectionClassValue* ecitygml::IntersectionClassValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::IntersectionClassValue*>(this);
}

inline const ecitygml::IntersectionClassValue* ecitygml::IntersectionClassValue::FromFFI(const ecitygml::capi::IntersectionClassValue* ptr) {
    return reinterpret_cast<const ecitygml::IntersectionClassValue*>(ptr);
}

inline ecitygml::IntersectionClassValue* ecitygml::IntersectionClassValue::FromFFI(ecitygml::capi::IntersectionClassValue* ptr) {
    return reinterpret_cast<ecitygml::IntersectionClassValue*>(ptr);
}

inline void ecitygml::IntersectionClassValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_IntersectionClassValue_destroy(reinterpret_cast<ecitygml::capi::IntersectionClassValue*>(ptr));
}


#endif // ecitygml_IntersectionClassValue_HPP
