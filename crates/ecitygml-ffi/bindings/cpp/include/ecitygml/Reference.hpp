#ifndef ecitygml_Reference_HPP
#define ecitygml_Reference_HPP

#include "Reference.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "HRef.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::HRef* ecitygml_Reference_href(const ecitygml::capi::Reference* self);

    void ecitygml_Reference_destroy(Reference* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::HRef* ecitygml::Reference::href() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Reference_href(this->AsFFI());
    return ecitygml::HRef::FromFFI(result);
}

inline const ecitygml::capi::Reference* ecitygml::Reference::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::Reference*>(this);
}

inline ecitygml::capi::Reference* ecitygml::Reference::AsFFI() {
    return reinterpret_cast<ecitygml::capi::Reference*>(this);
}

inline const ecitygml::Reference* ecitygml::Reference::FromFFI(const ecitygml::capi::Reference* ptr) {
    return reinterpret_cast<const ecitygml::Reference*>(ptr);
}

inline ecitygml::Reference* ecitygml::Reference::FromFFI(ecitygml::capi::Reference* ptr) {
    return reinterpret_cast<ecitygml::Reference*>(ptr);
}

inline void ecitygml::Reference::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_Reference_destroy(reinterpret_cast<ecitygml::capi::Reference*>(ptr));
}


#endif // ecitygml_Reference_HPP
