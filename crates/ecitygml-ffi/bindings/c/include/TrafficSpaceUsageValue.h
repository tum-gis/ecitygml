#ifndef TrafficSpaceUsageValue_H
#define TrafficSpaceUsageValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "TrafficSpaceUsageValue.d.h"






const Code* ecitygml_TrafficSpaceUsageValue_code(const TrafficSpaceUsageValue* self);

DiplomatStringView ecitygml_TrafficSpaceUsageValue_value(const TrafficSpaceUsageValue* self);

void ecitygml_TrafficSpaceUsageValue_destroy(TrafficSpaceUsageValue* self);





#endif // TrafficSpaceUsageValue_H
