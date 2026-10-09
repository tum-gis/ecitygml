#ifndef ECITYGML_AuxiliaryTrafficSpacePropertyIterator_HPP
#define ECITYGML_AuxiliaryTrafficSpacePropertyIterator_HPP

#include "AuxiliaryTrafficSpacePropertyIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "AuxiliaryTrafficSpaceProperty.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::AuxiliaryTrafficSpaceProperty* ecitygml_AuxiliaryTrafficSpacePropertyIterator_next(ecitygml::capi::AuxiliaryTrafficSpacePropertyIterator* self);

    void ecitygml_AuxiliaryTrafficSpacePropertyIterator_destroy(AuxiliaryTrafficSpacePropertyIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::AuxiliaryTrafficSpaceProperty* ecitygml::AuxiliaryTrafficSpacePropertyIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AuxiliaryTrafficSpacePropertyIterator_next(this->AsFFI());
    return ecitygml::AuxiliaryTrafficSpaceProperty::FromFFI(result);
}

inline const ecitygml::capi::AuxiliaryTrafficSpacePropertyIterator* ecitygml::AuxiliaryTrafficSpacePropertyIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AuxiliaryTrafficSpacePropertyIterator*>(this);
}

inline ecitygml::capi::AuxiliaryTrafficSpacePropertyIterator* ecitygml::AuxiliaryTrafficSpacePropertyIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AuxiliaryTrafficSpacePropertyIterator*>(this);
}

inline const ecitygml::AuxiliaryTrafficSpacePropertyIterator* ecitygml::AuxiliaryTrafficSpacePropertyIterator::FromFFI(const ecitygml::capi::AuxiliaryTrafficSpacePropertyIterator* ptr) {
    return reinterpret_cast<const ecitygml::AuxiliaryTrafficSpacePropertyIterator*>(ptr);
}

inline ecitygml::AuxiliaryTrafficSpacePropertyIterator* ecitygml::AuxiliaryTrafficSpacePropertyIterator::FromFFI(ecitygml::capi::AuxiliaryTrafficSpacePropertyIterator* ptr) {
    return reinterpret_cast<ecitygml::AuxiliaryTrafficSpacePropertyIterator*>(ptr);
}

inline void ecitygml::AuxiliaryTrafficSpacePropertyIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AuxiliaryTrafficSpacePropertyIterator_destroy(reinterpret_cast<ecitygml::capi::AuxiliaryTrafficSpacePropertyIterator*>(ptr));
}


#endif // ECITYGML_AuxiliaryTrafficSpacePropertyIterator_HPP
