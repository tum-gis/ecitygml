#ifndef ecitygml_MarkingClassValue_D_HPP
#define ecitygml_MarkingClassValue_D_HPP

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
    struct MarkingClassValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `class` property of a Marking.
 */
class MarkingClassValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::MarkingClassValue* AsFFI() const;
    inline ecitygml::capi::MarkingClassValue* AsFFI();
    inline static const ecitygml::MarkingClassValue* FromFFI(const ecitygml::capi::MarkingClassValue* ptr);
    inline static ecitygml::MarkingClassValue* FromFFI(ecitygml::capi::MarkingClassValue* ptr);
    inline static void operator delete(void* ptr);
private:
    MarkingClassValue() = delete;
    MarkingClassValue(const ecitygml::MarkingClassValue&) = delete;
    MarkingClassValue(ecitygml::MarkingClassValue&&) noexcept = delete;
    MarkingClassValue operator=(const ecitygml::MarkingClassValue&) = delete;
    MarkingClassValue operator=(ecitygml::MarkingClassValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_MarkingClassValue_D_HPP
