#ifndef ECITYGML_DateTime_HPP
#define ECITYGML_DateTime_HPP

#include "DateTime.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "Error.hpp"
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    typedef struct ecitygml_DateTime_from_parts_result {union {ecitygml::capi::DateTime* ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_DateTime_from_parts_result;
    ecitygml_DateTime_from_parts_result ecitygml_DateTime_from_parts(int32_t year, uint32_t month, uint32_t day, uint32_t hour, uint32_t minute, uint32_t second, uint32_t nanosecond, int32_t offset_seconds);

    int32_t ecitygml_DateTime_year(const ecitygml::capi::DateTime* self);

    uint32_t ecitygml_DateTime_month(const ecitygml::capi::DateTime* self);

    uint32_t ecitygml_DateTime_day(const ecitygml::capi::DateTime* self);

    uint32_t ecitygml_DateTime_hour(const ecitygml::capi::DateTime* self);

    uint32_t ecitygml_DateTime_minute(const ecitygml::capi::DateTime* self);

    uint32_t ecitygml_DateTime_second(const ecitygml::capi::DateTime* self);

    uint32_t ecitygml_DateTime_nanosecond(const ecitygml::capi::DateTime* self);

    int32_t ecitygml_DateTime_offset_seconds(const ecitygml::capi::DateTime* self);

    void ecitygml_DateTime_to_rfc3339(const ecitygml::capi::DateTime* self, ecitygml::diplomat::capi::DiplomatWrite* write);

    int64_t ecitygml_DateTime_timestamp(const ecitygml::capi::DateTime* self);

    uint32_t ecitygml_DateTime_timestamp_subsec_nanos(const ecitygml::capi::DateTime* self);

    void ecitygml_DateTime_destroy(DateTime* self);

    } // extern "C"
} // namespace capi
} // namespace

inline ecitygml::diplomat::result<std::unique_ptr<ecitygml::DateTime>, std::unique_ptr<ecitygml::Error>> ecitygml::DateTime::from_parts(int32_t year, uint32_t month, uint32_t day, uint32_t hour, uint32_t minute, uint32_t second, uint32_t nanosecond, int32_t offset_seconds) {
    auto result = ecitygml::capi::ecitygml_DateTime_from_parts(year,
        month,
        day,
        hour,
        minute,
        second,
        nanosecond,
        offset_seconds);
    return result.is_ok ? ecitygml::diplomat::result<std::unique_ptr<ecitygml::DateTime>, std::unique_ptr<ecitygml::Error>>(ecitygml::diplomat::Ok<std::unique_ptr<ecitygml::DateTime>>(std::unique_ptr<ecitygml::DateTime>(ecitygml::DateTime::FromFFI(result.ok)))) : ecitygml::diplomat::result<std::unique_ptr<ecitygml::DateTime>, std::unique_ptr<ecitygml::Error>>(ecitygml::diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline int32_t ecitygml::DateTime::year() const {
    auto result = ecitygml::capi::ecitygml_DateTime_year(this->AsFFI());
    return result;
}

inline uint32_t ecitygml::DateTime::month() const {
    auto result = ecitygml::capi::ecitygml_DateTime_month(this->AsFFI());
    return result;
}

inline uint32_t ecitygml::DateTime::day() const {
    auto result = ecitygml::capi::ecitygml_DateTime_day(this->AsFFI());
    return result;
}

inline uint32_t ecitygml::DateTime::hour() const {
    auto result = ecitygml::capi::ecitygml_DateTime_hour(this->AsFFI());
    return result;
}

inline uint32_t ecitygml::DateTime::minute() const {
    auto result = ecitygml::capi::ecitygml_DateTime_minute(this->AsFFI());
    return result;
}

inline uint32_t ecitygml::DateTime::second() const {
    auto result = ecitygml::capi::ecitygml_DateTime_second(this->AsFFI());
    return result;
}

inline uint32_t ecitygml::DateTime::nanosecond() const {
    auto result = ecitygml::capi::ecitygml_DateTime_nanosecond(this->AsFFI());
    return result;
}

inline int32_t ecitygml::DateTime::offset_seconds() const {
    auto result = ecitygml::capi::ecitygml_DateTime_offset_seconds(this->AsFFI());
    return result;
}

inline std::string ecitygml::DateTime::to_rfc3339() const {
    std::string output;
    ecitygml::diplomat::capi::DiplomatWrite write = ecitygml::diplomat::WriteFromString(output);
    ecitygml::capi::ecitygml_DateTime_to_rfc3339(this->AsFFI(),
        &write);
    return output;
}
template<typename W>
inline void ecitygml::DateTime::to_rfc3339_write(W& writeable) const {
    ecitygml::diplomat::capi::DiplomatWrite write = ecitygml::diplomat::WriteTrait<W>::Construct(writeable);
    ecitygml::capi::ecitygml_DateTime_to_rfc3339(this->AsFFI(),
        &write);
}

inline int64_t ecitygml::DateTime::timestamp() const {
    auto result = ecitygml::capi::ecitygml_DateTime_timestamp(this->AsFFI());
    return result;
}

inline uint32_t ecitygml::DateTime::timestamp_subsec_nanos() const {
    auto result = ecitygml::capi::ecitygml_DateTime_timestamp_subsec_nanos(this->AsFFI());
    return result;
}

inline const ecitygml::capi::DateTime* ecitygml::DateTime::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::DateTime*>(this);
}

inline ecitygml::capi::DateTime* ecitygml::DateTime::AsFFI() {
    return reinterpret_cast<ecitygml::capi::DateTime*>(this);
}

inline const ecitygml::DateTime* ecitygml::DateTime::FromFFI(const ecitygml::capi::DateTime* ptr) {
    return reinterpret_cast<const ecitygml::DateTime*>(ptr);
}

inline ecitygml::DateTime* ecitygml::DateTime::FromFFI(ecitygml::capi::DateTime* ptr) {
    return reinterpret_cast<ecitygml::DateTime*>(ptr);
}

inline void ecitygml::DateTime::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_DateTime_destroy(reinterpret_cast<ecitygml::capi::DateTime*>(ptr));
}


#endif // ECITYGML_DateTime_HPP
