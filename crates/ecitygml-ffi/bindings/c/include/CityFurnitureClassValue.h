#ifndef CityFurnitureClassValue_H
#define CityFurnitureClassValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "CityFurnitureClassValue.d.h"






const Code* ecitygml_CityFurnitureClassValue_code(const CityFurnitureClassValue* self);

DiplomatStringView ecitygml_CityFurnitureClassValue_value(const CityFurnitureClassValue* self);

void ecitygml_CityFurnitureClassValue_destroy(CityFurnitureClassValue* self);





#endif // CityFurnitureClassValue_H
