#ifndef ECITYGML_ImplicitGeometryProperty_D_HPP
#define ECITYGML_ImplicitGeometryProperty_D_HPP

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
namespace capi { struct ImplicitGeometry; }
class ImplicitGeometry;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct ImplicitGeometryProperty;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * An implicit geometry property (inline implicit geometry and/or `xlink:href`), borrowed from a city model.
 */
class ImplicitGeometryProperty {
public:

  /**
   * The inline implicit geometry; none if the property only references one via `href`.
   */
  inline const ecitygml::ImplicitGeometry* object() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::HRef* href() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::ImplicitGeometryProperty* AsFFI() const;
    inline ecitygml::capi::ImplicitGeometryProperty* AsFFI();
    inline static const ecitygml::ImplicitGeometryProperty* FromFFI(const ecitygml::capi::ImplicitGeometryProperty* ptr);
    inline static ecitygml::ImplicitGeometryProperty* FromFFI(ecitygml::capi::ImplicitGeometryProperty* ptr);
    inline static void operator delete(void* ptr);
private:
    ImplicitGeometryProperty() = delete;
    ImplicitGeometryProperty(const ecitygml::ImplicitGeometryProperty&) = delete;
    ImplicitGeometryProperty(ecitygml::ImplicitGeometryProperty&&) noexcept = delete;
    ImplicitGeometryProperty operator=(const ecitygml::ImplicitGeometryProperty&) = delete;
    ImplicitGeometryProperty operator=(ecitygml::ImplicitGeometryProperty&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_ImplicitGeometryProperty_D_HPP
