#ifndef ECITYGML_BuildingUsageValueIterator_D_HPP
#define ECITYGML_BuildingUsageValueIterator_D_HPP

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
namespace capi { struct BuildingUsageValue; }
class BuildingUsageValue;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct BuildingUsageValueIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over a list of code-list values, borrowed from a city model.
 */
class BuildingUsageValueIterator {
public:

  inline const ecitygml::BuildingUsageValue* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::BuildingUsageValueIterator* AsFFI() const;
    inline ecitygml::capi::BuildingUsageValueIterator* AsFFI();
    inline static const ecitygml::BuildingUsageValueIterator* FromFFI(const ecitygml::capi::BuildingUsageValueIterator* ptr);
    inline static ecitygml::BuildingUsageValueIterator* FromFFI(ecitygml::capi::BuildingUsageValueIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    BuildingUsageValueIterator() = delete;
    BuildingUsageValueIterator(const ecitygml::BuildingUsageValueIterator&) = delete;
    BuildingUsageValueIterator(ecitygml::BuildingUsageValueIterator&&) noexcept = delete;
    BuildingUsageValueIterator operator=(const ecitygml::BuildingUsageValueIterator&) = delete;
    BuildingUsageValueIterator operator=(ecitygml::BuildingUsageValueIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_BuildingUsageValueIterator_D_HPP
