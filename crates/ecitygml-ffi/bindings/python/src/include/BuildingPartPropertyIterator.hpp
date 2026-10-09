#ifndef ECITYGML_BuildingPartPropertyIterator_HPP
#define ECITYGML_BuildingPartPropertyIterator_HPP

#include "BuildingPartPropertyIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "BuildingPartProperty.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::BuildingPartProperty* ecitygml_BuildingPartPropertyIterator_next(ecitygml::capi::BuildingPartPropertyIterator* self);

    void ecitygml_BuildingPartPropertyIterator_destroy(BuildingPartPropertyIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::BuildingPartProperty* ecitygml::BuildingPartPropertyIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingPartPropertyIterator_next(this->AsFFI());
    return ecitygml::BuildingPartProperty::FromFFI(result);
}

inline const ecitygml::capi::BuildingPartPropertyIterator* ecitygml::BuildingPartPropertyIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::BuildingPartPropertyIterator*>(this);
}

inline ecitygml::capi::BuildingPartPropertyIterator* ecitygml::BuildingPartPropertyIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::BuildingPartPropertyIterator*>(this);
}

inline const ecitygml::BuildingPartPropertyIterator* ecitygml::BuildingPartPropertyIterator::FromFFI(const ecitygml::capi::BuildingPartPropertyIterator* ptr) {
    return reinterpret_cast<const ecitygml::BuildingPartPropertyIterator*>(ptr);
}

inline ecitygml::BuildingPartPropertyIterator* ecitygml::BuildingPartPropertyIterator::FromFFI(ecitygml::capi::BuildingPartPropertyIterator* ptr) {
    return reinterpret_cast<ecitygml::BuildingPartPropertyIterator*>(ptr);
}

inline void ecitygml::BuildingPartPropertyIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_BuildingPartPropertyIterator_destroy(reinterpret_cast<ecitygml::capi::BuildingPartPropertyIterator*>(ptr));
}


#endif // ECITYGML_BuildingPartPropertyIterator_HPP
