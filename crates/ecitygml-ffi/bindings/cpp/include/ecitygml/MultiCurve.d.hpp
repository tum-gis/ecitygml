#ifndef ecitygml_MultiCurve_D_HPP
#define ecitygml_MultiCurve_D_HPP

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
namespace capi { struct AbstractCurvePropertyIterator; }
class AbstractCurvePropertyIterator;
namespace capi { struct AbstractGeometryKind; }
class AbstractGeometryKind;
namespace capi { struct CodeIterator; }
class CodeIterator;
namespace capi { struct Envelope; }
class Envelope;
namespace capi { struct Error; }
class Error;
namespace capi { struct Id; }
class Id;
namespace capi { struct MultiCurve; }
class MultiCurve;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct MultiCurve;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A multi curve, borrowed from a city model.
 */
class MultiCurve {
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
   * The geometry as a `MultiCurve`, or none if it is another type (Rust: nested
   * `AbstractGeometryKind` variants).
   */
  inline static const ecitygml::MultiCurve* try_from(const ecitygml::AbstractGeometryKind& geometry DIPLOMAT_LIFETIME_BOUND);

  /**
   * The curve members (`gml:curveMember`).
   */
  inline std::unique_ptr<ecitygml::AbstractCurvePropertyIterator> curve_member() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * Sum of the members' lengths; fails with `UnresolvedReference` if a member is only an
   * `xlink:href`.
   */
  inline diplomat::result<double, std::unique_ptr<ecitygml::Error>> length_3d() const;

  /**
   * Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
   */
  inline std::unique_ptr<ecitygml::Envelope> compute_envelope() const;

    inline const ecitygml::capi::MultiCurve* AsFFI() const;
    inline ecitygml::capi::MultiCurve* AsFFI();
    inline static const ecitygml::MultiCurve* FromFFI(const ecitygml::capi::MultiCurve* ptr);
    inline static ecitygml::MultiCurve* FromFFI(ecitygml::capi::MultiCurve* ptr);
    inline static void operator delete(void* ptr);
private:
    MultiCurve() = delete;
    MultiCurve(const ecitygml::MultiCurve&) = delete;
    MultiCurve(ecitygml::MultiCurve&&) noexcept = delete;
    MultiCurve operator=(const ecitygml::MultiCurve&) = delete;
    MultiCurve operator=(ecitygml::MultiCurve&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_MultiCurve_D_HPP
