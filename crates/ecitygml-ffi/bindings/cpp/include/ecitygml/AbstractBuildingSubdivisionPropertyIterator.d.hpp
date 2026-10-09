#ifndef ecitygml_AbstractBuildingSubdivisionPropertyIterator_D_HPP
#define ecitygml_AbstractBuildingSubdivisionPropertyIterator_D_HPP

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
namespace capi { struct AbstractBuildingSubdivisionProperty; }
class AbstractBuildingSubdivisionProperty;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct AbstractBuildingSubdivisionPropertyIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over building subdivision properties, borrowed from a city model.
 */
class AbstractBuildingSubdivisionPropertyIterator {
public:

  inline const ecitygml::AbstractBuildingSubdivisionProperty* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AbstractBuildingSubdivisionPropertyIterator* AsFFI() const;
    inline ecitygml::capi::AbstractBuildingSubdivisionPropertyIterator* AsFFI();
    inline static const ecitygml::AbstractBuildingSubdivisionPropertyIterator* FromFFI(const ecitygml::capi::AbstractBuildingSubdivisionPropertyIterator* ptr);
    inline static ecitygml::AbstractBuildingSubdivisionPropertyIterator* FromFFI(ecitygml::capi::AbstractBuildingSubdivisionPropertyIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    AbstractBuildingSubdivisionPropertyIterator() = delete;
    AbstractBuildingSubdivisionPropertyIterator(const ecitygml::AbstractBuildingSubdivisionPropertyIterator&) = delete;
    AbstractBuildingSubdivisionPropertyIterator(ecitygml::AbstractBuildingSubdivisionPropertyIterator&&) noexcept = delete;
    AbstractBuildingSubdivisionPropertyIterator operator=(const ecitygml::AbstractBuildingSubdivisionPropertyIterator&) = delete;
    AbstractBuildingSubdivisionPropertyIterator operator=(ecitygml::AbstractBuildingSubdivisionPropertyIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_AbstractBuildingSubdivisionPropertyIterator_D_HPP
