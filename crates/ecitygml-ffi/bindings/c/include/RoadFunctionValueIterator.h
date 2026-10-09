#ifndef RoadFunctionValueIterator_H
#define RoadFunctionValueIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "RoadFunctionValue.d.h"

#include "RoadFunctionValueIterator.d.h"






const RoadFunctionValue* ecitygml_RoadFunctionValueIterator_next(RoadFunctionValueIterator* self);

void ecitygml_RoadFunctionValueIterator_destroy(RoadFunctionValueIterator* self);





#endif // RoadFunctionValueIterator_H
