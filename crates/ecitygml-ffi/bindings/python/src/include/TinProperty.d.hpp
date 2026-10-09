#ifndef ECITYGML_TinProperty_D_HPP
#define ECITYGML_TinProperty_D_HPP

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
namespace capi { struct TriangulatedSurface; }
class TriangulatedSurface;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct TinProperty;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A TIN property (inline triangulated surface and/or `xlink:href`), borrowed from a city model.
 */
class TinProperty {
public:

  /**
   * The inline triangulated surface; none if the property only references one via `href`.
   */
  inline const ecitygml::TriangulatedSurface* object() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::HRef* href() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::TinProperty* AsFFI() const;
    inline ecitygml::capi::TinProperty* AsFFI();
    inline static const ecitygml::TinProperty* FromFFI(const ecitygml::capi::TinProperty* ptr);
    inline static ecitygml::TinProperty* FromFFI(ecitygml::capi::TinProperty* ptr);
    inline static void operator delete(void* ptr);
private:
    TinProperty() = delete;
    TinProperty(const ecitygml::TinProperty&) = delete;
    TinProperty(ecitygml::TinProperty&&) noexcept = delete;
    TinProperty operator=(const ecitygml::TinProperty&) = delete;
    TinProperty operator=(ecitygml::TinProperty&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_TinProperty_D_HPP
