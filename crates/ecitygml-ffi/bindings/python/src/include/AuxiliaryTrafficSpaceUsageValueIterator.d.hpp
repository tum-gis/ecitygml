#ifndef ECITYGML_AuxiliaryTrafficSpaceUsageValueIterator_D_HPP
#define ECITYGML_AuxiliaryTrafficSpaceUsageValueIterator_D_HPP

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
namespace capi { struct AuxiliaryTrafficSpaceUsageValue; }
class AuxiliaryTrafficSpaceUsageValue;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct AuxiliaryTrafficSpaceUsageValueIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over a list of code-list values, borrowed from a city model.
 */
class AuxiliaryTrafficSpaceUsageValueIterator {
public:

  inline const ecitygml::AuxiliaryTrafficSpaceUsageValue* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AuxiliaryTrafficSpaceUsageValueIterator* AsFFI() const;
    inline ecitygml::capi::AuxiliaryTrafficSpaceUsageValueIterator* AsFFI();
    inline static const ecitygml::AuxiliaryTrafficSpaceUsageValueIterator* FromFFI(const ecitygml::capi::AuxiliaryTrafficSpaceUsageValueIterator* ptr);
    inline static ecitygml::AuxiliaryTrafficSpaceUsageValueIterator* FromFFI(ecitygml::capi::AuxiliaryTrafficSpaceUsageValueIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    AuxiliaryTrafficSpaceUsageValueIterator() = delete;
    AuxiliaryTrafficSpaceUsageValueIterator(const ecitygml::AuxiliaryTrafficSpaceUsageValueIterator&) = delete;
    AuxiliaryTrafficSpaceUsageValueIterator(ecitygml::AuxiliaryTrafficSpaceUsageValueIterator&&) noexcept = delete;
    AuxiliaryTrafficSpaceUsageValueIterator operator=(const ecitygml::AuxiliaryTrafficSpaceUsageValueIterator&) = delete;
    AuxiliaryTrafficSpaceUsageValueIterator operator=(ecitygml::AuxiliaryTrafficSpaceUsageValueIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_AuxiliaryTrafficSpaceUsageValueIterator_D_HPP
