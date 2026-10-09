#ifndef ecitygml_AbstractSurfacePatchKind_D_HPP
#define ecitygml_AbstractSurfacePatchKind_D_HPP

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
namespace capi { struct DirectPositionIterator; }
class DirectPositionIterator;
namespace capi { struct Envelope; }
class Envelope;
namespace capi { struct Error; }
class Error;
namespace capi { struct Triangulation; }
class Triangulation;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct AbstractSurfacePatchKind;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A surface patch of any type, borrowed from a city model; convert it with
 * `PolygonPatch::try_from` or `Triangle::try_from`. Patches aren't GML objects (no `gml:id`).
 */
class AbstractSurfacePatchKind {
public:

  /**
   * Triangulates the geometry (Rust: `Triangulate::triangulate`). Members that fail to
   * triangulate are listed in `Triangulation::skipped`; as in egml, members that are only an
   * `xlink:href` are left out without such an entry.
   */
  inline diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>> triangulate() const;

  inline diplomat::result<double, std::unique_ptr<ecitygml::Error>> area_3d() const;

  /**
   * The patch's positions.
   */
  inline std::unique_ptr<ecitygml::DirectPositionIterator> points() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
   */
  inline std::unique_ptr<ecitygml::Envelope> compute_envelope() const;

    inline const ecitygml::capi::AbstractSurfacePatchKind* AsFFI() const;
    inline ecitygml::capi::AbstractSurfacePatchKind* AsFFI();
    inline static const ecitygml::AbstractSurfacePatchKind* FromFFI(const ecitygml::capi::AbstractSurfacePatchKind* ptr);
    inline static ecitygml::AbstractSurfacePatchKind* FromFFI(ecitygml::capi::AbstractSurfacePatchKind* ptr);
    inline static void operator delete(void* ptr);
private:
    AbstractSurfacePatchKind() = delete;
    AbstractSurfacePatchKind(const ecitygml::AbstractSurfacePatchKind&) = delete;
    AbstractSurfacePatchKind(ecitygml::AbstractSurfacePatchKind&&) noexcept = delete;
    AbstractSurfacePatchKind operator=(const ecitygml::AbstractSurfacePatchKind&) = delete;
    AbstractSurfacePatchKind operator=(ecitygml::AbstractSurfacePatchKind&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_AbstractSurfacePatchKind_D_HPP
