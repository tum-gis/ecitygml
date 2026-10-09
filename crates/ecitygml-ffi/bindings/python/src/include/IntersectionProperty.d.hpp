#ifndef ECITYGML_IntersectionProperty_D_HPP
#define ECITYGML_IntersectionProperty_D_HPP

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
namespace capi { struct Intersection; }
class Intersection;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct IntersectionProperty;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A intersection property (inline intersection and/or `xlink:href`), borrowed from a city model.
 */
class IntersectionProperty {
public:

  /**
   * The inline intersection; none if the property only references one via `href`.
   */
  inline const ecitygml::Intersection* object() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::HRef* href() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::IntersectionProperty* AsFFI() const;
    inline ecitygml::capi::IntersectionProperty* AsFFI();
    inline static const ecitygml::IntersectionProperty* FromFFI(const ecitygml::capi::IntersectionProperty* ptr);
    inline static ecitygml::IntersectionProperty* FromFFI(ecitygml::capi::IntersectionProperty* ptr);
    inline static void operator delete(void* ptr);
private:
    IntersectionProperty() = delete;
    IntersectionProperty(const ecitygml::IntersectionProperty&) = delete;
    IntersectionProperty(ecitygml::IntersectionProperty&&) noexcept = delete;
    IntersectionProperty operator=(const ecitygml::IntersectionProperty&) = delete;
    IntersectionProperty operator=(ecitygml::IntersectionProperty&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_IntersectionProperty_D_HPP
