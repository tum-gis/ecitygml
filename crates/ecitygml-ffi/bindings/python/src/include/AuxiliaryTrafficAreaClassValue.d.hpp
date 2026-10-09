#ifndef ECITYGML_AuxiliaryTrafficAreaClassValue_D_HPP
#define ECITYGML_AuxiliaryTrafficAreaClassValue_D_HPP

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
    struct AuxiliaryTrafficAreaClassValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `class` property of an AuxiliaryTrafficArea.
 */
class AuxiliaryTrafficAreaClassValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AuxiliaryTrafficAreaClassValue* AsFFI() const;
    inline ecitygml::capi::AuxiliaryTrafficAreaClassValue* AsFFI();
    inline static const ecitygml::AuxiliaryTrafficAreaClassValue* FromFFI(const ecitygml::capi::AuxiliaryTrafficAreaClassValue* ptr);
    inline static ecitygml::AuxiliaryTrafficAreaClassValue* FromFFI(ecitygml::capi::AuxiliaryTrafficAreaClassValue* ptr);
    inline static void operator delete(void* ptr);
private:
    AuxiliaryTrafficAreaClassValue() = delete;
    AuxiliaryTrafficAreaClassValue(const ecitygml::AuxiliaryTrafficAreaClassValue&) = delete;
    AuxiliaryTrafficAreaClassValue(ecitygml::AuxiliaryTrafficAreaClassValue&&) noexcept = delete;
    AuxiliaryTrafficAreaClassValue operator=(const ecitygml::AuxiliaryTrafficAreaClassValue&) = delete;
    AuxiliaryTrafficAreaClassValue operator=(ecitygml::AuxiliaryTrafficAreaClassValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_AuxiliaryTrafficAreaClassValue_D_HPP
