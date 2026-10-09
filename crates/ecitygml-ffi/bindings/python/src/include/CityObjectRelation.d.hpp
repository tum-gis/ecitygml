#ifndef ECITYGML_CityObjectRelation_D_HPP
#define ECITYGML_CityObjectRelation_D_HPP

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
namespace capi { struct GenericAttributeKindIterator; }
class GenericAttributeKindIterator;
namespace capi { struct Reference; }
class Reference;
namespace capi { struct RelationTypeValue; }
class RelationTypeValue;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct CityObjectRelation;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A relation of a city object to another one, borrowed from a city model.
 */
class CityObjectRelation {
public:

  inline const ecitygml::RelationTypeValue& relation_type() const DIPLOMAT_LIFETIME_BOUND;

  /**
   * The related city object (`relatedTo`), by reference.
   */
  inline const ecitygml::Reference& relation_to() const DIPLOMAT_LIFETIME_BOUND;

  inline std::unique_ptr<ecitygml::GenericAttributeKindIterator> generic_attributes() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::CityObjectRelation* AsFFI() const;
    inline ecitygml::capi::CityObjectRelation* AsFFI();
    inline static const ecitygml::CityObjectRelation* FromFFI(const ecitygml::capi::CityObjectRelation* ptr);
    inline static ecitygml::CityObjectRelation* FromFFI(ecitygml::capi::CityObjectRelation* ptr);
    inline static void operator delete(void* ptr);
private:
    CityObjectRelation() = delete;
    CityObjectRelation(const ecitygml::CityObjectRelation&) = delete;
    CityObjectRelation(ecitygml::CityObjectRelation&&) noexcept = delete;
    CityObjectRelation operator=(const ecitygml::CityObjectRelation&) = delete;
    CityObjectRelation operator=(ecitygml::CityObjectRelation&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_CityObjectRelation_D_HPP
