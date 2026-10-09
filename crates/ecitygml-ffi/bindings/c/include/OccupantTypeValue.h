#ifndef OccupantTypeValue_H
#define OccupantTypeValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "OccupantTypeValue.d.h"






const Code* ecitygml_OccupantTypeValue_code(const OccupantTypeValue* self);

DiplomatStringView ecitygml_OccupantTypeValue_value(const OccupantTypeValue* self);

void ecitygml_OccupantTypeValue_destroy(OccupantTypeValue* self);





#endif // OccupantTypeValue_H
