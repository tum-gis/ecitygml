#ifndef PlantCoverFunctionValue_H
#define PlantCoverFunctionValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "PlantCoverFunctionValue.d.h"






const Code* ecitygml_PlantCoverFunctionValue_code(const PlantCoverFunctionValue* self);

DiplomatStringView ecitygml_PlantCoverFunctionValue_value(const PlantCoverFunctionValue* self);

void ecitygml_PlantCoverFunctionValue_destroy(PlantCoverFunctionValue* self);





#endif // PlantCoverFunctionValue_H
