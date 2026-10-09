#ifndef ECITYGML_Height_D_HPP
#define ECITYGML_Height_D_HPP

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
namespace capi { struct ElevationReferenceValue; }
class ElevationReferenceValue;
namespace capi { struct Length; }
class Length;
class HeightStatusValue;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct Height;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A height of a construction between two reference levels, borrowed from a city model.
 */
class Height {
public:

  inline const ecitygml::ElevationReferenceValue& high_reference() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::ElevationReferenceValue& low_reference() const DIPLOMAT_LIFETIME_BOUND;

  inline ecitygml::HeightStatusValue status() const;

  /**
   * The height value (`con:value`).
   */
  inline const ecitygml::Length& length() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::Height* AsFFI() const;
    inline ecitygml::capi::Height* AsFFI();
    inline static const ecitygml::Height* FromFFI(const ecitygml::capi::Height* ptr);
    inline static ecitygml::Height* FromFFI(ecitygml::capi::Height* ptr);
    inline static void operator delete(void* ptr);
private:
    Height() = delete;
    Height(const ecitygml::Height&) = delete;
    Height(ecitygml::Height&&) noexcept = delete;
    Height operator=(const ecitygml::Height&) = delete;
    Height operator=(ecitygml::Height&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_Height_D_HPP
