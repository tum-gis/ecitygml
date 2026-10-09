#ifndef ecitygml_AbstractRingKindIterator_HPP
#define ecitygml_AbstractRingKindIterator_HPP

#include "AbstractRingKindIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "AbstractRingKind.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::AbstractRingKind* ecitygml_AbstractRingKindIterator_next(ecitygml::capi::AbstractRingKindIterator* self);

    void ecitygml_AbstractRingKindIterator_destroy(AbstractRingKindIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::AbstractRingKind* ecitygml::AbstractRingKindIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractRingKindIterator_next(this->AsFFI());
    return ecitygml::AbstractRingKind::FromFFI(result);
}

inline const ecitygml::capi::AbstractRingKindIterator* ecitygml::AbstractRingKindIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AbstractRingKindIterator*>(this);
}

inline ecitygml::capi::AbstractRingKindIterator* ecitygml::AbstractRingKindIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AbstractRingKindIterator*>(this);
}

inline const ecitygml::AbstractRingKindIterator* ecitygml::AbstractRingKindIterator::FromFFI(const ecitygml::capi::AbstractRingKindIterator* ptr) {
    return reinterpret_cast<const ecitygml::AbstractRingKindIterator*>(ptr);
}

inline ecitygml::AbstractRingKindIterator* ecitygml::AbstractRingKindIterator::FromFFI(ecitygml::capi::AbstractRingKindIterator* ptr) {
    return reinterpret_cast<ecitygml::AbstractRingKindIterator*>(ptr);
}

inline void ecitygml::AbstractRingKindIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AbstractRingKindIterator_destroy(reinterpret_cast<ecitygml::capi::AbstractRingKindIterator*>(ptr));
}


#endif // ecitygml_AbstractRingKindIterator_HPP
