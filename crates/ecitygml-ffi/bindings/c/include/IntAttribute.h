#ifndef IntAttribute_H
#define IntAttribute_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"


#include "IntAttribute.d.h"






DiplomatStringView ecitygml_IntAttribute_name(const IntAttribute* self);

int64_t ecitygml_IntAttribute_value(const IntAttribute* self);

void ecitygml_IntAttribute_destroy(IntAttribute* self);





#endif // IntAttribute_H
