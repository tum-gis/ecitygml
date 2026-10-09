#ifndef ECITYGML_SolitaryVegetationObjectUsageValueIterator_D_HPP
#define ECITYGML_SolitaryVegetationObjectUsageValueIterator_D_HPP

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
namespace capi { struct SolitaryVegetationObjectUsageValue; }
class SolitaryVegetationObjectUsageValue;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct SolitaryVegetationObjectUsageValueIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over a list of code-list values, borrowed from a city model.
 */
class SolitaryVegetationObjectUsageValueIterator {
public:

  inline const ecitygml::SolitaryVegetationObjectUsageValue* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::SolitaryVegetationObjectUsageValueIterator* AsFFI() const;
    inline ecitygml::capi::SolitaryVegetationObjectUsageValueIterator* AsFFI();
    inline static const ecitygml::SolitaryVegetationObjectUsageValueIterator* FromFFI(const ecitygml::capi::SolitaryVegetationObjectUsageValueIterator* ptr);
    inline static ecitygml::SolitaryVegetationObjectUsageValueIterator* FromFFI(ecitygml::capi::SolitaryVegetationObjectUsageValueIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    SolitaryVegetationObjectUsageValueIterator() = delete;
    SolitaryVegetationObjectUsageValueIterator(const ecitygml::SolitaryVegetationObjectUsageValueIterator&) = delete;
    SolitaryVegetationObjectUsageValueIterator(ecitygml::SolitaryVegetationObjectUsageValueIterator&&) noexcept = delete;
    SolitaryVegetationObjectUsageValueIterator operator=(const ecitygml::SolitaryVegetationObjectUsageValueIterator&) = delete;
    SolitaryVegetationObjectUsageValueIterator operator=(ecitygml::SolitaryVegetationObjectUsageValueIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_SolitaryVegetationObjectUsageValueIterator_D_HPP
