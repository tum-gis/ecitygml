#ifndef BuildingSubdivisionFunctionValue_H
#define BuildingSubdivisionFunctionValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "BuildingSubdivisionFunctionValue.d.h"






const Code* ecitygml_BuildingSubdivisionFunctionValue_code(const BuildingSubdivisionFunctionValue* self);

DiplomatStringView ecitygml_BuildingSubdivisionFunctionValue_value(const BuildingSubdivisionFunctionValue* self);

void ecitygml_BuildingSubdivisionFunctionValue_destroy(BuildingSubdivisionFunctionValue* self);





#endif // BuildingSubdivisionFunctionValue_H
