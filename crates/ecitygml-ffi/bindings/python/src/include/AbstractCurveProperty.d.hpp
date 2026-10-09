#ifndef ECITYGML_AbstractCurveProperty_D_HPP
#define ECITYGML_AbstractCurveProperty_D_HPP

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
namespace capi { struct AbstractCurveKind; }
class AbstractCurveKind;
namespace capi { struct HRef; }
class HRef;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct AbstractCurveProperty;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A curve property (inline curve and/or `xlink:href`), borrowed from a city model.
 */
class AbstractCurveProperty {
public:

  /**
   * The inline curve; none if the property only references one via `href`.
   */
  inline const ecitygml::AbstractCurveKind* object() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::HRef* href() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AbstractCurveProperty* AsFFI() const;
    inline ecitygml::capi::AbstractCurveProperty* AsFFI();
    inline static const ecitygml::AbstractCurveProperty* FromFFI(const ecitygml::capi::AbstractCurveProperty* ptr);
    inline static ecitygml::AbstractCurveProperty* FromFFI(ecitygml::capi::AbstractCurveProperty* ptr);
    inline static void operator delete(void* ptr);
private:
    AbstractCurveProperty() = delete;
    AbstractCurveProperty(const ecitygml::AbstractCurveProperty&) = delete;
    AbstractCurveProperty(ecitygml::AbstractCurveProperty&&) noexcept = delete;
    AbstractCurveProperty operator=(const ecitygml::AbstractCurveProperty&) = delete;
    AbstractCurveProperty operator=(ecitygml::AbstractCurveProperty&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_AbstractCurveProperty_D_HPP
