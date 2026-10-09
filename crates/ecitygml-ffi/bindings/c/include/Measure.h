#ifndef Measure_H
#define Measure_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"


#include "Measure.d.h"






double ecitygml_Measure_value(const Measure* self);

DiplomatStringView ecitygml_Measure_uom(const Measure* self);

void ecitygml_Measure_destroy(Measure* self);





#endif // Measure_H
