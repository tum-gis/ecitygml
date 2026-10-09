#ifndef ecitygml_GenericAttributeKindIterator_HPP
#define ecitygml_GenericAttributeKindIterator_HPP

#include "GenericAttributeKindIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "GenericAttributeKind.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::GenericAttributeKind* ecitygml_GenericAttributeKindIterator_next(ecitygml::capi::GenericAttributeKindIterator* self);

    void ecitygml_GenericAttributeKindIterator_destroy(GenericAttributeKindIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::GenericAttributeKind* ecitygml::GenericAttributeKindIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_GenericAttributeKindIterator_next(this->AsFFI());
    return ecitygml::GenericAttributeKind::FromFFI(result);
}

inline const ecitygml::capi::GenericAttributeKindIterator* ecitygml::GenericAttributeKindIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::GenericAttributeKindIterator*>(this);
}

inline ecitygml::capi::GenericAttributeKindIterator* ecitygml::GenericAttributeKindIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::GenericAttributeKindIterator*>(this);
}

inline const ecitygml::GenericAttributeKindIterator* ecitygml::GenericAttributeKindIterator::FromFFI(const ecitygml::capi::GenericAttributeKindIterator* ptr) {
    return reinterpret_cast<const ecitygml::GenericAttributeKindIterator*>(ptr);
}

inline ecitygml::GenericAttributeKindIterator* ecitygml::GenericAttributeKindIterator::FromFFI(ecitygml::capi::GenericAttributeKindIterator* ptr) {
    return reinterpret_cast<ecitygml::GenericAttributeKindIterator*>(ptr);
}

inline void ecitygml::GenericAttributeKindIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_GenericAttributeKindIterator_destroy(reinterpret_cast<ecitygml::capi::GenericAttributeKindIterator*>(ptr));
}


#endif // ecitygml_GenericAttributeKindIterator_HPP
