#ifndef ecitygml_BuildingSubdivisionUsageValueIterator_D_HPP
#define ecitygml_BuildingSubdivisionUsageValueIterator_D_HPP

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"

namespace ecitygml {
namespace capi { struct BuildingSubdivisionUsageValue; }
class BuildingSubdivisionUsageValue;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct BuildingSubdivisionUsageValueIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over a list of code-list values, borrowed from a city model.
 */
class BuildingSubdivisionUsageValueIterator {
public:

  inline const ecitygml::BuildingSubdivisionUsageValue* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::BuildingSubdivisionUsageValueIterator* AsFFI() const;
    inline ecitygml::capi::BuildingSubdivisionUsageValueIterator* AsFFI();
    inline static const ecitygml::BuildingSubdivisionUsageValueIterator* FromFFI(const ecitygml::capi::BuildingSubdivisionUsageValueIterator* ptr);
    inline static ecitygml::BuildingSubdivisionUsageValueIterator* FromFFI(ecitygml::capi::BuildingSubdivisionUsageValueIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    BuildingSubdivisionUsageValueIterator() = delete;
    BuildingSubdivisionUsageValueIterator(const ecitygml::BuildingSubdivisionUsageValueIterator&) = delete;
    BuildingSubdivisionUsageValueIterator(ecitygml::BuildingSubdivisionUsageValueIterator&&) noexcept = delete;
    BuildingSubdivisionUsageValueIterator operator=(const ecitygml::BuildingSubdivisionUsageValueIterator&) = delete;
    BuildingSubdivisionUsageValueIterator operator=(ecitygml::BuildingSubdivisionUsageValueIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_BuildingSubdivisionUsageValueIterator_D_HPP
