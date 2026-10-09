#ifndef ecitygml_AbstractGeometryKind_D_HPP
#define ecitygml_AbstractGeometryKind_D_HPP

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
namespace capi { struct CodeIterator; }
class CodeIterator;
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
    struct AbstractGeometryKind;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A geometry of any type, borrowed from a city model; convert it with `MultiSurface::try_from`,
 * `MultiCurve::try_from`, `Point::try_from`, `Solid::try_from`, `AbstractSurfaceKind::try_from`
 * or `AbstractCurveKind::try_from`. Not bound yet: `MultiPoint`, `MultiGeometry`.
 */
class AbstractGeometryKind {
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
  inline diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>> triangulate() const;

  inline ecitygml::GeometryType geometry_type() const;

  /**
   * Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
   */
  inline std::unique_ptr<ecitygml::Envelope> compute_envelope() const;

    inline const ecitygml::capi::AbstractGeometryKind* AsFFI() const;
    inline ecitygml::capi::AbstractGeometryKind* AsFFI();
    inline static const ecitygml::AbstractGeometryKind* FromFFI(const ecitygml::capi::AbstractGeometryKind* ptr);
    inline static ecitygml::AbstractGeometryKind* FromFFI(ecitygml::capi::AbstractGeometryKind* ptr);
    inline static void operator delete(void* ptr);
private:
    AbstractGeometryKind() = delete;
    AbstractGeometryKind(const ecitygml::AbstractGeometryKind&) = delete;
    AbstractGeometryKind(ecitygml::AbstractGeometryKind&&) noexcept = delete;
    AbstractGeometryKind operator=(const ecitygml::AbstractGeometryKind&) = delete;
    AbstractGeometryKind operator=(ecitygml::AbstractGeometryKind&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_AbstractGeometryKind_D_HPP
