#ifndef ECITYGML_AuxiliaryTrafficSpaceFunctionValueIterator_D_HPP
#define ECITYGML_AuxiliaryTrafficSpaceFunctionValueIterator_D_HPP

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
namespace capi { struct AuxiliaryTrafficSpaceFunctionValue; }
class AuxiliaryTrafficSpaceFunctionValue;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct AuxiliaryTrafficSpaceFunctionValueIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over a list of code-list values, borrowed from a city model.
 */
class AuxiliaryTrafficSpaceFunctionValueIterator {
public:

  inline const ecitygml::AuxiliaryTrafficSpaceFunctionValue* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AuxiliaryTrafficSpaceFunctionValueIterator* AsFFI() const;
    inline ecitygml::capi::AuxiliaryTrafficSpaceFunctionValueIterator* AsFFI();
    inline static const ecitygml::AuxiliaryTrafficSpaceFunctionValueIterator* FromFFI(const ecitygml::capi::AuxiliaryTrafficSpaceFunctionValueIterator* ptr);
    inline static ecitygml::AuxiliaryTrafficSpaceFunctionValueIterator* FromFFI(ecitygml::capi::AuxiliaryTrafficSpaceFunctionValueIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    AuxiliaryTrafficSpaceFunctionValueIterator() = delete;
    AuxiliaryTrafficSpaceFunctionValueIterator(const ecitygml::AuxiliaryTrafficSpaceFunctionValueIterator&) = delete;
    AuxiliaryTrafficSpaceFunctionValueIterator(ecitygml::AuxiliaryTrafficSpaceFunctionValueIterator&&) noexcept = delete;
    AuxiliaryTrafficSpaceFunctionValueIterator operator=(const ecitygml::AuxiliaryTrafficSpaceFunctionValueIterator&) = delete;
    AuxiliaryTrafficSpaceFunctionValueIterator operator=(ecitygml::AuxiliaryTrafficSpaceFunctionValueIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_AuxiliaryTrafficSpaceFunctionValueIterator_D_HPP
