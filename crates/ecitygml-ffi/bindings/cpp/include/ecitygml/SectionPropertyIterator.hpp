#ifndef ecitygml_SectionPropertyIterator_HPP
#define ecitygml_SectionPropertyIterator_HPP

#include "SectionPropertyIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "SectionProperty.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::SectionProperty* ecitygml_SectionPropertyIterator_next(ecitygml::capi::SectionPropertyIterator* self);

    void ecitygml_SectionPropertyIterator_destroy(SectionPropertyIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::SectionProperty* ecitygml::SectionPropertyIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_SectionPropertyIterator_next(this->AsFFI());
    return ecitygml::SectionProperty::FromFFI(result);
}

inline const ecitygml::capi::SectionPropertyIterator* ecitygml::SectionPropertyIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::SectionPropertyIterator*>(this);
}

inline ecitygml::capi::SectionPropertyIterator* ecitygml::SectionPropertyIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::SectionPropertyIterator*>(this);
}

inline const ecitygml::SectionPropertyIterator* ecitygml::SectionPropertyIterator::FromFFI(const ecitygml::capi::SectionPropertyIterator* ptr) {
    return reinterpret_cast<const ecitygml::SectionPropertyIterator*>(ptr);
}

inline ecitygml::SectionPropertyIterator* ecitygml::SectionPropertyIterator::FromFFI(ecitygml::capi::SectionPropertyIterator* ptr) {
    return reinterpret_cast<ecitygml::SectionPropertyIterator*>(ptr);
}

inline void ecitygml::SectionPropertyIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_SectionPropertyIterator_destroy(reinterpret_cast<ecitygml::capi::SectionPropertyIterator*>(ptr));
}


#endif // ecitygml_SectionPropertyIterator_HPP
