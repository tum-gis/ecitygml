#ifndef ECITYGML_BuildingPartPropertyIterator_D_HPP
#define ECITYGML_BuildingPartPropertyIterator_D_HPP

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
namespace capi { struct BuildingPartProperty; }
class BuildingPartProperty;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct BuildingPartPropertyIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over building part properties, borrowed from a city model.
 */
class BuildingPartPropertyIterator {
public:

  inline const ecitygml::BuildingPartProperty* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::BuildingPartPropertyIterator* AsFFI() const;
    inline ecitygml::capi::BuildingPartPropertyIterator* AsFFI();
    inline static const ecitygml::BuildingPartPropertyIterator* FromFFI(const ecitygml::capi::BuildingPartPropertyIterator* ptr);
    inline static ecitygml::BuildingPartPropertyIterator* FromFFI(ecitygml::capi::BuildingPartPropertyIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    BuildingPartPropertyIterator() = delete;
    BuildingPartPropertyIterator(const ecitygml::BuildingPartPropertyIterator&) = delete;
    BuildingPartPropertyIterator(ecitygml::BuildingPartPropertyIterator&&) noexcept = delete;
    BuildingPartPropertyIterator operator=(const ecitygml::BuildingPartPropertyIterator&) = delete;
    BuildingPartPropertyIterator operator=(ecitygml::BuildingPartPropertyIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_BuildingPartPropertyIterator_D_HPP
