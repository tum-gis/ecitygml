#ifndef ECITYGML_BuildingPartProperty_D_HPP
#define ECITYGML_BuildingPartProperty_D_HPP

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
namespace capi { struct BuildingPart; }
class BuildingPart;
namespace capi { struct HRef; }
class HRef;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct BuildingPartProperty;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A building part property (inline building part and/or `xlink:href`), borrowed from a city model.
 */
class BuildingPartProperty {
public:

  /**
   * The inline building part; none if the property only references one via `href`.
   */
  inline const ecitygml::BuildingPart* object() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::HRef* href() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::BuildingPartProperty* AsFFI() const;
    inline ecitygml::capi::BuildingPartProperty* AsFFI();
    inline static const ecitygml::BuildingPartProperty* FromFFI(const ecitygml::capi::BuildingPartProperty* ptr);
    inline static ecitygml::BuildingPartProperty* FromFFI(ecitygml::capi::BuildingPartProperty* ptr);
    inline static void operator delete(void* ptr);
private:
    BuildingPartProperty() = delete;
    BuildingPartProperty(const ecitygml::BuildingPartProperty&) = delete;
    BuildingPartProperty(ecitygml::BuildingPartProperty&&) noexcept = delete;
    BuildingPartProperty operator=(const ecitygml::BuildingPartProperty&) = delete;
    BuildingPartProperty operator=(ecitygml::BuildingPartProperty&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_BuildingPartProperty_D_HPP
