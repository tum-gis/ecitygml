#ifndef ECITYGML_ShellIterator_HPP
#define ECITYGML_ShellIterator_HPP

#include "ShellIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "Shell.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Shell* ecitygml_ShellIterator_next(ecitygml::capi::ShellIterator* self);

    void ecitygml_ShellIterator_destroy(ShellIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Shell* ecitygml::ShellIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_ShellIterator_next(this->AsFFI());
    return ecitygml::Shell::FromFFI(result);
}

inline const ecitygml::capi::ShellIterator* ecitygml::ShellIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::ShellIterator*>(this);
}

inline ecitygml::capi::ShellIterator* ecitygml::ShellIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::ShellIterator*>(this);
}

inline const ecitygml::ShellIterator* ecitygml::ShellIterator::FromFFI(const ecitygml::capi::ShellIterator* ptr) {
    return reinterpret_cast<const ecitygml::ShellIterator*>(ptr);
}

inline ecitygml::ShellIterator* ecitygml::ShellIterator::FromFFI(ecitygml::capi::ShellIterator* ptr) {
    return reinterpret_cast<ecitygml::ShellIterator*>(ptr);
}

inline void ecitygml::ShellIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_ShellIterator_destroy(reinterpret_cast<ecitygml::capi::ShellIterator*>(ptr));
}


#endif // ECITYGML_ShellIterator_HPP
