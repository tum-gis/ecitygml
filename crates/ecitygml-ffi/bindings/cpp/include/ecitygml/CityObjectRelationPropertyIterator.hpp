#ifndef ecitygml_CityObjectRelationPropertyIterator_HPP
#define ecitygml_CityObjectRelationPropertyIterator_HPP

#include "CityObjectRelationPropertyIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "CityObjectRelationProperty.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::CityObjectRelationProperty* ecitygml_CityObjectRelationPropertyIterator_next(ecitygml::capi::CityObjectRelationPropertyIterator* self);

    void ecitygml_CityObjectRelationPropertyIterator_destroy(CityObjectRelationPropertyIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::CityObjectRelationProperty* ecitygml::CityObjectRelationPropertyIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityObjectRelationPropertyIterator_next(this->AsFFI());
    return ecitygml::CityObjectRelationProperty::FromFFI(result);
}

inline const ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml::CityObjectRelationPropertyIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::CityObjectRelationPropertyIterator*>(this);
}

inline ecitygml::capi::CityObjectRelationPropertyIterator* ecitygml::CityObjectRelationPropertyIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::CityObjectRelationPropertyIterator*>(this);
}

inline const ecitygml::CityObjectRelationPropertyIterator* ecitygml::CityObjectRelationPropertyIterator::FromFFI(const ecitygml::capi::CityObjectRelationPropertyIterator* ptr) {
    return reinterpret_cast<const ecitygml::CityObjectRelationPropertyIterator*>(ptr);
}

inline ecitygml::CityObjectRelationPropertyIterator* ecitygml::CityObjectRelationPropertyIterator::FromFFI(ecitygml::capi::CityObjectRelationPropertyIterator* ptr) {
    return reinterpret_cast<ecitygml::CityObjectRelationPropertyIterator*>(ptr);
}

inline void ecitygml::CityObjectRelationPropertyIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_CityObjectRelationPropertyIterator_destroy(reinterpret_cast<ecitygml::capi::CityObjectRelationPropertyIterator*>(ptr));
}


#endif // ecitygml_CityObjectRelationPropertyIterator_HPP
