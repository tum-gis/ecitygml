#ifndef ECITYGML_Code_D_HPP
#define ECITYGML_Code_D_HPP

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
namespace capi {
    struct Code;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A code-list value with an optional code space, borrowed from a city model.
 */
class Code {
public:

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

  inline std::optional<std::string_view> code_space() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::Code* AsFFI() const;
    inline ecitygml::capi::Code* AsFFI();
    inline static const ecitygml::Code* FromFFI(const ecitygml::capi::Code* ptr);
    inline static ecitygml::Code* FromFFI(ecitygml::capi::Code* ptr);
    inline static void operator delete(void* ptr);
private:
    Code() = delete;
    Code(const ecitygml::Code&) = delete;
    Code(ecitygml::Code&&) noexcept = delete;
    Code operator=(const ecitygml::Code&) = delete;
    Code operator=(ecitygml::Code&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_Code_D_HPP
