#ifndef ECITYGML_PlantCoverFunctionValue_HPP
#define ECITYGML_PlantCoverFunctionValue_HPP

#include "PlantCoverFunctionValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_PlantCoverFunctionValue_code(const ecitygml::capi::PlantCoverFunctionValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_PlantCoverFunctionValue_value(const ecitygml::capi::PlantCoverFunctionValue* self);

    void ecitygml_PlantCoverFunctionValue_destroy(PlantCoverFunctionValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::PlantCoverFunctionValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCoverFunctionValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::PlantCoverFunctionValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCoverFunctionValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::PlantCoverFunctionValue* ecitygml::PlantCoverFunctionValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::PlantCoverFunctionValue*>(this);
}

inline ecitygml::capi::PlantCoverFunctionValue* ecitygml::PlantCoverFunctionValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::PlantCoverFunctionValue*>(this);
}

inline const ecitygml::PlantCoverFunctionValue* ecitygml::PlantCoverFunctionValue::FromFFI(const ecitygml::capi::PlantCoverFunctionValue* ptr) {
    return reinterpret_cast<const ecitygml::PlantCoverFunctionValue*>(ptr);
}

inline ecitygml::PlantCoverFunctionValue* ecitygml::PlantCoverFunctionValue::FromFFI(ecitygml::capi::PlantCoverFunctionValue* ptr) {
    return reinterpret_cast<ecitygml::PlantCoverFunctionValue*>(ptr);
}

inline void ecitygml::PlantCoverFunctionValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_PlantCoverFunctionValue_destroy(reinterpret_cast<ecitygml::capi::PlantCoverFunctionValue*>(ptr));
}


#endif // ECITYGML_PlantCoverFunctionValue_HPP
