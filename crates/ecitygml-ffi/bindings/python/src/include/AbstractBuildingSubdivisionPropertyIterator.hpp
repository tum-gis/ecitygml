#ifndef ECITYGML_AbstractBuildingSubdivisionPropertyIterator_HPP
#define ECITYGML_AbstractBuildingSubdivisionPropertyIterator_HPP

#include "AbstractBuildingSubdivisionPropertyIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "AbstractBuildingSubdivisionProperty.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::AbstractBuildingSubdivisionProperty* ecitygml_AbstractBuildingSubdivisionPropertyIterator_next(ecitygml::capi::AbstractBuildingSubdivisionPropertyIterator* self);

    void ecitygml_AbstractBuildingSubdivisionPropertyIterator_destroy(AbstractBuildingSubdivisionPropertyIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::AbstractBuildingSubdivisionProperty* ecitygml::AbstractBuildingSubdivisionPropertyIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionPropertyIterator_next(this->AsFFI());
    return ecitygml::AbstractBuildingSubdivisionProperty::FromFFI(result);
}

inline const ecitygml::capi::AbstractBuildingSubdivisionPropertyIterator* ecitygml::AbstractBuildingSubdivisionPropertyIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AbstractBuildingSubdivisionPropertyIterator*>(this);
}

inline ecitygml::capi::AbstractBuildingSubdivisionPropertyIterator* ecitygml::AbstractBuildingSubdivisionPropertyIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AbstractBuildingSubdivisionPropertyIterator*>(this);
}

inline const ecitygml::AbstractBuildingSubdivisionPropertyIterator* ecitygml::AbstractBuildingSubdivisionPropertyIterator::FromFFI(const ecitygml::capi::AbstractBuildingSubdivisionPropertyIterator* ptr) {
    return reinterpret_cast<const ecitygml::AbstractBuildingSubdivisionPropertyIterator*>(ptr);
}

inline ecitygml::AbstractBuildingSubdivisionPropertyIterator* ecitygml::AbstractBuildingSubdivisionPropertyIterator::FromFFI(ecitygml::capi::AbstractBuildingSubdivisionPropertyIterator* ptr) {
    return reinterpret_cast<ecitygml::AbstractBuildingSubdivisionPropertyIterator*>(ptr);
}

inline void ecitygml::AbstractBuildingSubdivisionPropertyIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AbstractBuildingSubdivisionPropertyIterator_destroy(reinterpret_cast<ecitygml::capi::AbstractBuildingSubdivisionPropertyIterator*>(ptr));
}


#endif // ECITYGML_AbstractBuildingSubdivisionPropertyIterator_HPP
