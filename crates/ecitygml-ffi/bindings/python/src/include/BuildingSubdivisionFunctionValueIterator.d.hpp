#ifndef ECITYGML_BuildingSubdivisionFunctionValueIterator_D_HPP
#define ECITYGML_BuildingSubdivisionFunctionValueIterator_D_HPP

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
namespace capi { struct BuildingSubdivisionFunctionValue; }
class BuildingSubdivisionFunctionValue;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct BuildingSubdivisionFunctionValueIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over a list of code-list values, borrowed from a city model.
 */
class BuildingSubdivisionFunctionValueIterator {
public:

  inline const ecitygml::BuildingSubdivisionFunctionValue* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::BuildingSubdivisionFunctionValueIterator* AsFFI() const;
    inline ecitygml::capi::BuildingSubdivisionFunctionValueIterator* AsFFI();
    inline static const ecitygml::BuildingSubdivisionFunctionValueIterator* FromFFI(const ecitygml::capi::BuildingSubdivisionFunctionValueIterator* ptr);
    inline static ecitygml::BuildingSubdivisionFunctionValueIterator* FromFFI(ecitygml::capi::BuildingSubdivisionFunctionValueIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    BuildingSubdivisionFunctionValueIterator() = delete;
    BuildingSubdivisionFunctionValueIterator(const ecitygml::BuildingSubdivisionFunctionValueIterator&) = delete;
    BuildingSubdivisionFunctionValueIterator(ecitygml::BuildingSubdivisionFunctionValueIterator&&) noexcept = delete;
    BuildingSubdivisionFunctionValueIterator operator=(const ecitygml::BuildingSubdivisionFunctionValueIterator&) = delete;
    BuildingSubdivisionFunctionValueIterator operator=(ecitygml::BuildingSubdivisionFunctionValueIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_BuildingSubdivisionFunctionValueIterator_D_HPP
