#ifndef BuildingUsageValueIterator_H
#define BuildingUsageValueIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "BuildingUsageValue.d.h"

#include "BuildingUsageValueIterator.d.h"






const BuildingUsageValue* ecitygml_BuildingUsageValueIterator_next(BuildingUsageValueIterator* self);

void ecitygml_BuildingUsageValueIterator_destroy(BuildingUsageValueIterator* self);





#endif // BuildingUsageValueIterator_H
