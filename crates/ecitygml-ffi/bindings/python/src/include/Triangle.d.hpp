#ifndef ECITYGML_Triangle_D_HPP
#define ECITYGML_Triangle_D_HPP

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
namespace capi { struct AbstractSurfacePatchKind; }
class AbstractSurfacePatchKind;
namespace capi { struct DirectPosition; }
class DirectPosition;
namespace capi { struct DirectPositionIterator; }
class DirectPositionIterator;
namespace capi { struct Envelope; }
class Envelope;
namespace capi { struct Error; }
class Error;
namespace capi { struct Triangle; }
class Triangle;
namespace capi { struct Triangulation; }
class Triangulation;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct Triangle;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A triangle, borrowed from a city model.
 */
class Triangle {
public:

  /**
   * Triangulates the geometry (Rust: `Triangulate::triangulate`). Members that fail to
   * triangulate are listed in `Triangulation::skipped`; as in egml, members that are only an
   * `xlink:href` are left out without such an entry.
   */
  inline ecitygml::diplomat::result<std::unique_ptr<ecitygml::Triangulation>, std::unique_ptr<ecitygml::Error>> triangulate() const;

  /**
   * The patch as a triangle, or none if it is another type (Rust: `Triangle::try_from`, which
   * takes the patch by value).
   */
  inline static const ecitygml::Triangle* try_from(const ecitygml::AbstractSurfacePatchKind& patch DIPLOMAT_LIFETIME_BOUND);

  inline const ecitygml::AbstractRingKind& exterior() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::DirectPosition& a() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::DirectPosition& b() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::DirectPosition& c() const DIPLOMAT_LIFETIME_BOUND;

  inline double area() const;

  /**
   * The three corners.
   */
  inline std::unique_ptr<ecitygml::DirectPositionIterator> points() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
   */
  inline std::unique_ptr<ecitygml::Envelope> compute_envelope() const;

    inline const ecitygml::capi::Triangle* AsFFI() const;
    inline ecitygml::capi::Triangle* AsFFI();
    inline static const ecitygml::Triangle* FromFFI(const ecitygml::capi::Triangle* ptr);
    inline static ecitygml::Triangle* FromFFI(ecitygml::capi::Triangle* ptr);
    inline static void operator delete(void* ptr);
private:
    Triangle() = delete;
    Triangle(const ecitygml::Triangle&) = delete;
    Triangle(ecitygml::Triangle&&) noexcept = delete;
    Triangle operator=(const ecitygml::Triangle&) = delete;
    Triangle operator=(ecitygml::Triangle&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_Triangle_D_HPP
