#ifndef ecitygml_BoundingShape_D_HPP
#define ecitygml_BoundingShape_D_HPP

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
namespace capi { struct Envelope; }
class Envelope;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct BoundingShape;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The bounding shape of a feature (`gml:boundedBy`), borrowed from a city model.
 */
class BoundingShape {
public:

  /**
   * The envelope; none if the shape is nil.
   */
  inline const ecitygml::Envelope* envelope() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::BoundingShape* AsFFI() const;
    inline ecitygml::capi::BoundingShape* AsFFI();
    inline static const ecitygml::BoundingShape* FromFFI(const ecitygml::capi::BoundingShape* ptr);
    inline static ecitygml::BoundingShape* FromFFI(ecitygml::capi::BoundingShape* ptr);
    inline static void operator delete(void* ptr);
private:
    BoundingShape() = delete;
    BoundingShape(const ecitygml::BoundingShape&) = delete;
    BoundingShape(ecitygml::BoundingShape&&) noexcept = delete;
    BoundingShape operator=(const ecitygml::BoundingShape&) = delete;
    BoundingShape operator=(ecitygml::BoundingShape&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_BoundingShape_D_HPP
