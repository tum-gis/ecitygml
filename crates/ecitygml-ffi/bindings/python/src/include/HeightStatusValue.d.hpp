#ifndef ECITYGML_HeightStatusValue_D_HPP
#define ECITYGML_HeightStatusValue_D_HPP

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
    enum HeightStatusValue {
      HeightStatusValue_Estimated = 0,
      HeightStatusValue_Measured = 1,
    };

    typedef struct HeightStatusValue_option {union { HeightStatusValue ok; }; bool is_ok; } HeightStatusValue_option;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Whether a height was estimated or measured.
 */
class HeightStatusValue {
public:
    enum Value {
        Estimated = 0,
        Measured = 1,
    };

    HeightStatusValue(): value(Value::Estimated) {}

    // Implicit conversions between enum and ::Value
    constexpr HeightStatusValue(Value v) : value(v) {}
    constexpr operator Value() const { return value; }
    // Prevent usage as boolean value
    explicit operator bool() const = delete;

    inline ecitygml::capi::HeightStatusValue AsFFI() const;
    inline static ecitygml::HeightStatusValue FromFFI(ecitygml::capi::HeightStatusValue c_enum);
private:
    Value value;
};

} // namespace
#endif // ECITYGML_HeightStatusValue_D_HPP
