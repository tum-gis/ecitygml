#ifndef ECITYGML_AuxiliaryTrafficSpaceProperty_D_HPP
#define ECITYGML_AuxiliaryTrafficSpaceProperty_D_HPP

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
namespace capi { struct AuxiliaryTrafficSpace; }
class AuxiliaryTrafficSpace;
namespace capi { struct HRef; }
class HRef;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct AuxiliaryTrafficSpaceProperty;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A auxiliary traffic space property (inline auxiliary traffic space and/or `xlink:href`), borrowed from a city model.
 */
class AuxiliaryTrafficSpaceProperty {
public:

  /**
   * The inline auxiliary traffic space; none if the property only references one via `href`.
   */
  inline const ecitygml::AuxiliaryTrafficSpace* object() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::HRef* href() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AuxiliaryTrafficSpaceProperty* AsFFI() const;
    inline ecitygml::capi::AuxiliaryTrafficSpaceProperty* AsFFI();
    inline static const ecitygml::AuxiliaryTrafficSpaceProperty* FromFFI(const ecitygml::capi::AuxiliaryTrafficSpaceProperty* ptr);
    inline static ecitygml::AuxiliaryTrafficSpaceProperty* FromFFI(ecitygml::capi::AuxiliaryTrafficSpaceProperty* ptr);
    inline static void operator delete(void* ptr);
private:
    AuxiliaryTrafficSpaceProperty() = delete;
    AuxiliaryTrafficSpaceProperty(const ecitygml::AuxiliaryTrafficSpaceProperty&) = delete;
    AuxiliaryTrafficSpaceProperty(ecitygml::AuxiliaryTrafficSpaceProperty&&) noexcept = delete;
    AuxiliaryTrafficSpaceProperty operator=(const ecitygml::AuxiliaryTrafficSpaceProperty&) = delete;
    AuxiliaryTrafficSpaceProperty operator=(ecitygml::AuxiliaryTrafficSpaceProperty&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_AuxiliaryTrafficSpaceProperty_D_HPP
