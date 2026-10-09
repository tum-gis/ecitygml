#ifndef ECITYGML_AbstractSurfacePatchKindIterator_HPP
#define ECITYGML_AbstractSurfacePatchKindIterator_HPP

#include "AbstractSurfacePatchKindIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "AbstractSurfacePatchKind.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::AbstractSurfacePatchKind* ecitygml_AbstractSurfacePatchKindIterator_next(ecitygml::capi::AbstractSurfacePatchKindIterator* self);

    void ecitygml_AbstractSurfacePatchKindIterator_destroy(AbstractSurfacePatchKindIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::AbstractSurfacePatchKind* ecitygml::AbstractSurfacePatchKindIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractSurfacePatchKindIterator_next(this->AsFFI());
    return ecitygml::AbstractSurfacePatchKind::FromFFI(result);
}

inline const ecitygml::capi::AbstractSurfacePatchKindIterator* ecitygml::AbstractSurfacePatchKindIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AbstractSurfacePatchKindIterator*>(this);
}

inline ecitygml::capi::AbstractSurfacePatchKindIterator* ecitygml::AbstractSurfacePatchKindIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AbstractSurfacePatchKindIterator*>(this);
}

inline const ecitygml::AbstractSurfacePatchKindIterator* ecitygml::AbstractSurfacePatchKindIterator::FromFFI(const ecitygml::capi::AbstractSurfacePatchKindIterator* ptr) {
    return reinterpret_cast<const ecitygml::AbstractSurfacePatchKindIterator*>(ptr);
}

inline ecitygml::AbstractSurfacePatchKindIterator* ecitygml::AbstractSurfacePatchKindIterator::FromFFI(ecitygml::capi::AbstractSurfacePatchKindIterator* ptr) {
    return reinterpret_cast<ecitygml::AbstractSurfacePatchKindIterator*>(ptr);
}

inline void ecitygml::AbstractSurfacePatchKindIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AbstractSurfacePatchKindIterator_destroy(reinterpret_cast<ecitygml::capi::AbstractSurfacePatchKindIterator*>(ptr));
}


#endif // ECITYGML_AbstractSurfacePatchKindIterator_HPP
