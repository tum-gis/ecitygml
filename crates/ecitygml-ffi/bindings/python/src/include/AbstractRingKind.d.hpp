#ifndef ECITYGML_AbstractRingKind_D_HPP
#define ECITYGML_AbstractRingKind_D_HPP

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
namespace capi { struct AbstractCurveKind; }
class AbstractCurveKind;
namespace capi { struct AbstractRingKind; }
class AbstractRingKind;
namespace capi { struct CodeIterator; }
class CodeIterator;
namespace capi { struct DirectPositionIterator; }
class DirectPositionIterator;
namespace capi { struct Envelope; }
class Envelope;
namespace capi { struct Id; }
class Id;
class GeometryType;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct AbstractRingKind;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A ring of any type, borrowed from a city model; convert it with `LinearRing::try_from`.
 */
class AbstractRingKind {
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
   * The curve as a ring, or none if it is another type (Rust: `AbstractRingKind::try_from`,
   * which takes the curve by value).
   */
  inline static const ecitygml::AbstractRingKind* try_from(const ecitygml::AbstractCurveKind& curve DIPLOMAT_LIFETIME_BOUND);

  inline ecitygml::GeometryType geometry_type() const;

  /**
   * The positions, without the repeated closing position.
   */
  inline std::unique_ptr<ecitygml::DirectPositionIterator> points() const DIPLOMAT_LIFETIME_BOUND;

  inline double length_3d() const;

  inline double area_3d() const;

  /**
   * Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
   */
  inline std::unique_ptr<ecitygml::Envelope> compute_envelope() const;

    inline const ecitygml::capi::AbstractRingKind* AsFFI() const;
    inline ecitygml::capi::AbstractRingKind* AsFFI();
    inline static const ecitygml::AbstractRingKind* FromFFI(const ecitygml::capi::AbstractRingKind* ptr);
    inline static ecitygml::AbstractRingKind* FromFFI(ecitygml::capi::AbstractRingKind* ptr);
    inline static void operator delete(void* ptr);
private:
    AbstractRingKind() = delete;
    AbstractRingKind(const ecitygml::AbstractRingKind&) = delete;
    AbstractRingKind(ecitygml::AbstractRingKind&&) noexcept = delete;
    AbstractRingKind operator=(const ecitygml::AbstractRingKind&) = delete;
    AbstractRingKind operator=(ecitygml::AbstractRingKind&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_AbstractRingKind_D_HPP
