#ifndef ecitygml_ExternalReferenceIterator_HPP
#define ecitygml_ExternalReferenceIterator_HPP

#include "ExternalReferenceIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "ExternalReference.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::ExternalReference* ecitygml_ExternalReferenceIterator_next(ecitygml::capi::ExternalReferenceIterator* self);

    void ecitygml_ExternalReferenceIterator_destroy(ExternalReferenceIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::ExternalReference* ecitygml::ExternalReferenceIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_ExternalReferenceIterator_next(this->AsFFI());
    return ecitygml::ExternalReference::FromFFI(result);
}

inline const ecitygml::capi::ExternalReferenceIterator* ecitygml::ExternalReferenceIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::ExternalReferenceIterator*>(this);
}

inline ecitygml::capi::ExternalReferenceIterator* ecitygml::ExternalReferenceIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::ExternalReferenceIterator*>(this);
}

inline const ecitygml::ExternalReferenceIterator* ecitygml::ExternalReferenceIterator::FromFFI(const ecitygml::capi::ExternalReferenceIterator* ptr) {
    return reinterpret_cast<const ecitygml::ExternalReferenceIterator*>(ptr);
}

inline ecitygml::ExternalReferenceIterator* ecitygml::ExternalReferenceIterator::FromFFI(ecitygml::capi::ExternalReferenceIterator* ptr) {
    return reinterpret_cast<ecitygml::ExternalReferenceIterator*>(ptr);
}

inline void ecitygml::ExternalReferenceIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_ExternalReferenceIterator_destroy(reinterpret_cast<ecitygml::capi::ExternalReferenceIterator*>(ptr));
}


#endif // ecitygml_ExternalReferenceIterator_HPP
