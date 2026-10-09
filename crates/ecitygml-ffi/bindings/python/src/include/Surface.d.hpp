#ifndef ECITYGML_Surface_D_HPP
#define ECITYGML_Surface_D_HPP

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
namespace capi { struct AbstractSurfacePatchKindIterator; }
class AbstractSurfacePatchKindIterator;
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
namespace capi { struct Triangulation; }
class Triangulation;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct Surface;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A surface made of patches, borrowed from a city model.
 */
class Surface {
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
   * The surface as a `gml:Surface`, or none if it is another type (Rust: `Surface::try_from`,
   * which takes the surface by value).
   */
  inline static const ecitygml::Surface* try_from(const ecitygml::AbstractSurfaceKind& surface DIPLOMAT_LIFETIME_BOUND);

  /**
   * The patches (`gml:patches`).
   */
  inline std::unique_ptr<ecitygml::AbstractSurfacePatchKindIterator> patches() const DIPLOMAT_LIFETIME_BOUND;

  inline ecitygml::diplomat::result<double, std::unique_ptr<ecitygml::Error>> area_3d() const;

  /**
   * All positions of the patches.
   */
  inline std::unique_ptr<ecitygml::DirectPositionIterator> points() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
   */
  inline std::unique_ptr<ecitygml::Envelope> compute_envelope() const;

    inline const ecitygml::capi::Surface* AsFFI() const;
    inline ecitygml::capi::Surface* AsFFI();
    inline static const ecitygml::Surface* FromFFI(const ecitygml::capi::Surface* ptr);
    inline static ecitygml::Surface* FromFFI(ecitygml::capi::Surface* ptr);
    inline static void operator delete(void* ptr);
private:
    Surface() = delete;
    Surface(const ecitygml::Surface&) = delete;
    Surface(ecitygml::Surface&&) noexcept = delete;
    Surface operator=(const ecitygml::Surface&) = delete;
    Surface operator=(ecitygml::Surface&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_Surface_D_HPP
