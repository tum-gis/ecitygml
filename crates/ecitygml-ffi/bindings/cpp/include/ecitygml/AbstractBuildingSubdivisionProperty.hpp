#ifndef ecitygml_AbstractBuildingSubdivisionProperty_HPP
#define ecitygml_AbstractBuildingSubdivisionProperty_HPP

#include "AbstractBuildingSubdivisionProperty.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "AbstractBuildingSubdivisionKind.hpp"
#include "HRef.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::AbstractBuildingSubdivisionKind* ecitygml_AbstractBuildingSubdivisionProperty_object(const ecitygml::capi::AbstractBuildingSubdivisionProperty* self);

    const ecitygml::capi::HRef* ecitygml_AbstractBuildingSubdivisionProperty_href(const ecitygml::capi::AbstractBuildingSubdivisionProperty* self);

    void ecitygml_AbstractBuildingSubdivisionProperty_destroy(AbstractBuildingSubdivisionProperty* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::AbstractBuildingSubdivisionKind* ecitygml::AbstractBuildingSubdivisionProperty::object() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionProperty_object(this->AsFFI());
    return ecitygml::AbstractBuildingSubdivisionKind::FromFFI(result);
}

inline const ecitygml::HRef* ecitygml::AbstractBuildingSubdivisionProperty::href() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractBuildingSubdivisionProperty_href(this->AsFFI());
    return ecitygml::HRef::FromFFI(result);
}

inline const ecitygml::capi::AbstractBuildingSubdivisionProperty* ecitygml::AbstractBuildingSubdivisionProperty::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AbstractBuildingSubdivisionProperty*>(this);
}

inline ecitygml::capi::AbstractBuildingSubdivisionProperty* ecitygml::AbstractBuildingSubdivisionProperty::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AbstractBuildingSubdivisionProperty*>(this);
}

inline const ecitygml::AbstractBuildingSubdivisionProperty* ecitygml::AbstractBuildingSubdivisionProperty::FromFFI(const ecitygml::capi::AbstractBuildingSubdivisionProperty* ptr) {
    return reinterpret_cast<const ecitygml::AbstractBuildingSubdivisionProperty*>(ptr);
}

inline ecitygml::AbstractBuildingSubdivisionProperty* ecitygml::AbstractBuildingSubdivisionProperty::FromFFI(ecitygml::capi::AbstractBuildingSubdivisionProperty* ptr) {
    return reinterpret_cast<ecitygml::AbstractBuildingSubdivisionProperty*>(ptr);
}

inline void ecitygml::AbstractBuildingSubdivisionProperty::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AbstractBuildingSubdivisionProperty_destroy(reinterpret_cast<ecitygml::capi::AbstractBuildingSubdivisionProperty*>(ptr));
}


#endif // ecitygml_AbstractBuildingSubdivisionProperty_HPP
