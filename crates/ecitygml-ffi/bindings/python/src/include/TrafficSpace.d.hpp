#ifndef ECITYGML_TrafficSpace_D_HPP
#define ECITYGML_TrafficSpace_D_HPP

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
namespace capi { struct AbstractFeatureKindRef; }
class AbstractFeatureKindRef;
namespace capi { struct AbstractSpaceBoundaryPropertyIterator; }
class AbstractSpaceBoundaryPropertyIterator;
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
namespace capi { struct OccupancyIterator; }
class OccupancyIterator;
namespace capi { struct PointProperty; }
class PointProperty;
namespace capi { struct SolidProperty; }
class SolidProperty;
namespace capi { struct TrafficSpace; }
class TrafficSpace;
namespace capi { struct TrafficSpaceClassValue; }
class TrafficSpaceClassValue;
namespace capi { struct TrafficSpaceFunctionValueIterator; }
class TrafficSpaceFunctionValueIterator;
namespace capi { struct TrafficSpaceUsageValueIterator; }
class TrafficSpaceUsageValueIterator;
class GranularityValue;
class RelativeToTerrain;
class RelativeToWater;
class SpaceType;
class TrafficDirectionValue;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct TrafficSpace;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A traffic space, borrowed from a city model.
 */
class TrafficSpace {
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

  inline std::optional<ecitygml::SpaceType> space_type() const;

  inline const ecitygml::SolidProperty* lod1_solid() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::SolidProperty* lod2_solid() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::SolidProperty* lod3_solid() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::MultiSurfaceProperty* lod0_multi_surface() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::MultiSurfaceProperty* lod2_multi_surface() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::MultiSurfaceProperty* lod3_multi_surface() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::MultiCurveProperty* lod0_multi_curve() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::MultiCurveProperty* lod2_multi_curve() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::MultiCurveProperty* lod3_multi_curve() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::PointProperty* lod0_point() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * The space's boundaries (e.g. wall surfaces or traffic areas).
   */
  inline std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator> boundaries() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::MultiCurveProperty* lod1_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::MultiCurveProperty* lod2_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::MultiCurveProperty* lod3_terrain_intersection_curve() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * The feature as a traffic space, or none if it is another type (Rust: `<&TrafficSpace>::try_from`).
   */
  inline static const ecitygml::TrafficSpace* try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND);

  inline const ecitygml::TrafficSpaceClassValue* class_() const DIPLOMAT_LIFETIME_BOUND;

  inline std::unique_ptr<ecitygml::TrafficSpaceFunctionValueIterator> functions() const DIPLOMAT_LIFETIME_BOUND;

  inline std::unique_ptr<ecitygml::TrafficSpaceUsageValueIterator> usages() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * Returned by value (Rust: `&GranularityValue`), as Diplomat enums are values.
   */
  inline ecitygml::GranularityValue granularity() const;

  inline std::optional<ecitygml::TrafficDirectionValue> traffic_direction() const;

  inline std::unique_ptr<ecitygml::OccupancyIterator> occupancies() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::TrafficSpace* AsFFI() const;
    inline ecitygml::capi::TrafficSpace* AsFFI();
    inline static const ecitygml::TrafficSpace* FromFFI(const ecitygml::capi::TrafficSpace* ptr);
    inline static ecitygml::TrafficSpace* FromFFI(ecitygml::capi::TrafficSpace* ptr);
    inline static void operator delete(void* ptr);
private:
    TrafficSpace() = delete;
    TrafficSpace(const ecitygml::TrafficSpace&) = delete;
    TrafficSpace(ecitygml::TrafficSpace&&) noexcept = delete;
    TrafficSpace operator=(const ecitygml::TrafficSpace&) = delete;
    TrafficSpace operator=(ecitygml::TrafficSpace&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_TrafficSpace_D_HPP
