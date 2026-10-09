#ifndef ECITYGML_SpeciesValue_HPP
#define ECITYGML_SpeciesValue_HPP

#include "SpeciesValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_SpeciesValue_code(const ecitygml::capi::SpeciesValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_SpeciesValue_value(const ecitygml::capi::SpeciesValue* self);

    void ecitygml_SpeciesValue_destroy(SpeciesValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::SpeciesValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SpeciesValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::SpeciesValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SpeciesValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::SpeciesValue* ecitygml::SpeciesValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::SpeciesValue*>(this);
}

inline ecitygml::capi::SpeciesValue* ecitygml::SpeciesValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::SpeciesValue*>(this);
}

inline const ecitygml::SpeciesValue* ecitygml::SpeciesValue::FromFFI(const ecitygml::capi::SpeciesValue* ptr) {
    return reinterpret_cast<const ecitygml::SpeciesValue*>(ptr);
}

inline ecitygml::SpeciesValue* ecitygml::SpeciesValue::FromFFI(ecitygml::capi::SpeciesValue* ptr) {
    return reinterpret_cast<ecitygml::SpeciesValue*>(ptr);
}

inline void ecitygml::SpeciesValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_SpeciesValue_destroy(reinterpret_cast<ecitygml::capi::SpeciesValue*>(ptr));
}


#endif // ECITYGML_SpeciesValue_HPP
