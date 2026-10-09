#ifndef ECITYGML_PlantCoverFunctionValueIterator_D_HPP
#define ECITYGML_PlantCoverFunctionValueIterator_D_HPP

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
namespace capi { struct PlantCoverFunctionValue; }
class PlantCoverFunctionValue;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct PlantCoverFunctionValueIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over a list of code-list values, borrowed from a city model.
 */
class PlantCoverFunctionValueIterator {
public:

  inline const ecitygml::PlantCoverFunctionValue* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::PlantCoverFunctionValueIterator* AsFFI() const;
    inline ecitygml::capi::PlantCoverFunctionValueIterator* AsFFI();
    inline static const ecitygml::PlantCoverFunctionValueIterator* FromFFI(const ecitygml::capi::PlantCoverFunctionValueIterator* ptr);
    inline static ecitygml::PlantCoverFunctionValueIterator* FromFFI(ecitygml::capi::PlantCoverFunctionValueIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    PlantCoverFunctionValueIterator() = delete;
    PlantCoverFunctionValueIterator(const ecitygml::PlantCoverFunctionValueIterator&) = delete;
    PlantCoverFunctionValueIterator(ecitygml::PlantCoverFunctionValueIterator&&) noexcept = delete;
    PlantCoverFunctionValueIterator operator=(const ecitygml::PlantCoverFunctionValueIterator&) = delete;
    PlantCoverFunctionValueIterator operator=(ecitygml::PlantCoverFunctionValueIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_PlantCoverFunctionValueIterator_D_HPP
