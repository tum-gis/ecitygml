#ifndef ECITYGML_MarkingProperty_D_HPP
#define ECITYGML_MarkingProperty_D_HPP

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
namespace capi { struct Marking; }
class Marking;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct MarkingProperty;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A marking property (inline marking and/or `xlink:href`), borrowed from a city model.
 */
class MarkingProperty {
public:

  /**
   * The inline marking; none if the property only references one via `href`.
   */
  inline const ecitygml::Marking* object() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::HRef* href() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::MarkingProperty* AsFFI() const;
    inline ecitygml::capi::MarkingProperty* AsFFI();
    inline static const ecitygml::MarkingProperty* FromFFI(const ecitygml::capi::MarkingProperty* ptr);
    inline static ecitygml::MarkingProperty* FromFFI(ecitygml::capi::MarkingProperty* ptr);
    inline static void operator delete(void* ptr);
private:
    MarkingProperty() = delete;
    MarkingProperty(const ecitygml::MarkingProperty&) = delete;
    MarkingProperty(ecitygml::MarkingProperty&&) noexcept = delete;
    MarkingProperty operator=(const ecitygml::MarkingProperty&) = delete;
    MarkingProperty operator=(ecitygml::MarkingProperty&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_MarkingProperty_D_HPP
