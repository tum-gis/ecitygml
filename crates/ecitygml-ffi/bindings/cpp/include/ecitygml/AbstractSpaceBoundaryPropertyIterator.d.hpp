#ifndef ecitygml_AbstractSpaceBoundaryPropertyIterator_D_HPP
#define ecitygml_AbstractSpaceBoundaryPropertyIterator_D_HPP

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
namespace capi { struct AbstractSpaceBoundaryProperty; }
class AbstractSpaceBoundaryProperty;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct AbstractSpaceBoundaryPropertyIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over space boundary properties, borrowed from a city model.
 */
class AbstractSpaceBoundaryPropertyIterator {
public:

  inline const ecitygml::AbstractSpaceBoundaryProperty* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AbstractSpaceBoundaryPropertyIterator* AsFFI() const;
    inline ecitygml::capi::AbstractSpaceBoundaryPropertyIterator* AsFFI();
    inline static const ecitygml::AbstractSpaceBoundaryPropertyIterator* FromFFI(const ecitygml::capi::AbstractSpaceBoundaryPropertyIterator* ptr);
    inline static ecitygml::AbstractSpaceBoundaryPropertyIterator* FromFFI(ecitygml::capi::AbstractSpaceBoundaryPropertyIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    AbstractSpaceBoundaryPropertyIterator() = delete;
    AbstractSpaceBoundaryPropertyIterator(const ecitygml::AbstractSpaceBoundaryPropertyIterator&) = delete;
    AbstractSpaceBoundaryPropertyIterator(ecitygml::AbstractSpaceBoundaryPropertyIterator&&) noexcept = delete;
    AbstractSpaceBoundaryPropertyIterator operator=(const ecitygml::AbstractSpaceBoundaryPropertyIterator&) = delete;
    AbstractSpaceBoundaryPropertyIterator operator=(ecitygml::AbstractSpaceBoundaryPropertyIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_AbstractSpaceBoundaryPropertyIterator_D_HPP
