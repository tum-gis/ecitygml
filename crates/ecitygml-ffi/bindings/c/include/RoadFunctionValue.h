#ifndef RoadFunctionValue_H
#define RoadFunctionValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "RoadFunctionValue.d.h"






const Code* ecitygml_RoadFunctionValue_code(const RoadFunctionValue* self);

DiplomatStringView ecitygml_RoadFunctionValue_value(const RoadFunctionValue* self);

void ecitygml_RoadFunctionValue_destroy(RoadFunctionValue* self);





#endif // RoadFunctionValue_H
