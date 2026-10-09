#ifndef ecitygml_SectionClassValue_D_HPP
#define ecitygml_SectionClassValue_D_HPP

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
    struct SectionClassValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `class` property of a Section.
 */
class SectionClassValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::SectionClassValue* AsFFI() const;
    inline ecitygml::capi::SectionClassValue* AsFFI();
    inline static const ecitygml::SectionClassValue* FromFFI(const ecitygml::capi::SectionClassValue* ptr);
    inline static ecitygml::SectionClassValue* FromFFI(ecitygml::capi::SectionClassValue* ptr);
    inline static void operator delete(void* ptr);
private:
    SectionClassValue() = delete;
    SectionClassValue(const ecitygml::SectionClassValue&) = delete;
    SectionClassValue(ecitygml::SectionClassValue&&) noexcept = delete;
    SectionClassValue operator=(const ecitygml::SectionClassValue&) = delete;
    SectionClassValue operator=(ecitygml::SectionClassValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_SectionClassValue_D_HPP
