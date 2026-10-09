#ifndef ECITYGML_Triangulation_HPP
#define ECITYGML_Triangulation_HPP

#include "Triangulation.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "TriangulatedSurface.hpp"
#include "TriangulationSkippedIterator.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::TriangulatedSurface* ecitygml_Triangulation_surface(const ecitygml::capi::Triangulation* self);

    bool ecitygml_Triangulation_has_skipped(const ecitygml::capi::Triangulation* self);

    ecitygml::capi::TriangulationSkippedIterator* ecitygml_Triangulation_skipped(const ecitygml::capi::Triangulation* self);

    void ecitygml_Triangulation_destroy(Triangulation* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::TriangulatedSurface& ecitygml::Triangulation::surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Triangulation_surface(this->AsFFI());
    return *ecitygml::TriangulatedSurface::FromFFI(result);
}

inline bool ecitygml::Triangulation::has_skipped() const {
    auto result = ecitygml::capi::ecitygml_Triangulation_has_skipped(this->AsFFI());
    return result;
}

inline std::unique_ptr<ecitygml::TriangulationSkippedIterator> ecitygml::Triangulation::skipped() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Triangulation_skipped(this->AsFFI());
    return std::unique_ptr<ecitygml::TriangulationSkippedIterator>(ecitygml::TriangulationSkippedIterator::FromFFI(result));
}

inline const ecitygml::capi::Triangulation* ecitygml::Triangulation::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::Triangulation*>(this);
}

inline ecitygml::capi::Triangulation* ecitygml::Triangulation::AsFFI() {
    return reinterpret_cast<ecitygml::capi::Triangulation*>(this);
}

inline const ecitygml::Triangulation* ecitygml::Triangulation::FromFFI(const ecitygml::capi::Triangulation* ptr) {
    return reinterpret_cast<const ecitygml::Triangulation*>(ptr);
}

inline ecitygml::Triangulation* ecitygml::Triangulation::FromFFI(ecitygml::capi::Triangulation* ptr) {
    return reinterpret_cast<ecitygml::Triangulation*>(ptr);
}

inline void ecitygml::Triangulation::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_Triangulation_destroy(reinterpret_cast<ecitygml::capi::Triangulation*>(ptr));
}


#endif // ECITYGML_Triangulation_HPP
