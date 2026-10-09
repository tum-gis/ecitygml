#ifndef ecitygml_HoleProperty_D_HPP
#define ecitygml_HoleProperty_D_HPP

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"

namespace ecitygml {
namespace capi { struct HRef; }
class HRef;
namespace capi { struct Hole; }
class Hole;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct HoleProperty;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A hole property (inline hole and/or `xlink:href`), borrowed from a city model.
 */
class HoleProperty {
public:

  /**
   * The inline hole; none if the property only references one via `href`.
   */
  inline const ecitygml::Hole* object() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::HRef* href() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::HoleProperty* AsFFI() const;
    inline ecitygml::capi::HoleProperty* AsFFI();
    inline static const ecitygml::HoleProperty* FromFFI(const ecitygml::capi::HoleProperty* ptr);
    inline static ecitygml::HoleProperty* FromFFI(ecitygml::capi::HoleProperty* ptr);
    inline static void operator delete(void* ptr);
private:
    HoleProperty() = delete;
    HoleProperty(const ecitygml::HoleProperty&) = delete;
    HoleProperty(ecitygml::HoleProperty&&) noexcept = delete;
    HoleProperty operator=(const ecitygml::HoleProperty&) = delete;
    HoleProperty operator=(ecitygml::HoleProperty&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_HoleProperty_D_HPP
