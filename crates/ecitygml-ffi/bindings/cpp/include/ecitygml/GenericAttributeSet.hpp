#ifndef ecitygml_GenericAttributeSet_HPP
#define ecitygml_GenericAttributeSet_HPP

#include "GenericAttributeSet.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "GenericAttributeKind.hpp"
#include "GenericAttributeKindIterator.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    const ecitygml::capi::GenericAttributeSet* ecitygml_GenericAttributeSet_try_from(const ecitygml::capi::GenericAttributeKind* attribute);

    diplomat::capi::DiplomatStringView ecitygml_GenericAttributeSet_name(const ecitygml::capi::GenericAttributeSet* self);

    ecitygml::capi::GenericAttributeKindIterator* ecitygml_GenericAttributeSet_generic_attributes(const ecitygml::capi::GenericAttributeSet* self);

    void ecitygml_GenericAttributeSet_destroy(GenericAttributeSet* self);

    } // extern "C"
} // namespace capi
} // namespace

inline const ecitygml::GenericAttributeSet* ecitygml::GenericAttributeSet::try_from(const ecitygml::GenericAttributeKind& attribute DIPLOMAT_LIFETIME_BOUND) {
    auto result = ecitygml::capi::ecitygml_GenericAttributeSet_try_from(attribute.AsFFI());
    return ecitygml::GenericAttributeSet::FromFFI(result);
}

inline std::string_view ecitygml::GenericAttributeSet::name() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_GenericAttributeSet_name(this->AsFFI());
    return std::string_view(result.data, result.len);
}

inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> ecitygml::GenericAttributeSet::generic_attributes() const DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_GenericAttributeSet_generic_attributes(this->AsFFI());
    return std::unique_ptr<ecitygml::GenericAttributeKindIterator>(ecitygml::GenericAttributeKindIterator::FromFFI(result));
}

inline const ecitygml::capi::GenericAttributeSet* ecitygml::GenericAttributeSet::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::GenericAttributeSet*>(this);
}

inline ecitygml::capi::GenericAttributeSet* ecitygml::GenericAttributeSet::AsFFI() {
    return reinterpret_cast<ecitygml::capi::GenericAttributeSet*>(this);
}

inline const ecitygml::GenericAttributeSet* ecitygml::GenericAttributeSet::FromFFI(const ecitygml::capi::GenericAttributeSet* ptr) {
    return reinterpret_cast<const ecitygml::GenericAttributeSet*>(ptr);
}

inline ecitygml::GenericAttributeSet* ecitygml::GenericAttributeSet::FromFFI(ecitygml::capi::GenericAttributeSet* ptr) {
    return reinterpret_cast<ecitygml::GenericAttributeSet*>(ptr);
}

inline void ecitygml::GenericAttributeSet::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_GenericAttributeSet_destroy(reinterpret_cast<ecitygml::capi::GenericAttributeSet*>(ptr));
}


#endif // ecitygml_GenericAttributeSet_HPP
