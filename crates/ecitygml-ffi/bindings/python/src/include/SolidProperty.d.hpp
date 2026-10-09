#ifndef ECITYGML_SolidProperty_D_HPP
#define ECITYGML_SolidProperty_D_HPP

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
namespace capi { struct Solid; }
class Solid;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct SolidProperty;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A solid property (inline solid and/or `xlink:href`), borrowed from a city model.
 */
class SolidProperty {
public:

  /**
   * The inline solid; none if the property only references one via `href`.
   */
  inline const ecitygml::Solid* object() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::HRef* href() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::SolidProperty* AsFFI() const;
    inline ecitygml::capi::SolidProperty* AsFFI();
    inline static const ecitygml::SolidProperty* FromFFI(const ecitygml::capi::SolidProperty* ptr);
    inline static ecitygml::SolidProperty* FromFFI(ecitygml::capi::SolidProperty* ptr);
    inline static void operator delete(void* ptr);
private:
    SolidProperty() = delete;
    SolidProperty(const ecitygml::SolidProperty&) = delete;
    SolidProperty(ecitygml::SolidProperty&&) noexcept = delete;
    SolidProperty operator=(const ecitygml::SolidProperty&) = delete;
    SolidProperty operator=(ecitygml::SolidProperty&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_SolidProperty_D_HPP
