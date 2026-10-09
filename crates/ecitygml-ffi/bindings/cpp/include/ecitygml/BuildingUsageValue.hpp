#ifndef ecitygml_BuildingUsageValue_HPP
#define ecitygml_BuildingUsageValue_HPP

#include "BuildingUsageValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_BuildingUsageValue_code(const ecitygml::capi::BuildingUsageValue* self);

    diplomat::capi::DiplomatStringView ecitygml_BuildingUsageValue_value(const ecitygml::capi::BuildingUsageValue* self);

    void ecitygml_BuildingUsageValue_destroy(BuildingUsageValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::BuildingUsageValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingUsageValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::BuildingUsageValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingUsageValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::BuildingUsageValue* ecitygml::BuildingUsageValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::BuildingUsageValue*>(this);
}

inline ecitygml::capi::BuildingUsageValue* ecitygml::BuildingUsageValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::BuildingUsageValue*>(this);
}

inline const ecitygml::BuildingUsageValue* ecitygml::BuildingUsageValue::FromFFI(const ecitygml::capi::BuildingUsageValue* ptr) {
    return reinterpret_cast<const ecitygml::BuildingUsageValue*>(ptr);
}

inline ecitygml::BuildingUsageValue* ecitygml::BuildingUsageValue::FromFFI(ecitygml::capi::BuildingUsageValue* ptr) {
    return reinterpret_cast<ecitygml::BuildingUsageValue*>(ptr);
}

inline void ecitygml::BuildingUsageValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_BuildingUsageValue_destroy(reinterpret_cast<ecitygml::capi::BuildingUsageValue*>(ptr));
}


#endif // ecitygml_BuildingUsageValue_HPP
