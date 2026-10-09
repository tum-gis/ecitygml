#ifndef ecitygml_MultiSurface_HPP
#define ecitygml_MultiSurface_HPP

#include "MultiSurface.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "AbstractGeometryKind.hpp"
#include "AbstractSurfacePropertyIterator.hpp"
#include "CodeIterator.hpp"
#include "DirectPositionIterator.hpp"
#include "Envelope.hpp"
#include "Error.hpp"
#include "Id.hpp"
#include "Triangulation.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_MultiSurface_id(const ecitygml::capi::MultiSurface* self);

    ecitygml::capi::CodeIterator* ecitygml_MultiSurface_names(const ecitygml::capi::MultiSurface* self);

    typedef struct ecitygml_MultiSurface_triangulate_result {union {ecitygml::capi::Triangulation* ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_MultiSurface_triangulate_result;
    ecitygml_MultiSurface_triangulate_result ecitygml_MultiSurface_triangulate(const ecitygml::capi::MultiSurface* self);

    const ecitygml::capi::MultiSurface* ecitygml_MultiSurface_try_from(const ecitygml::capi::AbstractGeometryKind* geometry);

    ecitygml::capi::AbstractSurfacePropertyIterator* ecitygml_MultiSurface_surface_member(const ecitygml::capi::MultiSurface* self);

    typedef struct ecitygml_MultiSurface_area_3d_result {union {double ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_MultiSurface_area_3d_result;
    ecitygml_MultiSurface_area_3d_result ecitygml_MultiSurface_area_3d(const ecitygml::capi::MultiSurface* self);

    ecitygml::capi::DirectPositionIterator* ecitygml_MultiSurface_points(const ecitygml::capi::MultiSurface* self);

    ecitygml::capi::Envelope* ecitygml_MultiSurface_compute_envelope(const ecitygml::capi::MultiSurface* self);

    void ecitygml_MultiSurface_destroy(MultiSurface* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::MultiSurface::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_MultiSurface_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::MultiSurface::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_MultiSurface_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>> ecitygml::MultiSurface::triangulate() const {
    auto result = ecitygml::capi::ecitygml_MultiSurface_triangulate(this->AsFFI());
    return result.is_ok ? diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>>(diplomat::Ok<std::unique_ptr<ecitygml::Triangulation>>(std::unique_ptr<ecitygml::Triangulation>(ecitygml::Triangulation::FromFFI(result.ok)))) : diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>>(diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline const ecitygml::MultiSurface* ecitygml::MultiSurface::try_from(const ecitygml::AbstractGeometryKind& geometry DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_MultiSurface_try_from(geometry.AsFFI());
    return ecitygml::MultiSurface::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AbstractSurfacePropertyIterator> ecitygml::MultiSurface::surface_member() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_MultiSurface_surface_member(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractSurfacePropertyIterator>(ecitygml::AbstractSurfacePropertyIterator::FromFFI(result));
}

inline diplomat::result<double, std::unique_ptr<ecitygml::Error>> ecitygml::MultiSurface::area_3d() const {
    auto result = ecitygml::capi::ecitygml_MultiSurface_area_3d(this->AsFFI());
    return result.is_ok ? diplomat::result<double, std::unique_ptr<ecitygml::Error>>(diplomat::Ok<double>(result.ok)) : diplomat::result<double, std::unique_ptr<ecitygml::Error>>(diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline std::unique_ptr<ecitygml::DirectPositionIterator> ecitygml::MultiSurface::points() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_MultiSurface_points(this->AsFFI());
    return std::unique_ptr<ecitygml::DirectPositionIterator>(ecitygml::DirectPositionIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::Envelope> ecitygml::MultiSurface::compute_envelope() const {
    auto result = ecitygml::capi::ecitygml_MultiSurface_compute_envelope(this->AsFFI());
    return std::unique_ptr<ecitygml::Envelope>(ecitygml::Envelope::FromFFI(result));
}

inline const ecitygml::capi::MultiSurface* ecitygml::MultiSurface::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::MultiSurface*>(this);
}

inline ecitygml::capi::MultiSurface* ecitygml::MultiSurface::AsFFI() {
    return reinterpret_cast<ecitygml::capi::MultiSurface*>(this);
}

inline const ecitygml::MultiSurface* ecitygml::MultiSurface::FromFFI(const ecitygml::capi::MultiSurface* ptr) {
    return reinterpret_cast<const ecitygml::MultiSurface*>(ptr);
}

inline ecitygml::MultiSurface* ecitygml::MultiSurface::FromFFI(ecitygml::capi::MultiSurface* ptr) {
    return reinterpret_cast<ecitygml::MultiSurface*>(ptr);
}

inline void ecitygml::MultiSurface::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_MultiSurface_destroy(reinterpret_cast<ecitygml::capi::MultiSurface*>(ptr));
}


#endif // ecitygml_MultiSurface_HPP
