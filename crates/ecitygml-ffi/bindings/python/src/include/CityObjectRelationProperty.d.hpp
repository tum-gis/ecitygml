#ifndef ECITYGML_CityObjectRelationProperty_D_HPP
#define ECITYGML_CityObjectRelationProperty_D_HPP

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
namespace capi { struct CityObjectRelation; }
class CityObjectRelation;
namespace capi { struct HRef; }
class HRef;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct CityObjectRelationProperty;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A city object relation property (inline relation and/or `xlink:href`), borrowed from a
 * city model.
 */
class CityObjectRelationProperty {
public:

  /**
   * The inline relation; none if the property only references one via `href`.
   */
  inline const ecitygml::CityObjectRelation* object() const DIPLOMAT_LIFETIME_BOUND;

  inline const ecitygml::HRef* href() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::CityObjectRelationProperty* AsFFI() const;
    inline ecitygml::capi::CityObjectRelationProperty* AsFFI();
    inline static const ecitygml::CityObjectRelationProperty* FromFFI(const ecitygml::capi::CityObjectRelationProperty* ptr);
    inline static ecitygml::CityObjectRelationProperty* FromFFI(ecitygml::capi::CityObjectRelationProperty* ptr);
    inline static void operator delete(void* ptr);
private:
    CityObjectRelationProperty() = delete;
    CityObjectRelationProperty(const ecitygml::CityObjectRelationProperty&) = delete;
    CityObjectRelationProperty(ecitygml::CityObjectRelationProperty&&) noexcept = delete;
    CityObjectRelationProperty operator=(const ecitygml::CityObjectRelationProperty&) = delete;
    CityObjectRelationProperty operator=(ecitygml::CityObjectRelationProperty&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_CityObjectRelationProperty_D_HPP
