#ifndef ECITYGML_ElevationReferenceValue_HPP
#define ECITYGML_ElevationReferenceValue_HPP

#include "ElevationReferenceValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_ElevationReferenceValue_code(const ecitygml::capi::ElevationReferenceValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_ElevationReferenceValue_value(const ecitygml::capi::ElevationReferenceValue* self);

    void ecitygml_ElevationReferenceValue_destroy(ElevationReferenceValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::ElevationReferenceValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_ElevationReferenceValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::ElevationReferenceValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_ElevationReferenceValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::ElevationReferenceValue* ecitygml::ElevationReferenceValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::ElevationReferenceValue*>(this);
}

inline ecitygml::capi::ElevationReferenceValue* ecitygml::ElevationReferenceValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::ElevationReferenceValue*>(this);
}

inline const ecitygml::ElevationReferenceValue* ecitygml::ElevationReferenceValue::FromFFI(const ecitygml::capi::ElevationReferenceValue* ptr) {
    return reinterpret_cast<const ecitygml::ElevationReferenceValue*>(ptr);
}

inline ecitygml::ElevationReferenceValue* ecitygml::ElevationReferenceValue::FromFFI(ecitygml::capi::ElevationReferenceValue* ptr) {
    return reinterpret_cast<ecitygml::ElevationReferenceValue*>(ptr);
}

inline void ecitygml::ElevationReferenceValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_ElevationReferenceValue_destroy(reinterpret_cast<ecitygml::capi::ElevationReferenceValue*>(ptr));
}


#endif // ECITYGML_ElevationReferenceValue_HPP
