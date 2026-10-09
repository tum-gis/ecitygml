#ifndef ECITYGML_AbstractSurfaceKind_D_HPP
#define ECITYGML_AbstractSurfaceKind_D_HPP

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
namespace capi { struct AbstractGeometryKind; }
class AbstractGeometryKind;
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
namespace capi { struct Triangulation; }
class Triangulation;
class GeometryType;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct AbstractSurfaceKind;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A surface of any type, borrowed from a city model; convert it with `Polygon::try_from`,
 * `CompositeSurface::try_from`, `Shell::try_from`, `Surface::try_from` or
 * `TriangulatedSurface::try_from`.
 */
class AbstractSurfaceKind {
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
   * The geometry as an `AbstractSurfaceKind`, or none if it is another type (Rust: nested
   * `AbstractGeometryKind` variants).
   */
  inline static const ecitygml::AbstractSurfaceKind* try_from(const ecitygml::AbstractGeometryKind& geometry DIPLOMAT_LIFETIME_BOUND);

  inline ecitygml::GeometryType geometry_type() const;

  inline ecitygml::diplomat::result<double, std::unique_ptr<ecitygml::Error>> area_3d() const;

  inline std::unique_ptr<ecitygml::DirectPositionIterator> points() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
   */
  inline std::unique_ptr<ecitygml::Envelope> compute_envelope() const;

    inline const ecitygml::capi::AbstractSurfaceKind* AsFFI() const;
    inline ecitygml::capi::AbstractSurfaceKind* AsFFI();
    inline static const ecitygml::AbstractSurfaceKind* FromFFI(const ecitygml::capi::AbstractSurfaceKind* ptr);
    inline static ecitygml::AbstractSurfaceKind* FromFFI(ecitygml::capi::AbstractSurfaceKind* ptr);
    inline static void operator delete(void* ptr);
private:
    AbstractSurfaceKind() = delete;
    AbstractSurfaceKind(const ecitygml::AbstractSurfaceKind&) = delete;
    AbstractSurfaceKind(ecitygml::AbstractSurfaceKind&&) noexcept = delete;
    AbstractSurfaceKind operator=(const ecitygml::AbstractSurfaceKind&) = delete;
    AbstractSurfaceKind operator=(ecitygml::AbstractSurfaceKind&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_AbstractSurfaceKind_D_HPP
