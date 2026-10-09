#ifndef ecitygml_BuildingClassValue_HPP
#define ecitygml_BuildingClassValue_HPP

#include "BuildingClassValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_BuildingClassValue_code(const ecitygml::capi::BuildingClassValue* self);

    diplomat::capi::DiplomatStringView ecitygml_BuildingClassValue_value(const ecitygml::capi::BuildingClassValue* self);

    void ecitygml_BuildingClassValue_destroy(BuildingClassValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::BuildingClassValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingClassValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::BuildingClassValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingClassValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::BuildingClassValue* ecitygml::BuildingClassValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::BuildingClassValue*>(this);
}

inline ecitygml::capi::BuildingClassValue* ecitygml::BuildingClassValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::BuildingClassValue*>(this);
}

inline const ecitygml::BuildingClassValue* ecitygml::BuildingClassValue::FromFFI(const ecitygml::capi::BuildingClassValue* ptr) {
    return reinterpret_cast<const ecitygml::BuildingClassValue*>(ptr);
}

inline ecitygml::BuildingClassValue* ecitygml::BuildingClassValue::FromFFI(ecitygml::capi::BuildingClassValue* ptr) {
    return reinterpret_cast<ecitygml::BuildingClassValue*>(ptr);
}

inline void ecitygml::BuildingClassValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_BuildingClassValue_destroy(reinterpret_cast<ecitygml::capi::BuildingClassValue*>(ptr));
}


#endif // ecitygml_BuildingClassValue_HPP
