#ifndef ECITYGML_CityObjectRelationPropertyIterator_D_HPP
#define ECITYGML_CityObjectRelationPropertyIterator_D_HPP

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "diplomat_runtime.hpp"
namespace ecitygml {
namespace capi { struct CityObjectRelationProperty; }
class CityObjectRelationProperty;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct CityObjectRelationPropertyIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over city object relation properties, borrowed from a city model.
 */
class CityObjectRelationPropertyIterator {
public:

  inline const ecitygml::CityObjectRelationProperty* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::CityObjectRelationPropertyIterator* AsFFI() const;
    inline ecitygml::capi::CityObjectRelationPropertyIterator* AsFFI();
    inline static const ecitygml::CityObjectRelationPropertyIterator* FromFFI(const ecitygml::capi::CityObjectRelationPropertyIterator* ptr);
    inline static ecitygml::CityObjectRelationPropertyIterator* FromFFI(ecitygml::capi::CityObjectRelationPropertyIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    CityObjectRelationPropertyIterator() = delete;
    CityObjectRelationPropertyIterator(const ecitygml::CityObjectRelationPropertyIterator&) = delete;
    CityObjectRelationPropertyIterator(ecitygml::CityObjectRelationPropertyIterator&&) noexcept = delete;
    CityObjectRelationPropertyIterator operator=(const ecitygml::CityObjectRelationPropertyIterator&) = delete;
    CityObjectRelationPropertyIterator operator=(ecitygml::CityObjectRelationPropertyIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_CityObjectRelationPropertyIterator_D_HPP
