#ifndef ECITYGML_Measure_D_HPP
#define ECITYGML_Measure_D_HPP

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
    struct Measure;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A numeric value with its unit of measure, borrowed from a city model.
 */
class Measure {
public:

  inline double value() const;

  /**
   * Unit of measure (`uom`), e.g. `m2`.
   */
  inline std::string_view uom() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::Measure* AsFFI() const;
    inline ecitygml::capi::Measure* AsFFI();
    inline static const ecitygml::Measure* FromFFI(const ecitygml::capi::Measure* ptr);
    inline static ecitygml::Measure* FromFFI(ecitygml::capi::Measure* ptr);
    inline static void operator delete(void* ptr);
private:
    Measure() = delete;
    Measure(const ecitygml::Measure&) = delete;
    Measure(ecitygml::Measure&&) noexcept = delete;
    Measure operator=(const ecitygml::Measure&) = delete;
    Measure operator=(ecitygml::Measure&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_Measure_D_HPP
