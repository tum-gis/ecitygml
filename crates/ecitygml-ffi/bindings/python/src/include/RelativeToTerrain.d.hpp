#ifndef ECITYGML_RelativeToTerrain_D_HPP
#define ECITYGML_RelativeToTerrain_D_HPP

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
namespace capi {
    enum RelativeToTerrain {
      RelativeToTerrain_EntirelyAboveTerrain = 0,
      RelativeToTerrain_SubstantiallyAboveTerrain = 1,
      RelativeToTerrain_SubstantiallyAboveAndBelowTerrain = 2,
      RelativeToTerrain_SubstantiallyBelowTerrain = 3,
      RelativeToTerrain_EntirelyBelowTerrain = 4,
    };

    typedef struct RelativeToTerrain_option {union { RelativeToTerrain ok; }; bool is_ok; } RelativeToTerrain_option;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Position of a city object relative to the terrain.
 */
class RelativeToTerrain {
public:
    enum Value {
        EntirelyAboveTerrain = 0,
        SubstantiallyAboveTerrain = 1,
        SubstantiallyAboveAndBelowTerrain = 2,
        SubstantiallyBelowTerrain = 3,
        EntirelyBelowTerrain = 4,
    };

    RelativeToTerrain(): value(Value::EntirelyAboveTerrain) {}

    // Implicit conversions between enum and ::Value
    constexpr RelativeToTerrain(Value v) : value(v) {}
    constexpr operator Value() const { return value; }
    // Prevent usage as boolean value
    explicit operator bool() const = delete;

    inline ecitygml::capi::RelativeToTerrain AsFFI() const;
    inline static ecitygml::RelativeToTerrain FromFFI(ecitygml::capi::RelativeToTerrain c_enum);
private:
    Value value;
};

} // namespace
#endif // ECITYGML_RelativeToTerrain_D_HPP
