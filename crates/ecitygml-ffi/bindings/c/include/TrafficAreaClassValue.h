#ifndef TrafficAreaClassValue_H
#define TrafficAreaClassValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "TrafficAreaClassValue.d.h"






const Code* ecitygml_TrafficAreaClassValue_code(const TrafficAreaClassValue* self);

DiplomatStringView ecitygml_TrafficAreaClassValue_value(const TrafficAreaClassValue* self);

void ecitygml_TrafficAreaClassValue_destroy(TrafficAreaClassValue* self);





#endif // TrafficAreaClassValue_H
