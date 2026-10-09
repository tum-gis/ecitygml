#ifndef RoadUsageValue_H
#define RoadUsageValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "RoadUsageValue.d.h"






const Code* ecitygml_RoadUsageValue_code(const RoadUsageValue* self);

DiplomatStringView ecitygml_RoadUsageValue_value(const RoadUsageValue* self);

void ecitygml_RoadUsageValue_destroy(RoadUsageValue* self);





#endif // RoadUsageValue_H
