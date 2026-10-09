#ifndef ECITYGML_DoubleAttribute_HPP
#define ECITYGML_DoubleAttribute_HPP

#include "DoubleAttribute.d.hpp"

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

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_DoubleAttribute_name(const ecitygml::capi::DoubleAttribute* self);

    double ecitygml_DoubleAttribute_value(const ecitygml::capi::DoubleAttribute* self);

    void ecitygml_DoubleAttribute_destroy(DoubleAttribute* self);

    } // extern "C"
} // namespace capi
} // namespace

inline std::string_view ecitygml::DoubleAttribute::name() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_DoubleAttribute_name(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline double ecitygml::DoubleAttribute::value() const {
    auto result = ecitygml::capi::ecitygml_DoubleAttribute_value(this->AsFFI());
    return result;
}

inline const ecitygml::capi::DoubleAttribute* ecitygml::DoubleAttribute::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::DoubleAttribute*>(this);
}

inline ecitygml::capi::DoubleAttribute* ecitygml::DoubleAttribute::AsFFI() {
    return reinterpret_cast<ecitygml::capi::DoubleAttribute*>(this);
}

inline const ecitygml::DoubleAttribute* ecitygml::DoubleAttribute::FromFFI(const ecitygml::capi::DoubleAttribute* ptr) {
    return reinterpret_cast<const ecitygml::DoubleAttribute*>(ptr);
}

inline ecitygml::DoubleAttribute* ecitygml::DoubleAttribute::FromFFI(ecitygml::capi::DoubleAttribute* ptr) {
    return reinterpret_cast<ecitygml::DoubleAttribute*>(ptr);
}

inline void ecitygml::DoubleAttribute::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_DoubleAttribute_destroy(reinterpret_cast<ecitygml::capi::DoubleAttribute*>(ptr));
}


#endif // ECITYGML_DoubleAttribute_HPP
