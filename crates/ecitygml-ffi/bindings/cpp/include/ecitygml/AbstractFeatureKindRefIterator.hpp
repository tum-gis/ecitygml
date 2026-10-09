#ifndef ecitygml_AbstractFeatureKindRefIterator_HPP
#define ecitygml_AbstractFeatureKindRefIterator_HPP

#include "AbstractFeatureKindRefIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "AbstractFeatureKindRef.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    ecitygml::capi::AbstractFeatureKindRef* ecitygml_AbstractFeatureKindRefIterator_next(ecitygml::capi::AbstractFeatureKindRefIterator* self);

    void ecitygml_AbstractFeatureKindRefIterator_destroy(AbstractFeatureKindRefIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline std::unique_ptr<ecitygml::AbstractFeatureKindRef> ecitygml::AbstractFeatureKindRefIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractFeatureKindRefIterator_next(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractFeatureKindRef>(ecitygml::AbstractFeatureKindRef::FromFFI(result));
}

inline const ecitygml::capi::AbstractFeatureKindRefIterator* ecitygml::AbstractFeatureKindRefIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AbstractFeatureKindRefIterator*>(this);
}

inline ecitygml::capi::AbstractFeatureKindRefIterator* ecitygml::AbstractFeatureKindRefIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AbstractFeatureKindRefIterator*>(this);
}

inline const ecitygml::AbstractFeatureKindRefIterator* ecitygml::AbstractFeatureKindRefIterator::FromFFI(const ecitygml::capi::AbstractFeatureKindRefIterator* ptr) {
    return reinterpret_cast<const ecitygml::AbstractFeatureKindRefIterator*>(ptr);
}

inline ecitygml::AbstractFeatureKindRefIterator* ecitygml::AbstractFeatureKindRefIterator::FromFFI(ecitygml::capi::AbstractFeatureKindRefIterator* ptr) {
    return reinterpret_cast<ecitygml::AbstractFeatureKindRefIterator*>(ptr);
}

inline void ecitygml::AbstractFeatureKindRefIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AbstractFeatureKindRefIterator_destroy(reinterpret_cast<ecitygml::capi::AbstractFeatureKindRefIterator*>(ptr));
}


#endif // ecitygml_AbstractFeatureKindRefIterator_HPP
