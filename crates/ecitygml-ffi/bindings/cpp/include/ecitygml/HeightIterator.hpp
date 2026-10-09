#ifndef ecitygml_HeightIterator_HPP
#define ecitygml_HeightIterator_HPP

#include "HeightIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "Height.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Height* ecitygml_HeightIterator_next(ecitygml::capi::HeightIterator* self);

    void ecitygml_HeightIterator_destroy(HeightIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Height* ecitygml::HeightIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_HeightIterator_next(this->AsFFI());
    return ecitygml::Height::FromFFI(result);
}

inline const ecitygml::capi::HeightIterator* ecitygml::HeightIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::HeightIterator*>(this);
}

inline ecitygml::capi::HeightIterator* ecitygml::HeightIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::HeightIterator*>(this);
}

inline const ecitygml::HeightIterator* ecitygml::HeightIterator::FromFFI(const ecitygml::capi::HeightIterator* ptr) {
    return reinterpret_cast<const ecitygml::HeightIterator*>(ptr);
}

inline ecitygml::HeightIterator* ecitygml::HeightIterator::FromFFI(ecitygml::capi::HeightIterator* ptr) {
    return reinterpret_cast<ecitygml::HeightIterator*>(ptr);
}

inline void ecitygml::HeightIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_HeightIterator_destroy(reinterpret_cast<ecitygml::capi::HeightIterator*>(ptr));
}


#endif // ecitygml_HeightIterator_HPP
