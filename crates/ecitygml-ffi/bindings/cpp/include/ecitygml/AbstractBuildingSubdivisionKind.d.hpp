#ifndef ecitygml_AbstractBuildingSubdivisionKind_D_HPP
#define ecitygml_AbstractBuildingSubdivisionKind_D_HPP

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
namespace capi { struct AbstractSpaceBoundaryPropertyIterator; }
class AbstractSpaceBoundaryPropertyIterator;
namespace capi { struct BoundingShape; }
class BoundingShape;
namespace capi { struct BuildingSubdivisionClassValue; }
class BuildingSubdivisionClassValue;
namespace capi { struct BuildingSubdivisionFunctionValueIterator; }
class BuildingSubdivisionFunctionValueIterator;
namespace capi { struct BuildingSubdivisionUsageValueIterator; }
class BuildingSubdivisionUsageValueIterator;
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
namespace capi { struct PointProperty; }
class PointProperty;
namespace capi { struct SolidProperty; }
class SolidProperty;
class FeatureType;
class RelativeToTerrain;
class RelativeToWater;
class SpaceType;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct AbstractBuildingSubdivisionKind;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A building subdivision (storey or building unit), borrowed from a city model. It has the
 * getters of every ancestor, like the concrete types, which add none; `feature_type()` tells
 * which one it is.
 */
class AbstractBuildingSubdivisionKind {
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

  inline const ecitygml::BuildingSubdivisionClassValue* class_() const DIPLOMAT_LIFETIME_BOUND;

  inline std::unique_ptr<ecitygml::BuildingSubdivisionFunctionValueIterator> functions() const DIPLOMAT_LIFETIME_BOUND;

  inline std::unique_ptr<ecitygml::BuildingSubdivisionUsageValueIterator> usages() const DIPLOMAT_LIFETIME_BOUND;

  inline ecitygml::FeatureType feature_type() const;

    inline const ecitygml::capi::AbstractBuildingSubdivisionKind* AsFFI() const;
    inline ecitygml::capi::AbstractBuildingSubdivisionKind* AsFFI();
    inline static const ecitygml::AbstractBuildingSubdivisionKind* FromFFI(const ecitygml::capi::AbstractBuildingSubdivisionKind* ptr);
    inline static ecitygml::AbstractBuildingSubdivisionKind* FromFFI(ecitygml::capi::AbstractBuildingSubdivisionKind* ptr);
    inline static void operator delete(void* ptr);
private:
    AbstractBuildingSubdivisionKind() = delete;
    AbstractBuildingSubdivisionKind(const ecitygml::AbstractBuildingSubdivisionKind&) = delete;
    AbstractBuildingSubdivisionKind(ecitygml::AbstractBuildingSubdivisionKind&&) noexcept = delete;
    AbstractBuildingSubdivisionKind operator=(const ecitygml::AbstractBuildingSubdivisionKind&) = delete;
    AbstractBuildingSubdivisionKind operator=(ecitygml::AbstractBuildingSubdivisionKind&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_AbstractBuildingSubdivisionKind_D_HPP
