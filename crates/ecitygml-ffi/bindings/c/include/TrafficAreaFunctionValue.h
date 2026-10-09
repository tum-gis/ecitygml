#ifndef TrafficAreaFunctionValue_H
#define TrafficAreaFunctionValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "TrafficAreaFunctionValue.d.h"






const Code* ecitygml_TrafficAreaFunctionValue_code(const TrafficAreaFunctionValue* self);

DiplomatStringView ecitygml_TrafficAreaFunctionValue_value(const TrafficAreaFunctionValue* self);

void ecitygml_TrafficAreaFunctionValue_destroy(TrafficAreaFunctionValue* self);





#endif // TrafficAreaFunctionValue_H
