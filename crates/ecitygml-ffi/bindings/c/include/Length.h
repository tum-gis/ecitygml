#ifndef Length_H
#define Length_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"


#include "Length.d.h"






double ecitygml_Length_value(const Length* self);

DiplomatStringView ecitygml_Length_uom(const Length* self);

void ecitygml_Length_destroy(Length* self);





#endif // Length_H
