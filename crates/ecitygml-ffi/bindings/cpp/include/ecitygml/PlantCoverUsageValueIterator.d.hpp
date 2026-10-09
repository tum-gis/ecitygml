#ifndef ecitygml_PlantCoverUsageValueIterator_D_HPP
#define ecitygml_PlantCoverUsageValueIterator_D_HPP

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
namespace capi { struct PlantCoverUsageValue; }
class PlantCoverUsageValue;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct PlantCoverUsageValueIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over a list of code-list values, borrowed from a city model.
 */
class PlantCoverUsageValueIterator {
public:

  inline const ecitygml::PlantCoverUsageValue* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::PlantCoverUsageValueIterator* AsFFI() const;
    inline ecitygml::capi::PlantCoverUsageValueIterator* AsFFI();
    inline static const ecitygml::PlantCoverUsageValueIterator* FromFFI(const ecitygml::capi::PlantCoverUsageValueIterator* ptr);
    inline static ecitygml::PlantCoverUsageValueIterator* FromFFI(ecitygml::capi::PlantCoverUsageValueIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    PlantCoverUsageValueIterator() = delete;
    PlantCoverUsageValueIterator(const ecitygml::PlantCoverUsageValueIterator&) = delete;
    PlantCoverUsageValueIterator(ecitygml::PlantCoverUsageValueIterator&&) noexcept = delete;
    PlantCoverUsageValueIterator operator=(const ecitygml::PlantCoverUsageValueIterator&) = delete;
    PlantCoverUsageValueIterator operator=(ecitygml::PlantCoverUsageValueIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_PlantCoverUsageValueIterator_D_HPP
