#ifndef ecitygml_CitygmlFormat_D_HPP
#define ecitygml_CitygmlFormat_D_HPP

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
    enum CitygmlFormat {
      CitygmlFormat_Gml = 0,
      CitygmlFormat_GmlZst = 1,
      CitygmlFormat_GmlGz = 2,
    };

    typedef struct CitygmlFormat_option {union { CitygmlFormat ok; }; bool is_ok; } CitygmlFormat_option;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Encoding of CityGML content.
 */
class CitygmlFormat {
public:
    enum Value {
        /**
         * Plain GML (`.gml`, `.xml`).
         */
        Gml = 0,
        /**
         * Zstandard-compressed GML (`.gml.zst`).
         */
        GmlZst = 1,
        /**
         * Gzip-compressed GML (`.gml.gz`).
         */
        GmlGz = 2,
    };

    CitygmlFormat(): value(Value::Gml) {}

    // Implicit conversions between enum and ::Value
    constexpr CitygmlFormat(Value v) : value(v) {}
    constexpr operator Value() const { return value; }
    // Prevent usage as boolean value
    explicit operator bool() const = delete;

    inline ecitygml::capi::CitygmlFormat AsFFI() const;
    inline static ecitygml::CitygmlFormat FromFFI(ecitygml::capi::CitygmlFormat c_enum);
private:
    Value value;
};

} // namespace
#endif // ecitygml_CitygmlFormat_D_HPP
