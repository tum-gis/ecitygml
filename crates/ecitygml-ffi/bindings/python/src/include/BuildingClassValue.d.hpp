#ifndef ECITYGML_BuildingClassValue_D_HPP
#define ECITYGML_BuildingClassValue_D_HPP

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
    struct BuildingClassValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `class` property of a Building or BuildingPart.
 */
class BuildingClassValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::BuildingClassValue* AsFFI() const;
    inline ecitygml::capi::BuildingClassValue* AsFFI();
    inline static const ecitygml::BuildingClassValue* FromFFI(const ecitygml::capi::BuildingClassValue* ptr);
    inline static ecitygml::BuildingClassValue* FromFFI(ecitygml::capi::BuildingClassValue* ptr);
    inline static void operator delete(void* ptr);
private:
    BuildingClassValue() = delete;
    BuildingClassValue(const ecitygml::BuildingClassValue&) = delete;
    BuildingClassValue(ecitygml::BuildingClassValue&&) noexcept = delete;
    BuildingClassValue operator=(const ecitygml::BuildingClassValue&) = delete;
    BuildingClassValue operator=(ecitygml::BuildingClassValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_BuildingClassValue_D_HPP
