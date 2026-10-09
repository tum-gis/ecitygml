#ifndef ECITYGML_Surface_HPP
#define ECITYGML_Surface_HPP

#include "Surface.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "AbstractSurfaceKind.hpp"
#include "AbstractSurfacePatchKindIterator.hpp"
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

    const ecitygml::capi::Id* ecitygml_Surface_id(const ecitygml::capi::Surface* self);

    ecitygml::capi::CodeIterator* ecitygml_Surface_names(const ecitygml::capi::Surface* self);

    typedef struct ecitygml_Surface_triangulate_result {union {ecitygml::capi::Triangulation* ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_Surface_triangulate_result;
    ecitygml_Surface_triangulate_result ecitygml_Surface_triangulate(const ecitygml::capi::Surface* self);

    const ecitygml::capi::Surface* ecitygml_Surface_try_from(const ecitygml::capi::AbstractSurfaceKind* surface);

    ecitygml::capi::AbstractSurfacePatchKindIterator* ecitygml_Surface_patches(const ecitygml::capi::Surface* self);

    typedef struct ecitygml_Surface_area_3d_result {union {double ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_Surface_area_3d_result;
    ecitygml_Surface_area_3d_result ecitygml_Surface_area_3d(const ecitygml::capi::Surface* self);

    ecitygml::capi::DirectPositionIterator* ecitygml_Surface_points(const ecitygml::capi::Surface* self);

    ecitygml::capi::Envelope* ecitygml_Surface_compute_envelope(const ecitygml::capi::Surface* self);

    void ecitygml_Surface_destroy(Surface* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::Surface::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Surface_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::Surface::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Surface_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline ecitygml::diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>> ecitygml::Surface::triangulate() const {
    auto result = ecitygml::capi::ecitygml_Surface_triangulate(this->AsFFI());
    return result.is_ok ? ecitygml::diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>>(ecitygml::diplomat::Ok<std::unique_ptr<ecitygml::Triangulation>>(std::unique_ptr<ecitygml::Triangulation>(ecitygml::Triangulation::FromFFI(result.ok)))) : ecitygml::diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>>(ecitygml::diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline const ecitygml::Surface* ecitygml::Surface::try_from(const ecitygml::AbstractSurfaceKind& surface DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_Surface_try_from(surface.AsFFI());
    return ecitygml::Surface::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AbstractSurfacePatchKindIterator> ecitygml::Surface::patches() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Surface_patches(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractSurfacePatchKindIterator>(ecitygml::AbstractSurfacePatchKindIterator::FromFFI(result));
}

inline ecitygml::diplomat::result<double, std::unique_ptr<ecitygml::Error>> ecitygml::Surface::area_3d() const {
    auto result = ecitygml::capi::ecitygml_Surface_area_3d(this->AsFFI());
    return result.is_ok ? ecitygml::diplomat::result<double, std::unique_ptr<ecitygml::Error>>(ecitygml::diplomat::Ok<double>(result.ok)) : ecitygml::diplomat::result<double, std::unique_ptr<ecitygml::Error>>(ecitygml::diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline std::unique_ptr<ecitygml::DirectPositionIterator> ecitygml::Surface::points() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Surface_points(this->AsFFI());
    return std::unique_ptr<ecitygml::DirectPositionIterator>(ecitygml::DirectPositionIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::Envelope> ecitygml::Surface::compute_envelope() const {
    auto result = ecitygml::capi::ecitygml_Surface_compute_envelope(this->AsFFI());
    return std::unique_ptr<ecitygml::Envelope>(ecitygml::Envelope::FromFFI(result));
}

inline const ecitygml::capi::Surface* ecitygml::Surface::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::Surface*>(this);
}

inline ecitygml::capi::Surface* ecitygml::Surface::AsFFI() {
    return reinterpret_cast<ecitygml::capi::Surface*>(this);
}

inline const ecitygml::Surface* ecitygml::Surface::FromFFI(const ecitygml::capi::Surface* ptr) {
    return reinterpret_cast<const ecitygml::Surface*>(ptr);
}

inline ecitygml::Surface* ecitygml::Surface::FromFFI(ecitygml::capi::Surface* ptr) {
    return reinterpret_cast<ecitygml::Surface*>(ptr);
}

inline void ecitygml::Surface::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_Surface_destroy(reinterpret_cast<ecitygml::capi::Surface*>(ptr));
}


#endif // ECITYGML_Surface_HPP
