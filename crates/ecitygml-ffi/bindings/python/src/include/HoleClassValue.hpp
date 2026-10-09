#ifndef ECITYGML_HoleClassValue_HPP
#define ECITYGML_HoleClassValue_HPP

#include "HoleClassValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_HoleClassValue_code(const ecitygml::capi::HoleClassValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_HoleClassValue_value(const ecitygml::capi::HoleClassValue* self);

    void ecitygml_HoleClassValue_destroy(HoleClassValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::HoleClassValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_HoleClassValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::HoleClassValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_HoleClassValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::HoleClassValue* ecitygml::HoleClassValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::HoleClassValue*>(this);
}

inline ecitygml::capi::HoleClassValue* ecitygml::HoleClassValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::HoleClassValue*>(this);
}

inline const ecitygml::HoleClassValue* ecitygml::HoleClassValue::FromFFI(const ecitygml::capi::HoleClassValue* ptr) {
    return reinterpret_cast<const ecitygml::HoleClassValue*>(ptr);
}

inline ecitygml::HoleClassValue* ecitygml::HoleClassValue::FromFFI(ecitygml::capi::HoleClassValue* ptr) {
    return reinterpret_cast<ecitygml::HoleClassValue*>(ptr);
}

inline void ecitygml::HoleClassValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_HoleClassValue_destroy(reinterpret_cast<ecitygml::capi::HoleClassValue*>(ptr));
}


#endif // ECITYGML_HoleClassValue_HPP
