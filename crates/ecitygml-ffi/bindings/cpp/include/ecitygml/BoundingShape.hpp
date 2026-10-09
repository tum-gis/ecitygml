#ifndef ecitygml_BoundingShape_HPP
#define ecitygml_BoundingShape_HPP

#include "BoundingShape.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "Envelope.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Envelope* ecitygml_BoundingShape_envelope(const ecitygml::capi::BoundingShape* self);

    void ecitygml_BoundingShape_destroy(BoundingShape* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Envelope* ecitygml::BoundingShape::envelope() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BoundingShape_envelope(this->AsFFI());
    return ecitygml::Envelope::FromFFI(result);
}

inline const ecitygml::capi::BoundingShape* ecitygml::BoundingShape::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::BoundingShape*>(this);
}

inline ecitygml::capi::BoundingShape* ecitygml::BoundingShape::AsFFI() {
    return reinterpret_cast<ecitygml::capi::BoundingShape*>(this);
}

inline const ecitygml::BoundingShape* ecitygml::BoundingShape::FromFFI(const ecitygml::capi::BoundingShape* ptr) {
    return reinterpret_cast<const ecitygml::BoundingShape*>(ptr);
}

inline ecitygml::BoundingShape* ecitygml::BoundingShape::FromFFI(ecitygml::capi::BoundingShape* ptr) {
    return reinterpret_cast<ecitygml::BoundingShape*>(ptr);
}

inline void ecitygml::BoundingShape::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_BoundingShape_destroy(reinterpret_cast<ecitygml::capi::BoundingShape*>(ptr));
}


#endif // ecitygml_BoundingShape_HPP
