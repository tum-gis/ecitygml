#ifndef ECITYGML_MultiSurfaceProperty_D_HPP
#define ECITYGML_MultiSurfaceProperty_D_HPP

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
namespace capi { struct HRef; }
class HRef;
namespace capi { struct MultiSurface; }
class MultiSurface;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct MultiSurfaceProperty;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A multi-surface property (inline multi surface and/or `xlink:href`), borrowed from a city model.
 */
class MultiSurfaceProperty {
public:

  /**
   * The inline multi surface; none if the property only references one via `href`.
   */
  inline const ecitygml::MultiSurface* object() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::HRef* href() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::MultiSurfaceProperty* AsFFI() const;
    inline ecitygml::capi::MultiSurfaceProperty* AsFFI();
    inline static const ecitygml::MultiSurfaceProperty* FromFFI(const ecitygml::capi::MultiSurfaceProperty* ptr);
    inline static ecitygml::MultiSurfaceProperty* FromFFI(ecitygml::capi::MultiSurfaceProperty* ptr);
    inline static void operator delete(void* ptr);
private:
    MultiSurfaceProperty() = delete;
    MultiSurfaceProperty(const ecitygml::MultiSurfaceProperty&) = delete;
    MultiSurfaceProperty(ecitygml::MultiSurfaceProperty&&) noexcept = delete;
    MultiSurfaceProperty operator=(const ecitygml::MultiSurfaceProperty&) = delete;
    MultiSurfaceProperty operator=(ecitygml::MultiSurfaceProperty&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_MultiSurfaceProperty_D_HPP
