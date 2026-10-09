#ifndef BuildingFunctionValueIterator_H
#define BuildingFunctionValueIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "BuildingFunctionValue.d.h"

#include "BuildingFunctionValueIterator.d.h"






const BuildingFunctionValue* ecitygml_BuildingFunctionValueIterator_next(BuildingFunctionValueIterator* self);

void ecitygml_BuildingFunctionValueIterator_destroy(BuildingFunctionValueIterator* self);





#endif // BuildingFunctionValueIterator_H
