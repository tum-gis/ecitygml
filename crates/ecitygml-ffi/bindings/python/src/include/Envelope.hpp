#ifndef ECITYGML_Envelope_HPP
#define ECITYGML_Envelope_HPP

#include "Envelope.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "DirectPosition.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::DirectPosition* ecitygml_Envelope_lower_corner(const ecitygml::capi::Envelope* self);

    const ecitygml::capi::DirectPosition* ecitygml_Envelope_upper_corner(const ecitygml::capi::Envelope* self);

    double ecitygml_Envelope_size_x(const ecitygml::capi::Envelope* self);

    double ecitygml_Envelope_size_y(const ecitygml::capi::Envelope* self);

    double ecitygml_Envelope_size_z(const ecitygml::capi::Envelope* self);

    double ecitygml_Envelope_volume(const ecitygml::capi::Envelope* self);

    bool ecitygml_Envelope_contains(const ecitygml::capi::Envelope* self, const ecitygml::capi::DirectPosition* point);

    void ecitygml_Envelope_destroy(Envelope* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::DirectPosition& ecitygml::Envelope::lower_corner() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Envelope_lower_corner(this->AsFFI());
    return *ecitygml::DirectPosition::FromFFI(result);
}

inline const ecitygml::DirectPosition& ecitygml::Envelope::upper_corner() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Envelope_upper_corner(this->AsFFI());
    return *ecitygml::DirectPosition::FromFFI(result);
}

inline double ecitygml::Envelope::size_x() const {
    auto result = ecitygml::capi::ecitygml_Envelope_size_x(this->AsFFI());
    return result;
}

inline double ecitygml::Envelope::size_y() const {
    auto result = ecitygml::capi::ecitygml_Envelope_size_y(this->AsFFI());
    return result;
}

inline double ecitygml::Envelope::size_z() const {
    auto result = ecitygml::capi::ecitygml_Envelope_size_z(this->AsFFI());
    return result;
}

inline double ecitygml::Envelope::volume() const {
    auto result = ecitygml::capi::ecitygml_Envelope_volume(this->AsFFI());
    return result;
}

inline bool ecitygml::Envelope::contains(const ecitygml::DirectPosition& point) const {
    auto result = ecitygml::capi::ecitygml_Envelope_contains(this->AsFFI(),
        point.AsFFI());
    return result;
}

inline const ecitygml::capi::Envelope* ecitygml::Envelope::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::Envelope*>(this);
}

inline ecitygml::capi::Envelope* ecitygml::Envelope::AsFFI() {
    return reinterpret_cast<ecitygml::capi::Envelope*>(this);
}

inline const ecitygml::Envelope* ecitygml::Envelope::FromFFI(const ecitygml::capi::Envelope* ptr) {
    return reinterpret_cast<const ecitygml::Envelope*>(ptr);
}

inline ecitygml::Envelope* ecitygml::Envelope::FromFFI(ecitygml::capi::Envelope* ptr) {
    return reinterpret_cast<ecitygml::Envelope*>(ptr);
}

inline void ecitygml::Envelope::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_Envelope_destroy(reinterpret_cast<ecitygml::capi::Envelope*>(ptr));
}


#endif // ECITYGML_Envelope_HPP
