#ifndef ecitygml_AbstractFillingSurfaceKind_D_HPP
#define ecitygml_AbstractFillingSurfaceKind_D_HPP

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
class FeatureType;
class RelativeToTerrain;
class RelativeToWater;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct AbstractFillingSurfaceKind;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A filling surface (door or window surface), borrowed from a city model. It has the getters of
 * every ancestor, like the concrete types; `feature_type()` tells which one it is.
 */
class AbstractFillingSurfaceKind {
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

  inline ecitygml::FeatureType feature_type() const;

    inline const ecitygml::capi::AbstractFillingSurfaceKind* AsFFI() const;
    inline ecitygml::capi::AbstractFillingSurfaceKind* AsFFI();
    inline static const ecitygml::AbstractFillingSurfaceKind* FromFFI(const ecitygml::capi::AbstractFillingSurfaceKind* ptr);
    inline static ecitygml::AbstractFillingSurfaceKind* FromFFI(ecitygml::capi::AbstractFillingSurfaceKind* ptr);
    inline static void operator delete(void* ptr);
private:
    AbstractFillingSurfaceKind() = delete;
    AbstractFillingSurfaceKind(const ecitygml::AbstractFillingSurfaceKind&) = delete;
    AbstractFillingSurfaceKind(ecitygml::AbstractFillingSurfaceKind&&) noexcept = delete;
    AbstractFillingSurfaceKind operator=(const ecitygml::AbstractFillingSurfaceKind&) = delete;
    AbstractFillingSurfaceKind operator=(ecitygml::AbstractFillingSurfaceKind&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_AbstractFillingSurfaceKind_D_HPP
