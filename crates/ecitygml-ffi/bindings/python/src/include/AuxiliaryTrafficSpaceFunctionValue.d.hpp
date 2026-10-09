#ifndef ECITYGML_AuxiliaryTrafficSpaceFunctionValue_D_HPP
#define ECITYGML_AuxiliaryTrafficSpaceFunctionValue_D_HPP

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
    struct AuxiliaryTrafficSpaceFunctionValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `function` property of an AuxiliaryTrafficSpace.
 */
class AuxiliaryTrafficSpaceFunctionValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AuxiliaryTrafficSpaceFunctionValue* AsFFI() const;
    inline ecitygml::capi::AuxiliaryTrafficSpaceFunctionValue* AsFFI();
    inline static const ecitygml::AuxiliaryTrafficSpaceFunctionValue* FromFFI(const ecitygml::capi::AuxiliaryTrafficSpaceFunctionValue* ptr);
    inline static ecitygml::AuxiliaryTrafficSpaceFunctionValue* FromFFI(ecitygml::capi::AuxiliaryTrafficSpaceFunctionValue* ptr);
    inline static void operator delete(void* ptr);
private:
    AuxiliaryTrafficSpaceFunctionValue() = delete;
    AuxiliaryTrafficSpaceFunctionValue(const ecitygml::AuxiliaryTrafficSpaceFunctionValue&) = delete;
    AuxiliaryTrafficSpaceFunctionValue(ecitygml::AuxiliaryTrafficSpaceFunctionValue&&) noexcept = delete;
    AuxiliaryTrafficSpaceFunctionValue operator=(const ecitygml::AuxiliaryTrafficSpaceFunctionValue&) = delete;
    AuxiliaryTrafficSpaceFunctionValue operator=(ecitygml::AuxiliaryTrafficSpaceFunctionValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_AuxiliaryTrafficSpaceFunctionValue_D_HPP
