#ifndef StringAttribute_H
#define StringAttribute_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"


#include "StringAttribute.d.h"






DiplomatStringView ecitygml_StringAttribute_name(const StringAttribute* self);

DiplomatStringView ecitygml_StringAttribute_value(const StringAttribute* self);

void ecitygml_StringAttribute_destroy(StringAttribute* self);





#endif // StringAttribute_H
