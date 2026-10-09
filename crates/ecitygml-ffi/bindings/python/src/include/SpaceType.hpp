#ifndef ECITYGML_SpaceType_HPP
#define ECITYGML_SpaceType_HPP

#include "SpaceType.d.hpp"

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

inline ecitygml::capi::SpaceType ecitygml::SpaceType::AsFFI() const {
    return static_cast<ecitygml::capi::SpaceType>(value);
}

inline ecitygml::SpaceType ecitygml::SpaceType::FromFFI(ecitygml::capi::SpaceType c_enum) {
    switch (c_enum) {
        case ecitygml::capi::SpaceType_Closed:
        case ecitygml::capi::SpaceType_Open:
        case ecitygml::capi::SpaceType_SemiOpen:
            return static_cast<ecitygml::SpaceType::Value>(c_enum);
        default:
            std::abort();
    }
}
#endif // ECITYGML_SpaceType_HPP
