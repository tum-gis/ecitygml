#ifndef ECITYGML_TinRelief_D_HPP
#define ECITYGML_TinRelief_D_HPP

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
namespace capi { struct TinProperty; }
class TinProperty;
namespace capi { struct TinRelief; }
class TinRelief;
class LevelOfDetail;
class RelativeToTerrain;
class RelativeToWater;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct TinRelief;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A relief component given as a triangulated irregular network, borrowed from a city model.
 */
class TinRelief {
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

  /**
   * The feature as a tin relief, or none if it is another type (Rust: `<&TinRelief>::try_from`).
   */
  inline static const ecitygml::TinRelief* try_from(const ecitygml::AbstractFeatureKindRef& feature DIPLOMAT_LIFETIME_BOUND);

  inline const ecitygml::TinProperty* tin() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::TinRelief* AsFFI() const;
    inline ecitygml::capi::TinRelief* AsFFI();
    inline static const ecitygml::TinRelief* FromFFI(const ecitygml::capi::TinRelief* ptr);
    inline static ecitygml::TinRelief* FromFFI(ecitygml::capi::TinRelief* ptr);
    inline static void operator delete(void* ptr);
private:
    TinRelief() = delete;
    TinRelief(const ecitygml::TinRelief&) = delete;
    TinRelief(ecitygml::TinRelief&&) noexcept = delete;
    TinRelief operator=(const ecitygml::TinRelief&) = delete;
    TinRelief operator=(ecitygml::TinRelief&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_TinRelief_D_HPP
