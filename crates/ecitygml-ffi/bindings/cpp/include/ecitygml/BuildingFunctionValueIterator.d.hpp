#ifndef ecitygml_BuildingFunctionValueIterator_D_HPP
#define ecitygml_BuildingFunctionValueIterator_D_HPP

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
namespace capi { struct BuildingFunctionValue; }
class BuildingFunctionValue;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct BuildingFunctionValueIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over a list of code-list values, borrowed from a city model.
 */
class BuildingFunctionValueIterator {
public:

  inline const ecitygml::BuildingFunctionValue* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::BuildingFunctionValueIterator* AsFFI() const;
    inline ecitygml::capi::BuildingFunctionValueIterator* AsFFI();
    inline static const ecitygml::BuildingFunctionValueIterator* FromFFI(const ecitygml::capi::BuildingFunctionValueIterator* ptr);
    inline static ecitygml::BuildingFunctionValueIterator* FromFFI(ecitygml::capi::BuildingFunctionValueIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    BuildingFunctionValueIterator() = delete;
    BuildingFunctionValueIterator(const ecitygml::BuildingFunctionValueIterator&) = delete;
    BuildingFunctionValueIterator(ecitygml::BuildingFunctionValueIterator&&) noexcept = delete;
    BuildingFunctionValueIterator operator=(const ecitygml::BuildingFunctionValueIterator&) = delete;
    BuildingFunctionValueIterator operator=(ecitygml::BuildingFunctionValueIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_BuildingFunctionValueIterator_D_HPP
