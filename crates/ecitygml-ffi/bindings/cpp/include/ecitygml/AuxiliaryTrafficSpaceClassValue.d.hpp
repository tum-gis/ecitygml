#ifndef ecitygml_AuxiliaryTrafficSpaceClassValue_D_HPP
#define ecitygml_AuxiliaryTrafficSpaceClassValue_D_HPP

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
    struct AuxiliaryTrafficSpaceClassValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `class` property of an AuxiliaryTrafficSpace.
 */
class AuxiliaryTrafficSpaceClassValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AuxiliaryTrafficSpaceClassValue* AsFFI() const;
    inline ecitygml::capi::AuxiliaryTrafficSpaceClassValue* AsFFI();
    inline static const ecitygml::AuxiliaryTrafficSpaceClassValue* FromFFI(const ecitygml::capi::AuxiliaryTrafficSpaceClassValue* ptr);
    inline static ecitygml::AuxiliaryTrafficSpaceClassValue* FromFFI(ecitygml::capi::AuxiliaryTrafficSpaceClassValue* ptr);
    inline static void operator delete(void* ptr);
private:
    AuxiliaryTrafficSpaceClassValue() = delete;
    AuxiliaryTrafficSpaceClassValue(const ecitygml::AuxiliaryTrafficSpaceClassValue&) = delete;
    AuxiliaryTrafficSpaceClassValue(ecitygml::AuxiliaryTrafficSpaceClassValue&&) noexcept = delete;
    AuxiliaryTrafficSpaceClassValue operator=(const ecitygml::AuxiliaryTrafficSpaceClassValue&) = delete;
    AuxiliaryTrafficSpaceClassValue operator=(ecitygml::AuxiliaryTrafficSpaceClassValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_AuxiliaryTrafficSpaceClassValue_D_HPP
