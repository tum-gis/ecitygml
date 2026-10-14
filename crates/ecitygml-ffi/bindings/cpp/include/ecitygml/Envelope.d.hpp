#ifndef ecitygml_Envelope_D_HPP
#define ecitygml_Envelope_D_HPP

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
namespace capi { struct DirectPosition; }
class DirectPosition;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct Envelope;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * An axis-aligned bounding box, borrowed from a city model.
 */
class Envelope {
public:

  inline const ecitygml::DirectPosition& lower_corner() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::DirectPosition& upper_corner() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * The center of the envelope (Rust: `Envelope::center`).
   */
  inline std::unique_ptr<ecitygml::DirectPosition> center() const;

  /**
   * Extent along the x axis.
   */
  inline double size_x() const;

  /**
   * Extent along the y axis.
   */
  inline double size_y() const;

  /**
   * Extent along the z axis.
   */
  inline double size_z() const;

  /**
   * Volume of the box (`size_x * size_y * size_z`); `0.0` if an extent is zero.
   */
  inline double volume() const;

  /**
   * Whether `point` lies inside or on the boundary of the box.
   */
  inline bool contains(const ecitygml::DirectPosition& point) const;

    inline const ecitygml::capi::Envelope* AsFFI() const;
    inline ecitygml::capi::Envelope* AsFFI();
    inline static const ecitygml::Envelope* FromFFI(const ecitygml::capi::Envelope* ptr);
    inline static ecitygml::Envelope* FromFFI(ecitygml::capi::Envelope* ptr);
    inline static void operator delete(void* ptr);
private:
    Envelope() = delete;
    Envelope(const ecitygml::Envelope&) = delete;
    Envelope(ecitygml::Envelope&&) noexcept = delete;
    Envelope operator=(const ecitygml::Envelope&) = delete;
    Envelope operator=(ecitygml::Envelope&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_Envelope_D_HPP
