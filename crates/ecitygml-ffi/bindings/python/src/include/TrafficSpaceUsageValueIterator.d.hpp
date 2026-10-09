#ifndef ECITYGML_TrafficSpaceUsageValueIterator_D_HPP
#define ECITYGML_TrafficSpaceUsageValueIterator_D_HPP

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
namespace capi { struct TrafficSpaceUsageValue; }
class TrafficSpaceUsageValue;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct TrafficSpaceUsageValueIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over a list of code-list values, borrowed from a city model.
 */
class TrafficSpaceUsageValueIterator {
public:

  inline const ecitygml::TrafficSpaceUsageValue* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::TrafficSpaceUsageValueIterator* AsFFI() const;
    inline ecitygml::capi::TrafficSpaceUsageValueIterator* AsFFI();
    inline static const ecitygml::TrafficSpaceUsageValueIterator* FromFFI(const ecitygml::capi::TrafficSpaceUsageValueIterator* ptr);
    inline static ecitygml::TrafficSpaceUsageValueIterator* FromFFI(ecitygml::capi::TrafficSpaceUsageValueIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    TrafficSpaceUsageValueIterator() = delete;
    TrafficSpaceUsageValueIterator(const ecitygml::TrafficSpaceUsageValueIterator&) = delete;
    TrafficSpaceUsageValueIterator(ecitygml::TrafficSpaceUsageValueIterator&&) noexcept = delete;
    TrafficSpaceUsageValueIterator operator=(const ecitygml::TrafficSpaceUsageValueIterator&) = delete;
    TrafficSpaceUsageValueIterator operator=(ecitygml::TrafficSpaceUsageValueIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_TrafficSpaceUsageValueIterator_D_HPP
