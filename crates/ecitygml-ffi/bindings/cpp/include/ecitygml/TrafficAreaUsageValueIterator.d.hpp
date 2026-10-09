#ifndef ecitygml_TrafficAreaUsageValueIterator_D_HPP
#define ecitygml_TrafficAreaUsageValueIterator_D_HPP

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
namespace capi { struct TrafficAreaUsageValue; }
class TrafficAreaUsageValue;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct TrafficAreaUsageValueIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over a list of code-list values, borrowed from a city model.
 */
class TrafficAreaUsageValueIterator {
public:

  inline const ecitygml::TrafficAreaUsageValue* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::TrafficAreaUsageValueIterator* AsFFI() const;
    inline ecitygml::capi::TrafficAreaUsageValueIterator* AsFFI();
    inline static const ecitygml::TrafficAreaUsageValueIterator* FromFFI(const ecitygml::capi::TrafficAreaUsageValueIterator* ptr);
    inline static ecitygml::TrafficAreaUsageValueIterator* FromFFI(ecitygml::capi::TrafficAreaUsageValueIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    TrafficAreaUsageValueIterator() = delete;
    TrafficAreaUsageValueIterator(const ecitygml::TrafficAreaUsageValueIterator&) = delete;
    TrafficAreaUsageValueIterator(ecitygml::TrafficAreaUsageValueIterator&&) noexcept = delete;
    TrafficAreaUsageValueIterator operator=(const ecitygml::TrafficAreaUsageValueIterator&) = delete;
    TrafficAreaUsageValueIterator operator=(ecitygml::TrafficAreaUsageValueIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_TrafficAreaUsageValueIterator_D_HPP
