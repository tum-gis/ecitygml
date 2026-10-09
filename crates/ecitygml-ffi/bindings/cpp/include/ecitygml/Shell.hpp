#ifndef ecitygml_Shell_HPP
#define ecitygml_Shell_HPP

#include "Shell.d.hpp"

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

    const ecitygml::capi::Id* ecitygml_Shell_id(const ecitygml::capi::Shell* self);

    ecitygml::capi::CodeIterator* ecitygml_Shell_names(const ecitygml::capi::Shell* self);

    typedef struct ecitygml_Shell_triangulate_result {union {ecitygml::capi::Triangulation* ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_Shell_triangulate_result;
    ecitygml_Shell_triangulate_result ecitygml_Shell_triangulate(const ecitygml::capi::Shell* self);

    const ecitygml::capi::Shell* ecitygml_Shell_try_from(const ecitygml::capi::AbstractSurfaceKind* surface);

    ecitygml::capi::AbstractSurfacePropertyIterator* ecitygml_Shell_members(const ecitygml::capi::Shell* self);

    ecitygml::capi::DirectPositionIterator* ecitygml_Shell_points(const ecitygml::capi::Shell* self);

    typedef struct ecitygml_Shell_area_3d_result {union {double ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_Shell_area_3d_result;
    ecitygml_Shell_area_3d_result ecitygml_Shell_area_3d(const ecitygml::capi::Shell* self);

    typedef struct ecitygml_Shell_volume_3d_result {union {double ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_Shell_volume_3d_result;
    ecitygml_Shell_volume_3d_result ecitygml_Shell_volume_3d(const ecitygml::capi::Shell* self);

    ecitygml::capi::Envelope* ecitygml_Shell_compute_envelope(const ecitygml::capi::Shell* self);

    void ecitygml_Shell_destroy(Shell* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::Shell::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Shell_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::Shell::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Shell_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>> ecitygml::Shell::triangulate() const {
    auto result = ecitygml::capi::ecitygml_Shell_triangulate(this->AsFFI());
    return result.is_ok ? diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>>(diplomat::Ok<std::unique_ptr<ecitygml::Triangulation>>(std::unique_ptr<ecitygml::Triangulation>(ecitygml::Triangulation::FromFFI(result.ok)))) : diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>>(diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline const ecitygml::Shell* ecitygml::Shell::try_from(const ecitygml::AbstractSurfaceKind& surface DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_Shell_try_from(surface.AsFFI());
    return ecitygml::Shell::FromFFI(result);
}

inline std::unique_ptr<ecitygml::AbstractSurfacePropertyIterator> ecitygml::Shell::members() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Shell_members(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractSurfacePropertyIterator>(ecitygml::AbstractSurfacePropertyIterator::FromFFI(result));
}

inline std::unique_ptr<ecitygml::DirectPositionIterator> ecitygml::Shell::points() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Shell_points(this->AsFFI());
    return std::unique_ptr<ecitygml::DirectPositionIterator>(ecitygml::DirectPositionIterator::FromFFI(result));
}

inline diplomat::result<double, std::unique_ptr<ecitygml::Error>> ecitygml::Shell::area_3d() const {
    auto result = ecitygml::capi::ecitygml_Shell_area_3d(this->AsFFI());
    return result.is_ok ? diplomat::result<double, std::unique_ptr<ecitygml::Error>>(diplomat::Ok<double>(result.ok)) : diplomat::result<double, std::unique_ptr<ecitygml::Error>>(diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline diplomat::result<double, std::unique_ptr<ecitygml::Error>> ecitygml::Shell::volume_3d() const {
    auto result = ecitygml::capi::ecitygml_Shell_volume_3d(this->AsFFI());
    return result.is_ok ? diplomat::result<double, std::unique_ptr<ecitygml::Error>>(diplomat::Ok<double>(result.ok)) : diplomat::result<double, std::unique_ptr<ecitygml::Error>>(diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline std::unique_ptr<ecitygml::Envelope> ecitygml::Shell::compute_envelope() const {
    auto result = ecitygml::capi::ecitygml_Shell_compute_envelope(this->AsFFI());
    return std::unique_ptr<ecitygml::Envelope>(ecitygml::Envelope::FromFFI(result));
}

inline const ecitygml::capi::Shell* ecitygml::Shell::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::Shell*>(this);
}

inline ecitygml::capi::Shell* ecitygml::Shell::AsFFI() {
    return reinterpret_cast<ecitygml::capi::Shell*>(this);
}

inline const ecitygml::Shell* ecitygml::Shell::FromFFI(const ecitygml::capi::Shell* ptr) {
    return reinterpret_cast<const ecitygml::Shell*>(ptr);
}

inline ecitygml::Shell* ecitygml::Shell::FromFFI(ecitygml::capi::Shell* ptr) {
    return reinterpret_cast<ecitygml::Shell*>(ptr);
}

inline void ecitygml::Shell::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_Shell_destroy(reinterpret_cast<ecitygml::capi::Shell*>(ptr));
}


#endif // ecitygml_Shell_HPP
