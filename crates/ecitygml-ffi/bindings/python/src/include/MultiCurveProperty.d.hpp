#ifndef ECITYGML_MultiCurveProperty_D_HPP
#define ECITYGML_MultiCurveProperty_D_HPP

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
namespace capi { struct MultiCurve; }
class MultiCurve;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct MultiCurveProperty;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A multi-curve property (inline multi curve and/or `xlink:href`), borrowed from a city model.
 */
class MultiCurveProperty {
public:

  /**
   * The inline multi curve; none if the property only references one via `href`.
   */
  inline const ecitygml::MultiCurve* object() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::HRef* href() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::MultiCurveProperty* AsFFI() const;
    inline ecitygml::capi::MultiCurveProperty* AsFFI();
    inline static const ecitygml::MultiCurveProperty* FromFFI(const ecitygml::capi::MultiCurveProperty* ptr);
    inline static ecitygml::MultiCurveProperty* FromFFI(ecitygml::capi::MultiCurveProperty* ptr);
    inline static void operator delete(void* ptr);
private:
    MultiCurveProperty() = delete;
    MultiCurveProperty(const ecitygml::MultiCurveProperty&) = delete;
    MultiCurveProperty(ecitygml::MultiCurveProperty&&) noexcept = delete;
    MultiCurveProperty operator=(const ecitygml::MultiCurveProperty&) = delete;
    MultiCurveProperty operator=(ecitygml::MultiCurveProperty&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_MultiCurveProperty_D_HPP
