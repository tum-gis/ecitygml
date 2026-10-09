#ifndef ECITYGML_AuxiliaryTrafficSpaceUsageValue_HPP
#define ECITYGML_AuxiliaryTrafficSpaceUsageValue_HPP

#include "AuxiliaryTrafficSpaceUsageValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_AuxiliaryTrafficSpaceUsageValue_code(const ecitygml::capi::AuxiliaryTrafficSpaceUsageValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_AuxiliaryTrafficSpaceUsageValue_value(const ecitygml::capi::AuxiliaryTrafficSpaceUsageValue* self);

    void ecitygml_AuxiliaryTrafficSpaceUsageValue_destroy(AuxiliaryTrafficSpaceUsageValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::AuxiliaryTrafficSpaceUsageValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpaceUsageValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::AuxiliaryTrafficSpaceUsageValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpaceUsageValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::AuxiliaryTrafficSpaceUsageValue* ecitygml::AuxiliaryTrafficSpaceUsageValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AuxiliaryTrafficSpaceUsageValue*>(this);
}

inline ecitygml::capi::AuxiliaryTrafficSpaceUsageValue* ecitygml::AuxiliaryTrafficSpaceUsageValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AuxiliaryTrafficSpaceUsageValue*>(this);
}

inline const ecitygml::AuxiliaryTrafficSpaceUsageValue* ecitygml::AuxiliaryTrafficSpaceUsageValue::FromFFI(const ecitygml::capi::AuxiliaryTrafficSpaceUsageValue* ptr) {
    return reinterpret_cast<const ecitygml::AuxiliaryTrafficSpaceUsageValue*>(ptr);
}

inline ecitygml::AuxiliaryTrafficSpaceUsageValue* ecitygml::AuxiliaryTrafficSpaceUsageValue::FromFFI(ecitygml::capi::AuxiliaryTrafficSpaceUsageValue* ptr) {
    return reinterpret_cast<ecitygml::AuxiliaryTrafficSpaceUsageValue*>(ptr);
}

inline void ecitygml::AuxiliaryTrafficSpaceUsageValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AuxiliaryTrafficSpaceUsageValue_destroy(reinterpret_cast<ecitygml::capi::AuxiliaryTrafficSpaceUsageValue*>(ptr));
}


#endif // ECITYGML_AuxiliaryTrafficSpaceUsageValue_HPP
