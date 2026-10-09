#ifndef ecitygml_Triangle_HPP
#define ecitygml_Triangle_HPP

#include "Triangle.d.hpp"

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
#include "AbstractSurfacePatchKind.hpp"
#include "DirectPosition.hpp"
#include "DirectPositionIterator.hpp"
#include "Envelope.hpp"
#include "Error.hpp"
#include "Triangulation.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    typedef struct ecitygml_Triangle_triangulate_result {union {ecitygml::capi::Triangulation* ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_Triangle_triangulate_result;
    ecitygml_Triangle_triangulate_result ecitygml_Triangle_triangulate(const ecitygml::capi::Triangle* self);

    const ecitygml::capi::Triangle* ecitygml_Triangle_try_from(const ecitygml::capi::AbstractSurfacePatchKind* patch);

    const ecitygml::capi::AbstractRingKind* ecitygml_Triangle_exterior(const ecitygml::capi::Triangle* self);

    const ecitygml::capi::DirectPosition* ecitygml_Triangle_a(const ecitygml::capi::Triangle* self);

    const ecitygml::capi::DirectPosition* ecitygml_Triangle_b(const ecitygml::capi::Triangle* self);

    const ecitygml::capi::DirectPosition* ecitygml_Triangle_c(const ecitygml::capi::Triangle* self);

    double ecitygml_Triangle_area(const ecitygml::capi::Triangle* self);

    ecitygml::capi::DirectPositionIterator* ecitygml_Triangle_points(const ecitygml::capi::Triangle* self);

    ecitygml::capi::Envelope* ecitygml_Triangle_compute_envelope(const ecitygml::capi::Triangle* self);

    void ecitygml_Triangle_destroy(Triangle* self);

    } // extern "C"
} // namespace capi
} // namespace

inline diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>> ecitygml::Triangle::triangulate() const {
    auto result = ecitygml::capi::ecitygml_Triangle_triangulate(this->AsFFI());
    return result.is_ok ? diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>>(diplomat::Ok<std::unique_ptr<ecitygml::Triangulation>>(std::unique_ptr<ecitygml::Triangulation>(ecitygml::Triangulation::FromFFI(result.ok)))) : diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>>(diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline const ecitygml::Triangle* ecitygml::Triangle::try_from(const ecitygml::AbstractSurfacePatchKind& patch DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_Triangle_try_from(patch.AsFFI());
    return ecitygml::Triangle::FromFFI(result);
}

inline const ecitygml::AbstractRingKind& ecitygml::Triangle::exterior() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Triangle_exterior(this->AsFFI());
    return *ecitygml::AbstractRingKind::FromFFI(result);
}

inline const ecitygml::DirectPosition& ecitygml::Triangle::a() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Triangle_a(this->AsFFI());
    return *ecitygml::DirectPosition::FromFFI(result);
}

inline const ecitygml::DirectPosition& ecitygml::Triangle::b() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Triangle_b(this->AsFFI());
    return *ecitygml::DirectPosition::FromFFI(result);
}

inline const ecitygml::DirectPosition& ecitygml::Triangle::c() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Triangle_c(this->AsFFI());
    return *ecitygml::DirectPosition::FromFFI(result);
}

inline double ecitygml::Triangle::area() const {
    auto result = ecitygml::capi::ecitygml_Triangle_area(this->AsFFI());
    return result;
}

inline std::unique_ptr<ecitygml::DirectPositionIterator> ecitygml::Triangle::points() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Triangle_points(this->AsFFI());
    return std::unique_ptr<ecitygml::DirectPositionIterator>(ecitygml::DirectPositionIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::Envelope> ecitygml::Triangle::compute_envelope() const {
    auto result = ecitygml::capi::ecitygml_Triangle_compute_envelope(this->AsFFI());
    return std::unique_ptr<ecitygml::Envelope>(ecitygml::Envelope::FromFFI(result));
}

inline const ecitygml::capi::Triangle* ecitygml::Triangle::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::Triangle*>(this);
}

inline ecitygml::capi::Triangle* ecitygml::Triangle::AsFFI() {
    return reinterpret_cast<ecitygml::capi::Triangle*>(this);
}

inline const ecitygml::Triangle* ecitygml::Triangle::FromFFI(const ecitygml::capi::Triangle* ptr) {
    return reinterpret_cast<const ecitygml::Triangle*>(ptr);
}

inline ecitygml::Triangle* ecitygml::Triangle::FromFFI(ecitygml::capi::Triangle* ptr) {
    return reinterpret_cast<ecitygml::Triangle*>(ptr);
}

inline void ecitygml::Triangle::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_Triangle_destroy(reinterpret_cast<ecitygml::capi::Triangle*>(ptr));
}


#endif // ecitygml_Triangle_HPP
