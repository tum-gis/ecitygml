#ifndef ecitygml_AuxiliaryTrafficAreaUsageValue_HPP
#define ecitygml_AuxiliaryTrafficAreaUsageValue_HPP

#include "AuxiliaryTrafficAreaUsageValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_AuxiliaryTrafficAreaUsageValue_code(const ecitygml::capi::AuxiliaryTrafficAreaUsageValue* self);

    diplomat::capi::DiplomatStringView ecitygml_AuxiliaryTrafficAreaUsageValue_value(const ecitygml::capi::AuxiliaryTrafficAreaUsageValue* self);

    void ecitygml_AuxiliaryTrafficAreaUsageValue_destroy(AuxiliaryTrafficAreaUsageValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::AuxiliaryTrafficAreaUsageValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficAreaUsageValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::AuxiliaryTrafficAreaUsageValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficAreaUsageValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::AuxiliaryTrafficAreaUsageValue* ecitygml::AuxiliaryTrafficAreaUsageValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AuxiliaryTrafficAreaUsageValue*>(this);
}

inline ecitygml::capi::AuxiliaryTrafficAreaUsageValue* ecitygml::AuxiliaryTrafficAreaUsageValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AuxiliaryTrafficAreaUsageValue*>(this);
}

inline const ecitygml::AuxiliaryTrafficAreaUsageValue* ecitygml::AuxiliaryTrafficAreaUsageValue::FromFFI(const ecitygml::capi::AuxiliaryTrafficAreaUsageValue* ptr) {
    return reinterpret_cast<const ecitygml::AuxiliaryTrafficAreaUsageValue*>(ptr);
}

inline ecitygml::AuxiliaryTrafficAreaUsageValue* ecitygml::AuxiliaryTrafficAreaUsageValue::FromFFI(ecitygml::capi::AuxiliaryTrafficAreaUsageValue* ptr) {
    return reinterpret_cast<ecitygml::AuxiliaryTrafficAreaUsageValue*>(ptr);
}

inline void ecitygml::AuxiliaryTrafficAreaUsageValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AuxiliaryTrafficAreaUsageValue_destroy(reinterpret_cast<ecitygml::capi::AuxiliaryTrafficAreaUsageValue*>(ptr));
}


#endif // ecitygml_AuxiliaryTrafficAreaUsageValue_HPP
