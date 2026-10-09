#ifndef BuildingSubdivisionFunctionValueIterator_H
#define BuildingSubdivisionFunctionValueIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "BuildingSubdivisionFunctionValue.d.h"

#include "BuildingSubdivisionFunctionValueIterator.d.h"






const BuildingSubdivisionFunctionValue* ecitygml_BuildingSubdivisionFunctionValueIterator_next(BuildingSubdivisionFunctionValueIterator* self);

void ecitygml_BuildingSubdivisionFunctionValueIterator_destroy(BuildingSubdivisionFunctionValueIterator* self);





#endif // BuildingSubdivisionFunctionValueIterator_H
