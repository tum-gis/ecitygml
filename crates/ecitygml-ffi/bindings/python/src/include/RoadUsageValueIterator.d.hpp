#ifndef ECITYGML_RoadUsageValueIterator_D_HPP
#define ECITYGML_RoadUsageValueIterator_D_HPP

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
namespace capi { struct RoadUsageValue; }
class RoadUsageValue;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct RoadUsageValueIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over a list of code-list values, borrowed from a city model.
 */
class RoadUsageValueIterator {
public:

  inline const ecitygml::RoadUsageValue* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::RoadUsageValueIterator* AsFFI() const;
    inline ecitygml::capi::RoadUsageValueIterator* AsFFI();
    inline static const ecitygml::RoadUsageValueIterator* FromFFI(const ecitygml::capi::RoadUsageValueIterator* ptr);
    inline static ecitygml::RoadUsageValueIterator* FromFFI(ecitygml::capi::RoadUsageValueIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    RoadUsageValueIterator() = delete;
    RoadUsageValueIterator(const ecitygml::RoadUsageValueIterator&) = delete;
    RoadUsageValueIterator(ecitygml::RoadUsageValueIterator&&) noexcept = delete;
    RoadUsageValueIterator operator=(const ecitygml::RoadUsageValueIterator&) = delete;
    RoadUsageValueIterator operator=(ecitygml::RoadUsageValueIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_RoadUsageValueIterator_D_HPP
