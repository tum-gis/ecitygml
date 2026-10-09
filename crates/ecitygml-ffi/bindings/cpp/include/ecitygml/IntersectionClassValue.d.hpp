#ifndef ecitygml_IntersectionClassValue_D_HPP
#define ecitygml_IntersectionClassValue_D_HPP

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
    struct IntersectionClassValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `class` property of an Intersection.
 */
class IntersectionClassValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::IntersectionClassValue* AsFFI() const;
    inline ecitygml::capi::IntersectionClassValue* AsFFI();
    inline static const ecitygml::IntersectionClassValue* FromFFI(const ecitygml::capi::IntersectionClassValue* ptr);
    inline static ecitygml::IntersectionClassValue* FromFFI(ecitygml::capi::IntersectionClassValue* ptr);
    inline static void operator delete(void* ptr);
private:
    IntersectionClassValue() = delete;
    IntersectionClassValue(const ecitygml::IntersectionClassValue&) = delete;
    IntersectionClassValue(ecitygml::IntersectionClassValue&&) noexcept = delete;
    IntersectionClassValue operator=(const ecitygml::IntersectionClassValue&) = delete;
    IntersectionClassValue operator=(ecitygml::IntersectionClassValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_IntersectionClassValue_D_HPP
