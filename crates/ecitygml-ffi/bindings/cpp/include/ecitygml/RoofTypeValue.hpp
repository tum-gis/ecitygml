#ifndef ecitygml_RoofTypeValue_HPP
#define ecitygml_RoofTypeValue_HPP

#include "RoofTypeValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_RoofTypeValue_code(const ecitygml::capi::RoofTypeValue* self);

    diplomat::capi::DiplomatStringView ecitygml_RoofTypeValue_value(const ecitygml::capi::RoofTypeValue* self);

    void ecitygml_RoofTypeValue_destroy(RoofTypeValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::RoofTypeValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_RoofTypeValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::RoofTypeValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_RoofTypeValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::RoofTypeValue* ecitygml::RoofTypeValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::RoofTypeValue*>(this);
}

inline ecitygml::capi::RoofTypeValue* ecitygml::RoofTypeValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::RoofTypeValue*>(this);
}

inline const ecitygml::RoofTypeValue* ecitygml::RoofTypeValue::FromFFI(const ecitygml::capi::RoofTypeValue* ptr) {
    return reinterpret_cast<const ecitygml::RoofTypeValue*>(ptr);
}

inline ecitygml::RoofTypeValue* ecitygml::RoofTypeValue::FromFFI(ecitygml::capi::RoofTypeValue* ptr) {
    return reinterpret_cast<ecitygml::RoofTypeValue*>(ptr);
}

inline void ecitygml::RoofTypeValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_RoofTypeValue_destroy(reinterpret_cast<ecitygml::capi::RoofTypeValue*>(ptr));
}


#endif // ecitygml_RoofTypeValue_HPP
