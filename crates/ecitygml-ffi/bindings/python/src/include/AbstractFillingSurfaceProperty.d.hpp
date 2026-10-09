#ifndef ECITYGML_AbstractFillingSurfaceProperty_D_HPP
#define ECITYGML_AbstractFillingSurfaceProperty_D_HPP

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
namespace capi { struct AbstractFillingSurfaceKind; }
class AbstractFillingSurfaceKind;
namespace capi { struct HRef; }
class HRef;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct AbstractFillingSurfaceProperty;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A filling surface property (inline filling surface and/or `xlink:href`), borrowed from a city model.
 */
class AbstractFillingSurfaceProperty {
public:

  /**
   * The inline filling surface; none if the property only references one via `href`.
   */
  inline const ecitygml::AbstractFillingSurfaceKind* object() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::HRef* href() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AbstractFillingSurfaceProperty* AsFFI() const;
    inline ecitygml::capi::AbstractFillingSurfaceProperty* AsFFI();
    inline static const ecitygml::AbstractFillingSurfaceProperty* FromFFI(const ecitygml::capi::AbstractFillingSurfaceProperty* ptr);
    inline static ecitygml::AbstractFillingSurfaceProperty* FromFFI(ecitygml::capi::AbstractFillingSurfaceProperty* ptr);
    inline static void operator delete(void* ptr);
private:
    AbstractFillingSurfaceProperty() = delete;
    AbstractFillingSurfaceProperty(const ecitygml::AbstractFillingSurfaceProperty&) = delete;
    AbstractFillingSurfaceProperty(ecitygml::AbstractFillingSurfaceProperty&&) noexcept = delete;
    AbstractFillingSurfaceProperty operator=(const ecitygml::AbstractFillingSurfaceProperty&) = delete;
    AbstractFillingSurfaceProperty operator=(ecitygml::AbstractFillingSurfaceProperty&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_AbstractFillingSurfaceProperty_D_HPP
