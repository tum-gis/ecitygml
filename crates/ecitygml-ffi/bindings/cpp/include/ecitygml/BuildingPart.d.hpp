#ifndef ecitygml_BuildingPart_D_HPP
#define ecitygml_BuildingPart_D_HPP

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
namespace capi { struct AbstractBuildingSubdivisionPropertyIterator; }
class AbstractBuildingSubdivisionPropertyIterator;
namespace capi { struct AbstractFeatureKindRef; }
class AbstractFeatureKindRef;
namespace capi { struct AbstractSpaceBoundaryPropertyIterator; }
class AbstractSpaceBoundaryPropertyIterator;
namespace capi { struct BoundingShape; }
class BoundingShape;
namespace capi { struct BuildingClassValue; }
class BuildingClassValue;
namespace capi { struct BuildingFunctionValueIterator; }
class BuildingFunctionValueIterator;
namespace capi { struct BuildingPart; }
class BuildingPart;
namespace capi { struct BuildingUsageValueIterator; }
class BuildingUsageValueIterator;
namespace capi { struct CityObjectRelationPropertyIterator; }
class CityObjectRelationPropertyIterator;
namespace capi { struct CodeIterator; }
class CodeIterator;
namespace capi { struct Date; }
class Date;
namespace capi { struct DateTime; }
class DateTime;
namespace capi { struct ExternalReferenceIterator; }
class ExternalReferenceIterator;
namespace capi { struct GenericAttributeKindIterator; }
class GenericAttributeKindIterator;
namespace capi { struct HeightIterator; }
class HeightIterator;
namespace capi { struct Id; }
class Id;
namespace capi { struct ImplicitGeometryProperty; }
class ImplicitGeometryProperty;
namespace capi { struct MultiCurveProperty; }
class MultiCurveProperty;
namespace capi { struct MultiSurfaceProperty; }
class MultiSurfaceProperty;
namespace capi { struct OccupancyIterator; }
class OccupancyIterator;
namespace capi { struct PointProperty; }
class PointProperty;
namespace capi { struct RoofTypeValue; }
class RoofTypeValue;
namespace capi { struct SolidProperty; }
class SolidProperty;
class RelativeToTerrain;
class RelativeToWater;
class SpaceType;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct BuildingPart;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A building part, borrowed from a city model.
 */
class BuildingPart {
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

  inline const ecitygml::ImplicitGeometryProperty* lod1_implicit_representation() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::ImplicitGeometryProperty* lod2_implicit_representation() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::ImplicitGeometryProperty* lod3_implicit_representation() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::Date* date_of_construction() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::Date* date_of_demolition() const DIPLOMAT_LIFETIME_BOUND;

  inline std::unique_ptr<ecitygml::HeightIterator> heights() const DIPLOMAT_LIFETIME_BOUND;

  inline std::unique_ptr<ecitygml::OccupancyIterator> occupancies() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::BuildingClassValue* class_() const DIPLOMAT_LIFETIME_BOUND;

  inline std::unique_ptr<ecitygml::BuildingFunctionValueIterator> functions() const DIPLOMAT_LIFETIME_BOUND;

  inline std::unique_ptr<ecitygml::BuildingUsageValueIterator> usages() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::RoofTypeValue* roof_type() const DIPLOMAT_LIFETIME_BOUND;

  inline std::optional<int64_t> storeys_above_ground() const;

  inline std::optional<int64_t> storeys_below_ground() const;

  /**
   * The storeys and building units (`buildingSubdivision`).
   */
  inline std::unique_ptr<ecitygml::AbstractBuildingSubdivisionPropertyIterator> building_subdivisions() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * The feature as a building part, or none if it is another type (Rust: `<&BuildingPart>::try_from`).
   */
  inline static const ecitygml::BuildingPart* try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND);

    inline const ecitygml::capi::BuildingPart* AsFFI() const;
    inline ecitygml::capi::BuildingPart* AsFFI();
    inline static const ecitygml::BuildingPart* FromFFI(const ecitygml::capi::BuildingPart* ptr);
    inline static ecitygml::BuildingPart* FromFFI(ecitygml::capi::BuildingPart* ptr);
    inline static void operator delete(void* ptr);
private:
    BuildingPart() = delete;
    BuildingPart(const ecitygml::BuildingPart&) = delete;
    BuildingPart(ecitygml::BuildingPart&&) noexcept = delete;
    BuildingPart operator=(const ecitygml::BuildingPart&) = delete;
    BuildingPart operator=(ecitygml::BuildingPart&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_BuildingPart_D_HPP
