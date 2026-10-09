#ifndef ECITYGML_BuildingSubdivisionUsageValue_HPP
#define ECITYGML_BuildingSubdivisionUsageValue_HPP

#include "BuildingSubdivisionUsageValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_BuildingSubdivisionUsageValue_code(const ecitygml::capi::BuildingSubdivisionUsageValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_BuildingSubdivisionUsageValue_value(const ecitygml::capi::BuildingSubdivisionUsageValue* self);

    void ecitygml_BuildingSubdivisionUsageValue_destroy(BuildingSubdivisionUsageValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::BuildingSubdivisionUsageValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingSubdivisionUsageValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::BuildingSubdivisionUsageValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingSubdivisionUsageValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::BuildingSubdivisionUsageValue* ecitygml::BuildingSubdivisionUsageValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::BuildingSubdivisionUsageValue*>(this);
}

inline ecitygml::capi::BuildingSubdivisionUsageValue* ecitygml::BuildingSubdivisionUsageValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::BuildingSubdivisionUsageValue*>(this);
}

inline const ecitygml::BuildingSubdivisionUsageValue* ecitygml::BuildingSubdivisionUsageValue::FromFFI(const ecitygml::capi::BuildingSubdivisionUsageValue* ptr) {
    return reinterpret_cast<const ecitygml::BuildingSubdivisionUsageValue*>(ptr);
}

inline ecitygml::BuildingSubdivisionUsageValue* ecitygml::BuildingSubdivisionUsageValue::FromFFI(ecitygml::capi::BuildingSubdivisionUsageValue* ptr) {
    return reinterpret_cast<ecitygml::BuildingSubdivisionUsageValue*>(ptr);
}

inline void ecitygml::BuildingSubdivisionUsageValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_BuildingSubdivisionUsageValue_destroy(reinterpret_cast<ecitygml::capi::BuildingSubdivisionUsageValue*>(ptr));
}


#endif // ECITYGML_BuildingSubdivisionUsageValue_HPP
