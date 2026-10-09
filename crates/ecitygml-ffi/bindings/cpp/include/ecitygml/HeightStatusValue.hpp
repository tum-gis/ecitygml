#ifndef ecitygml_HeightStatusValue_HPP
#define ecitygml_HeightStatusValue_HPP

#include "HeightStatusValue.d.hpp"

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

inline ecitygml::capi::HeightStatusValue ecitygml::HeightStatusValue::AsFFI() const {
    return static_cast<ecitygml::capi::HeightStatusValue>(value);
}

inline ecitygml::HeightStatusValue ecitygml::HeightStatusValue::FromFFI(ecitygml::capi::HeightStatusValue c_enum) {
    switch (c_enum) {
        case ecitygml::capi::HeightStatusValue_Estimated:
        case ecitygml::capi::HeightStatusValue_Measured:
            return static_cast<ecitygml::HeightStatusValue::Value>(c_enum);
        default:
            std::abort();
    }
}
#endif // ecitygml_HeightStatusValue_HPP
