#ifndef ECITYGML_TunnelPartProperty_D_HPP
#define ECITYGML_TunnelPartProperty_D_HPP

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
namespace capi { struct TunnelPart; }
class TunnelPart;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct TunnelPartProperty;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A tunnel part property (inline tunnel part and/or `xlink:href`), borrowed from a city model.
 */
class TunnelPartProperty {
public:

  /**
   * The inline tunnel part; none if the property only references one via `href`.
   */
  inline const ecitygml::TunnelPart* object() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::HRef* href() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::TunnelPartProperty* AsFFI() const;
    inline ecitygml::capi::TunnelPartProperty* AsFFI();
    inline static const ecitygml::TunnelPartProperty* FromFFI(const ecitygml::capi::TunnelPartProperty* ptr);
    inline static ecitygml::TunnelPartProperty* FromFFI(ecitygml::capi::TunnelPartProperty* ptr);
    inline static void operator delete(void* ptr);
private:
    TunnelPartProperty() = delete;
    TunnelPartProperty(const ecitygml::TunnelPartProperty&) = delete;
    TunnelPartProperty(ecitygml::TunnelPartProperty&&) noexcept = delete;
    TunnelPartProperty operator=(const ecitygml::TunnelPartProperty&) = delete;
    TunnelPartProperty operator=(ecitygml::TunnelPartProperty&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_TunnelPartProperty_D_HPP
