#ifndef ECITYGML_AbstractSpaceBoundaryProperty_D_HPP
#define ECITYGML_AbstractSpaceBoundaryProperty_D_HPP

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
namespace capi { struct AbstractSpaceBoundaryKind; }
class AbstractSpaceBoundaryKind;
namespace capi { struct HRef; }
class HRef;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct AbstractSpaceBoundaryProperty;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A space boundary property (inline space boundary and/or `xlink:href`), borrowed from a city model.
 */
class AbstractSpaceBoundaryProperty {
public:

  /**
   * The inline space boundary; none if the property only references one via `href`.
   */
  inline const ecitygml::AbstractSpaceBoundaryKind* object() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::HRef* href() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AbstractSpaceBoundaryProperty* AsFFI() const;
    inline ecitygml::capi::AbstractSpaceBoundaryProperty* AsFFI();
    inline static const ecitygml::AbstractSpaceBoundaryProperty* FromFFI(const ecitygml::capi::AbstractSpaceBoundaryProperty* ptr);
    inline static ecitygml::AbstractSpaceBoundaryProperty* FromFFI(ecitygml::capi::AbstractSpaceBoundaryProperty* ptr);
    inline static void operator delete(void* ptr);
private:
    AbstractSpaceBoundaryProperty() = delete;
    AbstractSpaceBoundaryProperty(const ecitygml::AbstractSpaceBoundaryProperty&) = delete;
    AbstractSpaceBoundaryProperty(ecitygml::AbstractSpaceBoundaryProperty&&) noexcept = delete;
    AbstractSpaceBoundaryProperty operator=(const ecitygml::AbstractSpaceBoundaryProperty&) = delete;
    AbstractSpaceBoundaryProperty operator=(ecitygml::AbstractSpaceBoundaryProperty&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_AbstractSpaceBoundaryProperty_D_HPP
