#ifndef ecitygml_Point_HPP
#define ecitygml_Point_HPP

#include "Point.d.hpp"

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
#include "DirectPosition.hpp"
#include "Envelope.hpp"
#include "Id.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_Point_id(const ecitygml::capi::Point* self);

    ecitygml::capi::CodeIterator* ecitygml_Point_names(const ecitygml::capi::Point* self);

    const ecitygml::capi::Point* ecitygml_Point_try_from(const ecitygml::capi::AbstractGeometryKind* geometry);

    const ecitygml::capi::DirectPosition* ecitygml_Point_pos(const ecitygml::capi::Point* self);

    ecitygml::capi::Envelope* ecitygml_Point_compute_envelope(const ecitygml::capi::Point* self);

    void ecitygml_Point_destroy(Point* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id* ecitygml::Point::id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Point_id(this->AsFFI());
    return ecitygml::Id::FromFFI(result);
}

inline std::unique_ptr<ecitygml::CodeIterator> ecitygml::Point::names() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Point_names(this->AsFFI());
    return std::unique_ptr<ecitygml::CodeIterator>(ecitygml::CodeIterator::FromFFI(result));
}

inline const ecitygml::Point* ecitygml::Point::try_from(const ecitygml::AbstractGeometryKind& geometry DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_Point_try_from(geometry.AsFFI());
    return ecitygml::Point::FromFFI(result);
}

inline const ecitygml::DirectPosition& ecitygml::Point::pos() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_Point_pos(this->AsFFI());
    return *ecitygml::DirectPosition::FromFFI(result);
}

inline std::unique_ptr<ecitygml::Envelope> ecitygml::Point::compute_envelope() const {
    auto result = ecitygml::capi::ecitygml_Point_compute_envelope(this->AsFFI());
    return std::unique_ptr<ecitygml::Envelope>(ecitygml::Envelope::FromFFI(result));
}

inline const ecitygml::capi::Point* ecitygml::Point::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::Point*>(this);
}

inline ecitygml::capi::Point* ecitygml::Point::AsFFI() {
    return reinterpret_cast<ecitygml::capi::Point*>(this);
}

inline const ecitygml::Point* ecitygml::Point::FromFFI(const ecitygml::capi::Point* ptr) {
    return reinterpret_cast<const ecitygml::Point*>(ptr);
}

inline ecitygml::Point* ecitygml::Point::FromFFI(ecitygml::capi::Point* ptr) {
    return reinterpret_cast<ecitygml::Point*>(ptr);
}

inline void ecitygml::Point::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_Point_destroy(reinterpret_cast<ecitygml::capi::Point*>(ptr));
}


#endif // ecitygml_Point_HPP
