#ifndef ecitygml_AbstractFillingSurfacePropertyIterator_D_HPP
#define ecitygml_AbstractFillingSurfacePropertyIterator_D_HPP

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
namespace capi { struct AbstractFillingSurfaceProperty; }
class AbstractFillingSurfaceProperty;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct AbstractFillingSurfacePropertyIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over filling surface properties, borrowed from a city model.
 */
class AbstractFillingSurfacePropertyIterator {
public:

  inline const ecitygml::AbstractFillingSurfaceProperty* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AbstractFillingSurfacePropertyIterator* AsFFI() const;
    inline ecitygml::capi::AbstractFillingSurfacePropertyIterator* AsFFI();
    inline static const ecitygml::AbstractFillingSurfacePropertyIterator* FromFFI(const ecitygml::capi::AbstractFillingSurfacePropertyIterator* ptr);
    inline static ecitygml::AbstractFillingSurfacePropertyIterator* FromFFI(ecitygml::capi::AbstractFillingSurfacePropertyIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    AbstractFillingSurfacePropertyIterator() = delete;
    AbstractFillingSurfacePropertyIterator(const ecitygml::AbstractFillingSurfacePropertyIterator&) = delete;
    AbstractFillingSurfacePropertyIterator(ecitygml::AbstractFillingSurfacePropertyIterator&&) noexcept = delete;
    AbstractFillingSurfacePropertyIterator operator=(const ecitygml::AbstractFillingSurfacePropertyIterator&) = delete;
    AbstractFillingSurfacePropertyIterator operator=(ecitygml::AbstractFillingSurfacePropertyIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_AbstractFillingSurfacePropertyIterator_D_HPP
