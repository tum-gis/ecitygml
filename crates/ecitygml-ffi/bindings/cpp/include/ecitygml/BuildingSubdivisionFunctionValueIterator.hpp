#ifndef ecitygml_BuildingSubdivisionFunctionValueIterator_HPP
#define ecitygml_BuildingSubdivisionFunctionValueIterator_HPP

#include "BuildingSubdivisionFunctionValueIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "BuildingSubdivisionFunctionValue.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::BuildingSubdivisionFunctionValue* ecitygml_BuildingSubdivisionFunctionValueIterator_next(ecitygml::capi::BuildingSubdivisionFunctionValueIterator* self);

    void ecitygml_BuildingSubdivisionFunctionValueIterator_destroy(BuildingSubdivisionFunctionValueIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::BuildingSubdivisionFunctionValue* ecitygml::BuildingSubdivisionFunctionValueIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_BuildingSubdivisionFunctionValueIterator_next(this->AsFFI());
    return ecitygml::BuildingSubdivisionFunctionValue::FromFFI(result);
}

inline const ecitygml::capi::BuildingSubdivisionFunctionValueIterator* ecitygml::BuildingSubdivisionFunctionValueIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::BuildingSubdivisionFunctionValueIterator*>(this);
}

inline ecitygml::capi::BuildingSubdivisionFunctionValueIterator* ecitygml::BuildingSubdivisionFunctionValueIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::BuildingSubdivisionFunctionValueIterator*>(this);
}

inline const ecitygml::BuildingSubdivisionFunctionValueIterator* ecitygml::BuildingSubdivisionFunctionValueIterator::FromFFI(const ecitygml::capi::BuildingSubdivisionFunctionValueIterator* ptr) {
    return reinterpret_cast<const ecitygml::BuildingSubdivisionFunctionValueIterator*>(ptr);
}

inline ecitygml::BuildingSubdivisionFunctionValueIterator* ecitygml::BuildingSubdivisionFunctionValueIterator::FromFFI(ecitygml::capi::BuildingSubdivisionFunctionValueIterator* ptr) {
    return reinterpret_cast<ecitygml::BuildingSubdivisionFunctionValueIterator*>(ptr);
}

inline void ecitygml::BuildingSubdivisionFunctionValueIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_BuildingSubdivisionFunctionValueIterator_destroy(reinterpret_cast<ecitygml::capi::BuildingSubdivisionFunctionValueIterator*>(ptr));
}


#endif // ecitygml_BuildingSubdivisionFunctionValueIterator_HPP
