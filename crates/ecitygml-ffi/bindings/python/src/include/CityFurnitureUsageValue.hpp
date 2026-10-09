#ifndef ECITYGML_CityFurnitureUsageValue_HPP
#define ECITYGML_CityFurnitureUsageValue_HPP

#include "CityFurnitureUsageValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_CityFurnitureUsageValue_code(const ecitygml::capi::CityFurnitureUsageValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_CityFurnitureUsageValue_value(const ecitygml::capi::CityFurnitureUsageValue* self);

    void ecitygml_CityFurnitureUsageValue_destroy(CityFurnitureUsageValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::CityFurnitureUsageValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurnitureUsageValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::CityFurnitureUsageValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurnitureUsageValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::CityFurnitureUsageValue* ecitygml::CityFurnitureUsageValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::CityFurnitureUsageValue*>(this);
}

inline ecitygml::capi::CityFurnitureUsageValue* ecitygml::CityFurnitureUsageValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::CityFurnitureUsageValue*>(this);
}

inline const ecitygml::CityFurnitureUsageValue* ecitygml::CityFurnitureUsageValue::FromFFI(const ecitygml::capi::CityFurnitureUsageValue* ptr) {
    return reinterpret_cast<const ecitygml::CityFurnitureUsageValue*>(ptr);
}

inline ecitygml::CityFurnitureUsageValue* ecitygml::CityFurnitureUsageValue::FromFFI(ecitygml::capi::CityFurnitureUsageValue* ptr) {
    return reinterpret_cast<ecitygml::CityFurnitureUsageValue*>(ptr);
}

inline void ecitygml::CityFurnitureUsageValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_CityFurnitureUsageValue_destroy(reinterpret_cast<ecitygml::capi::CityFurnitureUsageValue*>(ptr));
}


#endif // ECITYGML_CityFurnitureUsageValue_HPP
