#ifndef ECITYGML_HolePropertyIterator_HPP
#define ECITYGML_HolePropertyIterator_HPP

#include "HolePropertyIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "HoleProperty.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::HoleProperty* ecitygml_HolePropertyIterator_next(ecitygml::capi::HolePropertyIterator* self);

    void ecitygml_HolePropertyIterator_destroy(HolePropertyIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::HoleProperty* ecitygml::HolePropertyIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_HolePropertyIterator_next(this->AsFFI());
    return ecitygml::HoleProperty::FromFFI(result);
}

inline const ecitygml::capi::HolePropertyIterator* ecitygml::HolePropertyIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::HolePropertyIterator*>(this);
}

inline ecitygml::capi::HolePropertyIterator* ecitygml::HolePropertyIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::HolePropertyIterator*>(this);
}

inline const ecitygml::HolePropertyIterator* ecitygml::HolePropertyIterator::FromFFI(const ecitygml::capi::HolePropertyIterator* ptr) {
    return reinterpret_cast<const ecitygml::HolePropertyIterator*>(ptr);
}

inline ecitygml::HolePropertyIterator* ecitygml::HolePropertyIterator::FromFFI(ecitygml::capi::HolePropertyIterator* ptr) {
    return reinterpret_cast<ecitygml::HolePropertyIterator*>(ptr);
}

inline void ecitygml::HolePropertyIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_HolePropertyIterator_destroy(reinterpret_cast<ecitygml::capi::HolePropertyIterator*>(ptr));
}


#endif // ECITYGML_HolePropertyIterator_HPP
