#ifndef PlantCoverFunctionValueIterator_H
#define PlantCoverFunctionValueIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "PlantCoverFunctionValue.d.h"

#include "PlantCoverFunctionValueIterator.d.h"






const PlantCoverFunctionValue* ecitygml_PlantCoverFunctionValueIterator_next(PlantCoverFunctionValueIterator* self);

void ecitygml_PlantCoverFunctionValueIterator_destroy(PlantCoverFunctionValueIterator* self);





#endif // PlantCoverFunctionValueIterator_H
