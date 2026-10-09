#ifndef ECITYGML_MarkingClassValue_HPP
#define ECITYGML_MarkingClassValue_HPP

#include "MarkingClassValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_MarkingClassValue_code(const ecitygml::capi::MarkingClassValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_MarkingClassValue_value(const ecitygml::capi::MarkingClassValue* self);

    void ecitygml_MarkingClassValue_destroy(MarkingClassValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::MarkingClassValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_MarkingClassValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::MarkingClassValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_MarkingClassValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::MarkingClassValue* ecitygml::MarkingClassValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::MarkingClassValue*>(this);
}

inline ecitygml::capi::MarkingClassValue* ecitygml::MarkingClassValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::MarkingClassValue*>(this);
}

inline const ecitygml::MarkingClassValue* ecitygml::MarkingClassValue::FromFFI(const ecitygml::capi::MarkingClassValue* ptr) {
    return reinterpret_cast<const ecitygml::MarkingClassValue*>(ptr);
}

inline ecitygml::MarkingClassValue* ecitygml::MarkingClassValue::FromFFI(ecitygml::capi::MarkingClassValue* ptr) {
    return reinterpret_cast<ecitygml::MarkingClassValue*>(ptr);
}

inline void ecitygml::MarkingClassValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_MarkingClassValue_destroy(reinterpret_cast<ecitygml::capi::MarkingClassValue*>(ptr));
}


#endif // ECITYGML_MarkingClassValue_HPP
