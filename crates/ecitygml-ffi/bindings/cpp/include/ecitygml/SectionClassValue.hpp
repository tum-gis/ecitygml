#ifndef ecitygml_SectionClassValue_HPP
#define ecitygml_SectionClassValue_HPP

#include "SectionClassValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_SectionClassValue_code(const ecitygml::capi::SectionClassValue* self);

    diplomat::capi::DiplomatStringView ecitygml_SectionClassValue_value(const ecitygml::capi::SectionClassValue* self);

    void ecitygml_SectionClassValue_destroy(SectionClassValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::SectionClassValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SectionClassValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::SectionClassValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SectionClassValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::SectionClassValue* ecitygml::SectionClassValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::SectionClassValue*>(this);
}

inline ecitygml::capi::SectionClassValue* ecitygml::SectionClassValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::SectionClassValue*>(this);
}

inline const ecitygml::SectionClassValue* ecitygml::SectionClassValue::FromFFI(const ecitygml::capi::SectionClassValue* ptr) {
    return reinterpret_cast<const ecitygml::SectionClassValue*>(ptr);
}

inline ecitygml::SectionClassValue* ecitygml::SectionClassValue::FromFFI(ecitygml::capi::SectionClassValue* ptr) {
    return reinterpret_cast<ecitygml::SectionClassValue*>(ptr);
}

inline void ecitygml::SectionClassValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_SectionClassValue_destroy(reinterpret_cast<ecitygml::capi::SectionClassValue*>(ptr));
}


#endif // ecitygml_SectionClassValue_HPP
