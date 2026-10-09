#ifndef ecitygml_BridgeUsageValueIterator_D_HPP
#define ecitygml_BridgeUsageValueIterator_D_HPP

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
namespace capi { struct BridgeUsageValue; }
class BridgeUsageValue;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct BridgeUsageValueIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over a list of code-list values, borrowed from a city model.
 */
class BridgeUsageValueIterator {
public:

  inline const ecitygml::BridgeUsageValue* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::BridgeUsageValueIterator* AsFFI() const;
    inline ecitygml::capi::BridgeUsageValueIterator* AsFFI();
    inline static const ecitygml::BridgeUsageValueIterator* FromFFI(const ecitygml::capi::BridgeUsageValueIterator* ptr);
    inline static ecitygml::BridgeUsageValueIterator* FromFFI(ecitygml::capi::BridgeUsageValueIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    BridgeUsageValueIterator() = delete;
    BridgeUsageValueIterator(const ecitygml::BridgeUsageValueIterator&) = delete;
    BridgeUsageValueIterator(ecitygml::BridgeUsageValueIterator&&) noexcept = delete;
    BridgeUsageValueIterator operator=(const ecitygml::BridgeUsageValueIterator&) = delete;
    BridgeUsageValueIterator operator=(ecitygml::BridgeUsageValueIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_BridgeUsageValueIterator_D_HPP
