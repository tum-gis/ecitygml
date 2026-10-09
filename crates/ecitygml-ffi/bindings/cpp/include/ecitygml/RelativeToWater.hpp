#ifndef ecitygml_RelativeToWater_HPP
#define ecitygml_RelativeToWater_HPP

#include "RelativeToWater.d.hpp"

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

} // namespace capi
} // namespace

inline ecitygml::capi::RelativeToWater ecitygml::RelativeToWater::AsFFI() const {
    return static_cast<ecitygml::capi::RelativeToWater>(value);
}

inline ecitygml::RelativeToWater ecitygml::RelativeToWater::FromFFI(ecitygml::capi::RelativeToWater c_enum) {
    switch (c_enum) {
        case ecitygml::capi::RelativeToWater_EntirelyAboveWaterSurface:
        case ecitygml::capi::RelativeToWater_SubstantiallyAboveWaterSurface:
        case ecitygml::capi::RelativeToWater_SubstantiallyAboveAndBelowWaterSurface:
        case ecitygml::capi::RelativeToWater_SubstantiallyBelowWaterSurface:
        case ecitygml::capi::RelativeToWater_EntirelyBelowWaterSurface:
        case ecitygml::capi::RelativeToWater_TemporarilyAboveAndBelowWaterSurface:
            return static_cast<ecitygml::RelativeToWater::Value>(c_enum);
        default:
            std::abort();
    }
}
#endif // ecitygml_RelativeToWater_HPP
