#ifndef ecitygml_AuxiliaryTrafficSpaceUsageValue_D_HPP
#define ecitygml_AuxiliaryTrafficSpaceUsageValue_D_HPP

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
    struct AuxiliaryTrafficSpaceUsageValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `usage` property of an AuxiliaryTrafficSpace.
 */
class AuxiliaryTrafficSpaceUsageValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AuxiliaryTrafficSpaceUsageValue* AsFFI() const;
    inline ecitygml::capi::AuxiliaryTrafficSpaceUsageValue* AsFFI();
    inline static const ecitygml::AuxiliaryTrafficSpaceUsageValue* FromFFI(const ecitygml::capi::AuxiliaryTrafficSpaceUsageValue* ptr);
    inline static ecitygml::AuxiliaryTrafficSpaceUsageValue* FromFFI(ecitygml::capi::AuxiliaryTrafficSpaceUsageValue* ptr);
    inline static void operator delete(void* ptr);
private:
    AuxiliaryTrafficSpaceUsageValue() = delete;
    AuxiliaryTrafficSpaceUsageValue(const ecitygml::AuxiliaryTrafficSpaceUsageValue&) = delete;
    AuxiliaryTrafficSpaceUsageValue(ecitygml::AuxiliaryTrafficSpaceUsageValue&&) noexcept = delete;
    AuxiliaryTrafficSpaceUsageValue operator=(const ecitygml::AuxiliaryTrafficSpaceUsageValue&) = delete;
    AuxiliaryTrafficSpaceUsageValue operator=(ecitygml::AuxiliaryTrafficSpaceUsageValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_AuxiliaryTrafficSpaceUsageValue_D_HPP
