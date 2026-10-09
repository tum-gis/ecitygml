#ifndef ECITYGML_CompositeSurface_HPP
#define ECITYGML_CompositeSurface_HPP

#include "CompositeSurface.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "AbstractSurfaceKind.hpp"
#include "AbstractSurfacePropertyIterator.hpp"
#include "CodeIterator.hpp"
#include "DirectPositionIterator.hpp"
#include "Envelope.hpp"
#include "Error.hpp"
#include "Id.hpp"
#include "Triangulation.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_CompositeSurface_id(const ecitygml::capi::CompositeSurface* self);

    ecitygml::capi::CodeIterator* ecitygml_CompositeSurface_names(const ecitygml::capi::CompositeSurface* self);

    typedef struct ecitygml_CompositeSurface_triangulate_result {union {ecitygml::capi::Triangulation* ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_CompositeSurface_triangulate_result;
    ecitygml_CompositeSurface_triangulate_result ecitygml_CompositeSurface_triangulate(const ecitygml::capi::CompositeSurface* self);

    const ecitygml::capi::CompositeSurface* ecitygml_CompositeSurface_try_from(const ecitygml::capi::AbstractSurfaceKind* surface);

    ecitygml::capi::AbstractSurfacePropertyIterator* ecitygml_CompositeSurface_surface_member(const ecitygml::capi::CompositeSurface* self);

    typedef struct ecitygml_CompositeSurface_area_3d_result {union {double ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_CompositeSurface_area_3d_result;
    ecitygml_CompositeSurface_area_3d_result ecitygml_CompositeSurface_area_3d(const ecitygml::capi::CompositeSurface* self);

    ecitygml::capi::DirectPositionIterator* ecitygml_CompositeSurface_points(const ecitygml::capi::CompositeSurface* self);

    ecitygml::capi::Envelope* ecitygml_CompositeSurface_compute_envelope(const ecitygml::capi::CompositeSurface* self);

    void ecitygml_CompositeSurface_destroy(CompositeSurface* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::CompositeSurface::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CompositeSurface_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::CompositeSurface::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CompositeSurface_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline ecitygml::diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>> ecitygml::CompositeSurface::triangulate() const {
    auto result = ecitygml::capi::ecitygml_CompositeSurface_triangulate(this->AsFFI());
    return result.is_ok ? ecitygml::diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>>(ecitygml::diplomat::Ok<std::unique_ptr<ecitygml::Triangulation>>(std::unique_ptr<ecitygml::Triangulation>(ecitygml::Triangulation::FromFFI(result.ok)))) : ecitygml::diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>>(ecitygml::diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline const ecitygml::CompositeSurface* ecitygml::CompositeSurface::try_from(const ecitygml::AbstractSurfaceKind& surface DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_CompositeSurface_try_from(surface.AsFFI());
    return ecitygml::CompositeSurface::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AbstractSurfacePropertyIterator> ecitygml::CompositeSurface::surface_member() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CompositeSurface_surface_member(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractSurfacePropertyIterator>(ecitygml::AbstractSurfacePropertyIterator::FromFFI(result));
}

inline ecitygml::diplomat::result<double, std::unique_ptr<ecitygml::Error>> ecitygml::CompositeSurface::area_3d() const {
    auto result = ecitygml::capi::ecitygml_CompositeSurface_area_3d(this->AsFFI());
    return result.is_ok ? ecitygml::diplomat::result<double, std::unique_ptr<ecitygml::Error>>(ecitygml::diplomat::Ok<double>(result.ok)) : ecitygml::diplomat::result<double, std::unique_ptr<ecitygml::Error>>(ecitygml::diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline std::unique_ptr<ecitygml::DirectPositionIterator> ecitygml::CompositeSurface::points() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CompositeSurface_points(this->AsFFI());
    return std::unique_ptr<ecitygml::DirectPositionIterator>(ecitygml::DirectPositionIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::Envelope> ecitygml::CompositeSurface::compute_envelope() const {
    auto result = ecitygml::capi::ecitygml_CompositeSurface_compute_envelope(this->AsFFI());
    return std::unique_ptr<ecitygml::Envelope>(ecitygml::Envelope::FromFFI(result));
}

inline const ecitygml::capi::CompositeSurface* ecitygml::CompositeSurface::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::CompositeSurface*>(this);
}

inline ecitygml::capi::CompositeSurface* ecitygml::CompositeSurface::AsFFI() {
    return reinterpret_cast<ecitygml::capi::CompositeSurface*>(this);
}

inline const ecitygml::CompositeSurface* ecitygml::CompositeSurface::FromFFI(const ecitygml::capi::CompositeSurface* ptr) {
    return reinterpret_cast<const ecitygml::CompositeSurface*>(ptr);
}

inline ecitygml::CompositeSurface* ecitygml::CompositeSurface::FromFFI(ecitygml::capi::CompositeSurface* ptr) {
    return reinterpret_cast<ecitygml::CompositeSurface*>(ptr);
}

inline void ecitygml::CompositeSurface::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_CompositeSurface_destroy(reinterpret_cast<ecitygml::capi::CompositeSurface*>(ptr));
}


#endif // ECITYGML_CompositeSurface_HPP
