#ifndef ECITYGML_BuildingSubdivisionClassValue_D_HPP
#define ECITYGML_BuildingSubdivisionClassValue_D_HPP

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
    struct BuildingSubdivisionClassValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `class` property of a Storey or BuildingUnit (AbstractBuildingSubdivision).
 */
class BuildingSubdivisionClassValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::BuildingSubdivisionClassValue* AsFFI() const;
    inline ecitygml::capi::BuildingSubdivisionClassValue* AsFFI();
    inline static const ecitygml::BuildingSubdivisionClassValue* FromFFI(const ecitygml::capi::BuildingSubdivisionClassValue* ptr);
    inline static ecitygml::BuildingSubdivisionClassValue* FromFFI(ecitygml::capi::BuildingSubdivisionClassValue* ptr);
    inline static void operator delete(void* ptr);
private:
    BuildingSubdivisionClassValue() = delete;
    BuildingSubdivisionClassValue(const ecitygml::BuildingSubdivisionClassValue&) = delete;
    BuildingSubdivisionClassValue(ecitygml::BuildingSubdivisionClassValue&&) noexcept = delete;
    BuildingSubdivisionClassValue operator=(const ecitygml::BuildingSubdivisionClassValue&) = delete;
    BuildingSubdivisionClassValue operator=(ecitygml::BuildingSubdivisionClassValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_BuildingSubdivisionClassValue_D_HPP
