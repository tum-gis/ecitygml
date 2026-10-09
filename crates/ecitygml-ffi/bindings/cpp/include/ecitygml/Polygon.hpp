#ifndef ecitygml_Polygon_HPP
#define ecitygml_Polygon_HPP

#include "Polygon.d.hpp"

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
#include "AbstractSurfaceKind.hpp"
#include "CodeIterator.hpp"
#include "DirectPositionIterator.hpp"
#include "Envelope.hpp"
#include "Error.hpp"
#include "Id.hpp"
#include "Triangulation.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_Polygon_id(const ecitygml::capi::Polygon* self);

    ecitygml::capi::CodeIterator* ecitygml_Polygon_names(const ecitygml::capi::Polygon* self);

    typedef struct ecitygml_Polygon_triangulate_result {union {ecitygml::capi::Triangulation* ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_Polygon_triangulate_result;
    ecitygml_Polygon_triangulate_result ecitygml_Polygon_triangulate(const ecitygml::capi::Polygon* self);

    const ecitygml::capi::Polygon* ecitygml_Polygon_try_from(const ecitygml::capi::AbstractSurfaceKind* surface);

    const ecitygml::capi::AbstractRingKind* ecitygml_Polygon_exterior(const ecitygml::capi::Polygon* self);

    ecitygml::capi::AbstractRingKindIterator* ecitygml_Polygon_interior(const ecitygml::capi::Polygon* self);

    typedef struct ecitygml_Polygon_area_3d_result {union {double ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_Polygon_area_3d_result;
    ecitygml_Polygon_area_3d_result ecitygml_Polygon_area_3d(const ecitygml::capi::Polygon* self);

    ecitygml::capi::DirectPositionIterator* ecitygml_Polygon_points(const ecitygml::capi::Polygon* self);

    ecitygml::capi::Envelope* ecitygml_Polygon_compute_envelope(const ecitygml::capi::Polygon* self);

    void ecitygml_Polygon_destroy(Polygon* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::Polygon::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Polygon_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::Polygon::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Polygon_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>> ecitygml::Polygon::triangulate() const {
    auto result = ecitygml::capi::ecitygml_Polygon_triangulate(this->AsFFI());
    return result.is_ok ? diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>>(diplomat::Ok<std::unique_ptr<ecitygml::Triangulation>>(std::unique_ptr<ecitygml::Triangulation>(ecitygml::Triangulation::FromFFI(result.ok)))) : diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>>(diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline const ecitygml::Polygon* ecitygml::Polygon::try_from(const ecitygml::AbstractSurfaceKind& surface DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_Polygon_try_from(surface.AsFFI());
    return ecitygml::Polygon::FromFFI(result);
}

inline const ecitygml::AbstractRingKind* ecitygml::Polygon::exterior() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Polygon_exterior(this->AsFFI());
    return ecitygml::AbstractRingKind::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AbstractRingKindIterator> ecitygml::Polygon::interior() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Polygon_interior(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractRingKindIterator>(ecitygml::AbstractRingKindIterator::FromFFI(result));
}

inline diplomat::result<double, std::unique_ptr<ecitygml::Error>> ecitygml::Polygon::area_3d() const {
    auto result = ecitygml::capi::ecitygml_Polygon_area_3d(this->AsFFI());
    return result.is_ok ? diplomat::result<double, std::unique_ptr<ecitygml::Error>>(diplomat::Ok<double>(result.ok)) : diplomat::result<double, std::unique_ptr<ecitygml::Error>>(diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline std::unique_ptr<ecitygml::DirectPositionIterator> ecitygml::Polygon::points() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Polygon_points(this->AsFFI());
    return std::unique_ptr<ecitygml::DirectPositionIterator>(ecitygml::DirectPositionIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::Envelope> ecitygml::Polygon::compute_envelope() const {
    auto result = ecitygml::capi::ecitygml_Polygon_compute_envelope(this->AsFFI());
    return std::unique_ptr<ecitygml::Envelope>(ecitygml::Envelope::FromFFI(result));
}

inline const ecitygml::capi::Polygon* ecitygml::Polygon::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::Polygon*>(this);
}

inline ecitygml::capi::Polygon* ecitygml::Polygon::AsFFI() {
    return reinterpret_cast<ecitygml::capi::Polygon*>(this);
}

inline const ecitygml::Polygon* ecitygml::Polygon::FromFFI(const ecitygml::capi::Polygon* ptr) {
    return reinterpret_cast<const ecitygml::Polygon*>(ptr);
}

inline ecitygml::Polygon* ecitygml::Polygon::FromFFI(ecitygml::capi::Polygon* ptr) {
    return reinterpret_cast<ecitygml::Polygon*>(ptr);
}

inline void ecitygml::Polygon::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_Polygon_destroy(reinterpret_cast<ecitygml::capi::Polygon*>(ptr));
}


#endif // ecitygml_Polygon_HPP
