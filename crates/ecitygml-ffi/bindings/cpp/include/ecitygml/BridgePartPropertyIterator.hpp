#ifndef ecitygml_BridgePartPropertyIterator_HPP
#define ecitygml_BridgePartPropertyIterator_HPP

#include "BridgePartPropertyIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "BridgePartProperty.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::BridgePartProperty* ecitygml_BridgePartPropertyIterator_next(ecitygml::capi::BridgePartPropertyIterator* self);

    void ecitygml_BridgePartPropertyIterator_destroy(BridgePartPropertyIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::BridgePartProperty* ecitygml::BridgePartPropertyIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BridgePartPropertyIterator_next(this->AsFFI());
    return ecitygml::BridgePartProperty::FromFFI(result);
}

inline const ecitygml::capi::BridgePartPropertyIterator* ecitygml::BridgePartPropertyIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::BridgePartPropertyIterator*>(this);
}

inline ecitygml::capi::BridgePartPropertyIterator* ecitygml::BridgePartPropertyIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::BridgePartPropertyIterator*>(this);
}

inline const ecitygml::BridgePartPropertyIterator* ecitygml::BridgePartPropertyIterator::FromFFI(const ecitygml::capi::BridgePartPropertyIterator* ptr) {
    return reinterpret_cast<const ecitygml::BridgePartPropertyIterator*>(ptr);
}

inline ecitygml::BridgePartPropertyIterator* ecitygml::BridgePartPropertyIterator::FromFFI(ecitygml::capi::BridgePartPropertyIterator* ptr) {
    return reinterpret_cast<ecitygml::BridgePartPropertyIterator*>(ptr);
}

inline void ecitygml::BridgePartPropertyIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_BridgePartPropertyIterator_destroy(reinterpret_cast<ecitygml::capi::BridgePartPropertyIterator*>(ptr));
}


#endif // ecitygml_BridgePartPropertyIterator_HPP
