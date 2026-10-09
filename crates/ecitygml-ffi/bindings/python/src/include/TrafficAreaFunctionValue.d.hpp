#ifndef ECITYGML_TrafficAreaFunctionValue_D_HPP
#define ECITYGML_TrafficAreaFunctionValue_D_HPP

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
namespace capi { struct Code; }
class Code;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct TrafficAreaFunctionValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `function` property of a TrafficArea.
 */
class TrafficAreaFunctionValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::TrafficAreaFunctionValue* AsFFI() const;
    inline ecitygml::capi::TrafficAreaFunctionValue* AsFFI();
    inline static const ecitygml::TrafficAreaFunctionValue* FromFFI(const ecitygml::capi::TrafficAreaFunctionValue* ptr);
    inline static ecitygml::TrafficAreaFunctionValue* FromFFI(ecitygml::capi::TrafficAreaFunctionValue* ptr);
    inline static void operator delete(void* ptr);
private:
    TrafficAreaFunctionValue() = delete;
    TrafficAreaFunctionValue(const ecitygml::TrafficAreaFunctionValue&) = delete;
    TrafficAreaFunctionValue(ecitygml::TrafficAreaFunctionValue&&) noexcept = delete;
    TrafficAreaFunctionValue operator=(const ecitygml::TrafficAreaFunctionValue&) = delete;
    TrafficAreaFunctionValue operator=(ecitygml::TrafficAreaFunctionValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_TrafficAreaFunctionValue_D_HPP
