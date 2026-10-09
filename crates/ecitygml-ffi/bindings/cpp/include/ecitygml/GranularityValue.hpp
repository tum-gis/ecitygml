#ifndef ecitygml_GranularityValue_HPP
#define ecitygml_GranularityValue_HPP

#include "GranularityValue.d.hpp"

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

inline ecitygml::capi::GranularityValue ecitygml::GranularityValue::AsFFI() const {
    return static_cast<ecitygml::capi::GranularityValue>(value);
}

inline ecitygml::GranularityValue ecitygml::GranularityValue::FromFFI(ecitygml::capi::GranularityValue c_enum) {
    switch (c_enum) {
        case ecitygml::capi::GranularityValue_Lane:
        case ecitygml::capi::GranularityValue_Way:
            return static_cast<ecitygml::GranularityValue::Value>(c_enum);
        default:
            std::abort();
    }
}
#endif // ecitygml_GranularityValue_HPP
