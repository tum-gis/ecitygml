#ifndef OccupancyIterator_H
#define OccupancyIterator_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Occupancy.d.h"

#include "OccupancyIterator.d.h"






const Occupancy* ecitygml_OccupancyIterator_next(OccupancyIterator* self);

void ecitygml_OccupancyIterator_destroy(OccupancyIterator* self);





#endif // OccupancyIterator_H
