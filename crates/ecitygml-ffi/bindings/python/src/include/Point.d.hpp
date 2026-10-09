#ifndef ECITYGML_Point_D_HPP
#define ECITYGML_Point_D_HPP

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
namespace capi { struct AbstractGeometryKind; }
class AbstractGeometryKind;
namespace capi { struct CodeIterator; }
class CodeIterator;
namespace capi { struct DirectPosition; }
class DirectPosition;
namespace capi { struct Envelope; }
class Envelope;
namespace capi { struct Id; }
class Id;
namespace capi { struct Point; }
class Point;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct Point;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A point, borrowed from a city model.
 */
class Point {
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
   * The geometry as a `Point`, or none if it is another type (Rust: nested
   * `AbstractGeometryKind` variants).
   */
  inline static const ecitygml::Point* try_from(const ecitygml::AbstractGeometryKind& geometry DIPLOMAT_LIFETIME_BOUND);

  /**
   * The position (`gml:pos`).
   */
  inline const ecitygml::DirectPosition& pos() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
   */
  inline std::unique_ptr<ecitygml::Envelope> compute_envelope() const;

    inline const ecitygml::capi::Point* AsFFI() const;
    inline ecitygml::capi::Point* AsFFI();
    inline static const ecitygml::Point* FromFFI(const ecitygml::capi::Point* ptr);
    inline static ecitygml::Point* FromFFI(ecitygml::capi::Point* ptr);
    inline static void operator delete(void* ptr);
private:
    Point() = delete;
    Point(const ecitygml::Point&) = delete;
    Point(ecitygml::Point&&) noexcept = delete;
    Point operator=(const ecitygml::Point&) = delete;
    Point operator=(ecitygml::Point&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_Point_D_HPP
