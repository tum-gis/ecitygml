#ifndef ecitygml_AbstractReliefComponentPropertyIterator_HPP
#define ecitygml_AbstractReliefComponentPropertyIterator_HPP

#include "AbstractReliefComponentPropertyIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "AbstractReliefComponentProperty.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::AbstractReliefComponentProperty* ecitygml_AbstractReliefComponentPropertyIterator_next(ecitygml::capi::AbstractReliefComponentPropertyIterator* self);

    void ecitygml_AbstractReliefComponentPropertyIterator_destroy(AbstractReliefComponentPropertyIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::AbstractReliefComponentProperty* ecitygml::AbstractReliefComponentPropertyIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractReliefComponentPropertyIterator_next(this->AsFFI());
    return ecitygml::AbstractReliefComponentProperty::FromFFI(result);
}

inline const ecitygml::capi::AbstractReliefComponentPropertyIterator* ecitygml::AbstractReliefComponentPropertyIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AbstractReliefComponentPropertyIterator*>(this);
}

inline ecitygml::capi::AbstractReliefComponentPropertyIterator* ecitygml::AbstractReliefComponentPropertyIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AbstractReliefComponentPropertyIterator*>(this);
}

inline const ecitygml::AbstractReliefComponentPropertyIterator* ecitygml::AbstractReliefComponentPropertyIterator::FromFFI(const ecitygml::capi::AbstractReliefComponentPropertyIterator* ptr) {
    return reinterpret_cast<const ecitygml::AbstractReliefComponentPropertyIterator*>(ptr);
}

inline ecitygml::AbstractReliefComponentPropertyIterator* ecitygml::AbstractReliefComponentPropertyIterator::FromFFI(ecitygml::capi::AbstractReliefComponentPropertyIterator* ptr) {
    return reinterpret_cast<ecitygml::AbstractReliefComponentPropertyIterator*>(ptr);
}

inline void ecitygml::AbstractReliefComponentPropertyIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AbstractReliefComponentPropertyIterator_destroy(reinterpret_cast<ecitygml::capi::AbstractReliefComponentPropertyIterator*>(ptr));
}


#endif // ecitygml_AbstractReliefComponentPropertyIterator_HPP
