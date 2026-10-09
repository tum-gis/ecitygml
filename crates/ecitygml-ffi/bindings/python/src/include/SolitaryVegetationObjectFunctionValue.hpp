#ifndef ECITYGML_SolitaryVegetationObjectFunctionValue_HPP
#define ECITYGML_SolitaryVegetationObjectFunctionValue_HPP

#include "SolitaryVegetationObjectFunctionValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_SolitaryVegetationObjectFunctionValue_code(const ecitygml::capi::SolitaryVegetationObjectFunctionValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_SolitaryVegetationObjectFunctionValue_value(const ecitygml::capi::SolitaryVegetationObjectFunctionValue* self);

    void ecitygml_SolitaryVegetationObjectFunctionValue_destroy(SolitaryVegetationObjectFunctionValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::SolitaryVegetationObjectFunctionValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObjectFunctionValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::SolitaryVegetationObjectFunctionValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObjectFunctionValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::SolitaryVegetationObjectFunctionValue* ecitygml::SolitaryVegetationObjectFunctionValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::SolitaryVegetationObjectFunctionValue*>(this);
}

inline ecitygml::capi::SolitaryVegetationObjectFunctionValue* ecitygml::SolitaryVegetationObjectFunctionValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::SolitaryVegetationObjectFunctionValue*>(this);
}

inline const ecitygml::SolitaryVegetationObjectFunctionValue* ecitygml::SolitaryVegetationObjectFunctionValue::FromFFI(const ecitygml::capi::SolitaryVegetationObjectFunctionValue* ptr) {
    return reinterpret_cast<const ecitygml::SolitaryVegetationObjectFunctionValue*>(ptr);
}

inline ecitygml::SolitaryVegetationObjectFunctionValue* ecitygml::SolitaryVegetationObjectFunctionValue::FromFFI(ecitygml::capi::SolitaryVegetationObjectFunctionValue* ptr) {
    return reinterpret_cast<ecitygml::SolitaryVegetationObjectFunctionValue*>(ptr);
}

inline void ecitygml::SolitaryVegetationObjectFunctionValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_SolitaryVegetationObjectFunctionValue_destroy(reinterpret_cast<ecitygml::capi::SolitaryVegetationObjectFunctionValue*>(ptr));
}


#endif // ECITYGML_SolitaryVegetationObjectFunctionValue_HPP
