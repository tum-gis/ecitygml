#ifndef ecitygml_IntersectionPropertyIterator_HPP
#define ecitygml_IntersectionPropertyIterator_HPP

#include "IntersectionPropertyIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "IntersectionProperty.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::IntersectionProperty* ecitygml_IntersectionPropertyIterator_next(ecitygml::capi::IntersectionPropertyIterator* self);

    void ecitygml_IntersectionPropertyIterator_destroy(IntersectionPropertyIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::IntersectionProperty* ecitygml::IntersectionPropertyIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_IntersectionPropertyIterator_next(this->AsFFI());
    return ecitygml::IntersectionProperty::FromFFI(result);
}

inline const ecitygml::capi::IntersectionPropertyIterator* ecitygml::IntersectionPropertyIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::IntersectionPropertyIterator*>(this);
}

inline ecitygml::capi::IntersectionPropertyIterator* ecitygml::IntersectionPropertyIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::IntersectionPropertyIterator*>(this);
}

inline const ecitygml::IntersectionPropertyIterator* ecitygml::IntersectionPropertyIterator::FromFFI(const ecitygml::capi::IntersectionPropertyIterator* ptr) {
    return reinterpret_cast<const ecitygml::IntersectionPropertyIterator*>(ptr);
}

inline ecitygml::IntersectionPropertyIterator* ecitygml::IntersectionPropertyIterator::FromFFI(ecitygml::capi::IntersectionPropertyIterator* ptr) {
    return reinterpret_cast<ecitygml::IntersectionPropertyIterator*>(ptr);
}

inline void ecitygml::IntersectionPropertyIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_IntersectionPropertyIterator_destroy(reinterpret_cast<ecitygml::capi::IntersectionPropertyIterator*>(ptr));
}


#endif // ecitygml_IntersectionPropertyIterator_HPP
