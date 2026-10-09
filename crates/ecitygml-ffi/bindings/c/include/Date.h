#ifndef Date_H
#define Date_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "DateTime.d.h"
#include "Error.d.h"

#include "Date.d.h"






typedef struct ecitygml_Date_from_parts_result {union {Date* ok; Error* err;}; bool is_ok;} ecitygml_Date_from_parts_result;
ecitygml_Date_from_parts_result ecitygml_Date_from_parts(int32_t year, uint32_t month, uint32_t day, int32_t offset_seconds);

int32_t ecitygml_Date_year(const Date* self);

uint32_t ecitygml_Date_month(const Date* self);

uint32_t ecitygml_Date_day(const Date* self);

int32_t ecitygml_Date_offset_seconds(const Date* self);

DateTime* ecitygml_Date_start_of_day(const Date* self);

void ecitygml_Date_destroy(Date* self);





#endif // Date_H
