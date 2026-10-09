#ifndef DateTime_H
#define DateTime_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Error.d.h"

#include "DateTime.d.h"






typedef struct ecitygml_DateTime_from_parts_result {union {DateTime* ok; Error* err;}; bool is_ok;} ecitygml_DateTime_from_parts_result;
ecitygml_DateTime_from_parts_result ecitygml_DateTime_from_parts(int32_t year, uint32_t month, uint32_t day, uint32_t hour, uint32_t minute, uint32_t second, uint32_t nanosecond, int32_t offset_seconds);

int32_t ecitygml_DateTime_year(const DateTime* self);

uint32_t ecitygml_DateTime_month(const DateTime* self);

uint32_t ecitygml_DateTime_day(const DateTime* self);

uint32_t ecitygml_DateTime_hour(const DateTime* self);

uint32_t ecitygml_DateTime_minute(const DateTime* self);

uint32_t ecitygml_DateTime_second(const DateTime* self);

uint32_t ecitygml_DateTime_nanosecond(const DateTime* self);

int32_t ecitygml_DateTime_offset_seconds(const DateTime* self);

void ecitygml_DateTime_to_rfc3339(const DateTime* self, DiplomatWrite* write);

int64_t ecitygml_DateTime_timestamp(const DateTime* self);

uint32_t ecitygml_DateTime_timestamp_subsec_nanos(const DateTime* self);

void ecitygml_DateTime_destroy(DateTime* self);





#endif // DateTime_H
