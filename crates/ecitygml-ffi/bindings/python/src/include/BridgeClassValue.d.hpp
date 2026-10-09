#ifndef ECITYGML_BridgeClassValue_D_HPP
#define ECITYGML_BridgeClassValue_D_HPP

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
    struct BridgeClassValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `class` property of a Bridge or BridgePart.
 */
class BridgeClassValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::BridgeClassValue* AsFFI() const;
    inline ecitygml::capi::BridgeClassValue* AsFFI();
    inline static const ecitygml::BridgeClassValue* FromFFI(const ecitygml::capi::BridgeClassValue* ptr);
    inline static ecitygml::BridgeClassValue* FromFFI(ecitygml::capi::BridgeClassValue* ptr);
    inline static void operator delete(void* ptr);
private:
    BridgeClassValue() = delete;
    BridgeClassValue(const ecitygml::BridgeClassValue&) = delete;
    BridgeClassValue(ecitygml::BridgeClassValue&&) noexcept = delete;
    BridgeClassValue operator=(const ecitygml::BridgeClassValue&) = delete;
    BridgeClassValue operator=(ecitygml::BridgeClassValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_BridgeClassValue_D_HPP
