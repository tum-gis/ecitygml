#ifndef ECITYGML_AbstractCityObjectKindRef_HPP
#define ECITYGML_AbstractCityObjectKindRef_HPP

#include "AbstractCityObjectKindRef.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "FeatureType.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    ecitygml::capi::FeatureType ecitygml_AbstractCityObjectKindRef_feature_type(const ecitygml::capi::AbstractCityObjectKindRef* self);

    void ecitygml_AbstractCityObjectKindRef_destroy(AbstractCityObjectKindRef* self);

    } // extern "C"
} // namespace capi
} // namespace

inline ecitygml::FeatureType ecitygml::AbstractCityObjectKindRef::feature_type() const {
    auto result = ecitygml::capi::ecitygml_AbstractCityObjectKindRef_feature_type(this->AsFFI());
    return ecitygml::FeatureType::FromFFI(result);
}

inline const ecitygml::capi::AbstractCityObjectKindRef* ecitygml::AbstractCityObjectKindRef::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AbstractCityObjectKindRef*>(this);
}

inline ecitygml::capi::AbstractCityObjectKindRef* ecitygml::AbstractCityObjectKindRef::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AbstractCityObjectKindRef*>(this);
}

inline const ecitygml::AbstractCityObjectKindRef* ecitygml::AbstractCityObjectKindRef::FromFFI(const ecitygml::capi::AbstractCityObjectKindRef* ptr) {
    return reinterpret_cast<const ecitygml::AbstractCityObjectKindRef*>(ptr);
}

inline ecitygml::AbstractCityObjectKindRef* ecitygml::AbstractCityObjectKindRef::FromFFI(ecitygml::capi::AbstractCityObjectKindRef* ptr) {
    return reinterpret_cast<ecitygml::AbstractCityObjectKindRef*>(ptr);
}

inline void ecitygml::AbstractCityObjectKindRef::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AbstractCityObjectKindRef_destroy(reinterpret_cast<ecitygml::capi::AbstractCityObjectKindRef*>(ptr));
}


#endif // ECITYGML_AbstractCityObjectKindRef_HPP
