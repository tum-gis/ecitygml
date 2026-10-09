#ifndef ECITYGML_TrafficDirectionValue_D_HPP
#define ECITYGML_TrafficDirectionValue_D_HPP

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
    enum TrafficDirectionValue {
      TrafficDirectionValue_Forwards = 0,
      TrafficDirectionValue_Backwards = 1,
      TrafficDirectionValue_Both = 2,
    };

    typedef struct TrafficDirectionValue_option {union { TrafficDirectionValue ok; }; bool is_ok; } TrafficDirectionValue_option;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Allowed traffic direction of a traffic space.
 */
class TrafficDirectionValue {
public:
    enum Value {
        Forwards = 0,
        Backwards = 1,
        Both = 2,
    };

    TrafficDirectionValue(): value(Value::Forwards) {}

    // Implicit conversions between enum and ::Value
    constexpr TrafficDirectionValue(Value v) : value(v) {}
    constexpr operator Value() const { return value; }
    // Prevent usage as boolean value
    explicit operator bool() const = delete;

    inline ecitygml::capi::TrafficDirectionValue AsFFI() const;
    inline static ecitygml::TrafficDirectionValue FromFFI(ecitygml::capi::TrafficDirectionValue c_enum);
private:
    Value value;
};

} // namespace
#endif // ECITYGML_TrafficDirectionValue_D_HPP
