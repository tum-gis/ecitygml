#ifndef ecitygml_CodeIterator_HPP
#define ecitygml_CodeIterator_HPP

#include "CodeIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "Code.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Code* ecitygml_CodeIterator_next(ecitygml::capi::CodeIterator* self);

    void ecitygml_CodeIterator_destroy(CodeIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Code* ecitygml::CodeIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CodeIterator_next(this->AsFFI());
    return ecitygml::Code::FromFFI(result);
}

inline const ecitygml::capi::CodeIterator* ecitygml::CodeIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::CodeIterator*>(this);
}

inline ecitygml::capi::CodeIterator* ecitygml::CodeIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::CodeIterator*>(this);
}

inline const ecitygml::CodeIterator* ecitygml::CodeIterator::FromFFI(const ecitygml::capi::CodeIterator* ptr) {
    return reinterpret_cast<const ecitygml::CodeIterator*>(ptr);
}

inline ecitygml::CodeIterator* ecitygml::CodeIterator::FromFFI(ecitygml::capi::CodeIterator* ptr) {
    return reinterpret_cast<ecitygml::CodeIterator*>(ptr);
}

inline void ecitygml::CodeIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_CodeIterator_destroy(reinterpret_cast<ecitygml::capi::CodeIterator*>(ptr));
}


#endif // ecitygml_CodeIterator_HPP
