#ifndef PlantCoverUsageValueIterator_H
#define PlantCoverUsageValueIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "PlantCoverUsageValue.d.h"

#include "PlantCoverUsageValueIterator.d.h"






const PlantCoverUsageValue* ecitygml_PlantCoverUsageValueIterator_next(PlantCoverUsageValueIterator* self);

void ecitygml_PlantCoverUsageValueIterator_destroy(PlantCoverUsageValueIterator* self);





#endif // PlantCoverUsageValueIterator_H
