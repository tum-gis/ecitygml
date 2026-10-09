#ifndef ecitygml_CityObjectRelation_HPP
#define ecitygml_CityObjectRelation_HPP

#include "CityObjectRelation.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "GenericAttributeKindIterator.hpp"
#include "Reference.hpp"
#include "RelationTypeValue.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::RelationTypeValue* ecitygml_CityObjectRelation_relation_type(const ecitygml::capi::CityObjectRelation* self);

    const ecitygml::capi::Reference* ecitygml_CityObjectRelation_relation_to(const ecitygml::capi::CityObjectRelation* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_CityObjectRelation_generic_attributes(const ecitygml::capi::CityObjectRelation* self);

    void ecitygml_CityObjectRelation_destroy(CityObjectRelation* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::RelationTypeValue& ecitygml::CityObjectRelation::relation_type() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityObjectRelation_relation_type(this->AsFFI());
    return *ecitygml::RelationTypeValue::FromFFI(result);
}

inline const ecitygml::Reference& ecitygml::CityObjectRelation::relation_to() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityObjectRelation_relation_to(this->AsFFI());
    return *ecitygml::Reference::FromFFI(result);
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::CityObjectRelation::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_CityObjectRelation_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline const ecitygml::capi::CityObjectRelation* ecitygml::CityObjectRelation::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::CityObjectRelation*>(this);
}

inline ecitygml::capi::CityObjectRelation* ecitygml::CityObjectRelation::AsFFI() {
    return reinterpret_cast<ecitygml::capi::CityObjectRelation*>(this);
}

inline const ecitygml::CityObjectRelation* ecitygml::CityObjectRelation::FromFFI(const ecitygml::capi::CityObjectRelation* ptr) {
    return reinterpret_cast<const ecitygml::CityObjectRelation*>(ptr);
}

inline ecitygml::CityObjectRelation* ecitygml::CityObjectRelation::FromFFI(ecitygml::capi::CityObjectRelation* ptr) {
    return reinterpret_cast<ecitygml::CityObjectRelation*>(ptr);
}

inline void ecitygml::CityObjectRelation::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_CityObjectRelation_destroy(reinterpret_cast<ecitygml::capi::CityObjectRelation*>(ptr));
}


#endif // ecitygml_CityObjectRelation_HPP
