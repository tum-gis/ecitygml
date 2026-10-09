#ifndef BuildingFunctionValue_H
#define BuildingFunctionValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "BuildingFunctionValue.d.h"






const Code* ecitygml_BuildingFunctionValue_code(const BuildingFunctionValue* self);

DiplomatStringView ecitygml_BuildingFunctionValue_value(const BuildingFunctionValue* self);

void ecitygml_BuildingFunctionValue_destroy(BuildingFunctionValue* self);





#endif // BuildingFunctionValue_H
