#ifndef TrafficAreaFunctionValueIterator_H
#define TrafficAreaFunctionValueIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "TrafficAreaFunctionValue.d.h"

#include "TrafficAreaFunctionValueIterator.d.h"






const TrafficAreaFunctionValue* ecitygml_TrafficAreaFunctionValueIterator_next(TrafficAreaFunctionValueIterator* self);

void ecitygml_TrafficAreaFunctionValueIterator_destroy(TrafficAreaFunctionValueIterator* self);





#endif // TrafficAreaFunctionValueIterator_H
