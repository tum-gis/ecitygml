#ifndef ECITYGML_SectionProperty_D_HPP
#define ECITYGML_SectionProperty_D_HPP

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
namespace capi { struct Section; }
class Section;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct SectionProperty;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A section property (inline section and/or `xlink:href`), borrowed from a city model.
 */
class SectionProperty {
public:

  /**
   * The inline section; none if the property only references one via `href`.
   */
  inline const ecitygml::Section* object() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::HRef* href() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::SectionProperty* AsFFI() const;
    inline ecitygml::capi::SectionProperty* AsFFI();
    inline static const ecitygml::SectionProperty* FromFFI(const ecitygml::capi::SectionProperty* ptr);
    inline static ecitygml::SectionProperty* FromFFI(ecitygml::capi::SectionProperty* ptr);
    inline static void operator delete(void* ptr);
private:
    SectionProperty() = delete;
    SectionProperty(const ecitygml::SectionProperty&) = delete;
    SectionProperty(ecitygml::SectionProperty&&) noexcept = delete;
    SectionProperty operator=(const ecitygml::SectionProperty&) = delete;
    SectionProperty operator=(ecitygml::SectionProperty&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_SectionProperty_D_HPP
