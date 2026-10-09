#ifndef ecitygml_AbstractSurfacePropertyIterator_D_HPP
#define ecitygml_AbstractSurfacePropertyIterator_D_HPP

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
namespace capi { struct AbstractSurfaceProperty; }
class AbstractSurfaceProperty;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct AbstractSurfacePropertyIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over curve properties, borrowed from a city model.
 */
class AbstractSurfacePropertyIterator {
public:

  inline const ecitygml::AbstractSurfaceProperty* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AbstractSurfacePropertyIterator* AsFFI() const;
    inline ecitygml::capi::AbstractSurfacePropertyIterator* AsFFI();
    inline static const ecitygml::AbstractSurfacePropertyIterator* FromFFI(const ecitygml::capi::AbstractSurfacePropertyIterator* ptr);
    inline static ecitygml::AbstractSurfacePropertyIterator* FromFFI(ecitygml::capi::AbstractSurfacePropertyIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    AbstractSurfacePropertyIterator() = delete;
    AbstractSurfacePropertyIterator(const ecitygml::AbstractSurfacePropertyIterator&) = delete;
    AbstractSurfacePropertyIterator(ecitygml::AbstractSurfacePropertyIterator&&) noexcept = delete;
    AbstractSurfacePropertyIterator operator=(const ecitygml::AbstractSurfacePropertyIterator&) = delete;
    AbstractSurfacePropertyIterator operator=(ecitygml::AbstractSurfacePropertyIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_AbstractSurfacePropertyIterator_D_HPP
