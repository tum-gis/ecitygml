#ifndef ECITYGML_BridgePartProperty_D_HPP
#define ECITYGML_BridgePartProperty_D_HPP

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
namespace capi { struct BridgePart; }
class BridgePart;
namespace capi { struct HRef; }
class HRef;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct BridgePartProperty;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A bridge part property (inline bridge part and/or `xlink:href`), borrowed from a city model.
 */
class BridgePartProperty {
public:

  /**
   * The inline bridge part; none if the property only references one via `href`.
   */
  inline const ecitygml::BridgePart* object() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::HRef* href() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::BridgePartProperty* AsFFI() const;
    inline ecitygml::capi::BridgePartProperty* AsFFI();
    inline static const ecitygml::BridgePartProperty* FromFFI(const ecitygml::capi::BridgePartProperty* ptr);
    inline static ecitygml::BridgePartProperty* FromFFI(ecitygml::capi::BridgePartProperty* ptr);
    inline static void operator delete(void* ptr);
private:
    BridgePartProperty() = delete;
    BridgePartProperty(const ecitygml::BridgePartProperty&) = delete;
    BridgePartProperty(ecitygml::BridgePartProperty&&) noexcept = delete;
    BridgePartProperty operator=(const ecitygml::BridgePartProperty&) = delete;
    BridgePartProperty operator=(ecitygml::BridgePartProperty&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_BridgePartProperty_D_HPP
