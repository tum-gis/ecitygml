#ifndef ECITYGML_AuxiliaryTrafficArea_D_HPP
#define ECITYGML_AuxiliaryTrafficArea_D_HPP

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
namespace capi { struct AuxiliaryTrafficArea; }
class AuxiliaryTrafficArea;
namespace capi { struct AuxiliaryTrafficAreaClassValue; }
class AuxiliaryTrafficAreaClassValue;
namespace capi { struct AuxiliaryTrafficAreaFunctionValueIterator; }
class AuxiliaryTrafficAreaFunctionValueIterator;
namespace capi { struct AuxiliaryTrafficAreaUsageValueIterator; }
class AuxiliaryTrafficAreaUsageValueIterator;
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
namespace capi { struct SurfaceMaterialValue; }
class SurfaceMaterialValue;
class RelativeToTerrain;
class RelativeToWater;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct AuxiliaryTrafficArea;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * An auxiliary traffic area, borrowed from a city model.
 */
class AuxiliaryTrafficArea {
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
   * The feature as an auxiliary traffic area, or none if it is another type (Rust: `<&AuxiliaryTrafficArea>::try_from`).
   */
  inline static const ecitygml::AuxiliaryTrafficArea* try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND);

  inline const ecitygml::AuxiliaryTrafficAreaClassValue* class_() const DIPLOMAT_LIFETIME_BOUND;

  inline std::unique_ptr<ecitygml::AuxiliaryTrafficAreaFunctionValueIterator> functions() const DIPLOMAT_LIFETIME_BOUND;

  inline std::unique_ptr<ecitygml::AuxiliaryTrafficAreaUsageValueIterator> usages() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::SurfaceMaterialValue* surface_material() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AuxiliaryTrafficArea* AsFFI() const;
    inline ecitygml::capi::AuxiliaryTrafficArea* AsFFI();
    inline static const ecitygml::AuxiliaryTrafficArea* FromFFI(const ecitygml::capi::AuxiliaryTrafficArea* ptr);
    inline static ecitygml::AuxiliaryTrafficArea* FromFFI(ecitygml::capi::AuxiliaryTrafficArea* ptr);
    inline static void operator delete(void* ptr);
private:
    AuxiliaryTrafficArea() = delete;
    AuxiliaryTrafficArea(const ecitygml::AuxiliaryTrafficArea&) = delete;
    AuxiliaryTrafficArea(ecitygml::AuxiliaryTrafficArea&&) noexcept = delete;
    AuxiliaryTrafficArea operator=(const ecitygml::AuxiliaryTrafficArea&) = delete;
    AuxiliaryTrafficArea operator=(ecitygml::AuxiliaryTrafficArea&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_AuxiliaryTrafficArea_D_HPP
