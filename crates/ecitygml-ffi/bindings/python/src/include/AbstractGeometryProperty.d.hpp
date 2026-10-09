#ifndef ECITYGML_AbstractGeometryProperty_D_HPP
#define ECITYGML_AbstractGeometryProperty_D_HPP

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
namespace capi { struct AbstractGeometryKind; }
class AbstractGeometryKind;
namespace capi { struct HRef; }
class HRef;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct AbstractGeometryProperty;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A geometry property (inline geometry and/or `xlink:href`), borrowed from a city model.
 */
class AbstractGeometryProperty {
public:

  /**
   * The inline geometry; none if the property only references one via `href`.
   */
  inline const ecitygml::AbstractGeometryKind* object() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::HRef* href() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AbstractGeometryProperty* AsFFI() const;
    inline ecitygml::capi::AbstractGeometryProperty* AsFFI();
    inline static const ecitygml::AbstractGeometryProperty* FromFFI(const ecitygml::capi::AbstractGeometryProperty* ptr);
    inline static ecitygml::AbstractGeometryProperty* FromFFI(ecitygml::capi::AbstractGeometryProperty* ptr);
    inline static void operator delete(void* ptr);
private:
    AbstractGeometryProperty() = delete;
    AbstractGeometryProperty(const ecitygml::AbstractGeometryProperty&) = delete;
    AbstractGeometryProperty(ecitygml::AbstractGeometryProperty&&) noexcept = delete;
    AbstractGeometryProperty operator=(const ecitygml::AbstractGeometryProperty&) = delete;
    AbstractGeometryProperty operator=(ecitygml::AbstractGeometryProperty&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_AbstractGeometryProperty_D_HPP
