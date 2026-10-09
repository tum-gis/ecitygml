#ifndef ecitygml_Date_HPP
#define ecitygml_Date_HPP

#include "Date.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"
#include "DateTime.hpp"
#include "Error.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    typedef struct ecitygml_Date_from_parts_result {union {ecitygml::capi::Date* ok; ecitygml::capi::Error* err;}; bool is_ok;} ecitygml_Date_from_parts_result;
    ecitygml_Date_from_parts_result ecitygml_Date_from_parts(int32_t year, uint32_t month, uint32_t day, int32_t offset_seconds);

    int32_t ecitygml_Date_year(const ecitygml::capi::Date* self);

    uint32_t ecitygml_Date_month(const ecitygml::capi::Date* self);

    uint32_t ecitygml_Date_day(const ecitygml::capi::Date* self);

    int32_t ecitygml_Date_offset_seconds(const ecitygml::capi::Date* self);

    ecitygml::capi::DateTime* ecitygml_Date_start_of_day(const ecitygml::capi::Date* self);

    void ecitygml_Date_destroy(Date* self);

    } // extern "C"
} // namespace capi
} // namespace

inline diplomat::result<std::unique_ptr<ecitygml::Date>, std::unique_ptr<ecitygml::Error>> ecitygml::Date::from_parts(int32_t year, uint32_t month, uint32_t day, int32_t offset_seconds) {
    auto result = ecitygml::capi::ecitygml_Date_from_parts(year,
        month,
        day,
        offset_seconds);
    return result.is_ok ? diplomat::result<std::unique_ptr<ecitygml::Date>, std::unique_ptr<ecitygml::Error>>(diplomat::Ok<std::unique_ptr<ecitygml::Date>>(std::unique_ptr<ecitygml::Date>(ecitygml::Date::FromFFI(result.ok)))) : diplomat::result<std::unique_ptr<ecitygml::Date>, std::unique_ptr<ecitygml::Error>>(diplomat::Err<std::unique_ptr<ecitygml::Error>>(std::unique_ptr<ecitygml::Error>(ecitygml::Error::FromFFI(result.err))));
}

inline int32_t ecitygml::Date::year() const {
    auto result = ecitygml::capi::ecitygml_Date_year(this->AsFFI());
    return result;
}

inline uint32_t ecitygml::Date::month() const {
    auto result = ecitygml::capi::ecitygml_Date_month(this->AsFFI());
    return result;
}

inline uint32_t ecitygml::Date::day() const {
    auto result = ecitygml::capi::ecitygml_Date_day(this->AsFFI());
    return result;
}

inline int32_t ecitygml::Date::offset_seconds() const {
    auto result = ecitygml::capi::ecitygml_Date_offset_seconds(this->AsFFI());
    return result;
}

inline std::unique_ptr<ecitygml::DateTime> ecitygml::Date::start_of_day() const {
    auto result = ecitygml::capi::ecitygml_Date_start_of_day(this->AsFFI());
    return std::unique_ptr<ecitygml::DateTime>(ecitygml::DateTime::FromFFI(result));
}

inline const ecitygml::capi::Date* ecitygml::Date::AsFFI() const {
    return reinterpret_cast<const ecitygml::capi::Date*>(this);
}

inline ecitygml::capi::Date* ecitygml::Date::AsFFI() {
    return reinterpret_cast<ecitygml::capi::Date*>(this);
}

inline const ecitygml::Date* ecitygml::Date::FromFFI(const ecitygml::capi::Date* ptr) {
    return reinterpret_cast<const ecitygml::Date*>(ptr);
}

inline ecitygml::Date* ecitygml::Date::FromFFI(ecitygml::capi::Date* ptr) {
    return reinterpret_cast<ecitygml::Date*>(ptr);
}

inline void ecitygml::Date::operator delete(void* ptr) {
    ecitygml::capi::ecitygml_Date_destroy(reinterpret_cast<ecitygml::capi::Date*>(ptr));
}


#endif // ecitygml_Date_HPP
