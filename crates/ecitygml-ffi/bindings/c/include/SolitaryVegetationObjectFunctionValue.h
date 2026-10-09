#ifndef SolitaryVegetationObjectFunctionValue_H
#define SolitaryVegetationObjectFunctionValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "SolitaryVegetationObjectFunctionValue.d.h"






const Code* ecitygml_SolitaryVegetationObjectFunctionValue_code(const SolitaryVegetationObjectFunctionValue* self);

DiplomatStringView ecitygml_SolitaryVegetationObjectFunctionValue_value(const SolitaryVegetationObjectFunctionValue* self);

void ecitygml_SolitaryVegetationObjectFunctionValue_destroy(SolitaryVegetationObjectFunctionValue* self);





#endif // SolitaryVegetationObjectFunctionValue_H
