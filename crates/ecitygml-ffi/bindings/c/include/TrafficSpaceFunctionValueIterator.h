#ifndef TrafficSpaceFunctionValueIterator_H
#define TrafficSpaceFunctionValueIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "TrafficSpaceFunctionValue.d.h"

#include "TrafficSpaceFunctionValueIterator.d.h"






const TrafficSpaceFunctionValue* ecitygml_TrafficSpaceFunctionValueIterator_next(TrafficSpaceFunctionValueIterator* self);

void ecitygml_TrafficSpaceFunctionValueIterator_destroy(TrafficSpaceFunctionValueIterator* self);





#endif // TrafficSpaceFunctionValueIterator_H
