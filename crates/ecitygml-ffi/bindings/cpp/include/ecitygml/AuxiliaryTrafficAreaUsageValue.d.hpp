#ifndef ecitygml_AuxiliaryTrafficAreaUsageValue_D_HPP
#define ecitygml_AuxiliaryTrafficAreaUsageValue_D_HPP

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
    struct AuxiliaryTrafficAreaUsageValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `usage` property of an AuxiliaryTrafficArea.
 */
class AuxiliaryTrafficAreaUsageValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AuxiliaryTrafficAreaUsageValue* AsFFI() const;
    inline ecitygml::capi::AuxiliaryTrafficAreaUsageValue* AsFFI();
    inline static const ecitygml::AuxiliaryTrafficAreaUsageValue* FromFFI(const ecitygml::capi::AuxiliaryTrafficAreaUsageValue* ptr);
    inline static ecitygml::AuxiliaryTrafficAreaUsageValue* FromFFI(ecitygml::capi::AuxiliaryTrafficAreaUsageValue* ptr);
    inline static void operator delete(void* ptr);
private:
    AuxiliaryTrafficAreaUsageValue() = delete;
    AuxiliaryTrafficAreaUsageValue(const ecitygml::AuxiliaryTrafficAreaUsageValue&) = delete;
    AuxiliaryTrafficAreaUsageValue(ecitygml::AuxiliaryTrafficAreaUsageValue&&) noexcept = delete;
    AuxiliaryTrafficAreaUsageValue operator=(const ecitygml::AuxiliaryTrafficAreaUsageValue&) = delete;
    AuxiliaryTrafficAreaUsageValue operator=(ecitygml::AuxiliaryTrafficAreaUsageValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_AuxiliaryTrafficAreaUsageValue_D_HPP
