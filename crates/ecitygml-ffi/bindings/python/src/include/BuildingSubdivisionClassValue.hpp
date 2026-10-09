#ifndef ECITYGML_BuildingSubdivisionClassValue_HPP
#define ECITYGML_BuildingSubdivisionClassValue_HPP

#include "BuildingSubdivisionClassValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_BuildingSubdivisionClassValue_code(const ecitygml::capi::BuildingSubdivisionClassValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_BuildingSubdivisionClassValue_value(const ecitygml::capi::BuildingSubdivisionClassValue* self);

    void ecitygml_BuildingSubdivisionClassValue_destroy(BuildingSubdivisionClassValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::BuildingSubdivisionClassValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingSubdivisionClassValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::BuildingSubdivisionClassValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingSubdivisionClassValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::BuildingSubdivisionClassValue* ecitygml::BuildingSubdivisionClassValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::BuildingSubdivisionClassValue*>(this);
}

inline ecitygml::capi::BuildingSubdivisionClassValue* ecitygml::BuildingSubdivisionClassValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::BuildingSubdivisionClassValue*>(this);
}

inline const ecitygml::BuildingSubdivisionClassValue* ecitygml::BuildingSubdivisionClassValue::FromFFI(const ecitygml::capi::BuildingSubdivisionClassValue* ptr) {
    return reinterpret_cast<const ecitygml::BuildingSubdivisionClassValue*>(ptr);
}

inline ecitygml::BuildingSubdivisionClassValue* ecitygml::BuildingSubdivisionClassValue::FromFFI(ecitygml::capi::BuildingSubdivisionClassValue* ptr) {
    return reinterpret_cast<ecitygml::BuildingSubdivisionClassValue*>(ptr);
}

inline void ecitygml::BuildingSubdivisionClassValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_BuildingSubdivisionClassValue_destroy(reinterpret_cast<ecitygml::capi::BuildingSubdivisionClassValue*>(ptr));
}


#endif // ECITYGML_BuildingSubdivisionClassValue_HPP
