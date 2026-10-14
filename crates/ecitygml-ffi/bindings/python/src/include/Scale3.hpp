#ifndef ECITYGML_Scale3_HPP
#define ECITYGML_Scale3_HPP

#include "Scale3.d.hpp"

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

} // namespace capi
} // namespace


inline ecitygml::capi::Scale3 ecitygml::Scale3::AsFFI() const {
    return ecitygml::capi::Scale3 {
        /* .x = */ x,
        /* .y = */ y,
        /* .z = */ z,
    };
}

inline ecitygml::Scale3 ecitygml::Scale3::FromFFI(ecitygml::capi::Scale3 c_struct) {
    return ecitygml::Scale3 {
        /* .x = */ c_struct.x,
        /* .y = */ c_struct.y,
        /* .z = */ c_struct.z,
    };
}


#endif // ECITYGML_Scale3_HPP
