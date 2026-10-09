#ifndef BuildingClassValue_H
#define BuildingClassValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "BuildingClassValue.d.h"






const Code* ecitygml_BuildingClassValue_code(const BuildingClassValue* self);

DiplomatStringView ecitygml_BuildingClassValue_value(const BuildingClassValue* self);

void ecitygml_BuildingClassValue_destroy(BuildingClassValue* self);





#endif // BuildingClassValue_H
