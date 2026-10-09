#ifndef ecitygml_AbstractCityObjectKindRefIterator_HPP
#define ecitygml_AbstractCityObjectKindRefIterator_HPP

#include "AbstractCityObjectKindRefIterator.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "AbstractCityObjectKindRef.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    ecitygml::capi::AbstractCityObjectKindRef* ecitygml_AbstractCityObjectKindRefIterator_next(ecitygml::capi::AbstractCityObjectKindRefIterator* self);

    void ecitygml_AbstractCityObjectKindRefIterator_destroy(AbstractCityObjectKindRefIterator* self);

    } // extern "C"
} // namespace capi
} // namespace

inline std::unique_ptr<ecitygml::AbstractCityObjectKindRef> ecitygml::AbstractCityObjectKindRefIterator::next() DIPLOMAT_LIFETIME_BOUND {
    auto result = ecitygml::capi::ecitygml_AbstractCityObjectKindRefIterator_next(this->AsFFI());
    return std::unique_ptr<ecitygml::AbstractCityObjectKindRef>(ecitygml::AbstractCityObjectKindRef::FromFFI(result));
}

inline const ecitygml::capi::AbstractCityObjectKindRefIterator* ecitygml::AbstractCityObjectKindRefIterator::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::AbstractCityObjectKindRefIterator*>(this);
}

inline ecitygml::capi::AbstractCityObjectKindRefIterator* ecitygml::AbstractCityObjectKindRefIterator::AsFFI() {
    return reinterpret_cast<ecitygml::capi::AbstractCityObjectKindRefIterator*>(this);
}

inline const ecitygml::AbstractCityObjectKindRefIterator* ecitygml::AbstractCityObjectKindRefIterator::FromFFI(const ecitygml::capi::AbstractCityObjectKindRefIterator* ptr) {
    return reinterpret_cast<const ecitygml::AbstractCityObjectKindRefIterator*>(ptr);
}

inline ecitygml::AbstractCityObjectKindRefIterator* ecitygml::AbstractCityObjectKindRefIterator::FromFFI(ecitygml::capi::AbstractCityObjectKindRefIterator* ptr) {
    return reinterpret_cast<ecitygml::AbstractCityObjectKindRefIterator*>(ptr);
}

inline void ecitygml::AbstractCityObjectKindRefIterator::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_AbstractCityObjectKindRefIterator_destroy(reinterpret_cast<ecitygml::capi::AbstractCityObjectKindRefIterator*>(ptr));
}


#endif // ecitygml_AbstractCityObjectKindRefIterator_HPP
