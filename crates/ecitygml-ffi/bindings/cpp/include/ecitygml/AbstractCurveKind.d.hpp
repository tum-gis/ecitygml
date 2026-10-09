#ifndef ecitygml_AbstractCurveKind_D_HPP
#define ecitygml_AbstractCurveKind_D_HPP

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
namespace capi { struct AbstractCurveKind; }
class AbstractCurveKind;
namespace capi { struct AbstractGeometryKind; }
class AbstractGeometryKind;
namespace capi { struct CodeIterator; }
class CodeIterator;
namespace capi { struct Envelope; }
class Envelope;
namespace capi { struct Id; }
class Id;
class GeometryType;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct AbstractCurveKind;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A curve of any type, borrowed from a city model; convert it with e.g. `LineString::try_from`.
 * Rings: `AbstractRingKind::try_from`.
 */
class AbstractCurveKind {
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
   * The geometry as an `AbstractCurveKind`, or none if it is another type (Rust: nested
   * `AbstractGeometryKind` variants).
   */
  inline static const ecitygml::AbstractCurveKind* try_from(const ecitygml::AbstractGeometryKind& geometry DIPLOMAT_LIFETIME_BOUND);

  inline ecitygml::GeometryType geometry_type() const;

  inline double length_3d() const;

  /**
   * Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
   */
  inline std::unique_ptr<ecitygml::Envelope> compute_envelope() const;

    inline const ecitygml::capi::AbstractCurveKind* AsFFI() const;
    inline ecitygml::capi::AbstractCurveKind* AsFFI();
    inline static const ecitygml::AbstractCurveKind* FromFFI(const ecitygml::capi::AbstractCurveKind* ptr);
    inline static ecitygml::AbstractCurveKind* FromFFI(ecitygml::capi::AbstractCurveKind* ptr);
    inline static void operator delete(void* ptr);
private:
    AbstractCurveKind() = delete;
    AbstractCurveKind(const ecitygml::AbstractCurveKind&) = delete;
    AbstractCurveKind(ecitygml::AbstractCurveKind&&) noexcept = delete;
    AbstractCurveKind operator=(const ecitygml::AbstractCurveKind&) = delete;
    AbstractCurveKind operator=(ecitygml::AbstractCurveKind&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_AbstractCurveKind_D_HPP
