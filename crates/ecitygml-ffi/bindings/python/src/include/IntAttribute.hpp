#ifndef ECITYGML_IntAttribute_HPP
#define ECITYGML_IntAttribute_HPP

#include "IntAttribute.d.hpp"

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

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_IntAttribute_name(const ecitygml::capi::IntAttribute* self);

    int64_t ecitygml_IntAttribute_value(const ecitygml::capi::IntAttribute* self);

    void ecitygml_IntAttribute_destroy(IntAttribute* self);

    } // extern "C"
} // namespace capi
} // namespace

inline std::string_view ecitygml::IntAttribute::name() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_IntAttribute_name(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline int64_t ecitygml::IntAttribute::value() const {
    auto result = ecitygml::capi::ecitygml_IntAttribute_value(this->AsFFI());
    return result;
}

inline const ecitygml::capi::IntAttribute* ecitygml::IntAttribute::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::IntAttribute*>(this);
}

inline ecitygml::capi::IntAttribute* ecitygml::IntAttribute::AsFFI() {
    return reinterpret_cast<ecitygml::capi::IntAttribute*>(this);
}

inline const ecitygml::IntAttribute* ecitygml::IntAttribute::FromFFI(const ecitygml::capi::IntAttribute* ptr) {
    return reinterpret_cast<const ecitygml::IntAttribute*>(ptr);
}

inline ecitygml::IntAttribute* ecitygml::IntAttribute::FromFFI(ecitygml::capi::IntAttribute* ptr) {
    return reinterpret_cast<ecitygml::IntAttribute*>(ptr);
}

inline void ecitygml::IntAttribute::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_IntAttribute_destroy(reinterpret_cast<ecitygml::capi::IntAttribute*>(ptr));
}


#endif // ECITYGML_IntAttribute_HPP
