#ifndef BuildingUsageValue_H
#define BuildingUsageValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "BuildingUsageValue.d.h"






const Code* ecitygml_BuildingUsageValue_code(const BuildingUsageValue* self);

DiplomatStringView ecitygml_BuildingUsageValue_value(const BuildingUsageValue* self);

void ecitygml_BuildingUsageValue_destroy(BuildingUsageValue* self);





#endif // BuildingUsageValue_H
