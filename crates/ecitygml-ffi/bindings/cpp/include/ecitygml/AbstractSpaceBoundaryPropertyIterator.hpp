#ifndef ecitygml_AbstractSpaceBoundaryPropertyIterator_HPP
#define ecitygml_AbstractSpaceBoundaryPropertyIterator_HPP

#include "AbstractSpaceBoundaryPropertyIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "AbstractSpaceBoundaryProperty.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::AbstractSpaceBoundaryProperty* ecitygml_AbstractSpaceBoundaryPropertyIterator_next(ecitygml::capi::AbstractSpaceBoundaryPropertyIterator* self);

    void ecitygml_AbstractSpaceBoundaryPropertyIterator_destroy(AbstractSpaceBoundaryPropertyIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::AbstractSpaceBoundaryProperty* ecitygml::AbstractSpaceBoundaryPropertyIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractSpaceBoundaryPropertyIterator_next(this->AsFFI());
    return ecitygml::AbstractSpaceBoundaryProperty::FromFFI(result);
}

inline const ecitygml::capi::AbstractSpaceBoundaryPropertyIterator* ecitygml::AbstractSpaceBoundaryPropertyIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AbstractSpaceBoundaryPropertyIterator*>(this);
}

inline ecitygml::capi::AbstractSpaceBoundaryPropertyIterator* ecitygml::AbstractSpaceBoundaryPropertyIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AbstractSpaceBoundaryPropertyIterator*>(this);
}

inline const ecitygml::AbstractSpaceBoundaryPropertyIterator* ecitygml::AbstractSpaceBoundaryPropertyIterator::FromFFI(const ecitygml::capi::AbstractSpaceBoundaryPropertyIterator* ptr) {
    return reinterpret_cast<const ecitygml::AbstractSpaceBoundaryPropertyIterator*>(ptr);
}

inline ecitygml::AbstractSpaceBoundaryPropertyIterator* ecitygml::AbstractSpaceBoundaryPropertyIterator::FromFFI(ecitygml::capi::AbstractSpaceBoundaryPropertyIterator* ptr) {
    return reinterpret_cast<ecitygml::AbstractSpaceBoundaryPropertyIterator*>(ptr);
}

inline void ecitygml::AbstractSpaceBoundaryPropertyIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AbstractSpaceBoundaryPropertyIterator_destroy(reinterpret_cast<ecitygml::capi::AbstractSpaceBoundaryPropertyIterator*>(ptr));
}


#endif // ecitygml_AbstractSpaceBoundaryPropertyIterator_HPP
