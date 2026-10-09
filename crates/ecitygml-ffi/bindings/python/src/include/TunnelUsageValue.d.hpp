#ifndef ECITYGML_TunnelUsageValue_D_HPP
#define ECITYGML_TunnelUsageValue_D_HPP

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
    struct TunnelUsageValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `usage` property of a Tunnel or TunnelPart.
 */
class TunnelUsageValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::TunnelUsageValue* AsFFI() const;
    inline ecitygml::capi::TunnelUsageValue* AsFFI();
    inline static const ecitygml::TunnelUsageValue* FromFFI(const ecitygml::capi::TunnelUsageValue* ptr);
    inline static ecitygml::TunnelUsageValue* FromFFI(ecitygml::capi::TunnelUsageValue* ptr);
    inline static void operator delete(void* ptr);
private:
    TunnelUsageValue() = delete;
    TunnelUsageValue(const ecitygml::TunnelUsageValue&) = delete;
    TunnelUsageValue(ecitygml::TunnelUsageValue&&) noexcept = delete;
    TunnelUsageValue operator=(const ecitygml::TunnelUsageValue&) = delete;
    TunnelUsageValue operator=(ecitygml::TunnelUsageValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_TunnelUsageValue_D_HPP
