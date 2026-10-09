#ifndef ECITYGML_Date_D_HPP
#define ECITYGML_Date_D_HPP

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
namespace capi { struct Date; }
class Date;
namespace capi { struct DateTime; }
class DateTime;
namespace capi { struct Error; }
class Error;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct Date;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A calendar date with a timezone, created or borrowed from a city model.
 */
class Date {
public:

  /**
   * Creates a date from its fields and the offset east of UTC in seconds; fails with
   * `InvalidArgument` for invalid fields or offsets.
   */
  inline static ecitygml::diplomat::result<std::unique_ptr<ecitygml::Date>, std::unique_ptr<ecitygml::Error>> from_parts(int32_t year, uint32_t month, uint32_t day, int32_t offset_seconds);

  inline int32_t year() const;

  /**
   * 1 to 12.
   */
  inline uint32_t month() const;

  /**
   * 1 to 31.
   */
  inline uint32_t day() const;

  /**
   * The UTC offset in seconds (local time minus UTC).
   */
  inline int32_t offset_seconds() const;

  /**
   * Midnight at the start of the date, in the date's timezone.
   */
  inline std::unique_ptr<ecitygml::DateTime> start_of_day() const;

    inline const ecitygml::capi::Date* AsFFI() const;
    inline ecitygml::capi::Date* AsFFI();
    inline static const ecitygml::Date* FromFFI(const ecitygml::capi::Date* ptr);
    inline static ecitygml::Date* FromFFI(ecitygml::capi::Date* ptr);
    inline static void operator delete(void* ptr);
private:
    Date() = delete;
    Date(const ecitygml::Date&) = delete;
    Date(ecitygml::Date&&) noexcept = delete;
    Date operator=(const ecitygml::Date&) = delete;
    Date operator=(ecitygml::Date&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_Date_D_HPP
