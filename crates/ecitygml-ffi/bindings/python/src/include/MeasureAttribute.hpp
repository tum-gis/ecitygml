#ifndef ECITYGML_MeasureAttribute_HPP
#define ECITYGML_MeasureAttribute_HPP

#include "MeasureAttribute.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "GenericAttributeKind.hpp"
#include "Measure.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::MeasureAttribute* ecitygml_MeasureAttribute_try_from(const ecitygml::capi::GenericAttributeKind* attribute);

    ecitygml::diplomat::capi::DiplomatStringView ecitygml_MeasureAttribute_name(const ecitygml::capi::MeasureAttribute* self);

    const ecitygml::capi::Measure* ecitygml_MeasureAttribute_value(const ecitygml::capi::MeasureAttribute* self);

    void ecitygml_MeasureAttribute_destroy(MeasureAttribute* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::MeasureAttribute* ecitygml::MeasureAttribute::try_from(const ecitygml::GenericAttributeKind& attribute DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_MeasureAttribute_try_from(attribute.AsFFI());
    return ecitygml::MeasureAttribute::FromFFI(result);
}

inline std::string_view ecitygml::MeasureAttribute::name() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_MeasureAttribute_name(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline const ecitygml::Measure& ecitygml::MeasureAttribute::value() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_MeasureAttribute_value(this->AsFFI());
    return *ecitygml::Measure::FromFFI(result);
}

inline const ecitygml::capi::MeasureAttribute* ecitygml::MeasureAttribute::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::MeasureAttribute*>(this);
}

inline ecitygml::capi::MeasureAttribute* ecitygml::MeasureAttribute::AsFFI() {
    return reinterpret_cast<ecitygml::capi::MeasureAttribute*>(this);
}

inline const ecitygml::MeasureAttribute* ecitygml::MeasureAttribute::FromFFI(const ecitygml::capi::MeasureAttribute* ptr) {
    return reinterpret_cast<const ecitygml::MeasureAttribute*>(ptr);
}

inline ecitygml::MeasureAttribute* ecitygml::MeasureAttribute::FromFFI(ecitygml::capi::MeasureAttribute* ptr) {
    return reinterpret_cast<ecitygml::MeasureAttribute*>(ptr);
}

inline void ecitygml::MeasureAttribute::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_MeasureAttribute_destroy(reinterpret_cast<ecitygml::capi::MeasureAttribute*>(ptr));
}


#endif // ECITYGML_MeasureAttribute_HPP
