#ifndef ECITYGML_PointProperty_D_HPP
#define ECITYGML_PointProperty_D_HPP

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
namespace capi { struct Point; }
class Point;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct PointProperty;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A point property (inline point and/or `xlink:href`), borrowed from a city model.
 */
class PointProperty {
public:

  /**
   * The inline point; none if the property only references one via `href`.
   */
  inline const ecitygml::Point* object() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::HRef* href() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::PointProperty* AsFFI() const;
    inline ecitygml::capi::PointProperty* AsFFI();
    inline static const ecitygml::PointProperty* FromFFI(const ecitygml::capi::PointProperty* ptr);
    inline static ecitygml::PointProperty* FromFFI(ecitygml::capi::PointProperty* ptr);
    inline static void operator delete(void* ptr);
private:
    PointProperty() = delete;
    PointProperty(const ecitygml::PointProperty&) = delete;
    PointProperty(ecitygml::PointProperty&&) noexcept = delete;
    PointProperty operator=(const ecitygml::PointProperty&) = delete;
    PointProperty operator=(ecitygml::PointProperty&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_PointProperty_D_HPP
