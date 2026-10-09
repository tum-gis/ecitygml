#ifndef ECITYGML_BuildingFunctionValue_HPP
#define ECITYGML_BuildingFunctionValue_HPP

#include "BuildingFunctionValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_BuildingFunctionValue_code(const ecitygml::capi::BuildingFunctionValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_BuildingFunctionValue_value(const ecitygml::capi::BuildingFunctionValue* self);

    void ecitygml_BuildingFunctionValue_destroy(BuildingFunctionValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::BuildingFunctionValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingFunctionValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::BuildingFunctionValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingFunctionValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::BuildingFunctionValue* ecitygml::BuildingFunctionValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::BuildingFunctionValue*>(this);
}

inline ecitygml::capi::BuildingFunctionValue* ecitygml::BuildingFunctionValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::BuildingFunctionValue*>(this);
}

inline const ecitygml::BuildingFunctionValue* ecitygml::BuildingFunctionValue::FromFFI(const ecitygml::capi::BuildingFunctionValue* ptr) {
    return reinterpret_cast<const ecitygml::BuildingFunctionValue*>(ptr);
}

inline ecitygml::BuildingFunctionValue* ecitygml::BuildingFunctionValue::FromFFI(ecitygml::capi::BuildingFunctionValue* ptr) {
    return reinterpret_cast<ecitygml::BuildingFunctionValue*>(ptr);
}

inline void ecitygml::BuildingFunctionValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_BuildingFunctionValue_destroy(reinterpret_cast<ecitygml::capi::BuildingFunctionValue*>(ptr));
}


#endif // ECITYGML_BuildingFunctionValue_HPP
