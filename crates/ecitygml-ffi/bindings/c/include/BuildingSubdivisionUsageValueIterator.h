#ifndef BuildingSubdivisionUsageValueIterator_H
#define BuildingSubdivisionUsageValueIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "BuildingSubdivisionUsageValue.d.h"

#include "BuildingSubdivisionUsageValueIterator.d.h"






const BuildingSubdivisionUsageValue* ecitygml_BuildingSubdivisionUsageValueIterator_next(BuildingSubdivisionUsageValueIterator* self);

void ecitygml_BuildingSubdivisionUsageValueIterator_destroy(BuildingSubdivisionUsageValueIterator* self);





#endif // BuildingSubdivisionUsageValueIterator_H
