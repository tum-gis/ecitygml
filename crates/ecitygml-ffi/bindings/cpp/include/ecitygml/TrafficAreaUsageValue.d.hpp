#ifndef ecitygml_TrafficAreaUsageValue_D_HPP
#define ecitygml_TrafficAreaUsageValue_D_HPP

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
    struct TrafficAreaUsageValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `usage` property of a TrafficArea.
 */
class TrafficAreaUsageValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::TrafficAreaUsageValue* AsFFI() const;
    inline ecitygml::capi::TrafficAreaUsageValue* AsFFI();
    inline static const ecitygml::TrafficAreaUsageValue* FromFFI(const ecitygml::capi::TrafficAreaUsageValue* ptr);
    inline static ecitygml::TrafficAreaUsageValue* FromFFI(ecitygml::capi::TrafficAreaUsageValue* ptr);
    inline static void operator delete(void* ptr);
private:
    TrafficAreaUsageValue() = delete;
    TrafficAreaUsageValue(const ecitygml::TrafficAreaUsageValue&) = delete;
    TrafficAreaUsageValue(ecitygml::TrafficAreaUsageValue&&) noexcept = delete;
    TrafficAreaUsageValue operator=(const ecitygml::TrafficAreaUsageValue&) = delete;
    TrafficAreaUsageValue operator=(ecitygml::TrafficAreaUsageValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_TrafficAreaUsageValue_D_HPP
