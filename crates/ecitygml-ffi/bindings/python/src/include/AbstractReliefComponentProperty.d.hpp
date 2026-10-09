#ifndef ECITYGML_AbstractReliefComponentProperty_D_HPP
#define ECITYGML_AbstractReliefComponentProperty_D_HPP

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
namespace capi { struct AbstractReliefComponentKind; }
class AbstractReliefComponentKind;
namespace capi { struct HRef; }
class HRef;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct AbstractReliefComponentProperty;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A relief component property (inline relief component and/or `xlink:href`), borrowed from a city model.
 */
class AbstractReliefComponentProperty {
public:

  /**
   * The inline relief component; none if the property only references one via `href`.
   */
  inline const ecitygml::AbstractReliefComponentKind* object() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::HRef* href() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AbstractReliefComponentProperty* AsFFI() const;
    inline ecitygml::capi::AbstractReliefComponentProperty* AsFFI();
    inline static const ecitygml::AbstractReliefComponentProperty* FromFFI(const ecitygml::capi::AbstractReliefComponentProperty* ptr);
    inline static ecitygml::AbstractReliefComponentProperty* FromFFI(ecitygml::capi::AbstractReliefComponentProperty* ptr);
    inline static void operator delete(void* ptr);
private:
    AbstractReliefComponentProperty() = delete;
    AbstractReliefComponentProperty(const ecitygml::AbstractReliefComponentProperty&) = delete;
    AbstractReliefComponentProperty(ecitygml::AbstractReliefComponentProperty&&) noexcept = delete;
    AbstractReliefComponentProperty operator=(const ecitygml::AbstractReliefComponentProperty&) = delete;
    AbstractReliefComponentProperty operator=(ecitygml::AbstractReliefComponentProperty&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_AbstractReliefComponentProperty_D_HPP
