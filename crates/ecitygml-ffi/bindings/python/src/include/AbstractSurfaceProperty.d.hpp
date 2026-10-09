#ifndef ECITYGML_AbstractSurfaceProperty_D_HPP
#define ECITYGML_AbstractSurfaceProperty_D_HPP

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
namespace capi { struct AbstractSurfaceKind; }
class AbstractSurfaceKind;
namespace capi { struct HRef; }
class HRef;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct AbstractSurfaceProperty;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A surface property (inline surface and/or `xlink:href`), borrowed from a city model.
 */
class AbstractSurfaceProperty {
public:

  /**
   * The inline surface; none if the property only references one via `href`.
   */
  inline const ecitygml::AbstractSurfaceKind* object() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::HRef* href() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AbstractSurfaceProperty* AsFFI() const;
    inline ecitygml::capi::AbstractSurfaceProperty* AsFFI();
    inline static const ecitygml::AbstractSurfaceProperty* FromFFI(const ecitygml::capi::AbstractSurfaceProperty* ptr);
    inline static ecitygml::AbstractSurfaceProperty* FromFFI(ecitygml::capi::AbstractSurfaceProperty* ptr);
    inline static void operator delete(void* ptr);
private:
    AbstractSurfaceProperty() = delete;
    AbstractSurfaceProperty(const ecitygml::AbstractSurfaceProperty&) = delete;
    AbstractSurfaceProperty(ecitygml::AbstractSurfaceProperty&&) noexcept = delete;
    AbstractSurfaceProperty operator=(const ecitygml::AbstractSurfaceProperty&) = delete;
    AbstractSurfaceProperty operator=(ecitygml::AbstractSurfaceProperty&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_AbstractSurfaceProperty_D_HPP
