#ifndef ecitygml_TrafficSpaceFunctionValue_D_HPP
#define ecitygml_TrafficSpaceFunctionValue_D_HPP

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
namespace capi { struct Code; }
class Code;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct TrafficSpaceFunctionValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `function` property of a TrafficSpace.
 */
class TrafficSpaceFunctionValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::TrafficSpaceFunctionValue* AsFFI() const;
    inline ecitygml::capi::TrafficSpaceFunctionValue* AsFFI();
    inline static const ecitygml::TrafficSpaceFunctionValue* FromFFI(const ecitygml::capi::TrafficSpaceFunctionValue* ptr);
    inline static ecitygml::TrafficSpaceFunctionValue* FromFFI(ecitygml::capi::TrafficSpaceFunctionValue* ptr);
    inline static void operator delete(void* ptr);
private:
    TrafficSpaceFunctionValue() = delete;
    TrafficSpaceFunctionValue(const ecitygml::TrafficSpaceFunctionValue&) = delete;
    TrafficSpaceFunctionValue(ecitygml::TrafficSpaceFunctionValue&&) noexcept = delete;
    TrafficSpaceFunctionValue operator=(const ecitygml::TrafficSpaceFunctionValue&) = delete;
    TrafficSpaceFunctionValue operator=(ecitygml::TrafficSpaceFunctionValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_TrafficSpaceFunctionValue_D_HPP
