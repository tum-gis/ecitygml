#ifndef ECITYGML_ErrorKind_HPP
#define ECITYGML_ErrorKind_HPP

#include "ErrorKind.d.hpp"

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

inline ecitygml::capi::ErrorKind ecitygml::ErrorKind::AsFFI() const {
    return static_cast<ecitygml::capi::ErrorKind>(value);
}

inline ecitygml::ErrorKind ecitygml::ErrorKind::FromFFI(ecitygml::capi::ErrorKind c_enum) {
    switch (c_enum) {
        case ecitygml::capi::ErrorKind_InvalidArgument:
        case ecitygml::capi::ErrorKind_Io:
        case ecitygml::capi::ErrorKind_Parse:
        case ecitygml::capi::ErrorKind_UnresolvedReference:
            return static_cast<ecitygml::ErrorKind::Value>(c_enum);
        default:
            std::abort();
    }
}
#endif // ECITYGML_ErrorKind_HPP
