#ifndef ecitygml_RelativeToTerrain_HPP
#define ecitygml_RelativeToTerrain_HPP

#include "RelativeToTerrain.d.hpp"

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

inline ecitygml::capi::RelativeToTerrain ecitygml::RelativeToTerrain::AsFFI() const {
    return static_cast<ecitygml::capi::RelativeToTerrain>(value);
}

inline ecitygml::RelativeToTerrain ecitygml::RelativeToTerrain::FromFFI(ecitygml::capi::RelativeToTerrain c_enum) {
    switch (c_enum) {
        case ecitygml::capi::RelativeToTerrain_EntirelyAboveTerrain:
        case ecitygml::capi::RelativeToTerrain_SubstantiallyAboveTerrain:
        case ecitygml::capi::RelativeToTerrain_SubstantiallyAboveAndBelowTerrain:
        case ecitygml::capi::RelativeToTerrain_SubstantiallyBelowTerrain:
        case ecitygml::capi::RelativeToTerrain_EntirelyBelowTerrain:
            return static_cast<ecitygml::RelativeToTerrain::Value>(c_enum);
        default:
            std::abort();
    }
}
#endif // ecitygml_RelativeToTerrain_HPP
