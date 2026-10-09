#ifndef ECITYGML_CitygmlFormat_HPP
#define ECITYGML_CitygmlFormat_HPP

#include "CitygmlFormat.d.hpp"

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

inline ecitygml::capi::CitygmlFormat ecitygml::CitygmlFormat::AsFFI() const {
    return static_cast<ecitygml::capi::CitygmlFormat>(value);
}

inline ecitygml::CitygmlFormat ecitygml::CitygmlFormat::FromFFI(ecitygml::capi::CitygmlFormat c_enum) {
    switch (c_enum) {
        case ecitygml::capi::CitygmlFormat_Gml:
        case ecitygml::capi::CitygmlFormat_GmlZst:
        case ecitygml::capi::CitygmlFormat_GmlGz:
            return static_cast<ecitygml::CitygmlFormat::Value>(c_enum);
        default:
            std::abort();
    }
}
#endif // ECITYGML_CitygmlFormat_HPP
