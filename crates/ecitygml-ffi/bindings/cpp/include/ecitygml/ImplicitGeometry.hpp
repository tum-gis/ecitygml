#ifndef ecitygml_ImplicitGeometry_HPP
#define ecitygml_ImplicitGeometry_HPP

#include "ImplicitGeometry.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "AbstractGeometryProperty.hpp"
#include "Envelope.hpp"
#include "Id.hpp"
#include "MimeTypeValue.hpp"
#include "PointProperty.hpp"
#include "TransformationMatrix4x4.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::Id* ecitygml_ImplicitGeometry_object_id(const ecitygml::capi::ImplicitGeometry* self);

    const ecitygml::capi::TransformationMatrix4x4* ecitygml_ImplicitGeometry_transformation_matrix(const ecitygml::capi::ImplicitGeometry* self);

    const ecitygml::capi::MimeTypeValue* ecitygml_ImplicitGeometry_mime_type(const ecitygml::capi::ImplicitGeometry* self);

    typedef struct ecitygml_ImplicitGeometry_library_object_result {union {diplomat::capi::DiplomatStringView ok; }; bool is_ok;} ecitygml_ImplicitGeometry_library_object_result;
    ecitygml_ImplicitGeometry_library_object_result ecitygml_ImplicitGeometry_library_object(const ecitygml::capi::ImplicitGeometry* self);

    const ecitygml::capi::PointProperty* ecitygml_ImplicitGeometry_reference_point(const ecitygml::capi::ImplicitGeometry* self);

    const ecitygml::capi::AbstractGeometryProperty* ecitygml_ImplicitGeometry_relative_geometry(const ecitygml::capi::ImplicitGeometry* self);

    ecitygml::capi::Envelope* ecitygml_ImplicitGeometry_compute_envelope(const ecitygml::capi::ImplicitGeometry* self);

    void ecitygml_ImplicitGeometry_destroy(ImplicitGeometry* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::Id& ecitygml::ImplicitGeometry::object_id() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_ImplicitGeometry_object_id(this->AsFFI());
    return *ecitygml::Id::FromFFI(result);
}

inline const ecitygml::TransformationMatrix4x4& ecitygml::ImplicitGeometry::transformation_matrix() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_ImplicitGeometry_transformation_matrix(this->AsFFI());
    return *ecitygml::TransformationMatrix4x4::FromFFI(result);
}

inline const ecitygml::MimeTypeValue* ecitygml::ImplicitGeometry::mime_type() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_ImplicitGeometry_mime_type(this->AsFFI());
    return ecitygml::MimeTypeValue::FromFFI(result);
}

inline std::optional<std::string_view> ecitygml::ImplicitGeometry::library_object() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_ImplicitGeometry_library_object(this->AsFFI());
    return result.is_ok ? std::optional<std::string_view>(std::string_view(result.ok.data, result.ok.len)) : std::nullopt;
}

inline const ecitygml::PointProperty& ecitygml::ImplicitGeometry::reference_point() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_ImplicitGeometry_reference_point(this->AsFFI());
    return *ecitygml::PointProperty::FromFFI(result);
}

inline const ecitygml::AbstractGeometryProperty* ecitygml::ImplicitGeometry::relative_geometry() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_ImplicitGeometry_relative_geometry(this->AsFFI());
    return ecitygml::AbstractGeometryProperty::FromFFI(result);
}

inline std::unique_ptr<ecitygml::Envelope> ecitygml::ImplicitGeometry::compute_envelope() const {
    auto result = ecitygml::capi::ecitygml_ImplicitGeometry_compute_envelope(this->AsFFI());
    return std::unique_ptr<ecitygml::Envelope>(ecitygml::Envelope::FromFFI(result));
}

inline const ecitygml::capi::ImplicitGeometry* ecitygml::ImplicitGeometry::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::ImplicitGeometry*>(this);
}

inline ecitygml::capi::ImplicitGeometry* ecitygml::ImplicitGeometry::AsFFI() {
    return reinterpret_cast<ecitygml::capi::ImplicitGeometry*>(this);
}

inline const ecitygml::ImplicitGeometry* ecitygml::ImplicitGeometry::FromFFI(const ecitygml::capi::ImplicitGeometry* ptr) {
    return reinterpret_cast<const ecitygml::ImplicitGeometry*>(ptr);
}

inline ecitygml::ImplicitGeometry* ecitygml::ImplicitGeometry::FromFFI(ecitygml::capi::ImplicitGeometry* ptr) {
    return reinterpret_cast<ecitygml::ImplicitGeometry*>(ptr);
}

inline void ecitygml::ImplicitGeometry::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_ImplicitGeometry_destroy(reinterpret_cast<ecitygml::capi::ImplicitGeometry*>(ptr));
}


#endif // ecitygml_ImplicitGeometry_HPP
