#ifndef ECITYGML_AuxiliaryTrafficAreaFunctionValueIterator_D_HPP
#define ECITYGML_AuxiliaryTrafficAreaFunctionValueIterator_D_HPP

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
namespace capi { struct AuxiliaryTrafficAreaFunctionValue; }
class AuxiliaryTrafficAreaFunctionValue;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct AuxiliaryTrafficAreaFunctionValueIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over a list of code-list values, borrowed from a city model.
 */
class AuxiliaryTrafficAreaFunctionValueIterator {
public:

  inline const ecitygml::AuxiliaryTrafficAreaFunctionValue* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AuxiliaryTrafficAreaFunctionValueIterator* AsFFI() const;
    inline ecitygml::capi::AuxiliaryTrafficAreaFunctionValueIterator* AsFFI();
    inline static const ecitygml::AuxiliaryTrafficAreaFunctionValueIterator* FromFFI(const ecitygml::capi::AuxiliaryTrafficAreaFunctionValueIterator* ptr);
    inline static ecitygml::AuxiliaryTrafficAreaFunctionValueIterator* FromFFI(ecitygml::capi::AuxiliaryTrafficAreaFunctionValueIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    AuxiliaryTrafficAreaFunctionValueIterator() = delete;
    AuxiliaryTrafficAreaFunctionValueIterator(const ecitygml::AuxiliaryTrafficAreaFunctionValueIterator&) = delete;
    AuxiliaryTrafficAreaFunctionValueIterator(ecitygml::AuxiliaryTrafficAreaFunctionValueIterator&&) noexcept = delete;
    AuxiliaryTrafficAreaFunctionValueIterator operator=(const ecitygml::AuxiliaryTrafficAreaFunctionValueIterator&) = delete;
    AuxiliaryTrafficAreaFunctionValueIterator operator=(ecitygml::AuxiliaryTrafficAreaFunctionValueIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_AuxiliaryTrafficAreaFunctionValueIterator_D_HPP
