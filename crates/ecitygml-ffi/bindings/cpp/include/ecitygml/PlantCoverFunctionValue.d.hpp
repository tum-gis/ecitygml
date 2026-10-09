#ifndef ecitygml_PlantCoverFunctionValue_D_HPP
#define ecitygml_PlantCoverFunctionValue_D_HPP

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
    struct PlantCoverFunctionValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `function` property of a PlantCover.
 */
class PlantCoverFunctionValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::PlantCoverFunctionValue* AsFFI() const;
    inline ecitygml::capi::PlantCoverFunctionValue* AsFFI();
    inline static const ecitygml::PlantCoverFunctionValue* FromFFI(const ecitygml::capi::PlantCoverFunctionValue* ptr);
    inline static ecitygml::PlantCoverFunctionValue* FromFFI(ecitygml::capi::PlantCoverFunctionValue* ptr);
    inline static void operator delete(void* ptr);
private:
    PlantCoverFunctionValue() = delete;
    PlantCoverFunctionValue(const ecitygml::PlantCoverFunctionValue&) = delete;
    PlantCoverFunctionValue(ecitygml::PlantCoverFunctionValue&&) noexcept = delete;
    PlantCoverFunctionValue operator=(const ecitygml::PlantCoverFunctionValue&) = delete;
    PlantCoverFunctionValue operator=(ecitygml::PlantCoverFunctionValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_PlantCoverFunctionValue_D_HPP
