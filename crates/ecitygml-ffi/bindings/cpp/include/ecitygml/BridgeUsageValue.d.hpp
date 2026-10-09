#ifndef ecitygml_BridgeUsageValue_D_HPP
#define ecitygml_BridgeUsageValue_D_HPP

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
    struct BridgeUsageValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `usage` property of a Bridge or BridgePart.
 */
class BridgeUsageValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::BridgeUsageValue* AsFFI() const;
    inline ecitygml::capi::BridgeUsageValue* AsFFI();
    inline static const ecitygml::BridgeUsageValue* FromFFI(const ecitygml::capi::BridgeUsageValue* ptr);
    inline static ecitygml::BridgeUsageValue* FromFFI(ecitygml::capi::BridgeUsageValue* ptr);
    inline static void operator delete(void* ptr);
private:
    BridgeUsageValue() = delete;
    BridgeUsageValue(const ecitygml::BridgeUsageValue&) = delete;
    BridgeUsageValue(ecitygml::BridgeUsageValue&&) noexcept = delete;
    BridgeUsageValue operator=(const ecitygml::BridgeUsageValue&) = delete;
    BridgeUsageValue operator=(ecitygml::BridgeUsageValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_BridgeUsageValue_D_HPP
