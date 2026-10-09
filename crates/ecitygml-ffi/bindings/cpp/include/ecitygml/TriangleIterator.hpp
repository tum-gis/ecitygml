#ifndef ecitygml_TriangleIterator_HPP
#define ecitygml_TriangleIterator_HPP

#include "TriangleIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "Triangle.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Triangle* ecitygml_TriangleIterator_next(ecitygml::capi::TriangleIterator* self);

    void ecitygml_TriangleIterator_destroy(TriangleIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Triangle* ecitygml::TriangleIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TriangleIterator_next(this->AsFFI());
    return ecitygml::Triangle::FromFFI(result);
}

inline const ecitygml::capi::TriangleIterator* ecitygml::TriangleIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::TriangleIterator*>(this);
}

inline ecitygml::capi::TriangleIterator* ecitygml::TriangleIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::TriangleIterator*>(this);
}

inline const ecitygml::TriangleIterator* ecitygml::TriangleIterator::FromFFI(const ecitygml::capi::TriangleIterator* ptr) {
    return reinterpret_cast<const ecitygml::TriangleIterator*>(ptr);
}

inline ecitygml::TriangleIterator* ecitygml::TriangleIterator::FromFFI(ecitygml::capi::TriangleIterator* ptr) {
    return reinterpret_cast<ecitygml::TriangleIterator*>(ptr);
}

inline void ecitygml::TriangleIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_TriangleIterator_destroy(reinterpret_cast<ecitygml::capi::TriangleIterator*>(ptr));
}


#endif // ecitygml_TriangleIterator_HPP
