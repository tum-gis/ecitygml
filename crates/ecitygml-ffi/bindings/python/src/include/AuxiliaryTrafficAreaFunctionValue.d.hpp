#ifndef ECITYGML_AuxiliaryTrafficAreaFunctionValue_D_HPP
#define ECITYGML_AuxiliaryTrafficAreaFunctionValue_D_HPP

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
    struct AuxiliaryTrafficAreaFunctionValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `function` property of an AuxiliaryTrafficArea.
 */
class AuxiliaryTrafficAreaFunctionValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AuxiliaryTrafficAreaFunctionValue* AsFFI() const;
    inline ecitygml::capi::AuxiliaryTrafficAreaFunctionValue* AsFFI();
    inline static const ecitygml::AuxiliaryTrafficAreaFunctionValue* FromFFI(const ecitygml::capi::AuxiliaryTrafficAreaFunctionValue* ptr);
    inline static ecitygml::AuxiliaryTrafficAreaFunctionValue* FromFFI(ecitygml::capi::AuxiliaryTrafficAreaFunctionValue* ptr);
    inline static void operator delete(void* ptr);
private:
    AuxiliaryTrafficAreaFunctionValue() = delete;
    AuxiliaryTrafficAreaFunctionValue(const ecitygml::AuxiliaryTrafficAreaFunctionValue&) = delete;
    AuxiliaryTrafficAreaFunctionValue(ecitygml::AuxiliaryTrafficAreaFunctionValue&&) noexcept = delete;
    AuxiliaryTrafficAreaFunctionValue operator=(const ecitygml::AuxiliaryTrafficAreaFunctionValue&) = delete;
    AuxiliaryTrafficAreaFunctionValue operator=(ecitygml::AuxiliaryTrafficAreaFunctionValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_AuxiliaryTrafficAreaFunctionValue_D_HPP
