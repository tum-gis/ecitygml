#ifndef ECITYGML_TriangulationSkippedIterator_HPP
#define ECITYGML_TriangulationSkippedIterator_HPP

#include "TriangulationSkippedIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "Error.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    ecitygml::capi::Error* ecitygml_TriangulationSkippedIterator_next(ecitygml::capi::TriangulationSkippedIterator* self);

    void ecitygml_TriangulationSkippedIterator_destroy(TriangulationSkippedIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline std::unique_ptr<ecitygml::Error> ecitygml::TriangulationSkippedIterator::next() {
    auto result = ecitygml::capi::ecitygml_TriangulationSkippedIterator_next(this->AsFFI());
    return std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result));
}

inline const ecitygml::capi::TriangulationSkippedIterator* ecitygml::TriangulationSkippedIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::TriangulationSkippedIterator*>(this);
}

inline ecitygml::capi::TriangulationSkippedIterator* ecitygml::TriangulationSkippedIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::TriangulationSkippedIterator*>(this);
}

inline const ecitygml::TriangulationSkippedIterator* ecitygml::TriangulationSkippedIterator::FromFFI(const ecitygml::capi::TriangulationSkippedIterator* ptr) {
    return reinterpret_cast<const ecitygml::TriangulationSkippedIterator*>(ptr);
}

inline ecitygml::TriangulationSkippedIterator* ecitygml::TriangulationSkippedIterator::FromFFI(ecitygml::capi::TriangulationSkippedIterator* ptr) {
    return reinterpret_cast<ecitygml::TriangulationSkippedIterator*>(ptr);
}

inline void ecitygml::TriangulationSkippedIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_TriangulationSkippedIterator_destroy(reinterpret_cast<ecitygml::capi::TriangulationSkippedIterator*>(ptr));
}


#endif // ECITYGML_TriangulationSkippedIterator_HPP
