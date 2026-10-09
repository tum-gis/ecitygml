#ifndef TrafficSpaceUsageValueIterator_H
#define TrafficSpaceUsageValueIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "TrafficSpaceUsageValue.d.h"

#include "TrafficSpaceUsageValueIterator.d.h"






const TrafficSpaceUsageValue* ecitygml_TrafficSpaceUsageValueIterator_next(TrafficSpaceUsageValueIterator* self);

void ecitygml_TrafficSpaceUsageValueIterator_destroy(TrafficSpaceUsageValueIterator* self);





#endif // TrafficSpaceUsageValueIterator_H
