#ifndef ECITYGML_SpaceType_D_HPP
#define ECITYGML_SpaceType_D_HPP

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
    enum SpaceType {
      SpaceType_Closed = 0,
      SpaceType_Open = 1,
      SpaceType_SemiOpen = 2,
    };

    typedef struct SpaceType_option {union { SpaceType ok; }; bool is_ok; } SpaceType_option;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Whether a space is closed, open or semi-open.
 */
class SpaceType {
public:
    enum Value {
        Closed = 0,
        Open = 1,
        SemiOpen = 2,
    };

    SpaceType(): value(Value::Closed) {}

    // Implicit conversions between enum and ::Value
    constexpr SpaceType(Value v) : value(v) {}
    constexpr operator Value() const { return value; }
    // Prevent usage as boolean value
    explicit operator bool() const = delete;

    inline ecitygml::capi::SpaceType AsFFI() const;
    inline static ecitygml::SpaceType FromFFI(ecitygml::capi::SpaceType c_enum);
private:
    Value value;
};

} // namespace
#endif // ECITYGML_SpaceType_D_HPP
