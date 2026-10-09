#ifndef ecitygml_CityObjectRelationProperty_HPP
#define ecitygml_CityObjectRelationProperty_HPP

#include "CityObjectRelationProperty.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "CityObjectRelation.hpp"
#include "HRef.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::CityObjectRelation* ecitygml_CityObjectRelationProperty_object(const ecitygml::capi::CityObjectRelationProperty* self);

    const ecitygml::capi::HRef* ecitygml_CityObjectRelationProperty_href(const ecitygml::capi::CityObjectRelationProperty* self);

    void ecitygml_CityObjectRelationProperty_destroy(CityObjectRelationProperty* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::CityObjectRelation* ecitygml::CityObjectRelationProperty::object() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityObjectRelationProperty_object(this->AsFFI());
    return ecitygml::CityObjectRelation::FromFFI(result);
}

inline const ecitygml::HRef* ecitygml::CityObjectRelationProperty::href() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityObjectRelationProperty_href(this->AsFFI());
    return ecitygml::HRef::FromFFI(result);
}

inline const ecitygml::capi::CityObjectRelationProperty* ecitygml::CityObjectRelationProperty::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::CityObjectRelationProperty*>(this);
}

inline ecitygml::capi::CityObjectRelationProperty* ecitygml::CityObjectRelationProperty::AsFFI() {
    return reinterpret_cast<ecitygml::capi::CityObjectRelationProperty*>(this);
}

inline const ecitygml::CityObjectRelationProperty* ecitygml::CityObjectRelationProperty::FromFFI(const ecitygml::capi::CityObjectRelationProperty* ptr) {
    return reinterpret_cast<const ecitygml::CityObjectRelationProperty*>(ptr);
}

inline ecitygml::CityObjectRelationProperty* ecitygml::CityObjectRelationProperty::FromFFI(ecitygml::capi::CityObjectRelationProperty* ptr) {
    return reinterpret_cast<ecitygml::CityObjectRelationProperty*>(ptr);
}

inline void ecitygml::CityObjectRelationProperty::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_CityObjectRelationProperty_destroy(reinterpret_cast<ecitygml::capi::CityObjectRelationProperty*>(ptr));
}


#endif // ecitygml_CityObjectRelationProperty_HPP
