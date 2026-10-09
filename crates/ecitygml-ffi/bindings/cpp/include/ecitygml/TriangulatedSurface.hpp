#ifndef ecitygml_TriangulatedSurface_HPP
#define ecitygml_TriangulatedSurface_HPP

#include "TriangulatedSurface.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "AbstractSurfaceKind.hpp"
#include "CodeIterator.hpp"
#include "DirectPositionIterator.hpp"
#include "Envelope.hpp"
#include "Error.hpp"
#include "Id.hpp"
#include "Surface.hpp"
#include "TriangleIterator.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_TriangulatedSurface_id(const ecitygml::capi::TriangulatedSurface* self);

    ecitygml::capi::CodeIterator* ecitygml_TriangulatedSurface_names(const ecitygml::capi::TriangulatedSurface* self);

    const ecitygml::capi::TriangulatedSurface* ecitygml_TriangulatedSurface_try_from(const ecitygml::capi::AbstractSurfaceKind* surface);

    ecitygml::capi::TriangleIterator* ecitygml_TriangulatedSurface_triangles(const ecitygml::capi::TriangulatedSurface* self);

    const ecitygml::capi::Surface* ecitygml_TriangulatedSurface_surface(const ecitygml::capi::TriangulatedSurface* self);

    ecitygml::capi::DirectPositionIterator* ecitygml_TriangulatedSurface_points(const ecitygml::capi::TriangulatedSurface* self);

    typedef struct ecitygml_TriangulatedSurface_area_3d_result {union {double ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_TriangulatedSurface_area_3d_result;
    ecitygml_TriangulatedSurface_area_3d_result ecitygml_TriangulatedSurface_area_3d(const ecitygml::capi::TriangulatedSurface* self);

    ecitygml::capi::Envelope* ecitygml_TriangulatedSurface_compute_envelope(const ecitygml::capi::TriangulatedSurface* self);

    void ecitygml_TriangulatedSurface_destroy(TriangulatedSurface* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::TriangulatedSurface::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TriangulatedSurface_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::TriangulatedSurface::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TriangulatedSurface_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::TriangulatedSurface* ecitygml::TriangulatedSurface::try_from(const ecitygml::AbstractSurfaceKind& surface DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_TriangulatedSurface_try_from(surface.AsFFI());
    return ecitygml::TriangulatedSurface::FromFFI(result);
}

inline std::unique_ptr<ecitygml::TriangleIterator> ecitygml::TriangulatedSurface::triangles() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TriangulatedSurface_triangles(this->AsFFI());
    return std::unique_ptr<ecitygml::TriangleIterator>(ecitygml::TriangleIterator::FromFFI(result));
}

inline const ecitygml::Surface& ecitygml::TriangulatedSurface::surface() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TriangulatedSurface_surface(this->AsFFI());
    return *ecitygml::Surface::FromFFI(result);
}

inline std::unique_ptr<ecitygml::DirectPositionIterator> ecitygml::TriangulatedSurface::points() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_TriangulatedSurface_points(this->AsFFI());
    return std::unique_ptr<ecitygml::DirectPositionIterator>(ecitygml::DirectPositionIterator::FromFFI(result));
}

inline diplomat::result<double, std::unique_ptr<ecitygml::Error>> ecitygml::TriangulatedSurface::area_3d() const {
    auto result = ecitygml::capi::ecitygml_TriangulatedSurface_area_3d(this->AsFFI());
    return result.is_ok ? diplomat::result<double, std::unique_ptr<ecitygml::Error>>(diplomat::Ok<double>(result.ok)) : diplomat::result<double, std::unique_ptr<ecitygml::Error>>(diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline std::unique_ptr<ecitygml::Envelope> ecitygml::TriangulatedSurface::compute_envelope() const {
    auto result = ecitygml::capi::ecitygml_TriangulatedSurface_compute_envelope(this->AsFFI());
    return std::unique_ptr<ecitygml::Envelope>(ecitygml::Envelope::FromFFI(result));
}

inline const ecitygml::capi::TriangulatedSurface* ecitygml::TriangulatedSurface::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::TriangulatedSurface*>(this);
}

inline ecitygml::capi::TriangulatedSurface* ecitygml::TriangulatedSurface::AsFFI() {
    return reinterpret_cast<ecitygml::capi::TriangulatedSurface*>(this);
}

inline const ecitygml::TriangulatedSurface* ecitygml::TriangulatedSurface::FromFFI(const ecitygml::capi::TriangulatedSurface* ptr) {
    return reinterpret_cast<const ecitygml::TriangulatedSurface*>(ptr);
}

inline ecitygml::TriangulatedSurface* ecitygml::TriangulatedSurface::FromFFI(ecitygml::capi::TriangulatedSurface* ptr) {
    return reinterpret_cast<ecitygml::TriangulatedSurface*>(ptr);
}

inline void ecitygml::TriangulatedSurface::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_TriangulatedSurface_destroy(reinterpret_cast<ecitygml::capi::TriangulatedSurface*>(ptr));
}


#endif // ecitygml_TriangulatedSurface_HPP
