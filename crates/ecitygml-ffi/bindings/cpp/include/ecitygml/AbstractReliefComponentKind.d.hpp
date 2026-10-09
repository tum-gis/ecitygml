#ifndef ecitygml_AbstractReliefComponentKind_D_HPP
#define ecitygml_AbstractReliefComponentKind_D_HPP

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
class FeatureType;
class LevelOfDetail;
class RelativeToTerrain;
class RelativeToWater;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct AbstractReliefComponentKind;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A relief component (a TIN relief), borrowed from a city model. It has the getters of every
 * ancestor; `feature_type()` tells which component it is. Not bound yet: the concrete types'
 * own getters (e.g. `tin`); get a `TinRelief` from the features with `TinRelief::try_from`.
 */
class AbstractReliefComponentKind {
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

  inline ecitygml::LevelOfDetail lod() const;

  inline ecitygml::FeatureType feature_type() const;

    inline const ecitygml::capi::AbstractReliefComponentKind* AsFFI() const;
    inline ecitygml::capi::AbstractReliefComponentKind* AsFFI();
    inline static const ecitygml::AbstractReliefComponentKind* FromFFI(const ecitygml::capi::AbstractReliefComponentKind* ptr);
    inline static ecitygml::AbstractReliefComponentKind* FromFFI(ecitygml::capi::AbstractReliefComponentKind* ptr);
    inline static void operator delete(void* ptr);
private:
    AbstractReliefComponentKind() = delete;
    AbstractReliefComponentKind(const ecitygml::AbstractReliefComponentKind&) = delete;
    AbstractReliefComponentKind(ecitygml::AbstractReliefComponentKind&&) noexcept = delete;
    AbstractReliefComponentKind operator=(const ecitygml::AbstractReliefComponentKind&) = delete;
    AbstractReliefComponentKind operator=(ecitygml::AbstractReliefComponentKind&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_AbstractReliefComponentKind_D_HPP
