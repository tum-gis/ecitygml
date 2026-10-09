#ifndef ecitygml_Length_HPP
#define ecitygml_Length_HPP

#include "Length.d.hpp"

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

    double ecitygml_Length_value(const ecitygml::capi::Length* self);

    diplomat::capi::DiplomatStringView ecitygml_Length_uom(const ecitygml::capi::Length* self);

    void ecitygml_Length_destroy(Length* self);

    } // extern "C"
} // namespace capi
} // namespace

inline double ecitygml::Length::value() const {
    auto result = ecitygml::capi::ecitygml_Length_value(this->AsFFI());
    return result;
}

inline std::string_view ecitygml::Length::uom() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Length_uom(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::Length* ecitygml::Length::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::Length*>(this);
}

inline ecitygml::capi::Length* ecitygml::Length::AsFFI() {
    return reinterpret_cast<ecitygml::capi::Length*>(this);
}

inline const ecitygml::Length* ecitygml::Length::FromFFI(const ecitygml::capi::Length* ptr) {
    return reinterpret_cast<const ecitygml::Length*>(ptr);
}

inline ecitygml::Length* ecitygml::Length::FromFFI(ecitygml::capi::Length* ptr) {
    return reinterpret_cast<ecitygml::Length*>(ptr);
}

inline void ecitygml::Length::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_Length_destroy(reinterpret_cast<ecitygml::capi::Length*>(ptr));
}


#endif // ecitygml_Length_HPP
