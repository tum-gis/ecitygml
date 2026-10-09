#ifndef ECITYGML_SolitaryVegetationObjectUsageValue_HPP
#define ECITYGML_SolitaryVegetationObjectUsageValue_HPP

#include "SolitaryVegetationObjectUsageValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_SolitaryVegetationObjectUsageValue_code(const ecitygml::capi::SolitaryVegetationObjectUsageValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_SolitaryVegetationObjectUsageValue_value(const ecitygml::capi::SolitaryVegetationObjectUsageValue* self);

    void ecitygml_SolitaryVegetationObjectUsageValue_destroy(SolitaryVegetationObjectUsageValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::SolitaryVegetationObjectUsageValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObjectUsageValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::SolitaryVegetationObjectUsageValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SolitaryVegetationObjectUsageValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::SolitaryVegetationObjectUsageValue* ecitygml::SolitaryVegetationObjectUsageValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::SolitaryVegetationObjectUsageValue*>(this);
}

inline ecitygml::capi::SolitaryVegetationObjectUsageValue* ecitygml::SolitaryVegetationObjectUsageValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::SolitaryVegetationObjectUsageValue*>(this);
}

inline const ecitygml::SolitaryVegetationObjectUsageValue* ecitygml::SolitaryVegetationObjectUsageValue::FromFFI(const ecitygml::capi::SolitaryVegetationObjectUsageValue* ptr) {
    return reinterpret_cast<const ecitygml::SolitaryVegetationObjectUsageValue*>(ptr);
}

inline ecitygml::SolitaryVegetationObjectUsageValue* ecitygml::SolitaryVegetationObjectUsageValue::FromFFI(ecitygml::capi::SolitaryVegetationObjectUsageValue* ptr) {
    return reinterpret_cast<ecitygml::SolitaryVegetationObjectUsageValue*>(ptr);
}

inline void ecitygml::SolitaryVegetationObjectUsageValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_SolitaryVegetationObjectUsageValue_destroy(reinterpret_cast<ecitygml::capi::SolitaryVegetationObjectUsageValue*>(ptr));
}


#endif // ECITYGML_SolitaryVegetationObjectUsageValue_HPP
