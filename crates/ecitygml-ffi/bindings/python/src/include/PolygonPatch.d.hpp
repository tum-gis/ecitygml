#ifndef ECITYGML_PolygonPatch_D_HPP
#define ECITYGML_PolygonPatch_D_HPP

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
namespace capi { struct AbstractSurfacePatchKind; }
class AbstractSurfacePatchKind;
namespace capi { struct DirectPositionIterator; }
class DirectPositionIterator;
namespace capi { struct Envelope; }
class Envelope;
namespace capi { struct Error; }
class Error;
namespace capi { struct PolygonPatch; }
class PolygonPatch;
namespace capi { struct Triangulation; }
class Triangulation;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct PolygonPatch;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A polygon patch, borrowed from a city model.
 */
class PolygonPatch {
public:

  /**
   * Triangulates the geometry (Rust: `Triangulate::triangulate`). Members that fail to
   * triangulate are listed in `Triangulation::skipped`; as in egml, members that are only an
   * `xlink:href` are left out without such an entry.
   */
  inline ecitygml::diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>> triangulate() const;

  /**
   * The patch as a polygon patch, or none if it is another type (Rust: `PolygonPatch::try_from`, which
   * takes the patch by value).
   */
  inline static const ecitygml::PolygonPatch* try_from(const ecitygml::AbstractSurfacePatchKind& patch DIPLOMAT_LIFETIME_BOUND);

  inline const ecitygml::AbstractRingKind* exterior() const DIPLOMAT_LIFETIME_BOUND;

  inline std::unique_ptr<ecitygml::AbstractRingKindIterator> interior() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * Exterior area minus the holes; fails if the patch has no exterior ring.
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

    inline const ecitygml::capi::PolygonPatch* AsFFI() const;
    inline ecitygml::capi::PolygonPatch* AsFFI();
    inline static const ecitygml::PolygonPatch* FromFFI(const ecitygml::capi::PolygonPatch* ptr);
    inline static ecitygml::PolygonPatch* FromFFI(ecitygml::capi::PolygonPatch* ptr);
    inline static void operator delete(void* ptr);
private:
    PolygonPatch() = delete;
    PolygonPatch(const ecitygml::PolygonPatch&) = delete;
    PolygonPatch(ecitygml::PolygonPatch&&) noexcept = delete;
    PolygonPatch operator=(const ecitygml::PolygonPatch&) = delete;
    PolygonPatch operator=(ecitygml::PolygonPatch&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_PolygonPatch_D_HPP
