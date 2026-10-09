#ifndef ecitygml_TrafficDirectionValue_HPP
#define ecitygml_TrafficDirectionValue_HPP

#include "TrafficDirectionValue.d.hpp"

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

inline ecitygml::capi::TrafficDirectionValue ecitygml::TrafficDirectionValue::AsFFI() const {
    return static_cast<ecitygml::capi::TrafficDirectionValue>(value);
}

inline ecitygml::TrafficDirectionValue ecitygml::TrafficDirectionValue::FromFFI(ecitygml::capi::TrafficDirectionValue c_enum) {
    switch (c_enum) {
        case ecitygml::capi::TrafficDirectionValue_Forwards:
        case ecitygml::capi::TrafficDirectionValue_Backwards:
        case ecitygml::capi::TrafficDirectionValue_Both:
            return static_cast<ecitygml::TrafficDirectionValue::Value>(c_enum);
        default:
            std::abort();
    }
}
#endif // ecitygml_TrafficDirectionValue_HPP
