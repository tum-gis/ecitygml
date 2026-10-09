#ifndef ECITYGML_AbstractFeatureKindRef_HPP
#define ECITYGML_AbstractFeatureKindRef_HPP

#include "AbstractFeatureKindRef.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "AbstractCityObjectKindRef.hpp"
#include "AbstractSpaceBoundaryKind.hpp"
#include "FeatureType.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    ecitygml::capi::AbstractFeatureKindRef* ecitygml_AbstractFeatureKindRef_from_space_boundary(const ecitygml::capi::AbstractSpaceBoundaryKind* boundary);

    ecitygml::capi::AbstractFeatureKindRef* ecitygml_AbstractFeatureKindRef_from_city_object(const ecitygml::capi::AbstractCityObjectKindRef* city_object);

    ecitygml::capi::FeatureType ecitygml_AbstractFeatureKindRef_feature_type(const ecitygml::capi::AbstractFeatureKindRef* self);

    void ecitygml_AbstractFeatureKindRef_destroy(AbstractFeatureKindRef* self);

    } // extern "C"
} // namespace capi
} // namespace

inline std::unique_ptr<ecitygml::AbstractFeatureKindRef> ecitygml::AbstractFeatureKindRef::from_space_boundary(const ecitygml::AbstractSpaceBoundaryKind& boundary DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_AbstractFeatureKindRef_from_space_boundary(boundary.AsFFI());
    return std::unique_ptr<ecitygml::AbstractFeatureKindRef>(ecitygml::AbstractFeatureKindRef::FromFFI(result));
}

inline std::unique_ptr<ecitygml::AbstractFeatureKindRef> ecitygml::AbstractFeatureKindRef::from_city_object(const ecitygml::AbstractCityObjectKindRef& city_object DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_AbstractFeatureKindRef_from_city_object(city_object.AsFFI());
    return std::unique_ptr<ecitygml::AbstractFeatureKindRef>(ecitygml::AbstractFeatureKindRef::FromFFI(result));
}

inline ecitygml::FeatureType ecitygml::AbstractFeatureKindRef::feature_type() const {
    auto result = ecitygml::capi::ecitygml_AbstractFeatureKindRef_feature_type(this->AsFFI());
    return ecitygml::FeatureType::FromFFI(result);
}

inline const ecitygml::capi::AbstractFeatureKindRef* ecitygml::AbstractFeatureKindRef::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AbstractFeatureKindRef*>(this);
}

inline ecitygml::capi::AbstractFeatureKindRef* ecitygml::AbstractFeatureKindRef::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AbstractFeatureKindRef*>(this);
}

inline const ecitygml::AbstractFeatureKindRef* ecitygml::AbstractFeatureKindRef::FromFFI(const ecitygml::capi::AbstractFeatureKindRef* ptr) {
    return reinterpret_cast<const ecitygml::AbstractFeatureKindRef*>(ptr);
}

inline ecitygml::AbstractFeatureKindRef* ecitygml::AbstractFeatureKindRef::FromFFI(ecitygml::capi::AbstractFeatureKindRef* ptr) {
    return reinterpret_cast<ecitygml::AbstractFeatureKindRef*>(ptr);
}

inline void ecitygml::AbstractFeatureKindRef::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AbstractFeatureKindRef_destroy(reinterpret_cast<ecitygml::capi::AbstractFeatureKindRef*>(ptr));
}


#endif // ECITYGML_AbstractFeatureKindRef_HPP
