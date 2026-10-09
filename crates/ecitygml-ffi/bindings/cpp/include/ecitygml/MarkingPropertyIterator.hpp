#ifndef ecitygml_MarkingPropertyIterator_HPP
#define ecitygml_MarkingPropertyIterator_HPP

#include "MarkingPropertyIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "MarkingProperty.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::MarkingProperty* ecitygml_MarkingPropertyIterator_next(ecitygml::capi::MarkingPropertyIterator* self);

    void ecitygml_MarkingPropertyIterator_destroy(MarkingPropertyIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::MarkingProperty* ecitygml::MarkingPropertyIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_MarkingPropertyIterator_next(this->AsFFI());
    return ecitygml::MarkingProperty::FromFFI(result);
}

inline const ecitygml::capi::MarkingPropertyIterator* ecitygml::MarkingPropertyIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::MarkingPropertyIterator*>(this);
}

inline ecitygml::capi::MarkingPropertyIterator* ecitygml::MarkingPropertyIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::MarkingPropertyIterator*>(this);
}

inline const ecitygml::MarkingPropertyIterator* ecitygml::MarkingPropertyIterator::FromFFI(const ecitygml::capi::MarkingPropertyIterator* ptr) {
    return reinterpret_cast<const ecitygml::MarkingPropertyIterator*>(ptr);
}

inline ecitygml::MarkingPropertyIterator* ecitygml::MarkingPropertyIterator::FromFFI(ecitygml::capi::MarkingPropertyIterator* ptr) {
    return reinterpret_cast<ecitygml::MarkingPropertyIterator*>(ptr);
}

inline void ecitygml::MarkingPropertyIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_MarkingPropertyIterator_destroy(reinterpret_cast<ecitygml::capi::MarkingPropertyIterator*>(ptr));
}


#endif // ecitygml_MarkingPropertyIterator_HPP
