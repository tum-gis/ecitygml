#ifndef ECITYGML_Id_HPP
#define ECITYGML_Id_HPP

#include "Id.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_Id_as_str(const ecitygml::capi::Id* self);

    void ecitygml_Id_destroy(Id* self);

    } // extern "C"
} // namespace capi
} // namespace

inline std::string_view ecitygml::Id::as_str() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Id_as_str(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::Id* ecitygml::Id::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::Id*>(this);
}

inline ecitygml::capi::Id* ecitygml::Id::AsFFI() {
    return reinterpret_cast<ecitygml::capi::Id*>(this);
}

inline const ecitygml::Id* ecitygml::Id::FromFFI(const ecitygml::capi::Id* ptr) {
    return reinterpret_cast<const ecitygml::Id*>(ptr);
}

inline ecitygml::Id* ecitygml::Id::FromFFI(ecitygml::capi::Id* ptr) {
    return reinterpret_cast<ecitygml::Id*>(ptr);
}

inline void ecitygml::Id::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_Id_destroy(reinterpret_cast<ecitygml::capi::Id*>(ptr));
}


#endif // ECITYGML_Id_HPP
