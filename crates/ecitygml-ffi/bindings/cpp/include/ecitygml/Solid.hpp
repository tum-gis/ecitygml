#ifndef ecitygml_Solid_HPP
#define ecitygml_Solid_HPP

#include "Solid.d.hpp"

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
#include "Id.hpp"
#include "Shell.hpp"
#include "ShellIterator.hpp"
#include "Triangulation.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_Solid_id(const ecitygml::capi::Solid* self);

    ecitygml::capi::CodeIterator* ecitygml_Solid_names(const ecitygml::capi::Solid* self);

    typedef struct ecitygml_Solid_triangulate_result {union {ecitygml::capi::Triangulation* ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_Solid_triangulate_result;
    ecitygml_Solid_triangulate_result ecitygml_Solid_triangulate(const ecitygml::capi::Solid* self);

    const ecitygml::capi::Solid* ecitygml_Solid_try_from(const ecitygml::capi::AbstractGeometryKind* geometry);

    const ecitygml::capi::Shell* ecitygml_Solid_exterior(const ecitygml::capi::Solid* self);

    ecitygml::capi::ShellIterator* ecitygml_Solid_interior(const ecitygml::capi::Solid* self);

    typedef struct ecitygml_Solid_volume_3d_result {union {double ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_Solid_volume_3d_result;
    ecitygml_Solid_volume_3d_result ecitygml_Solid_volume_3d(const ecitygml::capi::Solid* self);

    ecitygml::capi::Envelope* ecitygml_Solid_compute_envelope(const ecitygml::capi::Solid* self);

    ecitygml::capi::DirectPositionIterator* ecitygml_Solid_points(const ecitygml::capi::Solid* self);

    void ecitygml_Solid_destroy(Solid* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::Solid::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Solid_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::Solid::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Solid_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>> ecitygml::Solid::triangulate() const {
    auto result = ecitygml::capi::ecitygml_Solid_triangulate(this->AsFFI());
    return result.is_ok ? diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>>(diplomat::Ok<std::unique_ptr<ecitygml::Triangulation>>(std::unique_ptr<ecitygml::Triangulation>(ecitygml::Triangulation::FromFFI(result.ok)))) : diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>>(diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline const ecitygml::Solid* ecitygml::Solid::try_from(const ecitygml::AbstractGeometryKind& geometry DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_Solid_try_from(geometry.AsFFI());
    return ecitygml::Solid::FromFFI(result);
}

inline const ecitygml::Shell* ecitygml::Solid::exterior() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Solid_exterior(this->AsFFI());
    return ecitygml::Shell::FromFFI(result);
}

inline std::unique_ptr<ecitygml::ShellIterator> ecitygml::Solid::interior() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Solid_interior(this->AsFFI());
    return std::unique_ptr<ecitygml::ShellIterator>(ecitygml::ShellIterator::FromFFI(result));
}

inline diplomat::result<double, std::unique_ptr<ecitygml::Error>> ecitygml::Solid::volume_3d() const {
    auto result = ecitygml::capi::ecitygml_Solid_volume_3d(this->AsFFI());
    return result.is_ok ? diplomat::result<double, std::unique_ptr<ecitygml::Error>>(diplomat::Ok<double>(result.ok)) : diplomat::result<double, std::unique_ptr<ecitygml::Error>>(diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline std::unique_ptr<ecitygml::Envelope> ecitygml::Solid::compute_envelope() const {
    auto result = ecitygml::capi::ecitygml_Solid_compute_envelope(this->AsFFI());
    return std::unique_ptr<ecitygml::Envelope>(ecitygml::Envelope::FromFFI(result));
}

inline std::unique_ptr<ecitygml::DirectPositionIterator> ecitygml::Solid::points() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Solid_points(this->AsFFI());
    return std::unique_ptr<ecitygml::DirectPositionIterator>(ecitygml::DirectPositionIterator::FromFFI(result));
}

inline const ecitygml::capi::Solid* ecitygml::Solid::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::Solid*>(this);
}

inline ecitygml::capi::Solid* ecitygml::Solid::AsFFI() {
    return reinterpret_cast<ecitygml::capi::Solid*>(this);
}

inline const ecitygml::Solid* ecitygml::Solid::FromFFI(const ecitygml::capi::Solid* ptr) {
    return reinterpret_cast<const ecitygml::Solid*>(ptr);
}

inline ecitygml::Solid* ecitygml::Solid::FromFFI(ecitygml::capi::Solid* ptr) {
    return reinterpret_cast<ecitygml::Solid*>(ptr);
}

inline void ecitygml::Solid::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_Solid_destroy(reinterpret_cast<ecitygml::capi::Solid*>(ptr));
}


#endif // ecitygml_Solid_HPP
