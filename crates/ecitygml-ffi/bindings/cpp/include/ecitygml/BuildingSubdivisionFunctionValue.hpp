#ifndef ecitygml_BuildingSubdivisionFunctionValue_HPP
#define ecitygml_BuildingSubdivisionFunctionValue_HPP

#include "BuildingSubdivisionFunctionValue.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "Code.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Code* ecitygml_BuildingSubdivisionFunctionValue_code(const ecitygml::capi::BuildingSubdivisionFunctionValue* self);

    diplomat::capi::DiplomatStringView ecitygml_BuildingSubdivisionFunctionValue_value(const ecitygml::capi::BuildingSubdivisionFunctionValue* self);

    void ecitygml_BuildingSubdivisionFunctionValue_destroy(BuildingSubdivisionFunctionValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::BuildingSubdivisionFunctionValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingSubdivisionFunctionValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::BuildingSubdivisionFunctionValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingSubdivisionFunctionValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::BuildingSubdivisionFunctionValue* ecitygml::BuildingSubdivisionFunctionValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::BuildingSubdivisionFunctionValue*>(this);
}

inline ecitygml::capi::BuildingSubdivisionFunctionValue* ecitygml::BuildingSubdivisionFunctionValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::BuildingSubdivisionFunctionValue*>(this);
}

inline const ecitygml::BuildingSubdivisionFunctionValue* ecitygml::BuildingSubdivisionFunctionValue::FromFFI(const ecitygml::capi::BuildingSubdivisionFunctionValue* ptr) {
    return reinterpret_cast<const ecitygml::BuildingSubdivisionFunctionValue*>(ptr);
}

inline ecitygml::BuildingSubdivisionFunctionValue* ecitygml::BuildingSubdivisionFunctionValue::FromFFI(ecitygml::capi::BuildingSubdivisionFunctionValue* ptr) {
    return reinterpret_cast<ecitygml::BuildingSubdivisionFunctionValue*>(ptr);
}

inline void ecitygml::BuildingSubdivisionFunctionValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_BuildingSubdivisionFunctionValue_destroy(reinterpret_cast<ecitygml::capi::BuildingSubdivisionFunctionValue*>(ptr));
}


#endif // ecitygml_BuildingSubdivisionFunctionValue_HPP
