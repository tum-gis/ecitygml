#ifndef DoubleAttribute_H
#define DoubleAttribute_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"


#include "DoubleAttribute.d.h"






DiplomatStringView ecitygml_DoubleAttribute_name(const DoubleAttribute* self);

double ecitygml_DoubleAttribute_value(const DoubleAttribute* self);

void ecitygml_DoubleAttribute_destroy(DoubleAttribute* self);





#endif // DoubleAttribute_H
