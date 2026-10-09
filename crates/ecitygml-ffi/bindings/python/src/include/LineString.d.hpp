#ifndef ECITYGML_LineString_D_HPP
#define ECITYGML_LineString_D_HPP

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
namespace capi { struct CodeIterator; }
class CodeIterator;
namespace capi { struct DirectPositionIterator; }
class DirectPositionIterator;
namespace capi { struct Envelope; }
class Envelope;
namespace capi { struct Id; }
class Id;
namespace capi { struct LineString; }
class LineString;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct LineString;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A line string, borrowed from a city model.
 */
class LineString {
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
   * The curve as a line string, or none if it is another type (Rust: `LineString::try_from`,
   * which takes the curve by value).
   */
  inline static const ecitygml::LineString* try_from(const ecitygml::AbstractCurveKind& curve DIPLOMAT_LIFETIME_BOUND);

  /**
   * The positions (`gml:posList`).
   */
  inline std::unique_ptr<ecitygml::DirectPositionIterator> points() const DIPLOMAT_LIFETIME_BOUND;

  inline double length_3d() const;

  /**
   * Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
   */
  inline std::unique_ptr<ecitygml::Envelope> compute_envelope() const;

    inline const ecitygml::capi::LineString* AsFFI() const;
    inline ecitygml::capi::LineString* AsFFI();
    inline static const ecitygml::LineString* FromFFI(const ecitygml::capi::LineString* ptr);
    inline static ecitygml::LineString* FromFFI(ecitygml::capi::LineString* ptr);
    inline static void operator delete(void* ptr);
private:
    LineString() = delete;
    LineString(const ecitygml::LineString&) = delete;
    LineString(ecitygml::LineString&&) noexcept = delete;
    LineString operator=(const ecitygml::LineString&) = delete;
    LineString operator=(ecitygml::LineString&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_LineString_D_HPP
