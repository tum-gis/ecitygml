#ifndef ecitygml_StringAttribute_HPP
#define ecitygml_StringAttribute_HPP

#include "StringAttribute.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    diplomat::capi::DiplomatStringView ecitygml_StringAttribute_name(const ecitygml::capi::StringAttribute* self);

    diplomat::capi::DiplomatStringView ecitygml_StringAttribute_value(const ecitygml::capi::StringAttribute* self);

    void ecitygml_StringAttribute_destroy(StringAttribute* self);

    } // extern "C"
} // namespace capi
} // namespace

inline std::string_view ecitygml::StringAttribute::name() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_StringAttribute_name(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline std::string_view ecitygml::StringAttribute::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_StringAttribute_value(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::StringAttribute* ecitygml::StringAttribute::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::StringAttribute*>(this);
}

inline ecitygml::capi::StringAttribute* ecitygml::StringAttribute::AsFFI() {
    return reinterpret_cast<ecitygml::capi::StringAttribute*>(this);
}

inline const ecitygml::StringAttribute* ecitygml::StringAttribute::FromFFI(const ecitygml::capi::StringAttribute* ptr) {
    return reinterpret_cast<const ecitygml::StringAttribute*>(ptr);
}

inline ecitygml::StringAttribute* ecitygml::StringAttribute::FromFFI(ecitygml::capi::StringAttribute* ptr) {
    return reinterpret_cast<ecitygml::StringAttribute*>(ptr);
}

inline void ecitygml::StringAttribute::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_StringAttribute_destroy(reinterpret_cast<ecitygml::capi::StringAttribute*>(ptr));
}


#endif // ecitygml_StringAttribute_HPP
