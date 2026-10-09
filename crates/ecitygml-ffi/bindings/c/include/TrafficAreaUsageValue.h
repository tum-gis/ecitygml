#ifndef TrafficAreaUsageValue_H
#define TrafficAreaUsageValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "TrafficAreaUsageValue.d.h"






const Code* ecitygml_TrafficAreaUsageValue_code(const TrafficAreaUsageValue* self);

DiplomatStringView ecitygml_TrafficAreaUsageValue_value(const TrafficAreaUsageValue* self);

void ecitygml_TrafficAreaUsageValue_destroy(TrafficAreaUsageValue* self);





#endif // TrafficAreaUsageValue_H
