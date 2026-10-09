#ifndef ECITYGML_TriangulatedSurface_D_HPP
#define ECITYGML_TriangulatedSurface_D_HPP

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
namespace capi { struct Surface; }
class Surface;
namespace capi { struct TriangleIterator; }
class TriangleIterator;
namespace capi { struct TriangulatedSurface; }
class TriangulatedSurface;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct TriangulatedSurface;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A surface made of triangles, borrowed from a city model or a triangulation.
 */
class TriangulatedSurface {
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
   * The surface as a triangulated surface, or none if it is another type (Rust: a
   * `TriangulatedSurface` in `AbstractSurfaceKind::SurfaceKind`).
   */
  inline static const ecitygml::TriangulatedSurface* try_from(const ecitygml::AbstractSurfaceKind& surface DIPLOMAT_LIFETIME_BOUND);

  inline std::unique_ptr<ecitygml::TriangleIterator> triangles() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * The underlying surface, whose patches are the triangles.
   */
  inline const ecitygml::Surface& surface() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * All corners of the triangles.
   */
  inline std::unique_ptr<ecitygml::DirectPositionIterator> points() const DIPLOMAT_LIFETIME_BOUND;

  inline ecitygml::diplomat::result<double, std::unique_ptr<ecitygml::Error>> area_3d() const;

  /**
   * Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
   */
  inline std::unique_ptr<ecitygml::Envelope> compute_envelope() const;

    inline const ecitygml::capi::TriangulatedSurface* AsFFI() const;
    inline ecitygml::capi::TriangulatedSurface* AsFFI();
    inline static const ecitygml::TriangulatedSurface* FromFFI(const ecitygml::capi::TriangulatedSurface* ptr);
    inline static ecitygml::TriangulatedSurface* FromFFI(ecitygml::capi::TriangulatedSurface* ptr);
    inline static void operator delete(void* ptr);
private:
    TriangulatedSurface() = delete;
    TriangulatedSurface(const ecitygml::TriangulatedSurface&) = delete;
    TriangulatedSurface(ecitygml::TriangulatedSurface&&) noexcept = delete;
    TriangulatedSurface operator=(const ecitygml::TriangulatedSurface&) = delete;
    TriangulatedSurface operator=(ecitygml::TriangulatedSurface&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_TriangulatedSurface_D_HPP
