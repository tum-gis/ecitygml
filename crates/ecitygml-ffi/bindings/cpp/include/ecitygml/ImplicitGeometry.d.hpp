#ifndef ecitygml_ImplicitGeometry_D_HPP
#define ecitygml_ImplicitGeometry_D_HPP

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
namespace capi { struct AbstractGeometryProperty; }
class AbstractGeometryProperty;
namespace capi { struct Envelope; }
class Envelope;
namespace capi { struct Id; }
class Id;
namespace capi { struct MimeTypeValue; }
class MimeTypeValue;
namespace capi { struct PointProperty; }
class PointProperty;
namespace capi { struct TransformationMatrix4x4; }
class TransformationMatrix4x4;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct ImplicitGeometry;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A prototype geometry placed by a transformation and a reference point, borrowed from a city
 * model. Not bound yet: appearances.
 */
class ImplicitGeometry {
public:

  /**
   * Identifies the implicit geometry (from its `gml:id`).
   */
  inline const ecitygml::Id& object_id() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::TransformationMatrix4x4& transformation_matrix() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::MimeTypeValue* mime_type() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * Reference to the prototype in an external library.
   */
  inline std::optional<std::string_view> library_object() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::PointProperty& reference_point() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * The prototype geometry, in its own coordinate system.
   */
  inline const ecitygml::AbstractGeometryProperty* relative_geometry() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
   */
  inline std::unique_ptr<ecitygml::Envelope> compute_envelope() const;

    inline const ecitygml::capi::ImplicitGeometry* AsFFI() const;
    inline ecitygml::capi::ImplicitGeometry* AsFFI();
    inline static const ecitygml::ImplicitGeometry* FromFFI(const ecitygml::capi::ImplicitGeometry* ptr);
    inline static ecitygml::ImplicitGeometry* FromFFI(ecitygml::capi::ImplicitGeometry* ptr);
    inline static void operator delete(void* ptr);
private:
    ImplicitGeometry() = delete;
    ImplicitGeometry(const ecitygml::ImplicitGeometry&) = delete;
    ImplicitGeometry(ecitygml::ImplicitGeometry&&) noexcept = delete;
    ImplicitGeometry operator=(const ecitygml::ImplicitGeometry&) = delete;
    ImplicitGeometry operator=(ecitygml::ImplicitGeometry&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_ImplicitGeometry_D_HPP
