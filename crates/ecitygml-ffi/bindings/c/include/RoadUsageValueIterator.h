#ifndef RoadUsageValueIterator_H
#define RoadUsageValueIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "RoadUsageValue.d.h"

#include "RoadUsageValueIterator.d.h"






const RoadUsageValue* ecitygml_RoadUsageValueIterator_next(RoadUsageValueIterator* self);

void ecitygml_RoadUsageValueIterator_destroy(RoadUsageValueIterator* self);





#endif // RoadUsageValueIterator_H
