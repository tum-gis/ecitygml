#ifndef ECITYGML_DateTime_D_HPP
#define ECITYGML_DateTime_D_HPP

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
namespace capi { struct DateTime; }
class DateTime;
namespace capi { struct Error; }
class Error;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct DateTime;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A date and time of day with a timezone, created or borrowed from a city model.
 */
class DateTime {
public:

  /**
   * Creates a date-time from its local fields and the offset east of UTC in seconds; fails with
   * `InvalidArgument` for invalid fields or offsets.
   */
  inline static ecitygml::diplomat::result<std::unique_ptr<ecitygml::DateTime>, std::unique_ptr<ecitygml::Error>> from_parts(int32_t year, uint32_t month, uint32_t day, uint32_t hour, uint32_t minute, uint32_t second, uint32_t nanosecond, int32_t offset_seconds);

  inline int32_t year() const;

  /**
   * 1 to 12.
   */
  inline uint32_t month() const;

  /**
   * 1 to 31.
   */
  inline uint32_t day() const;

  inline uint32_t hour() const;

  inline uint32_t minute() const;

  inline uint32_t second() const;

  inline uint32_t nanosecond() const;

  /**
   * The UTC offset in seconds (local time minus UTC), e.g. 3600 for `+01:00`.
   */
  inline int32_t offset_seconds() const;

  /**
   * RFC 3339 / ISO 8601 representation, e.g. `2017-01-23T00:00:00+01:00` (via `as_chrono()`;
   * egml has no lexical form yet).
   */
  inline std::string to_rfc3339() const;
  template<typename W>
  inline void to_rfc3339_write(W& writeable_output) const;

  /**
   * Seconds since the Unix epoch (1970-01-01T00:00:00Z) (via `as_chrono()`).
   */
  inline int64_t timestamp() const;

  /**
   * Nanoseconds beyond the full seconds of `timestamp` (via `as_chrono()`).
   */
  inline uint32_t timestamp_subsec_nanos() const;

    inline const ecitygml::capi::DateTime* AsFFI() const;
    inline ecitygml::capi::DateTime* AsFFI();
    inline static const ecitygml::DateTime* FromFFI(const ecitygml::capi::DateTime* ptr);
    inline static ecitygml::DateTime* FromFFI(ecitygml::capi::DateTime* ptr);
    inline static void operator delete(void* ptr);
private:
    DateTime() = delete;
    DateTime(const ecitygml::DateTime&) = delete;
    DateTime(ecitygml::DateTime&&) noexcept = delete;
    DateTime operator=(const ecitygml::DateTime&) = delete;
    DateTime operator=(ecitygml::DateTime&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_DateTime_D_HPP
