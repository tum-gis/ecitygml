#ifndef ECITYGML_HoleClassValue_D_HPP
#define ECITYGML_HoleClassValue_D_HPP

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
    struct HoleClassValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `class` property of a Hole.
 */
class HoleClassValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::HoleClassValue* AsFFI() const;
    inline ecitygml::capi::HoleClassValue* AsFFI();
    inline static const ecitygml::HoleClassValue* FromFFI(const ecitygml::capi::HoleClassValue* ptr);
    inline static ecitygml::HoleClassValue* FromFFI(ecitygml::capi::HoleClassValue* ptr);
    inline static void operator delete(void* ptr);
private:
    HoleClassValue() = delete;
    HoleClassValue(const ecitygml::HoleClassValue&) = delete;
    HoleClassValue(ecitygml::HoleClassValue&&) noexcept = delete;
    HoleClassValue operator=(const ecitygml::HoleClassValue&) = delete;
    HoleClassValue operator=(ecitygml::HoleClassValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_HoleClassValue_D_HPP
