#ifndef ecitygml_Height_HPP
#define ecitygml_Height_HPP

#include "Height.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "ElevationReferenceValue.hpp"
#include "HeightStatusValue.hpp"
#include "Length.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::ElevationReferenceValue* ecitygml_Height_high_reference(const ecitygml::capi::Height* self);

    const ecitygml::capi::ElevationReferenceValue* ecitygml_Height_low_reference(const ecitygml::capi::Height* self);

    ecitygml::capi::HeightStatusValue ecitygml_Height_status(const ecitygml::capi::Height* self);

    const ecitygml::capi::Length* ecitygml_Height_length(const ecitygml::capi::Height* self);

    void ecitygml_Height_destroy(Height* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::ElevationReferenceValue& ecitygml::Height::high_reference() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Height_high_reference(this->AsFFI());
    return *ecitygml::ElevationReferenceValue::FromFFI(result);
}

inline const ecitygml::ElevationReferenceValue& ecitygml::Height::low_reference() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Height_low_reference(this->AsFFI());
    return *ecitygml::ElevationReferenceValue::FromFFI(result);
}

inline ecitygml::HeightStatusValue ecitygml::Height::status() const {
    auto result = ecitygml::capi::ecitygml_Height_status(this->AsFFI());
    return ecitygml::HeightStatusValue::FromFFI(result);
}

inline const ecitygml::Length& ecitygml::Height::length() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Height_length(this->AsFFI());
    return *ecitygml::Length::FromFFI(result);
}

inline const ecitygml::capi::Height* ecitygml::Height::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::Height*>(this);
}

inline ecitygml::capi::Height* ecitygml::Height::AsFFI() {
    return reinterpret_cast<ecitygml::capi::Height*>(this);
}

inline const ecitygml::Height* ecitygml::Height::FromFFI(const ecitygml::capi::Height* ptr) {
    return reinterpret_cast<const ecitygml::Height*>(ptr);
}

inline ecitygml::Height* ecitygml::Height::FromFFI(ecitygml::capi::Height* ptr) {
    return reinterpret_cast<ecitygml::Height*>(ptr);
}

inline void ecitygml::Height::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_Height_destroy(reinterpret_cast<ecitygml::capi::Height*>(ptr));
}


#endif // ecitygml_Height_HPP
