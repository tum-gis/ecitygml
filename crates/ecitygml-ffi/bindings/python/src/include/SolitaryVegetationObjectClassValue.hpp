#ifndef ECITYGML_SolitaryVegetationObjectClassValue_HPP
#define ECITYGML_SolitaryVegetationObjectClassValue_HPP

#include "SolitaryVegetationObjectClassValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_SolitaryVegetationObjectClassValue_code(const ecitygml::capi::SolitaryVegetationObjectClassValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_SolitaryVegetationObjectClassValue_value(const ecitygml::capi::SolitaryVegetationObjectClassValue* self);

    void ecitygml_SolitaryVegetationObjectClassValue_destroy(SolitaryVegetationObjectClassValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::SolitaryVegetationObjectClassValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObjectClassValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::SolitaryVegetationObjectClassValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObjectClassValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::SolitaryVegetationObjectClassValue* ecitygml::SolitaryVegetationObjectClassValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::SolitaryVegetationObjectClassValue*>(this);
}

inline ecitygml::capi::SolitaryVegetationObjectClassValue* ecitygml::SolitaryVegetationObjectClassValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::SolitaryVegetationObjectClassValue*>(this);
}

inline const ecitygml::SolitaryVegetationObjectClassValue* ecitygml::SolitaryVegetationObjectClassValue::FromFFI(const ecitygml::capi::SolitaryVegetationObjectClassValue* ptr) {
    return reinterpret_cast<const ecitygml::SolitaryVegetationObjectClassValue*>(ptr);
}

inline ecitygml::SolitaryVegetationObjectClassValue* ecitygml::SolitaryVegetationObjectClassValue::FromFFI(ecitygml::capi::SolitaryVegetationObjectClassValue* ptr) {
    return reinterpret_cast<ecitygml::SolitaryVegetationObjectClassValue*>(ptr);
}

inline void ecitygml::SolitaryVegetationObjectClassValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_SolitaryVegetationObjectClassValue_destroy(reinterpret_cast<ecitygml::capi::SolitaryVegetationObjectClassValue*>(ptr));
}


#endif // ECITYGML_SolitaryVegetationObjectClassValue_HPP
