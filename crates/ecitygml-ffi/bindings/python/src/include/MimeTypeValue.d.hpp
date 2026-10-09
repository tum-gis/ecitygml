#ifndef ECITYGML_MimeTypeValue_D_HPP
#define ECITYGML_MimeTypeValue_D_HPP

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
    struct MimeTypeValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `mimeType` property of an ImplicitGeometry.
 */
class MimeTypeValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::MimeTypeValue* AsFFI() const;
    inline ecitygml::capi::MimeTypeValue* AsFFI();
    inline static const ecitygml::MimeTypeValue* FromFFI(const ecitygml::capi::MimeTypeValue* ptr);
    inline static ecitygml::MimeTypeValue* FromFFI(ecitygml::capi::MimeTypeValue* ptr);
    inline static void operator delete(void* ptr);
private:
    MimeTypeValue() = delete;
    MimeTypeValue(const ecitygml::MimeTypeValue&) = delete;
    MimeTypeValue(ecitygml::MimeTypeValue&&) noexcept = delete;
    MimeTypeValue operator=(const ecitygml::MimeTypeValue&) = delete;
    MimeTypeValue operator=(ecitygml::MimeTypeValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_MimeTypeValue_D_HPP
