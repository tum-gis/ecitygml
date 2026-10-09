#ifndef CityFurnitureFunctionValue_H
#define CityFurnitureFunctionValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "CityFurnitureFunctionValue.d.h"






const Code* ecitygml_CityFurnitureFunctionValue_code(const CityFurnitureFunctionValue* self);

DiplomatStringView ecitygml_CityFurnitureFunctionValue_value(const CityFurnitureFunctionValue* self);

void ecitygml_CityFurnitureFunctionValue_destroy(CityFurnitureFunctionValue* self);





#endif // CityFurnitureFunctionValue_H
