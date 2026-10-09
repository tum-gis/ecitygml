#ifndef ecitygml_BuildingSubdivisionFunctionValue_D_HPP
#define ecitygml_BuildingSubdivisionFunctionValue_D_HPP

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
    struct BuildingSubdivisionFunctionValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `function` property of a Storey or BuildingUnit (AbstractBuildingSubdivision).
 */
class BuildingSubdivisionFunctionValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::BuildingSubdivisionFunctionValue* AsFFI() const;
    inline ecitygml::capi::BuildingSubdivisionFunctionValue* AsFFI();
    inline static const ecitygml::BuildingSubdivisionFunctionValue* FromFFI(const ecitygml::capi::BuildingSubdivisionFunctionValue* ptr);
    inline static ecitygml::BuildingSubdivisionFunctionValue* FromFFI(ecitygml::capi::BuildingSubdivisionFunctionValue* ptr);
    inline static void operator delete(void* ptr);
private:
    BuildingSubdivisionFunctionValue() = delete;
    BuildingSubdivisionFunctionValue(const ecitygml::BuildingSubdivisionFunctionValue&) = delete;
    BuildingSubdivisionFunctionValue(ecitygml::BuildingSubdivisionFunctionValue&&) noexcept = delete;
    BuildingSubdivisionFunctionValue operator=(const ecitygml::BuildingSubdivisionFunctionValue&) = delete;
    BuildingSubdivisionFunctionValue operator=(ecitygml::BuildingSubdivisionFunctionValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_BuildingSubdivisionFunctionValue_D_HPP
