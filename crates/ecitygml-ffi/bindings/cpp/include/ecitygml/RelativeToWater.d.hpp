#ifndef ecitygml_RelativeToWater_D_HPP
#define ecitygml_RelativeToWater_D_HPP

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
namespace capi {
    enum RelativeToWater {
      RelativeToWater_EntirelyAboveWaterSurface = 0,
      RelativeToWater_SubstantiallyAboveWaterSurface = 1,
      RelativeToWater_SubstantiallyAboveAndBelowWaterSurface = 2,
      RelativeToWater_SubstantiallyBelowWaterSurface = 3,
      RelativeToWater_EntirelyBelowWaterSurface = 4,
      RelativeToWater_TemporarilyAboveAndBelowWaterSurface = 5,
    };

    typedef struct RelativeToWater_option {union { RelativeToWater ok; }; bool is_ok; } RelativeToWater_option;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Position of a city object relative to the water surface.
 */
class RelativeToWater {
public:
    enum Value {
        EntirelyAboveWaterSurface = 0,
        SubstantiallyAboveWaterSurface = 1,
        SubstantiallyAboveAndBelowWaterSurface = 2,
        SubstantiallyBelowWaterSurface = 3,
        EntirelyBelowWaterSurface = 4,
        TemporarilyAboveAndBelowWaterSurface = 5,
    };

    RelativeToWater(): value(Value::EntirelyAboveWaterSurface) {}

    // Implicit conversions between enum and ::Value
    constexpr RelativeToWater(Value v) : value(v) {}
    constexpr operator Value() const { return value; }
    // Prevent usage as boolean value
    explicit operator bool() const = delete;

    inline ecitygml::capi::RelativeToWater AsFFI() const;
    inline static ecitygml::RelativeToWater FromFFI(ecitygml::capi::RelativeToWater c_enum);
private:
    Value value;
};

} // namespace
#endif // ecitygml_RelativeToWater_D_HPP
