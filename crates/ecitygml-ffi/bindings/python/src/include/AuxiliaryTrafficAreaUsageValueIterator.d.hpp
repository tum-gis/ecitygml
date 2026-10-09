#ifndef ECITYGML_AuxiliaryTrafficAreaUsageValueIterator_D_HPP
#define ECITYGML_AuxiliaryTrafficAreaUsageValueIterator_D_HPP

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
namespace capi { struct AuxiliaryTrafficAreaUsageValue; }
class AuxiliaryTrafficAreaUsageValue;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct AuxiliaryTrafficAreaUsageValueIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over a list of code-list values, borrowed from a city model.
 */
class AuxiliaryTrafficAreaUsageValueIterator {
public:

  inline const ecitygml::AuxiliaryTrafficAreaUsageValue* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AuxiliaryTrafficAreaUsageValueIterator* AsFFI() const;
    inline ecitygml::capi::AuxiliaryTrafficAreaUsageValueIterator* AsFFI();
    inline static const ecitygml::AuxiliaryTrafficAreaUsageValueIterator* FromFFI(const ecitygml::capi::AuxiliaryTrafficAreaUsageValueIterator* ptr);
    inline static ecitygml::AuxiliaryTrafficAreaUsageValueIterator* FromFFI(ecitygml::capi::AuxiliaryTrafficAreaUsageValueIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    AuxiliaryTrafficAreaUsageValueIterator() = delete;
    AuxiliaryTrafficAreaUsageValueIterator(const ecitygml::AuxiliaryTrafficAreaUsageValueIterator&) = delete;
    AuxiliaryTrafficAreaUsageValueIterator(ecitygml::AuxiliaryTrafficAreaUsageValueIterator&&) noexcept = delete;
    AuxiliaryTrafficAreaUsageValueIterator operator=(const ecitygml::AuxiliaryTrafficAreaUsageValueIterator&) = delete;
    AuxiliaryTrafficAreaUsageValueIterator operator=(ecitygml::AuxiliaryTrafficAreaUsageValueIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_AuxiliaryTrafficAreaUsageValueIterator_D_HPP
