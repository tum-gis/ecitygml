#ifndef ecitygml_Vector3_HPP
#define ecitygml_Vector3_HPP

#include "Vector3.d.hpp"

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


inline ecitygml::capi::Vector3 ecitygml::Vector3::AsFFI() const {
    return ecitygml::capi::Vector3 {
        /* .x = */ x,
        /* .y = */ y,
        /* .z = */ z,
    };
}

inline ecitygml::Vector3 ecitygml::Vector3::FromFFI(ecitygml::capi::Vector3 c_struct) {
    return ecitygml::Vector3 {
        /* .x = */ c_struct.x,
        /* .y = */ c_struct.y,
        /* .z = */ c_struct.z,
    };
}


#endif // ecitygml_Vector3_HPP
