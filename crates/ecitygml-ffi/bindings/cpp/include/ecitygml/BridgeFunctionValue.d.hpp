#ifndef ecitygml_BridgeFunctionValue_D_HPP
#define ecitygml_BridgeFunctionValue_D_HPP

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
    struct BridgeFunctionValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `function` property of a Bridge or BridgePart.
 */
class BridgeFunctionValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::BridgeFunctionValue* AsFFI() const;
    inline ecitygml::capi::BridgeFunctionValue* AsFFI();
    inline static const ecitygml::BridgeFunctionValue* FromFFI(const ecitygml::capi::BridgeFunctionValue* ptr);
    inline static ecitygml::BridgeFunctionValue* FromFFI(ecitygml::capi::BridgeFunctionValue* ptr);
    inline static void operator delete(void* ptr);
private:
    BridgeFunctionValue() = delete;
    BridgeFunctionValue(const ecitygml::BridgeFunctionValue&) = delete;
    BridgeFunctionValue(ecitygml::BridgeFunctionValue&&) noexcept = delete;
    BridgeFunctionValue operator=(const ecitygml::BridgeFunctionValue&) = delete;
    BridgeFunctionValue operator=(ecitygml::BridgeFunctionValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_BridgeFunctionValue_D_HPP
