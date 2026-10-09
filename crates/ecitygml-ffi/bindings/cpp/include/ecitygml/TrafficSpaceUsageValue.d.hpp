#ifndef ecitygml_TrafficSpaceUsageValue_D_HPP
#define ecitygml_TrafficSpaceUsageValue_D_HPP

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
    struct TrafficSpaceUsageValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `usage` property of a TrafficSpace.
 */
class TrafficSpaceUsageValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::TrafficSpaceUsageValue* AsFFI() const;
    inline ecitygml::capi::TrafficSpaceUsageValue* AsFFI();
    inline static const ecitygml::TrafficSpaceUsageValue* FromFFI(const ecitygml::capi::TrafficSpaceUsageValue* ptr);
    inline static ecitygml::TrafficSpaceUsageValue* FromFFI(ecitygml::capi::TrafficSpaceUsageValue* ptr);
    inline static void operator delete(void* ptr);
private:
    TrafficSpaceUsageValue() = delete;
    TrafficSpaceUsageValue(const ecitygml::TrafficSpaceUsageValue&) = delete;
    TrafficSpaceUsageValue(ecitygml::TrafficSpaceUsageValue&&) noexcept = delete;
    TrafficSpaceUsageValue operator=(const ecitygml::TrafficSpaceUsageValue&) = delete;
    TrafficSpaceUsageValue operator=(ecitygml::TrafficSpaceUsageValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_TrafficSpaceUsageValue_D_HPP
