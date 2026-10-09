#ifndef ecitygml_ReliefFeature_D_HPP
#define ecitygml_ReliefFeature_D_HPP

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
namespace capi { struct AbstractReliefComponentPropertyIterator; }
class AbstractReliefComponentPropertyIterator;
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
namespace capi { struct ReliefFeature; }
class ReliefFeature;
class LevelOfDetail;
class RelativeToTerrain;
class RelativeToWater;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct ReliefFeature;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A relief (terrain) feature made of relief components, borrowed from a city model.
 */
class ReliefFeature {
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

  /**
   * The feature as a relief feature, or none if it is another type (Rust: `<&ReliefFeature>::try_from`).
   */
  inline static const ecitygml::ReliefFeature* try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND);

  inline ecitygml::LevelOfDetail lod() const;

  inline std::unique_ptr<ecitygml::AbstractReliefComponentPropertyIterator> relief_components() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::ReliefFeature* AsFFI() const;
    inline ecitygml::capi::ReliefFeature* AsFFI();
    inline static const ecitygml::ReliefFeature* FromFFI(const ecitygml::capi::ReliefFeature* ptr);
    inline static ecitygml::ReliefFeature* FromFFI(ecitygml::capi::ReliefFeature* ptr);
    inline static void operator delete(void* ptr);
private:
    ReliefFeature() = delete;
    ReliefFeature(const ecitygml::ReliefFeature&) = delete;
    ReliefFeature(ecitygml::ReliefFeature&&) noexcept = delete;
    ReliefFeature operator=(const ecitygml::ReliefFeature&) = delete;
    ReliefFeature operator=(ecitygml::ReliefFeature&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_ReliefFeature_D_HPP
