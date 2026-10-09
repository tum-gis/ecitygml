#ifndef ecitygml_PolygonPatch_HPP
#define ecitygml_PolygonPatch_HPP

#include "PolygonPatch.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "AbstractRingKind.hpp"
#include "AbstractRingKindIterator.hpp"
#include "AbstractSurfacePatchKind.hpp"
#include "DirectPositionIterator.hpp"
#include "Envelope.hpp"
#include "Error.hpp"
#include "Triangulation.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    typedef struct ecitygml_PolygonPatch_triangulate_result {union {ecitygml::capi::Triangulation* ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_PolygonPatch_triangulate_result;
    ecitygml_PolygonPatch_triangulate_result ecitygml_PolygonPatch_triangulate(const ecitygml::capi::PolygonPatch* self);

    const ecitygml::capi::PolygonPatch* ecitygml_PolygonPatch_try_from(const ecitygml::capi::AbstractSurfacePatchKind* patch);

    const ecitygml::capi::AbstractRingKind* ecitygml_PolygonPatch_exterior(const ecitygml::capi::PolygonPatch* self);

    ecitygml::capi::AbstractRingKindIterator* ecitygml_PolygonPatch_interior(const ecitygml::capi::PolygonPatch* self);

    typedef struct ecitygml_PolygonPatch_area_3d_result {union {double ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_PolygonPatch_area_3d_result;
    ecitygml_PolygonPatch_area_3d_result ecitygml_PolygonPatch_area_3d(const ecitygml::capi::PolygonPatch* self);

    ecitygml::capi::DirectPositionIterator* ecitygml_PolygonPatch_points(const ecitygml::capi::PolygonPatch* self);

    ecitygml::capi::Envelope* ecitygml_PolygonPatch_compute_envelope(const ecitygml::capi::PolygonPatch* self);

    void ecitygml_PolygonPatch_destroy(PolygonPatch* self);

    } // extern "C"
} // namespace capi
} // namespace

inline diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>> ecitygml::PolygonPatch::triangulate() const {
    auto result = ecitygml::capi::ecitygml_PolygonPatch_triangulate(this->AsFFI());
    return result.is_ok ? diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>>(diplomat::Ok<std::unique_ptr<ecitygml::Triangulation>>(std::unique_ptr<ecitygml::Triangulation>(ecitygml::Triangulation::FromFFI(result.ok)))) : diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>>(diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline const ecitygml::PolygonPatch* ecitygml::PolygonPatch::try_from(const ecitygml::AbstractSurfacePatchKind& patch DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_PolygonPatch_try_from(patch.AsFFI());
    return ecitygml::PolygonPatch::FromFFI(result);
}

inline const ecitygml::AbstractRingKind* ecitygml::PolygonPatch::exterior() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PolygonPatch_exterior(this->AsFFI());
    return ecitygml::AbstractRingKind::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AbstractRingKindIterator> ecitygml::PolygonPatch::interior() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PolygonPatch_interior(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractRingKindIterator>(ecitygml::AbstractRingKindIterator::FromFFI(result));
}

inline diplomat::result<double, std::unique_ptr<ecitygml::Error>> ecitygml::PolygonPatch::area_3d() const {
    auto result = ecitygml::capi::ecitygml_PolygonPatch_area_3d(this->AsFFI());
    return result.is_ok ? diplomat::result<double, std::unique_ptr<ecitygml::Error>>(diplomat::Ok<double>(result.ok)) : diplomat::result<double, std::unique_ptr<ecitygml::Error>>(diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline std::unique_ptr<ecitygml::DirectPositionIterator> ecitygml::PolygonPatch::points() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_PolygonPatch_points(this->AsFFI());
    return std::unique_ptr<ecitygml::DirectPositionIterator>(ecitygml::DirectPositionIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::Envelope> ecitygml::PolygonPatch::compute_envelope() const {
    auto result = ecitygml::capi::ecitygml_PolygonPatch_compute_envelope(this->AsFFI());
    return std::unique_ptr<ecitygml::Envelope>(ecitygml::Envelope::FromFFI(result));
}

inline const ecitygml::capi::PolygonPatch* ecitygml::PolygonPatch::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::PolygonPatch*>(this);
}

inline ecitygml::capi::PolygonPatch* ecitygml::PolygonPatch::AsFFI() {
    return reinterpret_cast<ecitygml::capi::PolygonPatch*>(this);
}

inline const ecitygml::PolygonPatch* ecitygml::PolygonPatch::FromFFI(const ecitygml::capi::PolygonPatch* ptr) {
    return reinterpret_cast<const ecitygml::PolygonPatch*>(ptr);
}

inline ecitygml::PolygonPatch* ecitygml::PolygonPatch::FromFFI(ecitygml::capi::PolygonPatch* ptr) {
    return reinterpret_cast<ecitygml::PolygonPatch*>(ptr);
}

inline void ecitygml::PolygonPatch::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_PolygonPatch_destroy(reinterpret_cast<ecitygml::capi::PolygonPatch*>(ptr));
}


#endif // ecitygml_PolygonPatch_HPP
