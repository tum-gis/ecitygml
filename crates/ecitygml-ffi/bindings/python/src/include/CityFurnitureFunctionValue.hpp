#ifndef ECITYGML_CityFurnitureFunctionValue_HPP
#define ECITYGML_CityFurnitureFunctionValue_HPP

#include "CityFurnitureFunctionValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_CityFurnitureFunctionValue_code(const ecitygml::capi::CityFurnitureFunctionValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_CityFurnitureFunctionValue_value(const ecitygml::capi::CityFurnitureFunctionValue* self);

    void ecitygml_CityFurnitureFunctionValue_destroy(CityFurnitureFunctionValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::CityFurnitureFunctionValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurnitureFunctionValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::CityFurnitureFunctionValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityFurnitureFunctionValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::CityFurnitureFunctionValue* ecitygml::CityFurnitureFunctionValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::CityFurnitureFunctionValue*>(this);
}

inline ecitygml::capi::CityFurnitureFunctionValue* ecitygml::CityFurnitureFunctionValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::CityFurnitureFunctionValue*>(this);
}

inline const ecitygml::CityFurnitureFunctionValue* ecitygml::CityFurnitureFunctionValue::FromFFI(const ecitygml::capi::CityFurnitureFunctionValue* ptr) {
    return reinterpret_cast<const ecitygml::CityFurnitureFunctionValue*>(ptr);
}

inline ecitygml::CityFurnitureFunctionValue* ecitygml::CityFurnitureFunctionValue::FromFFI(ecitygml::capi::CityFurnitureFunctionValue* ptr) {
    return reinterpret_cast<ecitygml::CityFurnitureFunctionValue*>(ptr);
}

inline void ecitygml::CityFurnitureFunctionValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_CityFurnitureFunctionValue_destroy(reinterpret_cast<ecitygml::capi::CityFurnitureFunctionValue*>(ptr));
}


#endif // ECITYGML_CityFurnitureFunctionValue_HPP
