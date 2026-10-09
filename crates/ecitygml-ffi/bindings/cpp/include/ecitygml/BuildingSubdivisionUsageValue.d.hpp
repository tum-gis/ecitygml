#ifndef ecitygml_BuildingSubdivisionUsageValue_D_HPP
#define ecitygml_BuildingSubdivisionUsageValue_D_HPP

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
namespace capi { struct Code; }
class Code;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct BuildingSubdivisionUsageValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `usage` property of a Storey or BuildingUnit (AbstractBuildingSubdivision).
 */
class BuildingSubdivisionUsageValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::BuildingSubdivisionUsageValue* AsFFI() const;
    inline ecitygml::capi::BuildingSubdivisionUsageValue* AsFFI();
    inline static const ecitygml::BuildingSubdivisionUsageValue* FromFFI(const ecitygml::capi::BuildingSubdivisionUsageValue* ptr);
    inline static ecitygml::BuildingSubdivisionUsageValue* FromFFI(ecitygml::capi::BuildingSubdivisionUsageValue* ptr);
    inline static void operator delete(void* ptr);
private:
    BuildingSubdivisionUsageValue() = delete;
    BuildingSubdivisionUsageValue(const ecitygml::BuildingSubdivisionUsageValue&) = delete;
    BuildingSubdivisionUsageValue(ecitygml::BuildingSubdivisionUsageValue&&) noexcept = delete;
    BuildingSubdivisionUsageValue operator=(const ecitygml::BuildingSubdivisionUsageValue&) = delete;
    BuildingSubdivisionUsageValue operator=(ecitygml::BuildingSubdivisionUsageValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_BuildingSubdivisionUsageValue_D_HPP
