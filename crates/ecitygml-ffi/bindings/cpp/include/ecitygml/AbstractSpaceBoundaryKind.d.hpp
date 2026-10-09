#ifndef ecitygml_AbstractSpaceBoundaryKind_D_HPP
#define ecitygml_AbstractSpaceBoundaryKind_D_HPP

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
class RelativeToTerrain;
class RelativeToWater;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct AbstractSpaceBoundaryKind;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A space boundary of any type (e.g. a wall surface or traffic area), borrowed from a city model.
 * It has the getters of every ancestor; for the concrete type, convert it with
 * `AbstractFeatureKindRef::from_space_boundary` and e.g. `WallSurface::try_from`.
 */
class AbstractSpaceBoundaryKind {
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

  inline ecitygml::FeatureType feature_type() const;

    inline const ecitygml::capi::AbstractSpaceBoundaryKind* AsFFI() const;
    inline ecitygml::capi::AbstractSpaceBoundaryKind* AsFFI();
    inline static const ecitygml::AbstractSpaceBoundaryKind* FromFFI(const ecitygml::capi::AbstractSpaceBoundaryKind* ptr);
    inline static ecitygml::AbstractSpaceBoundaryKind* FromFFI(ecitygml::capi::AbstractSpaceBoundaryKind* ptr);
    inline static void operator delete(void* ptr);
private:
    AbstractSpaceBoundaryKind() = delete;
    AbstractSpaceBoundaryKind(const ecitygml::AbstractSpaceBoundaryKind&) = delete;
    AbstractSpaceBoundaryKind(ecitygml::AbstractSpaceBoundaryKind&&) noexcept = delete;
    AbstractSpaceBoundaryKind operator=(const ecitygml::AbstractSpaceBoundaryKind&) = delete;
    AbstractSpaceBoundaryKind operator=(ecitygml::AbstractSpaceBoundaryKind&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_AbstractSpaceBoundaryKind_D_HPP
