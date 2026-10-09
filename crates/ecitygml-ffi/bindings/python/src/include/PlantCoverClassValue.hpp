#ifndef ECITYGML_PlantCoverClassValue_HPP
#define ECITYGML_PlantCoverClassValue_HPP

#include "PlantCoverClassValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_PlantCoverClassValue_code(const ecitygml::capi::PlantCoverClassValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_PlantCoverClassValue_value(const ecitygml::capi::PlantCoverClassValue* self);

    void ecitygml_PlantCoverClassValue_destroy(PlantCoverClassValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::PlantCoverClassValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCoverClassValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::PlantCoverClassValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PlantCoverClassValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::PlantCoverClassValue* ecitygml::PlantCoverClassValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::PlantCoverClassValue*>(this);
}

inline ecitygml::capi::PlantCoverClassValue* ecitygml::PlantCoverClassValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::PlantCoverClassValue*>(this);
}

inline const ecitygml::PlantCoverClassValue* ecitygml::PlantCoverClassValue::FromFFI(const ecitygml::capi::PlantCoverClassValue* ptr) {
    return reinterpret_cast<const ecitygml::PlantCoverClassValue*>(ptr);
}

inline ecitygml::PlantCoverClassValue* ecitygml::PlantCoverClassValue::FromFFI(ecitygml::capi::PlantCoverClassValue* ptr) {
    return reinterpret_cast<ecitygml::PlantCoverClassValue*>(ptr);
}

inline void ecitygml::PlantCoverClassValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_PlantCoverClassValue_destroy(reinterpret_cast<ecitygml::capi::PlantCoverClassValue*>(ptr));
}


#endif // ECITYGML_PlantCoverClassValue_HPP
