#ifndef ECITYGML_Polygon_D_HPP
#define ECITYGML_Polygon_D_HPP

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
namespace capi { struct AbstractRingKind; }
class AbstractRingKind;
namespace capi { struct AbstractRingKindIterator; }
class AbstractRingKindIterator;
namespace capi { struct AbstractSurfaceKind; }
class AbstractSurfaceKind;
namespace capi { struct CodeIterator; }
class CodeIterator;
namespace capi { struct DirectPositionIterator; }
class DirectPositionIterator;
namespace capi { struct Envelope; }
class Envelope;
namespace capi { struct Error; }
class Error;
namespace capi { struct Id; }
class Id;
namespace capi { struct Polygon; }
class Polygon;
namespace capi { struct Triangulation; }
class Triangulation;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct Polygon;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A polygon, borrowed from a city model.
 */
class Polygon {
public:

  /**
   * The object's `gml:id`, if it has one.
   */
  inline const ecitygml::Id* id() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * The object's `gml:name`s.
   */
  inline std::unique_ptr<ecitygml::CodeIterator> names() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * Triangulates the geometry (Rust: `Triangulate::triangulate`). Members that fail to
   * triangulate are listed in `Triangulation::skipped`; as in egml, members that are only an
   * `xlink:href` are left out without such an entry.
   */
  inline ecitygml::diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>> triangulate() const;

  /**
   * The surface as a polygon, or none if it is another type (Rust: `Polygon::try_from`,
   * which takes the surface by value).
   */
  inline static const ecitygml::Polygon* try_from(const ecitygml::AbstractSurfaceKind& surface DIPLOMAT_LIFETIME_BOUND);

  inline const ecitygml::AbstractRingKind* exterior() const DIPLOMAT_LIFETIME_BOUND;

  inline std::unique_ptr<ecitygml::AbstractRingKindIterator> interior() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * Exterior area minus the holes; fails if the polygon has no exterior ring.
   */
  inline ecitygml::diplomat::result<double, std::unique_ptr<ecitygml::Error>> area_3d() const;

  /**
   * All positions of the exterior and interior rings.
   */
  inline std::unique_ptr<ecitygml::DirectPositionIterator> points() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
   */
  inline std::unique_ptr<ecitygml::Envelope> compute_envelope() const;

    inline const ecitygml::capi::Polygon* AsFFI() const;
    inline ecitygml::capi::Polygon* AsFFI();
    inline static const ecitygml::Polygon* FromFFI(const ecitygml::capi::Polygon* ptr);
    inline static ecitygml::Polygon* FromFFI(ecitygml::capi::Polygon* ptr);
    inline static void operator delete(void* ptr);
private:
    Polygon() = delete;
    Polygon(const ecitygml::Polygon&) = delete;
    Polygon(ecitygml::Polygon&&) noexcept = delete;
    Polygon operator=(const ecitygml::Polygon&) = delete;
    Polygon operator=(ecitygml::Polygon&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_Polygon_D_HPP
