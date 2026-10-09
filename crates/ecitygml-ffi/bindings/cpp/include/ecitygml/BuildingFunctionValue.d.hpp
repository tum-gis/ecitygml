#ifndef ecitygml_BuildingFunctionValue_D_HPP
#define ecitygml_BuildingFunctionValue_D_HPP

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
    struct BuildingFunctionValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `function` property of a Building or BuildingPart.
 */
class BuildingFunctionValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::BuildingFunctionValue* AsFFI() const;
    inline ecitygml::capi::BuildingFunctionValue* AsFFI();
    inline static const ecitygml::BuildingFunctionValue* FromFFI(const ecitygml::capi::BuildingFunctionValue* ptr);
    inline static ecitygml::BuildingFunctionValue* FromFFI(ecitygml::capi::BuildingFunctionValue* ptr);
    inline static void operator delete(void* ptr);
private:
    BuildingFunctionValue() = delete;
    BuildingFunctionValue(const ecitygml::BuildingFunctionValue&) = delete;
    BuildingFunctionValue(ecitygml::BuildingFunctionValue&&) noexcept = delete;
    BuildingFunctionValue operator=(const ecitygml::BuildingFunctionValue&) = delete;
    BuildingFunctionValue operator=(ecitygml::BuildingFunctionValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_BuildingFunctionValue_D_HPP
