#ifndef ECITYGML_AbstractCityObjectPropertyIterator_HPP
#define ECITYGML_AbstractCityObjectPropertyIterator_HPP

#include "AbstractCityObjectPropertyIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "AbstractCityObjectProperty.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::AbstractCityObjectProperty* ecitygml_AbstractCityObjectPropertyIterator_next(ecitygml::capi::AbstractCityObjectPropertyIterator* self);

    void ecitygml_AbstractCityObjectPropertyIterator_destroy(AbstractCityObjectPropertyIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::AbstractCityObjectProperty* ecitygml::AbstractCityObjectPropertyIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractCityObjectPropertyIterator_next(this->AsFFI());
    return ecitygml::AbstractCityObjectProperty::FromFFI(result);
}

inline const ecitygml::capi::AbstractCityObjectPropertyIterator* ecitygml::AbstractCityObjectPropertyIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AbstractCityObjectPropertyIterator*>(this);
}

inline ecitygml::capi::AbstractCityObjectPropertyIterator* ecitygml::AbstractCityObjectPropertyIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AbstractCityObjectPropertyIterator*>(this);
}

inline const ecitygml::AbstractCityObjectPropertyIterator* ecitygml::AbstractCityObjectPropertyIterator::FromFFI(const ecitygml::capi::AbstractCityObjectPropertyIterator* ptr) {
    return reinterpret_cast<const ecitygml::AbstractCityObjectPropertyIterator*>(ptr);
}

inline ecitygml::AbstractCityObjectPropertyIterator* ecitygml::AbstractCityObjectPropertyIterator::FromFFI(ecitygml::capi::AbstractCityObjectPropertyIterator* ptr) {
    return reinterpret_cast<ecitygml::AbstractCityObjectPropertyIterator*>(ptr);
}

inline void ecitygml::AbstractCityObjectPropertyIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AbstractCityObjectPropertyIterator_destroy(reinterpret_cast<ecitygml::capi::AbstractCityObjectPropertyIterator*>(ptr));
}


#endif // ECITYGML_AbstractCityObjectPropertyIterator_HPP
