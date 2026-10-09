#ifndef ECITYGML_CityFurnitureUsageValueIterator_D_HPP
#define ECITYGML_CityFurnitureUsageValueIterator_D_HPP

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
namespace capi { struct CityFurnitureUsageValue; }
class CityFurnitureUsageValue;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct CityFurnitureUsageValueIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over a list of code-list values, borrowed from a city model.
 */
class CityFurnitureUsageValueIterator {
public:

  inline const ecitygml::CityFurnitureUsageValue* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::CityFurnitureUsageValueIterator* AsFFI() const;
    inline ecitygml::capi::CityFurnitureUsageValueIterator* AsFFI();
    inline static const ecitygml::CityFurnitureUsageValueIterator* FromFFI(const ecitygml::capi::CityFurnitureUsageValueIterator* ptr);
    inline static ecitygml::CityFurnitureUsageValueIterator* FromFFI(ecitygml::capi::CityFurnitureUsageValueIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    CityFurnitureUsageValueIterator() = delete;
    CityFurnitureUsageValueIterator(const ecitygml::CityFurnitureUsageValueIterator&) = delete;
    CityFurnitureUsageValueIterator(ecitygml::CityFurnitureUsageValueIterator&&) noexcept = delete;
    CityFurnitureUsageValueIterator operator=(const ecitygml::CityFurnitureUsageValueIterator&) = delete;
    CityFurnitureUsageValueIterator operator=(ecitygml::CityFurnitureUsageValueIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_CityFurnitureUsageValueIterator_D_HPP
