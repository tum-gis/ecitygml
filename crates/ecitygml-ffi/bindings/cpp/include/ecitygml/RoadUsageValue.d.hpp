#ifndef ecitygml_RoadUsageValue_D_HPP
#define ecitygml_RoadUsageValue_D_HPP

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
    struct RoadUsageValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `usage` property of a Road.
 */
class RoadUsageValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::RoadUsageValue* AsFFI() const;
    inline ecitygml::capi::RoadUsageValue* AsFFI();
    inline static const ecitygml::RoadUsageValue* FromFFI(const ecitygml::capi::RoadUsageValue* ptr);
    inline static ecitygml::RoadUsageValue* FromFFI(ecitygml::capi::RoadUsageValue* ptr);
    inline static void operator delete(void* ptr);
private:
    RoadUsageValue() = delete;
    RoadUsageValue(const ecitygml::RoadUsageValue&) = delete;
    RoadUsageValue(ecitygml::RoadUsageValue&&) noexcept = delete;
    RoadUsageValue operator=(const ecitygml::RoadUsageValue&) = delete;
    RoadUsageValue operator=(ecitygml::RoadUsageValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_RoadUsageValue_D_HPP
