#ifndef ecitygml_ErrorKind_D_HPP
#define ecitygml_ErrorKind_D_HPP

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
    enum ErrorKind {
      ErrorKind_InvalidArgument = 0,
      ErrorKind_Io = 1,
      ErrorKind_Parse = 2,
      ErrorKind_UnresolvedReference = 3,
    };

    typedef struct ErrorKind_option {union { ErrorKind ok; }; bool is_ok; } ErrorKind_option;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Category of an {@link Error}.
 */
class ErrorKind {
public:
    enum Value {
        /**
         * An argument is invalid, e.g. an unsupported file extension or a non-UTF-8 string.
         */
        InvalidArgument = 0,
        /**
         * Reading a file failed.
         */
        Io = 1,
        /**
         * The file content is not valid CityGML.
         */
        Parse = 2,
        /**
         * Geometry is only referenced by `xlink:href` and the reference is not resolved.
         */
        UnresolvedReference = 3,
    };

    ErrorKind(): value(Value::InvalidArgument) {}

    // Implicit conversions between enum and ::Value
    constexpr ErrorKind(Value v) : value(v) {}
    constexpr operator Value() const { return value; }
    // Prevent usage as boolean value
    explicit operator bool() const = delete;

    inline ecitygml::capi::ErrorKind AsFFI() const;
    inline static ecitygml::ErrorKind FromFFI(ecitygml::capi::ErrorKind c_enum);
private:
    Value value;
};

} // namespace
#endif // ecitygml_ErrorKind_D_HPP
