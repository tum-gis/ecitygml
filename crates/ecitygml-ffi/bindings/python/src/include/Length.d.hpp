#ifndef ECITYGML_Length_D_HPP
#define ECITYGML_Length_D_HPP

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
    struct Length;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A length with its unit of measure, borrowed from a city model.
 */
class Length {
public:

  inline double value() const;

  /**
   * Unit of measure (`uom`), e.g. `m`.
   */
  inline std::string_view uom() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::Length* AsFFI() const;
    inline ecitygml::capi::Length* AsFFI();
    inline static const ecitygml::Length* FromFFI(const ecitygml::capi::Length* ptr);
    inline static ecitygml::Length* FromFFI(ecitygml::capi::Length* ptr);
    inline static void operator delete(void* ptr);
private:
    Length() = delete;
    Length(const ecitygml::Length&) = delete;
    Length(ecitygml::Length&&) noexcept = delete;
    Length operator=(const ecitygml::Length&) = delete;
    Length operator=(ecitygml::Length&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_Length_D_HPP
