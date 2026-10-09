#ifndef ECITYGML_RelationTypeValue_D_HPP
#define ECITYGML_RelationTypeValue_D_HPP

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
namespace capi { struct Code; }
class Code;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct RelationTypeValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `relationType` property of a CityObjectRelation.
 */
class RelationTypeValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::RelationTypeValue* AsFFI() const;
    inline ecitygml::capi::RelationTypeValue* AsFFI();
    inline static const ecitygml::RelationTypeValue* FromFFI(const ecitygml::capi::RelationTypeValue* ptr);
    inline static ecitygml::RelationTypeValue* FromFFI(ecitygml::capi::RelationTypeValue* ptr);
    inline static void operator delete(void* ptr);
private:
    RelationTypeValue() = delete;
    RelationTypeValue(const ecitygml::RelationTypeValue&) = delete;
    RelationTypeValue(ecitygml::RelationTypeValue&&) noexcept = delete;
    RelationTypeValue operator=(const ecitygml::RelationTypeValue&) = delete;
    RelationTypeValue operator=(ecitygml::RelationTypeValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_RelationTypeValue_D_HPP
