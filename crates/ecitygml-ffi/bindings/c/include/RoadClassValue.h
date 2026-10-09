#ifndef RoadClassValue_H
#define RoadClassValue_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"

#include "Code.d.h"

#include "RoadClassValue.d.h"






const Code* ecitygml_RoadClassValue_code(const RoadClassValue* self);

DiplomatStringView ecitygml_RoadClassValue_value(const RoadClassValue* self);

void ecitygml_RoadClassValue_destroy(RoadClassValue* self);





#endif // RoadClassValue_H
