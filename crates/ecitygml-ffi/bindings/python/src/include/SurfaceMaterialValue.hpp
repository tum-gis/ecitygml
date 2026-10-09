#ifndef ECITYGML_SurfaceMaterialValue_HPP
#define ECITYGML_SurfaceMaterialValue_HPP

#include "SurfaceMaterialValue.d.hpp"

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

    const ecitygml::capi::Code* ecitygml_SurfaceMaterialValue_code(const ecitygml::capi::SurfaceMaterialValue* self);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_SurfaceMaterialValue_value(const ecitygml::capi::SurfaceMaterialValue* self);

    void ecitygml_SurfaceMaterialValue_destroy(SurfaceMaterialValue* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code& ecitygml::SurfaceMaterialValue::code() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SurfaceMaterialValue_code(this->AsFFI());
    return *ecitygml::Code::FromFFI(result);
}

inline std::string_view ecitygml::SurfaceMaterialValue::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SurfaceMaterialValue_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::SurfaceMaterialValue* ecitygml::SurfaceMaterialValue::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::SurfaceMaterialValue*>(this);
}

inline ecitygml::capi::SurfaceMaterialValue* ecitygml::SurfaceMaterialValue::AsFFI() {
    return reinterpret_cast<ecitygml::capi::SurfaceMaterialValue*>(this);
}

inline const ecitygml::SurfaceMaterialValue* ecitygml::SurfaceMaterialValue::FromFFI(const ecitygml::capi::SurfaceMaterialValue* ptr) {
    return reinterpret_cast<const ecitygml::SurfaceMaterialValue*>(ptr);
}

inline ecitygml::SurfaceMaterialValue* ecitygml::SurfaceMaterialValue::FromFFI(ecitygml::capi::SurfaceMaterialValue* ptr) {
    return reinterpret_cast<ecitygml::SurfaceMaterialValue*>(ptr);
}

inline void ecitygml::SurfaceMaterialValue::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_SurfaceMaterialValue_destroy(reinterpret_cast<ecitygml::capi::SurfaceMaterialValue*>(ptr));
}


#endif // ECITYGML_SurfaceMaterialValue_HPP
