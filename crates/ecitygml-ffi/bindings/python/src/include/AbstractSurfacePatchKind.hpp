#ifndef ECITYGML_AbstractSurfacePatchKind_HPP
#define ECITYGML_AbstractSurfacePatchKind_HPP

#include "AbstractSurfacePatchKind.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "DirectPositionIterator.hpp"
#include "Envelope.hpp"
#include "Error.hpp"
#include "Triangulation.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    typedef struct ecitygml_AbstractSurfacePatchKind_triangulate_result {union {ecitygml::capi::Triangulation* ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_AbstractSurfacePatchKind_triangulate_result;
    ecitygml_AbstractSurfacePatchKind_triangulate_result ecitygml_AbstractSurfacePatchKind_triangulate(const ecitygml::capi::AbstractSurfacePatchKind* self);

    typedef struct ecitygml_AbstractSurfacePatchKind_area_3d_result {union {double ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_AbstractSurfacePatchKind_area_3d_result;
    ecitygml_AbstractSurfacePatchKind_area_3d_result ecitygml_AbstractSurfacePatchKind_area_3d(const ecitygml::capi::AbstractSurfacePatchKind* self);

    ecitygml::capi::DirectPositionIterator* ecitygml_AbstractSurfacePatchKind_points(const ecitygml::capi::AbstractSurfacePatchKind* self);

    ecitygml::capi::Envelope* ecitygml_AbstractSurfacePatchKind_compute_envelope(const ecitygml::capi::AbstractSurfacePatchKind* self);

    void ecitygml_AbstractSurfacePatchKind_destroy(AbstractSurfacePatchKind* self);

    } // extern "C"
} // namespace capi
} // namespace

inline ecitygml::diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>> ecitygml::AbstractSurfacePatchKind::triangulate() const {
    auto result = ecitygml::capi::ecitygml_AbstractSurfacePatchKind_triangulate(this->AsFFI());
    return result.is_ok ? ecitygml::diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>>(ecitygml::diplomat::Ok<std::unique_ptr<ecitygml::Triangulation>>(std::unique_ptr<ecitygml::Triangulation>(ecitygml::Triangulation::FromFFI(result.ok)))) : ecitygml::diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>>(ecitygml::diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline ecitygml::diplomat::result<double, std::unique_ptr<ecitygml::Error>> ecitygml::AbstractSurfacePatchKind::area_3d() const {
    auto result = ecitygml::capi::ecitygml_AbstractSurfacePatchKind_area_3d(this->AsFFI());
    return result.is_ok ? ecitygml::diplomat::result<double, std::unique_ptr<ecitygml::Error>>(ecitygml::diplomat::Ok<double>(result.ok)) : ecitygml::diplomat::result<double, std::unique_ptr<ecitygml::Error>>(ecitygml::diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline std::unique_ptr<ecitygml::DirectPositionIterator> ecitygml::AbstractSurfacePatchKind::points() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractSurfacePatchKind_points(this->AsFFI());
    return std::unique_ptr<ecitygml::DirectPositionIterator>(ecitygml::DirectPositionIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::Envelope> ecitygml::AbstractSurfacePatchKind::compute_envelope() const {
    auto result = ecitygml::capi::ecitygml_AbstractSurfacePatchKind_compute_envelope(this->AsFFI());
    return std::unique_ptr<ecitygml::Envelope>(ecitygml::Envelope::FromFFI(result));
}

inline const ecitygml::capi::AbstractSurfacePatchKind* ecitygml::AbstractSurfacePatchKind::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AbstractSurfacePatchKind*>(this);
}

inline ecitygml::capi::AbstractSurfacePatchKind* ecitygml::AbstractSurfacePatchKind::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AbstractSurfacePatchKind*>(this);
}

inline const ecitygml::AbstractSurfacePatchKind* ecitygml::AbstractSurfacePatchKind::FromFFI(const ecitygml::capi::AbstractSurfacePatchKind* ptr) {
    return reinterpret_cast<const ecitygml::AbstractSurfacePatchKind*>(ptr);
}

inline ecitygml::AbstractSurfacePatchKind* ecitygml::AbstractSurfacePatchKind::FromFFI(ecitygml::capi::AbstractSurfacePatchKind* ptr) {
    return reinterpret_cast<ecitygml::AbstractSurfacePatchKind*>(ptr);
}

inline void ecitygml::AbstractSurfacePatchKind::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AbstractSurfacePatchKind_destroy(reinterpret_cast<ecitygml::capi::AbstractSurfacePatchKind*>(ptr));
}


#endif // ECITYGML_AbstractSurfacePatchKind_HPP
