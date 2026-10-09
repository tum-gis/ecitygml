#ifndef ECITYGML_TrafficSpaceProperty_D_HPP
#define ECITYGML_TrafficSpaceProperty_D_HPP

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
namespace capi { struct TrafficSpace; }
class TrafficSpace;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct TrafficSpaceProperty;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A traffic space property (inline traffic space and/or `xlink:href`), borrowed from a city model.
 */
class TrafficSpaceProperty {
public:

  /**
   * The inline traffic space; none if the property only references one via `href`.
   */
  inline const ecitygml::TrafficSpace* object() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::HRef* href() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::TrafficSpaceProperty* AsFFI() const;
    inline ecitygml::capi::TrafficSpaceProperty* AsFFI();
    inline static const ecitygml::TrafficSpaceProperty* FromFFI(const ecitygml::capi::TrafficSpaceProperty* ptr);
    inline static ecitygml::TrafficSpaceProperty* FromFFI(ecitygml::capi::TrafficSpaceProperty* ptr);
    inline static void operator delete(void* ptr);
private:
    TrafficSpaceProperty() = delete;
    TrafficSpaceProperty(const ecitygml::TrafficSpaceProperty&) = delete;
    TrafficSpaceProperty(ecitygml::TrafficSpaceProperty&&) noexcept = delete;
    TrafficSpaceProperty operator=(const ecitygml::TrafficSpaceProperty&) = delete;
    TrafficSpaceProperty operator=(ecitygml::TrafficSpaceProperty&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_TrafficSpaceProperty_D_HPP
