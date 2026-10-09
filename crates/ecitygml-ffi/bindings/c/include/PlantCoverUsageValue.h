#ifndef PlantCoverUsageValue_H
#define PlantCoverUsageValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "PlantCoverUsageValue.d.h"






const Code* ecitygml_PlantCoverUsageValue_code(const PlantCoverUsageValue* self);

DiplomatStringView ecitygml_PlantCoverUsageValue_value(const PlantCoverUsageValue* self);

void ecitygml_PlantCoverUsageValue_destroy(PlantCoverUsageValue* self);





#endif // PlantCoverUsageValue_H
