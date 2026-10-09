#ifndef ecitygml_AbstractSurfaceKind_HPP
#define ecitygml_AbstractSurfaceKind_HPP

#include "AbstractSurfaceKind.d.hpp"

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
#include "CodeIterator.hpp"
#include "DirectPositionIterator.hpp"
#include "Envelope.hpp"
#include "Error.hpp"
#include "GeometryType.hpp"
#include "Id.hpp"
#include "Triangulation.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_AbstractSurfaceKind_id(const ecitygml::capi::AbstractSurfaceKind* self);

    ecitygml::capi::CodeIterator* ecitygml_AbstractSurfaceKind_names(const ecitygml::capi::AbstractSurfaceKind* self);

    typedef struct ecitygml_AbstractSurfaceKind_triangulate_result {union {ecitygml::capi::Triangulation* ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_AbstractSurfaceKind_triangulate_result;
    ecitygml_AbstractSurfaceKind_triangulate_result ecitygml_AbstractSurfaceKind_triangulate(const ecitygml::capi::AbstractSurfaceKind* self);

    const ecitygml::capi::AbstractSurfaceKind* ecitygml_AbstractSurfaceKind_try_from(const ecitygml::capi::AbstractGeometryKind* geometry);

    ecitygml::capi::GeometryType ecitygml_AbstractSurfaceKind_geometry_type(const ecitygml::capi::AbstractSurfaceKind* self);

    typedef struct ecitygml_AbstractSurfaceKind_area_3d_result {union {double ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_AbstractSurfaceKind_area_3d_result;
    ecitygml_AbstractSurfaceKind_area_3d_result ecitygml_AbstractSurfaceKind_area_3d(const ecitygml::capi::AbstractSurfaceKind* self);

    ecitygml::capi::DirectPositionIterator* ecitygml_AbstractSurfaceKind_points(const ecitygml::capi::AbstractSurfaceKind* self);

    ecitygml::capi::Envelope* ecitygml_AbstractSurfaceKind_compute_envelope(const ecitygml::capi::AbstractSurfaceKind* self);

    void ecitygml_AbstractSurfaceKind_destroy(AbstractSurfaceKind* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::AbstractSurfaceKind::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractSurfaceKind_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::AbstractSurfaceKind::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractSurfaceKind_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>> ecitygml::AbstractSurfaceKind::triangulate() const {
    auto result = ecitygml::capi::ecitygml_AbstractSurfaceKind_triangulate(this->AsFFI());
    return result.is_ok ? diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>>(diplomat::Ok<std::unique_ptr<ecitygml::Triangulation>>(std::unique_ptr<ecitygml::Triangulation>(ecitygml::Triangulation::FromFFI(result.ok)))) : diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>>(diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline const ecitygml::AbstractSurfaceKind* ecitygml::AbstractSurfaceKind::try_from(const ecitygml::AbstractGeometryKind& geometry DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_AbstractSurfaceKind_try_from(geometry.AsFFI());
    return ecitygml::AbstractSurfaceKind::FromFFI(result);
}

inline ecitygml::GeometryType ecitygml::AbstractSurfaceKind::geometry_type() const {
    auto result = ecitygml::capi::ecitygml_AbstractSurfaceKind_geometry_type(this->AsFFI());
    return ecitygml::GeometryType::FromFFI(result);
}

inline diplomat::result<double, std::unique_ptr<ecitygml::Error>> ecitygml::AbstractSurfaceKind::area_3d() const {
    auto result = ecitygml::capi::ecitygml_AbstractSurfaceKind_area_3d(this->AsFFI());
    return result.is_ok ? diplomat::result<double, std::unique_ptr<ecitygml::Error>>(diplomat::Ok<double>(result.ok)) : diplomat::result<double, std::unique_ptr<ecitygml::Error>>(diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline std::unique_ptr<ecitygml::DirectPositionIterator> ecitygml::AbstractSurfaceKind::points() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractSurfaceKind_points(this->AsFFI());
    return std::unique_ptr<ecitygml::DirectPositionIterator>(ecitygml::DirectPositionIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::Envelope> ecitygml::AbstractSurfaceKind::compute_envelope() const {
    auto result = ecitygml::capi::ecitygml_AbstractSurfaceKind_compute_envelope(this->AsFFI());
    return std::unique_ptr<ecitygml::Envelope>(ecitygml::Envelope::FromFFI(result));
}

inline const ecitygml::capi::AbstractSurfaceKind* ecitygml::AbstractSurfaceKind::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AbstractSurfaceKind*>(this);
}

inline ecitygml::capi::AbstractSurfaceKind* ecitygml::AbstractSurfaceKind::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AbstractSurfaceKind*>(this);
}

inline const ecitygml::AbstractSurfaceKind* ecitygml::AbstractSurfaceKind::FromFFI(const ecitygml::capi::AbstractSurfaceKind* ptr) {
    return reinterpret_cast<const ecitygml::AbstractSurfaceKind*>(ptr);
}

inline ecitygml::AbstractSurfaceKind* ecitygml::AbstractSurfaceKind::FromFFI(ecitygml::capi::AbstractSurfaceKind* ptr) {
    return reinterpret_cast<ecitygml::AbstractSurfaceKind*>(ptr);
}

inline void ecitygml::AbstractSurfaceKind::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AbstractSurfaceKind_destroy(reinterpret_cast<ecitygml::capi::AbstractSurfaceKind*>(ptr));
}


#endif // ecitygml_AbstractSurfaceKind_HPP
