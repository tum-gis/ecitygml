#ifndef ECITYGML_SolitaryVegetationObjectFunctionValue_D_HPP
#define ECITYGML_SolitaryVegetationObjectFunctionValue_D_HPP

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
    struct SolitaryVegetationObjectFunctionValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `function` property of a SolitaryVegetationObject.
 */
class SolitaryVegetationObjectFunctionValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::SolitaryVegetationObjectFunctionValue* AsFFI() const;
    inline ecitygml::capi::SolitaryVegetationObjectFunctionValue* AsFFI();
    inline static const ecitygml::SolitaryVegetationObjectFunctionValue* FromFFI(const ecitygml::capi::SolitaryVegetationObjectFunctionValue* ptr);
    inline static ecitygml::SolitaryVegetationObjectFunctionValue* FromFFI(ecitygml::capi::SolitaryVegetationObjectFunctionValue* ptr);
    inline static void operator delete(void* ptr);
private:
    SolitaryVegetationObjectFunctionValue() = delete;
    SolitaryVegetationObjectFunctionValue(const ecitygml::SolitaryVegetationObjectFunctionValue&) = delete;
    SolitaryVegetationObjectFunctionValue(ecitygml::SolitaryVegetationObjectFunctionValue&&) noexcept = delete;
    SolitaryVegetationObjectFunctionValue operator=(const ecitygml::SolitaryVegetationObjectFunctionValue&) = delete;
    SolitaryVegetationObjectFunctionValue operator=(ecitygml::SolitaryVegetationObjectFunctionValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_SolitaryVegetationObjectFunctionValue_D_HPP
