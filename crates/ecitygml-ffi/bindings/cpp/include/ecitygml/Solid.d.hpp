#ifndef ecitygml_Solid_D_HPP
#define ecitygml_Solid_D_HPP

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
namespace capi { struct AbstractGeometryKind; }
class AbstractGeometryKind;
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
namespace capi { struct Shell; }
class Shell;
namespace capi { struct ShellIterator; }
class ShellIterator;
namespace capi { struct Solid; }
class Solid;
namespace capi { struct Triangulation; }
class Triangulation;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct Solid;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A solid, borrowed from a city model.
 */
class Solid {
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
   * The geometry as a `Solid`, or none if it is another type (Rust: nested
   * `AbstractGeometryKind` variants).
   */
  inline static const ecitygml::Solid* try_from(const ecitygml::AbstractGeometryKind& geometry DIPLOMAT_LIFETIME_BOUND);

  inline const ecitygml::Shell* exterior() const DIPLOMAT_LIFETIME_BOUND;

  inline std::unique_ptr<ecitygml::ShellIterator> interior() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * Volume of the exterior shell. Stricter than Rust, which skips shell members it can't
   * triangulate (and panics on some): fails with `UnresolvedReference` if a member is only an
   * `xlink:href`, and with `InvalidArgument` if a member can't be triangulated, so the volume is
   * never computed from an incomplete shell.
   */
  inline diplomat::result<double, std::unique_ptr<ecitygml::Error>> volume_3d() const;

  /**
   * Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
   */
  inline std::unique_ptr<ecitygml::Envelope> compute_envelope() const;

  /**
   * All positions of the exterior shell.
   */
  inline std::unique_ptr<ecitygml::DirectPositionIterator> points() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::Solid* AsFFI() const;
    inline ecitygml::capi::Solid* AsFFI();
    inline static const ecitygml::Solid* FromFFI(const ecitygml::capi::Solid* ptr);
    inline static ecitygml::Solid* FromFFI(ecitygml::capi::Solid* ptr);
    inline static void operator delete(void* ptr);
private:
    Solid() = delete;
    Solid(const ecitygml::Solid&) = delete;
    Solid(ecitygml::Solid&&) noexcept = delete;
    Solid operator=(const ecitygml::Solid&) = delete;
    Solid operator=(ecitygml::Solid&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_Solid_D_HPP
