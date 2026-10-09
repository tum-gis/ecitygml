#ifndef TrafficSpaceClassValue_H
#define TrafficSpaceClassValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "TrafficSpaceClassValue.d.h"






const Code* ecitygml_TrafficSpaceClassValue_code(const TrafficSpaceClassValue* self);

DiplomatStringView ecitygml_TrafficSpaceClassValue_value(const TrafficSpaceClassValue* self);

void ecitygml_TrafficSpaceClassValue_destroy(TrafficSpaceClassValue* self);





#endif // TrafficSpaceClassValue_H
