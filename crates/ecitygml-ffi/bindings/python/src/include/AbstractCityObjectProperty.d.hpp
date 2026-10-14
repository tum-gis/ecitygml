#ifndef ECITYGML_AbstractCityObjectProperty_D_HPP
#define ECITYGML_AbstractCityObjectProperty_D_HPP

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
namespace capi { struct AbstractCityObjectKind; }
class AbstractCityObjectKind;
namespace capi { struct HRef; }
class HRef;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct AbstractCityObjectProperty;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A city object property (inline city object and/or `xlink:href`), borrowed from a city model.
 */
class AbstractCityObjectProperty {
public:

  /**
   * The inline city object; none if the property only references one via `href`.
   */
  inline const ecitygml::AbstractCityObjectKind* object() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::HRef* href() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AbstractCityObjectProperty* AsFFI() const;
    inline ecitygml::capi::AbstractCityObjectProperty* AsFFI();
    inline static const ecitygml::AbstractCityObjectProperty* FromFFI(const ecitygml::capi::AbstractCityObjectProperty* ptr);
    inline static ecitygml::AbstractCityObjectProperty* FromFFI(ecitygml::capi::AbstractCityObjectProperty* ptr);
    inline static void operator delete(void* ptr);
private:
    AbstractCityObjectProperty() = delete;
    AbstractCityObjectProperty(const ecitygml::AbstractCityObjectProperty&) = delete;
    AbstractCityObjectProperty(ecitygml::AbstractCityObjectProperty&&) noexcept = delete;
    AbstractCityObjectProperty operator=(const ecitygml::AbstractCityObjectProperty&) = delete;
    AbstractCityObjectProperty operator=(ecitygml::AbstractCityObjectProperty&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_AbstractCityObjectProperty_D_HPP
