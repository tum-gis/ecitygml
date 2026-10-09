#ifndef ecitygml_TunnelPartPropertyIterator_HPP
#define ecitygml_TunnelPartPropertyIterator_HPP

#include "TunnelPartPropertyIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "TunnelPartProperty.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::TunnelPartProperty* ecitygml_TunnelPartPropertyIterator_next(ecitygml::capi::TunnelPartPropertyIterator* self);

    void ecitygml_TunnelPartPropertyIterator_destroy(TunnelPartPropertyIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::TunnelPartProperty* ecitygml::TunnelPartPropertyIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TunnelPartPropertyIterator_next(this->AsFFI());
    return ecitygml::TunnelPartProperty::FromFFI(result);
}

inline const ecitygml::capi::TunnelPartPropertyIterator* ecitygml::TunnelPartPropertyIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::TunnelPartPropertyIterator*>(this);
}

inline ecitygml::capi::TunnelPartPropertyIterator* ecitygml::TunnelPartPropertyIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::TunnelPartPropertyIterator*>(this);
}

inline const ecitygml::TunnelPartPropertyIterator* ecitygml::TunnelPartPropertyIterator::FromFFI(const ecitygml::capi::TunnelPartPropertyIterator* ptr) {
    return reinterpret_cast<const ecitygml::TunnelPartPropertyIterator*>(ptr);
}

inline ecitygml::TunnelPartPropertyIterator* ecitygml::TunnelPartPropertyIterator::FromFFI(ecitygml::capi::TunnelPartPropertyIterator* ptr) {
    return reinterpret_cast<ecitygml::TunnelPartPropertyIterator*>(ptr);
}

inline void ecitygml::TunnelPartPropertyIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_TunnelPartPropertyIterator_destroy(reinterpret_cast<ecitygml::capi::TunnelPartPropertyIterator*>(ptr));
}


#endif // ecitygml_TunnelPartPropertyIterator_HPP
