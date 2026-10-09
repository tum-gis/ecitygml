#ifndef ECITYGML_SolitaryVegetationObjectFunctionValueIterator_D_HPP
#define ECITYGML_SolitaryVegetationObjectFunctionValueIterator_D_HPP

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
namespace capi { struct SolitaryVegetationObjectFunctionValue; }
class SolitaryVegetationObjectFunctionValue;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct SolitaryVegetationObjectFunctionValueIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over a list of code-list values, borrowed from a city model.
 */
class SolitaryVegetationObjectFunctionValueIterator {
public:

  inline const ecitygml::SolitaryVegetationObjectFunctionValue* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::SolitaryVegetationObjectFunctionValueIterator* AsFFI() const;
    inline ecitygml::capi::SolitaryVegetationObjectFunctionValueIterator* AsFFI();
    inline static const ecitygml::SolitaryVegetationObjectFunctionValueIterator* FromFFI(const ecitygml::capi::SolitaryVegetationObjectFunctionValueIterator* ptr);
    inline static ecitygml::SolitaryVegetationObjectFunctionValueIterator* FromFFI(ecitygml::capi::SolitaryVegetationObjectFunctionValueIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    SolitaryVegetationObjectFunctionValueIterator() = delete;
    SolitaryVegetationObjectFunctionValueIterator(const ecitygml::SolitaryVegetationObjectFunctionValueIterator&) = delete;
    SolitaryVegetationObjectFunctionValueIterator(ecitygml::SolitaryVegetationObjectFunctionValueIterator&&) noexcept = delete;
    SolitaryVegetationObjectFunctionValueIterator operator=(const ecitygml::SolitaryVegetationObjectFunctionValueIterator&) = delete;
    SolitaryVegetationObjectFunctionValueIterator operator=(ecitygml::SolitaryVegetationObjectFunctionValueIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_SolitaryVegetationObjectFunctionValueIterator_D_HPP
