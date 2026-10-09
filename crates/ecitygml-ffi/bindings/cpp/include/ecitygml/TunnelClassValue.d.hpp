#ifndef ecitygml_TunnelClassValue_D_HPP
#define ecitygml_TunnelClassValue_D_HPP

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
    struct TunnelClassValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `class` property of a Tunnel or TunnelPart.
 */
class TunnelClassValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::TunnelClassValue* AsFFI() const;
    inline ecitygml::capi::TunnelClassValue* AsFFI();
    inline static const ecitygml::TunnelClassValue* FromFFI(const ecitygml::capi::TunnelClassValue* ptr);
    inline static ecitygml::TunnelClassValue* FromFFI(ecitygml::capi::TunnelClassValue* ptr);
    inline static void operator delete(void* ptr);
private:
    TunnelClassValue() = delete;
    TunnelClassValue(const ecitygml::TunnelClassValue&) = delete;
    TunnelClassValue(ecitygml::TunnelClassValue&&) noexcept = delete;
    TunnelClassValue operator=(const ecitygml::TunnelClassValue&) = delete;
    TunnelClassValue operator=(ecitygml::TunnelClassValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_TunnelClassValue_D_HPP
