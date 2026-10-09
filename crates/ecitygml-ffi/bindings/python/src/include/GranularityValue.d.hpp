#ifndef ECITYGML_GranularityValue_D_HPP
#define ECITYGML_GranularityValue_D_HPP

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
    enum GranularityValue {
      GranularityValue_Lane = 0,
      GranularityValue_Way = 1,
    };

    typedef struct GranularityValue_option {union { GranularityValue ok; }; bool is_ok; } GranularityValue_option;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Level of subdivision of a transportation space (lane or way).
 */
class GranularityValue {
public:
    enum Value {
        Lane = 0,
        Way = 1,
    };

    GranularityValue(): value(Value::Lane) {}

    // Implicit conversions between enum and ::Value
    constexpr GranularityValue(Value v) : value(v) {}
    constexpr operator Value() const { return value; }
    // Prevent usage as boolean value
    explicit operator bool() const = delete;

    inline ecitygml::capi::GranularityValue AsFFI() const;
    inline static ecitygml::GranularityValue FromFFI(ecitygml::capi::GranularityValue c_enum);
private:
    Value value;
};

} // namespace
#endif // ECITYGML_GranularityValue_D_HPP
