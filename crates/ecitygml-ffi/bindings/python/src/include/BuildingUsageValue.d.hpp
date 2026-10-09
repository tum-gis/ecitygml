#ifndef ECITYGML_BuildingUsageValue_D_HPP
#define ECITYGML_BuildingUsageValue_D_HPP

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
    struct BuildingUsageValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `usage` property of a Building or BuildingPart.
 */
class BuildingUsageValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::BuildingUsageValue* AsFFI() const;
    inline ecitygml::capi::BuildingUsageValue* AsFFI();
    inline static const ecitygml::BuildingUsageValue* FromFFI(const ecitygml::capi::BuildingUsageValue* ptr);
    inline static ecitygml::BuildingUsageValue* FromFFI(ecitygml::capi::BuildingUsageValue* ptr);
    inline static void operator delete(void* ptr);
private:
    BuildingUsageValue() = delete;
    BuildingUsageValue(const ecitygml::BuildingUsageValue&) = delete;
    BuildingUsageValue(ecitygml::BuildingUsageValue&&) noexcept = delete;
    BuildingUsageValue operator=(const ecitygml::BuildingUsageValue&) = delete;
    BuildingUsageValue operator=(ecitygml::BuildingUsageValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_BuildingUsageValue_D_HPP
