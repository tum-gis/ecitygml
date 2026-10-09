#ifndef Id_H
#define Id_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"


#include "Id.d.h"






DiplomatStringView ecitygml_Id_as_str(const Id* self);

void ecitygml_Id_destroy(Id* self);





#endif // Id_H
