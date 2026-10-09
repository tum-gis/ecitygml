#ifndef Occupancy_H
#define Occupancy_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "IntervalValue.d.h"
#include "OccupantTypeValue.d.h"

#include "Occupancy.d.h"






int64_t ecitygml_Occupancy_number_of_occupants(const Occupancy* self);

const IntervalValue* ecitygml_Occupancy_interval(const Occupancy* self);

const OccupantTypeValue* ecitygml_Occupancy_occupant_type(const Occupancy* self);

void ecitygml_Occupancy_destroy(Occupancy* self);





#endif // Occupancy_H
