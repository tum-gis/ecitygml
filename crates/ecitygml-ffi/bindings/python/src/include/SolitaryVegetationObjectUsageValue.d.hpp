#ifndef ECITYGML_SolitaryVegetationObjectUsageValue_D_HPP
#define ECITYGML_SolitaryVegetationObjectUsageValue_D_HPP

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
    struct SolitaryVegetationObjectUsageValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `usage` property of a SolitaryVegetationObject.
 */
class SolitaryVegetationObjectUsageValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::SolitaryVegetationObjectUsageValue* AsFFI() const;
    inline ecitygml::capi::SolitaryVegetationObjectUsageValue* AsFFI();
    inline static const ecitygml::SolitaryVegetationObjectUsageValue* FromFFI(const ecitygml::capi::SolitaryVegetationObjectUsageValue* ptr);
    inline static ecitygml::SolitaryVegetationObjectUsageValue* FromFFI(ecitygml::capi::SolitaryVegetationObjectUsageValue* ptr);
    inline static void operator delete(void* ptr);
private:
    SolitaryVegetationObjectUsageValue() = delete;
    SolitaryVegetationObjectUsageValue(const ecitygml::SolitaryVegetationObjectUsageValue&) = delete;
    SolitaryVegetationObjectUsageValue(ecitygml::SolitaryVegetationObjectUsageValue&&) noexcept = delete;
    SolitaryVegetationObjectUsageValue operator=(const ecitygml::SolitaryVegetationObjectUsageValue&) = delete;
    SolitaryVegetationObjectUsageValue operator=(ecitygml::SolitaryVegetationObjectUsageValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_SolitaryVegetationObjectUsageValue_D_HPP
