#ifndef ECITYGML_TunnelUsageValueIterator_D_HPP
#define ECITYGML_TunnelUsageValueIterator_D_HPP

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
namespace capi { struct TunnelUsageValue; }
class TunnelUsageValue;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct TunnelUsageValueIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over a list of code-list values, borrowed from a city model.
 */
class TunnelUsageValueIterator {
public:

  inline const ecitygml::TunnelUsageValue* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::TunnelUsageValueIterator* AsFFI() const;
    inline ecitygml::capi::TunnelUsageValueIterator* AsFFI();
    inline static const ecitygml::TunnelUsageValueIterator* FromFFI(const ecitygml::capi::TunnelUsageValueIterator* ptr);
    inline static ecitygml::TunnelUsageValueIterator* FromFFI(ecitygml::capi::TunnelUsageValueIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    TunnelUsageValueIterator() = delete;
    TunnelUsageValueIterator(const ecitygml::TunnelUsageValueIterator&) = delete;
    TunnelUsageValueIterator(ecitygml::TunnelUsageValueIterator&&) noexcept = delete;
    TunnelUsageValueIterator operator=(const ecitygml::TunnelUsageValueIterator&) = delete;
    TunnelUsageValueIterator operator=(ecitygml::TunnelUsageValueIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_TunnelUsageValueIterator_D_HPP
