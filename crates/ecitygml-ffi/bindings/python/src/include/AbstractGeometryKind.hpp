#ifndef ECITYGML_AbstractGeometryKind_HPP
#define ECITYGML_AbstractGeometryKind_HPP

#include "AbstractGeometryKind.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "CodeIterator.hpp"
#include "Envelope.hpp"
#include "Error.hpp"
#include "GeometryType.hpp"
#include "Id.hpp"
#include "Triangulation.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_AbstractGeometryKind_id(const ecitygml::capi::AbstractGeometryKind* self);

    ecitygml::capi::CodeIterator* ecitygml_AbstractGeometryKind_names(const ecitygml::capi::AbstractGeometryKind* self);

    typedef struct ecitygml_AbstractGeometryKind_triangulate_result {union {ecitygml::capi::Triangulation* ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_AbstractGeometryKind_triangulate_result;
    ecitygml_AbstractGeometryKind_triangulate_result ecitygml_AbstractGeometryKind_triangulate(const ecitygml::capi::AbstractGeometryKind* self);

    ecitygml::capi::GeometryType ecitygml_AbstractGeometryKind_geometry_type(const ecitygml::capi::AbstractGeometryKind* self);

    ecitygml::capi::Envelope* ecitygml_AbstractGeometryKind_compute_envelope(const ecitygml::capi::AbstractGeometryKind* self);

    void ecitygml_AbstractGeometryKind_destroy(AbstractGeometryKind* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::AbstractGeometryKind::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractGeometryKind_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::AbstractGeometryKind::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractGeometryKind_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline ecitygml::diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>> ecitygml::AbstractGeometryKind::triangulate() const {
    auto result = ecitygml::capi::ecitygml_AbstractGeometryKind_triangulate(this->AsFFI());
    return result.is_ok ? ecitygml::diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>>(ecitygml::diplomat::Ok<std::unique_ptr<ecitygml::Triangulation>>(std::unique_ptr<ecitygml::Triangulation>(ecitygml::Triangulation::FromFFI(result.ok)))) : ecitygml::diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>>(ecitygml::diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline ecitygml::GeometryType ecitygml::AbstractGeometryKind::geometry_type() const {
    auto result = ecitygml::capi::ecitygml_AbstractGeometryKind_geometry_type(this->AsFFI());
    return ecitygml::GeometryType::FromFFI(result);
}

inline std::unique_ptr<ecitygml::Envelope> ecitygml::AbstractGeometryKind::compute_envelope() const {
    auto result = ecitygml::capi::ecitygml_AbstractGeometryKind_compute_envelope(this->AsFFI());
    return std::unique_ptr<ecitygml::Envelope>(ecitygml::Envelope::FromFFI(result));
}

inline const ecitygml::capi::AbstractGeometryKind* ecitygml::AbstractGeometryKind::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AbstractGeometryKind*>(this);
}

inline ecitygml::capi::AbstractGeometryKind* ecitygml::AbstractGeometryKind::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AbstractGeometryKind*>(this);
}

inline const ecitygml::AbstractGeometryKind* ecitygml::AbstractGeometryKind::FromFFI(const ecitygml::capi::AbstractGeometryKind* ptr) {
    return reinterpret_cast<const ecitygml::AbstractGeometryKind*>(ptr);
}

inline ecitygml::AbstractGeometryKind* ecitygml::AbstractGeometryKind::FromFFI(ecitygml::capi::AbstractGeometryKind* ptr) {
    return reinterpret_cast<ecitygml::AbstractGeometryKind*>(ptr);
}

inline void ecitygml::AbstractGeometryKind::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AbstractGeometryKind_destroy(reinterpret_cast<ecitygml::capi::AbstractGeometryKind*>(ptr));
}


#endif // ECITYGML_AbstractGeometryKind_HPP
