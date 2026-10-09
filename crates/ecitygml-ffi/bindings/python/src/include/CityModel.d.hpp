#ifndef ECITYGML_CityModel_D_HPP
#define ECITYGML_CityModel_D_HPP

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
namespace capi { struct AbstractCityObjectKindRefIterator; }
class AbstractCityObjectKindRefIterator;
namespace capi { struct AbstractFeatureKindRefIterator; }
class AbstractFeatureKindRefIterator;
namespace capi { struct BoundingShape; }
class BoundingShape;
namespace capi { struct CodeIterator; }
class CodeIterator;
namespace capi { struct DateTime; }
class DateTime;
namespace capi { struct Id; }
class Id;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct CityModel;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A city model; mutable for `recompute_child_bounding_shapes`.
 */
class CityModel {
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

  /**
   * Lazily iterates over all features at any depth (Rust: `IterFeatures::iter_features`).
   */
  inline std::unique_ptr<ecitygml::AbstractFeatureKindRefIterator> iter_features() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * Lazily iterates over all city objects at any depth, without the city model itself (Rust:
   * `iter_city_objects`).
   */
  inline std::unique_ptr<ecitygml::AbstractCityObjectKindRefIterator> iter_city_objects() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * Recomputes the bounding shape of every feature below the city model from its geometry.
   */
  inline void recompute_child_bounding_shapes();

  /**
   * Number of direct `cityObjectMember`s.
   */
  inline size_t city_objects_len() const;

    inline const ecitygml::capi::CityModel* AsFFI() const;
    inline ecitygml::capi::CityModel* AsFFI();
    inline static const ecitygml::CityModel* FromFFI(const ecitygml::capi::CityModel* ptr);
    inline static ecitygml::CityModel* FromFFI(ecitygml::capi::CityModel* ptr);
    inline static void operator delete(void* ptr);
private:
    CityModel() = delete;
    CityModel(const ecitygml::CityModel&) = delete;
    CityModel(ecitygml::CityModel&&) noexcept = delete;
    CityModel operator=(const ecitygml::CityModel&) = delete;
    CityModel operator=(ecitygml::CityModel&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_CityModel_D_HPP
