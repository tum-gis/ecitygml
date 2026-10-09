#ifndef ecitygml_CompositeSurface_D_HPP
#define ecitygml_CompositeSurface_D_HPP

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
namespace capi { struct AbstractSurfaceKind; }
class AbstractSurfaceKind;
namespace capi { struct AbstractSurfacePropertyIterator; }
class AbstractSurfacePropertyIterator;
namespace capi { struct CodeIterator; }
class CodeIterator;
namespace capi { struct CompositeSurface; }
class CompositeSurface;
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
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct CompositeSurface;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A composite surface, borrowed from a city model.
 */
class CompositeSurface {
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

  /**
   * The surface as a composite surface, or none if it is another type (Rust:
   * `CompositeSurface::try_from`, which takes the surface by value).
   */
  inline static const ecitygml::CompositeSurface* try_from(const ecitygml::AbstractSurfaceKind& surface DIPLOMAT_LIFETIME_BOUND);

  /**
   * The surface members (`gml:surfaceMember`).
   */
  inline std::unique_ptr<ecitygml::AbstractSurfacePropertyIterator> surface_member() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * Sum of the members' areas; fails with `UnresolvedReference` if a member is only an
   * `xlink:href`.
   */
  inline diplomat::result<double, std::unique_ptr<ecitygml::Error>> area_3d() const;

  /**
   * All positions of the inline members.
   */
  inline std::unique_ptr<ecitygml::DirectPositionIterator> points() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
   */
  inline std::unique_ptr<ecitygml::Envelope> compute_envelope() const;

    inline const ecitygml::capi::CompositeSurface* AsFFI() const;
    inline ecitygml::capi::CompositeSurface* AsFFI();
    inline static const ecitygml::CompositeSurface* FromFFI(const ecitygml::capi::CompositeSurface* ptr);
    inline static ecitygml::CompositeSurface* FromFFI(ecitygml::capi::CompositeSurface* ptr);
    inline static void operator delete(void* ptr);
private:
    CompositeSurface() = delete;
    CompositeSurface(const ecitygml::CompositeSurface&) = delete;
    CompositeSurface(ecitygml::CompositeSurface&&) noexcept = delete;
    CompositeSurface operator=(const ecitygml::CompositeSurface&) = delete;
    CompositeSurface operator=(ecitygml::CompositeSurface&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_CompositeSurface_D_HPP
