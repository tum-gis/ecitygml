#ifndef ecitygml_Measure_HPP
#define ecitygml_Measure_HPP

#include "Measure.d.hpp"

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

    double ecitygml_Measure_value(const ecitygml::capi::Measure* self);

    diplomat::capi::DiplomatStringView ecitygml_Measure_uom(const ecitygml::capi::Measure* self);

    void ecitygml_Measure_destroy(Measure* self);

    } // extern "C"
} // namespace capi
} // namespace

inline double ecitygml::Measure::value() const {
    auto result = ecitygml::capi::ecitygml_Measure_value(this->AsFFI());
    return result;
}

inline std::string_view ecitygml::Measure::uom() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Measure_uom(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::capi::Measure* ecitygml::Measure::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::Measure*>(this);
}

inline ecitygml::capi::Measure* ecitygml::Measure::AsFFI() {
    return reinterpret_cast<ecitygml::capi::Measure*>(this);
}

inline const ecitygml::Measure* ecitygml::Measure::FromFFI(const ecitygml::capi::Measure* ptr) {
    return reinterpret_cast<const ecitygml::Measure*>(ptr);
}

inline ecitygml::Measure* ecitygml::Measure::FromFFI(ecitygml::capi::Measure* ptr) {
    return reinterpret_cast<ecitygml::Measure*>(ptr);
}

inline void ecitygml::Measure::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_Measure_destroy(reinterpret_cast<ecitygml::capi::Measure*>(ptr));
}


#endif // ecitygml_Measure_HPP
