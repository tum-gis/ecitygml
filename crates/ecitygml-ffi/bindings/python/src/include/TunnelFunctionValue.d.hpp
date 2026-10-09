#ifndef ECITYGML_TunnelFunctionValue_D_HPP
#define ECITYGML_TunnelFunctionValue_D_HPP

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
    struct TunnelFunctionValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `function` property of a Tunnel or TunnelPart.
 */
class TunnelFunctionValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::TunnelFunctionValue* AsFFI() const;
    inline ecitygml::capi::TunnelFunctionValue* AsFFI();
    inline static const ecitygml::TunnelFunctionValue* FromFFI(const ecitygml::capi::TunnelFunctionValue* ptr);
    inline static ecitygml::TunnelFunctionValue* FromFFI(ecitygml::capi::TunnelFunctionValue* ptr);
    inline static void operator delete(void* ptr);
private:
    TunnelFunctionValue() = delete;
    TunnelFunctionValue(const ecitygml::TunnelFunctionValue&) = delete;
    TunnelFunctionValue(ecitygml::TunnelFunctionValue&&) noexcept = delete;
    TunnelFunctionValue operator=(const ecitygml::TunnelFunctionValue&) = delete;
    TunnelFunctionValue operator=(ecitygml::TunnelFunctionValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_TunnelFunctionValue_D_HPP
