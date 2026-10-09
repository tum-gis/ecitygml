#ifndef ecitygml_LinearRing_D_HPP
#define ecitygml_LinearRing_D_HPP

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
namespace capi { struct LinearRing; }
class LinearRing;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct LinearRing;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A linear ring, borrowed from a city model.
 */
class LinearRing {
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
   * The ring as a linear ring, or none if it is another type (Rust: `LinearRing::try_from`,
   * which takes the ring by value). Follows nested rings (`AbstractRingKind::AbstractRingKind`).
   */
  inline static const ecitygml::LinearRing* try_from(const ecitygml::AbstractRingKind& ring DIPLOMAT_LIFETIME_BOUND);

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

    inline const ecitygml::capi::LinearRing* AsFFI() const;
    inline ecitygml::capi::LinearRing* AsFFI();
    inline static const ecitygml::LinearRing* FromFFI(const ecitygml::capi::LinearRing* ptr);
    inline static ecitygml::LinearRing* FromFFI(ecitygml::capi::LinearRing* ptr);
    inline static void operator delete(void* ptr);
private:
    LinearRing() = delete;
    LinearRing(const ecitygml::LinearRing&) = delete;
    LinearRing(ecitygml::LinearRing&&) noexcept = delete;
    LinearRing operator=(const ecitygml::LinearRing&) = delete;
    LinearRing operator=(ecitygml::LinearRing&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_LinearRing_D_HPP
