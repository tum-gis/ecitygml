#ifndef TrafficSpaceFunctionValue_H
#define TrafficSpaceFunctionValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "TrafficSpaceFunctionValue.d.h"






const Code* ecitygml_TrafficSpaceFunctionValue_code(const TrafficSpaceFunctionValue* self);

DiplomatStringView ecitygml_TrafficSpaceFunctionValue_value(const TrafficSpaceFunctionValue* self);

void ecitygml_TrafficSpaceFunctionValue_destroy(TrafficSpaceFunctionValue* self);





#endif // TrafficSpaceFunctionValue_H
