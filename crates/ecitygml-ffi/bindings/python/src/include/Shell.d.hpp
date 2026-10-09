#ifndef ECITYGML_Shell_D_HPP
#define ECITYGML_Shell_D_HPP

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
namespace capi { struct AbstractSurfacePropertyIterator; }
class AbstractSurfacePropertyIterator;
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
namespace capi { struct Triangulation; }
class Triangulation;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct Shell;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A shell (closed surface), borrowed from a city model.
 */
class Shell {
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
   * The surface as a shell, or none if it is another type (Rust: `Shell::try_from`, which
   * takes the surface by value).
   */
  inline static const ecitygml::Shell* try_from(const ecitygml::AbstractSurfaceKind& surface DIPLOMAT_LIFETIME_BOUND);

  /**
   * The surface members (`gml:surfaceMember`).
   */
  inline std::unique_ptr<ecitygml::AbstractSurfacePropertyIterator> members() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * All positions of the inline members.
   */
  inline std::unique_ptr<ecitygml::DirectPositionIterator> points() const DIPLOMAT_LIFETIME_BOUND;

  inline ecitygml::diplomat::result<double, std::unique_ptr<ecitygml::Error>> area_3d() const;

  /**
   * Enclosed volume; fails with `UnresolvedReference` if a member is only an `xlink:href`.
   */
  inline ecitygml::diplomat::result<double, std::unique_ptr<ecitygml::Error>> volume_3d() const;

  /**
   * Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
   */
  inline std::unique_ptr<ecitygml::Envelope> compute_envelope() const;

    inline const ecitygml::capi::Shell* AsFFI() const;
    inline ecitygml::capi::Shell* AsFFI();
    inline static const ecitygml::Shell* FromFFI(const ecitygml::capi::Shell* ptr);
    inline static ecitygml::Shell* FromFFI(ecitygml::capi::Shell* ptr);
    inline static void operator delete(void* ptr);
private:
    Shell() = delete;
    Shell(const ecitygml::Shell&) = delete;
    Shell(ecitygml::Shell&&) noexcept = delete;
    Shell operator=(const ecitygml::Shell&) = delete;
    Shell operator=(ecitygml::Shell&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_Shell_D_HPP
