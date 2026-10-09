#ifndef ECITYGML_MimeTypeValue_HPP
#define ECITYGML_MimeTypeValue_HPP

#include "MimeTypeValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_MimeTypeValue_code(const ecitygml::capi::MimeTypeValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_MimeTypeValue_value(const ecitygml::capi::MimeTypeValue* self);

    void ecitygml_MimeTypeValue_destroy(MimeTypeValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::MimeTypeValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_MimeTypeValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::MimeTypeValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_MimeTypeValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::MimeTypeValue* ecitygml::MimeTypeValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::MimeTypeValue*>(this);
}

inline ecitygml::capi::MimeTypeValue* ecitygml::MimeTypeValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::MimeTypeValue*>(this);
}

inline const ecitygml::MimeTypeValue* ecitygml::MimeTypeValue::FromFFI(const ecitygml::capi::MimeTypeValue* ptr) {
    return reinterpret_cast<const ecitygml::MimeTypeValue*>(ptr);
}

inline ecitygml::MimeTypeValue* ecitygml::MimeTypeValue::FromFFI(ecitygml::capi::MimeTypeValue* ptr) {
    return reinterpret_cast<ecitygml::MimeTypeValue*>(ptr);
}

inline void ecitygml::MimeTypeValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_MimeTypeValue_destroy(reinterpret_cast<ecitygml::capi::MimeTypeValue*>(ptr));
}


#endif // ECITYGML_MimeTypeValue_HPP
