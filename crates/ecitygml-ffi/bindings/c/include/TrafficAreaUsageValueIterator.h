#ifndef TrafficAreaUsageValueIterator_H
#define TrafficAreaUsageValueIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "TrafficAreaUsageValue.d.h"

#include "TrafficAreaUsageValueIterator.d.h"






const TrafficAreaUsageValue* ecitygml_TrafficAreaUsageValueIterator_next(TrafficAreaUsageValueIterator* self);

void ecitygml_TrafficAreaUsageValueIterator_destroy(TrafficAreaUsageValueIterator* self);





#endif // TrafficAreaUsageValueIterator_H
