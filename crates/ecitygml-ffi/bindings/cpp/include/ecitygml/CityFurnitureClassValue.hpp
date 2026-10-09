#ifndef ecitygml_CityFurnitureClassValue_HPP
#define ecitygml_CityFurnitureClassValue_HPP

#include "CityFurnitureClassValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_CityFurnitureClassValue_code(const ecitygml::capi::CityFurnitureClassValue* self);

    diplomat::capi::DiplomatStringView ecitygml_CityFurnitureClassValue_value(const ecitygml::capi::CityFurnitureClassValue* self);

    void ecitygml_CityFurnitureClassValue_destroy(CityFurnitureClassValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::CityFurnitureClassValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurnitureClassValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::CityFurnitureClassValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurnitureClassValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::CityFurnitureClassValue* ecitygml::CityFurnitureClassValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::CityFurnitureClassValue*>(this);
}

inline ecitygml::capi::CityFurnitureClassValue* ecitygml::CityFurnitureClassValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::CityFurnitureClassValue*>(this);
}

inline const ecitygml::CityFurnitureClassValue* ecitygml::CityFurnitureClassValue::FromFFI(const ecitygml::capi::CityFurnitureClassValue* ptr) {
    return reinterpret_cast<const ecitygml::CityFurnitureClassValue*>(ptr);
}

inline ecitygml::CityFurnitureClassValue* ecitygml::CityFurnitureClassValue::FromFFI(ecitygml::capi::CityFurnitureClassValue* ptr) {
    return reinterpret_cast<ecitygml::CityFurnitureClassValue*>(ptr);
}

inline void ecitygml::CityFurnitureClassValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_CityFurnitureClassValue_destroy(reinterpret_cast<ecitygml::capi::CityFurnitureClassValue*>(ptr));
}


#endif // ecitygml_CityFurnitureClassValue_HPP
