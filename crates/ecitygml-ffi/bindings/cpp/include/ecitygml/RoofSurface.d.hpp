#ifndef ecitygml_RoofSurface_D_HPP
#define ecitygml_RoofSurface_D_HPP

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
namespace capi { struct AbstractFeatureKindRef; }
class AbstractFeatureKindRef;
namespace capi { struct AbstractFillingSurfacePropertyIterator; }
class AbstractFillingSurfacePropertyIterator;
namespace capi { struct BoundingShape; }
class BoundingShape;
namespace capi { struct CityObjectRelationPropertyIterator; }
class CityObjectRelationPropertyIterator;
namespace capi { struct CodeIterator; }
class CodeIterator;
namespace capi { struct DateTime; }
class DateTime;
namespace capi { struct ExternalReferenceIterator; }
class ExternalReferenceIterator;
namespace capi { struct GenericAttributeKindIterator; }
class GenericAttributeKindIterator;
namespace capi { struct Id; }
class Id;
namespace capi { struct MultiCurveProperty; }
class MultiCurveProperty;
namespace capi { struct MultiSurfaceProperty; }
class MultiSurfaceProperty;
namespace capi { struct RoofSurface; }
class RoofSurface;
class RelativeToTerrain;
class RelativeToWater;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct RoofSurface;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A roof surface, borrowed from a city model. It has no properties of its own in CityGML 3.0.
 */
class RoofSurface {
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
   * The feature's bounding shape (`gml:boundedBy`), if it has one.
   */
  inline const ecitygml::BoundingShape* bounded_by() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * The feature's `gml:id`.
   */
  inline const ecitygml::Id& feature_id() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::DateTime* creation_date() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::DateTime* termination_date() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::DateTime* valid_from() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::DateTime* valid_to() const DIPLOMAT_LIFETIME_BOUND;

  inline std::optional<ecitygml::RelativeToTerrain> relative_to_terrain() const;

  inline std::optional<ecitygml::RelativeToWater> relative_to_water() const;

  inline std::unique_ptr<ecitygml::ExternalReferenceIterator> external_references() const DIPLOMAT_LIFETIME_BOUND;

  inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> generic_attributes() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * Relations to other city objects (`relatedTo`).
   */
  inline std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator> related_to() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::MultiCurveProperty* lod0_multi_curve() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::MultiSurfaceProperty* lod0_multi_surface() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::MultiSurfaceProperty* lod1_multi_surface() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::MultiSurfaceProperty* lod2_multi_surface() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::MultiSurfaceProperty* lod3_multi_surface() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * The door and window surfaces in this surface (`con:fillingSurface`).
   */
  inline std::unique_ptr<ecitygml::AbstractFillingSurfacePropertyIterator> filling_surfaces() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * The feature as a roof surface, or none if it is another type (Rust: `<&RoofSurface>::try_from`).
   */
  inline static const ecitygml::RoofSurface* try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND);

    inline const ecitygml::capi::RoofSurface* AsFFI() const;
    inline ecitygml::capi::RoofSurface* AsFFI();
    inline static const ecitygml::RoofSurface* FromFFI(const ecitygml::capi::RoofSurface* ptr);
    inline static ecitygml::RoofSurface* FromFFI(ecitygml::capi::RoofSurface* ptr);
    inline static void operator delete(void* ptr);
private:
    RoofSurface() = delete;
    RoofSurface(const ecitygml::RoofSurface&) = delete;
    RoofSurface(ecitygml::RoofSurface&&) noexcept = delete;
    RoofSurface operator=(const ecitygml::RoofSurface&) = delete;
    RoofSurface operator=(ecitygml::RoofSurface&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_RoofSurface_D_HPP
